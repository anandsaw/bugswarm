import os
import subprocess
import time

import docker
import docker.errors
import requests
import ast

from bugswarm.common import log
from bugswarm.common.shell_wrapper import ShellWrapper
from bugswarm.common import utils as bugswarmutils
from bugswarm.common.credentials import DOCKER_HUB_PASSWORD, DOCKER_HUB_REPO, DOCKER_HUB_USERNAME, \
    DOCKER_REGISTRY_PASSWORD, DOCKER_REGISTRY_REPO, DOCKER_REGISTRY_USERNAME

class DockerWrapper(object):
    def __init__(self):
        self.client = docker.from_env()
        # self.client = docker.DockerClient(base_url='unix://var/run/docker.sock')
        # self.low_level_client = docker.APIClient(base_url='unix://var/run/docker.sock')
        # self.swarm = docker.DockerClient(base_url='tcp://localhost:2375')
        self.swarm = docker.DockerClient(base_url='tcp://172.16.0.5:2375')
        # self.swarm = docker.from_env()
        # docker.DockerClient(base_url='10.0.0.4:22')
        self.utils = bugswarmutils
        self.docker_hub_auth_config = {
            'username': DOCKER_HUB_USERNAME,
            'password': DOCKER_HUB_PASSWORD,
        }

    def build_and_run(self, job_id, gen_files_dir, repo_path, repo_name):
        log.info('Building and running job with ID {}.'.format(job_id))
        dockerfile_path = os.path.join(gen_files_dir, job_id + "-dockerfile")
        # Determine the image name.
        image_name = '{}'.format(job_id + "-" + repo_name)

        # Actually build the image now.
        image = self.build_image(path=gen_files_dir, dockerfile=dockerfile_path, full_image_name=image_name)

        # Spawn the container.
        container_name = job_id
        retry_count = 0
        while True:
            try:
                reproduced_log_destination = os.path.join(gen_files_dir, "docker-log.txt")
                self.spawn_container(image, container_name, reproduced_log_destination, repo_path)
            except requests.exceptions.ReadTimeout as e:
                log.error('Error while attempting to spawn a container:', e)
                log.info('Retrying to spawn container.')
                retry_count += 1
            else:
                break

        # Post job reproducing tasks: Removing image to save space
        # 1st way: self.client.images.remove(image=image_name, force=True)
        # 2nd way: self.client.containers.prune()
        # 3rd way: filters = {'dangling': True}
        # self.client.images.prune(filters)

    def build_image(self, path, dockerfile, full_image_name):
        image = None
        try:
            image = self.client.images.build(path=path, dockerfile=dockerfile, tag=full_image_name)
        except docker.errors.BuildError as e:
            log.debug(e)
            raise ValueError('Encountered a build error while building a Docker image: {}'.format(e))
        except docker.errors.APIError as e:
            raise ValueError('Encountered a Docker API error while building a Docker image: {}'.format(e))
        except KeyboardInterrupt:
            log.error('Caught a KeyboardInterrupt while building a Docker image.')
        return image

    def push_image(self, image_tag):
        # Push to Docker Hub
        try:
            result = self.client.images.push(DOCKER_HUB_REPO,
                                             tag=image_tag,
                                             stream=False,
                                             auth_config=self.docker_hub_auth_config)
            result = result.splitlines()
            result = result[-1]
            dictionary = ast.literal_eval(result)
            if "error" in dictionary.keys():
                log.error('Error: ', dictionary.get('error'))
            elif "status" in dictionary.keys():
                log.info('Status: ', dictionary.get('status'))

        except docker.errors.APIError:
            raise ValueError('Encountered a Docker API error while pushing a Docker image to Docker Hub.')
        except KeyboardInterrupt:
            log.error('Caught a KeyboardInterrupt while pushing a Docker image to Docker Hub.')
        # Push to Registry
        if not DOCKER_REGISTRY_REPO:
            log.warning('Docker Private Registry info not being set. Skipping.')
            return
        try:
            result = self.client.images.push(DOCKER_HUB_REPO,
                                             tag=image_tag,
                                             stream=False,
                                             auth_config=self.docker_registry_auth_config)
            result = result.splitlines()
            result = result[-1]
            dictionary = ast.literal_eval(result)
            if "error" in dictionary.keys():
                log.error('Error: ', dictionary.get('error'))
            elif "status" in dictionary.keys():
                log.info('Status: ', dictionary.get('status'))

        except docker.errors.APIError:
            raise ValueError('Encountered a Docker API error while pushing a Docker image to Docker Registry.')
        except KeyboardInterrupt:
            log.error('Caught a KeyboardInterrupt while pushing a Docker image to Docker Registry.')

    def spawn_container(self, image, container_name, reproduced_log_destination, repo_path):
        container_runtime = 0
        try:
            container = self.client.containers.run(image, detach=True, cpu_count=2, mem_limit='4g',
                                                   tty=True, user="travis", volumes={repo_path: {'bind': '/home/travis/build', 'mode': 'rw'}})  # privileged=True
        except docker.errors.ImageNotFound:
            log.error('Docker image not found.')
            return 1
        except docker.errors.APIError:
            log.error('Encountered a Docker API error while spawning a container.')
            raise

        to_kill = False
        while container.status != 'exited':
            container.reload()
            container_runtime += 5
            if container_runtime > 1800:
                to_kill = True
                break
            time.sleep(5)

        logs = container.logs()
        if to_kill:
            log.error('Timed out after 30 minutes. Killing the container.')
            container.kill()

        with open(reproduced_log_destination, 'wb') as f:
            f.write(logs)

        container.remove(force=True)

    def remove_image(self, image_name):
        self.client.images.remove(image=image_name, force=True, noprune=True)
        filters = {'dangling': True}
        self.client.images.prune(filters)

    def setup_docker_storage_path(self):
        try:
            docker_dict = self.client.info()
            docker_root_dir = docker_dict['DockerRootDir']
            storage_driver = docker_dict['Driver']
            path = os.path.join(docker_root_dir, storage_driver)
            return path
        except docker.errors.APIError:
            log.error('Encountered a Docker API error while gathering the Docker environment info.')
            raise

    @staticmethod
    def remove_image_in_shell(full_image_name):
        log.info('Removing a Docker image.')
        command = 'docker rmi -f {}'.format(full_image_name)
        _, _, returncode = ShellWrapper.run_commands(command, shell=True)
        return returncode

    @staticmethod
    def remove_all_images():
        log.info('Removing all containers and Docker images (except Travis images).')
        command = 'docker rm $(docker ps -a -q); docker rmi -f $(docker images -a | grep -v "travis")'
        ShellWrapper.run_commands(command, stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL, shell=True)
