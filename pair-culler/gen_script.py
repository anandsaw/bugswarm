import os
import subprocess

from bugswarm.common.shell_wrapper import ShellWrapper

def gen_script(build_sh_path, job_number, reproducing_dir):
    """
    Invoke travis-build to generate the build script.
    """
    travis_command = '/home/anandsaw/.travis/travis-build/bin/travis compile {} > {}'.format(job_number, build_sh_path)
    print("Creating travis build script with command: " + travis_command)
    cd_command = 'cd {}'.format(reproducing_dir)
    _, stderr, returncode = ShellWrapper.run_commands(cd_command, travis_command,
                                                      stdout=subprocess.PIPE, stderr=subprocess.PIPE, shell=True)
    if returncode != 0:
        raise ValueError(
            'Encountered an error while generating the build script with travis-build: {}.'.format(stderr))
