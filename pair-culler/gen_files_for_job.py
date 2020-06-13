import os
from os.path import isfile

# from bugswarm.common.log_downloader import download_log
# from setup_repo import setup_repo
# from setup_repo import tar_repo
from modify_build_sh import modify_build_sh
# from modify_build_sh import patch_build_script
from gen_dockerfile import gen_dockerfile
from gen_script import gen_script
# from apply_patching import modify_deprecated_links
from reproducer_utils import Utils


def gen_files_for_job(job, repo_path, gen_files_path, short_repo):
    """
    This function generates the files needed to reproduce a job.
    It begins running the steps to reproduce a job. The steps are explained in the comments.
    The steps are mainly calling functions written in the `pipeline` folder.
    Steps:
      Pre-job step: check for skipping
      1. Setup workspace repository: copy, reset, and tar the repository
      2. Ensure .travis.yml exists. Otherwise, skip the job
      3. Download the original log.
      4. Generate the build script with travis-build.
      5. Generate the Dockerfile.
      6. Build the Docker image.
      7. Spawn the Docker container.
      Post-job step: copying files

    :param job_dispatcher:
    :param job:
    """

    # If all three essential items to build a job are in the task folder, copy them to the workspace folder and return.

    # STEP 2: Download the original log if we do not yet have it.
    build_sh_path = os.path.join(gen_files_path, str(job['id']) + '.sh')
    # STEP 3: Generate the build script with travis-build and then modify and patch it.

    gen_script(build_sh_path, job['number'], repo_path)
    # modify_build_sh("radcli", build_sh_path)

    # # STEP 4: Generate the Dockerfile.
    dockerfile_path = os.path.join(gen_files_path, str(job['id']) + "-dockerfile")
    gen_dockerfile(job['heuristic_image'], str(job['id']), dockerfile_path)

