"""
Download metadata via the Travis API for all jobs for a repository.
"""

import os
import time

from typing import Any
from typing import Optional
from typing import Tuple
from requests.exceptions import RequestException

from bugswarm.common import log
from bugswarm.common.json import read_json
from bugswarm.common.json import write_json
from bugswarm.common.travis_wrapper import TravisWrapper

from utils_2 import Utils


class GetJobsFromTravisAPI():
    def process(self, repo, builds_json_file, builds_info_json_file) -> Optional[Any]:
        # repo = context['repo']
        travis = TravisWrapper()
        if os.path.isfile(builds_json_file):
            build_list = read_json(builds_json_file)
        else:
            log.info('Getting the list of builds...')
            start_time = time.time()
            try:
                builds = travis.get_builds_for_repo(repo)
            except RequestException:
                error_message = 'Encountered an error while downloading builds for repository {}.'.format(repo)
            build_list = list(builds)
            write_json(builds_json_file, build_list)
            log.info('Got the list of builds in', time.time() - start_time, 'seconds.')

        if os.path.isfile(builds_info_json_file):
            build_list = read_json(builds_info_json_file)
        else:
            log.info('Downloading build info for',
                     len(build_list),
                     'builds... This step may take several minutes for large repositories.')
            start_time = time.time()
            for idx, build in enumerate(build_list):
                build_id = build['id']
                try:
                    build_info = travis.get_build_info(build_id)
                except RequestException:
                    error_message = 'Encountered an error while downloading build info for build {}.'.format(build_id)
                build['build_info'] = build_info
                if (idx + 1) % 500 == 0:
                    log.info('Downloaded build info for', idx + 1, 'builds so far...')
            write_json(builds_info_json_file, build_list)
            log.info('Downloaded build info in', time.time() - start_time, 'seconds.')



    @staticmethod
    def _count_failed_builds(build_list) -> Tuple[int, int]:
        failed_builds = 0
        failed_pr_builds = 0
        for b in build_list:
            if b['build_info']['result'] == 0:
                # The build succeeded, so don't count it.
                continue
            is_pr = b['event_type'] == 'pull_request'
            if is_pr:
                failed_pr_builds += 1
            else:
                failed_builds += 1
        return failed_builds, failed_pr_builds

    @staticmethod
    def _count_failed_jobs(build_list) -> Tuple[int, int]:
        failed_jobs = 0
        failed_pr_jobs = 0
        for b in build_list:
            is_pr = b['event_type'] == 'pull_request'
            for j in b['build_info']['matrix']:
                # This condition accounts for when the Travis API returns a null job result. In those cases, assume the
                # build did not succeed.
                # A brief investigation suggests that the result is null when the job errored. See an example at
                # https://api.travis-ci.org/jobs/49217775. The corresponding Travis page with a GUI is at
                # https://travis-ci.org/gwtbootstrap3/gwtbootstrap3/jobs/49217775.
                if j.get('result') != 0:
                    if is_pr:
                        failed_pr_jobs += 1
                    else:
                        failed_jobs += 1
        return failed_jobs, failed_pr_jobs
