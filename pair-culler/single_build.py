import json
from bugswarm.common import log
from bugswarm.common.log_downloader import download_log
from bugswarm.common.json import read_json
import sys
import os
from constants import TRAVIS_IMAGES_JSON
from constants import DOCKERHUB_IMAGES_JSON
from image_chooser import ExactImageChooserByTime
from image_chooser import ExactImageChooserByTag
from image_chooser import ExactImageChooserByCommitSHA
from get_jobs_from_travis_api import GetJobsFromTravisAPI
from gen_files_for_job import gen_files_for_job
from build import Build
from docker_wrapper import DockerWrapper

BASE_DIR = "/home/anandsaw/bugswarm/pair-culler"

def main():
    argv = sys.argv
    repo = argv[2]
    repo_path = argv[4]
    branch = argv[6]

    #create paths and setup dirs
    gen_files_path = os.path.join(BASE_DIR, "files", repo)
    travis_api_path = os.path.join(BASE_DIR, "api-results", repo)
    log_path = os.path.join(BASE_DIR, "original-logs", repo)
    setup_dirs_for_project(gen_files_path, travis_api_path, log_path)
    print("Done setting up directories")
    get_jobs_from_travis = GetJobsFromTravisAPI()
    get_jobs_from_travis.process(repo, os.path.join(travis_api_path, "builds.json"), os.path.join(travis_api_path, "builds_info.json"))
    print("Done downloading Travis builds and build infos")
    latest_build_id = get_latest_build_id(travis_api_path, branch)
    latest_build = get_latest_build(travis_api_path, latest_build_id)
    print("Selected latest passing build: " + str(latest_build_id))
    build = get_build(latest_build_id, latest_build)
    job_list = []
    for job in build.job_list:
        image = filter_non_exact_images(job['id'], log_path)
        if image is not None:
            job['heuristic_image'] = image
            job_list.append(job)

    if len(job_list) == 0:
        print("We have no images for the jobs")
        exit(0)
    selected_job = select_job(job_list)
    print("Selected job from build: " + str(selected_job['id']) + " " + str(selected_job['number']))
    # at this point we have a build and its jobs with the image parsed
    # now we need to reproduce the job
    reproduce_job(selected_job, repo, gen_files_path, os.path.join(repo_path))
    print("Finished building with best effort.")


def setup_dirs_for_project(gen_files_path, travis_api_path, log_path):
    if not os.path.exists(gen_files_path):
        os.makedirs(gen_files_path)
        with open(os.path.join(gen_files_path, 'info.txt'), 'w') as fp:
            pass
    if not os.path.exists(travis_api_path):
        os.makedirs(travis_api_path)
    if not os.path.exists(log_path):
        os.makedirs(log_path)


def select_job(jobs):
    # for job in jobs:
    #     if job['heuristic_image'] is not None:
    #         return job
    # if we are here means we found no gcc return just the first job
    return jobs[0]


def reproduce_job(job, repo, gen_files_path, repo_path):
    """
    This is the main function to reproduce a job, which involves the following steps:
    1. Generate files for the job
    2. Build a Docker image
    3. Spawn a Docker container to reproduce the job
    4. Copy files after the job is reproduced.

    :param job: Job object
    :param repo: String repo slug
    """

    # repo_path = os.path.join("/Users/anandsaw/Documents/bugswarm/pair-culler/repos/", repo)
    repo = repo.replace("/", "-")
    print("Starting actual reproduction")
    gen_files_for_job(job, repo_path, gen_files_path, repo)
    print("Done generating files for docker container building")
    docker = DockerWrapper()
    print("Starting to build and run docker container")
    docker.build_and_run(str(job['id']), gen_files_path, repo_path, repo)
    print("Done running the container.")
    docker.push_image(str(job['id']) + "-" + repo)
    print("Done pushing image to dockerhub")


def get_build(latest_build_id, latest_build):
    build_matrix = latest_build['build_info']['matrix']
    jobs = []
    for job in build_matrix:
        jobs.append(job)
    filtered_jobs = filter_jobs(jobs)
    if len(filtered_jobs) == 0:
        exit(1)
    return Build(latest_build_id, filtered_jobs)


def filter_jobs(jobs):
    if len(jobs) == 1:
        return jobs
    else:
        filtered_jobs = []
        for job in jobs:
            if job['config']['os'] == "linux" and job['result'] == 0:
                filtered_jobs.append(job)
        return filtered_jobs


def get_latest_build_id(travis_api_path, branch):
    latest_build_id = None
    with open(os.path.join(travis_api_path, "builds.json")) as f:
        build_list = json.load(f)
        for build in build_list:
            latest_build_id = build['id']
            if build['state'] == "finished" and build['result'] == 0 and build['branch'] == branch:
                break
    return latest_build_id


def get_latest_build(travis_api_path, id):
    latest_build = None
    with open(os.path.join(travis_api_path, "builds_info.json")) as f:
        build_list = json.load(f)
        for build in build_list:
            latest_build = build
            if build['id'] == id:
                break
    return latest_build


def filter_non_exact_images(job_id, log_path):
    """
    Check if all jobs in this pair (from both the failed and passed build) used images that are available.

    If an image is found to match the job pair then it gets added to the job pair.

    This function assumes the language specified in the Travis configuration does not change between the failed and
    passed builds.

    Returns a 4-tuple of filter counts. The tuple members represent the following:
    1. The number of pairs filtered due to original log not found
    2. The number of pairs filtered due to an error reading the original log
    3. The number of pairs filtered due to no image provision timestamp in the original log
    4. The number of pairs filtered due to usage of a non-exact Docker image.
    """
    log.debug('To detect non-exact pairs, we first extract the used images from the original logs.')
    travis_images = read_json(os.path.join(BASE_DIR, "travis_images.json"))
    provisioned_strs = []
    for language in travis_images:
        provisioned_strs += travis_images[language].values()
    dockerhub_images = read_json(os.path.join(BASE_DIR, "dockerhub_images.json"))
    no_original_log = 0
    error_reading_original_log = 0
    orig_log_path = os.path.join(log_path, str(job_id) + ".txt")
    if not download_log(job_id, orig_log_path):
        no_original_log += 1

    # Try to find the image by timestamp. If found, add it to the job pair.
    try:
        chooser = ExactImageChooserByTime(orig_log_path, travis_images, language)
        orig_log_image_provision_timestamp = chooser.find_image_datetime_from_log()
        image = chooser.get_image_tag()
        if image is not None:
            return image
    except OSError:
        # The original log file was not found.
        error_reading_original_log += 1

    # Try to find image by tag. If found, add it to the job pair.
    if not image:
        chooser = ExactImageChooserByTag(orig_log_path)
        image = chooser.get_image_tag()
        if image is not None:
            return image
    # Try to find image by GCE commit SHA. If found, add it to the job pair.
    if not image:
        chooser = ExactImageChooserByCommitSHA(orig_log_path, dockerhub_images)
        image = chooser.get_image_tag()
        if image is not None:
            return image


if __name__ == '__main__':
    main()
