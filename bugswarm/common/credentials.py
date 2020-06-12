import sys

# DockerHub
DOCKER_HUB_REPO = 'annadsaw/cbuilds'
DOCKER_HUB_USERNAME = 'annadsaw'
DOCKER_HUB_PASSWORD = '@KA03p5209'
if not DOCKER_HUB_REPO:
    print('[ERROR]: DOCKER_HUB_REPO has not been found. Please input your credentials under '
          'common/credentials.py and rerun the bugswarm/provision.sh script.')
if not DOCKER_HUB_USERNAME:
    print('[ERROR]: DOCKER_HUB_USERNAME has not been found. Please input your credentials under '
          'common/credentials.py and rerun the bugswarm/provision.sh script.')
if not DOCKER_HUB_PASSWORD:
    print('[ERROR]: DOCKER_HUB_PASSWORD has not been found. Please input your credentials under '
          'common/credentials.py and rerun the bugswarm/provision.sh script.')

# Docker Private Registry
DOCKER_REGISTRY_REPO = ''
DOCKER_REGISTRY_USERNAME = ''
DOCKER_REGISTRY_PASSWORD = ''
if not DOCKER_REGISTRY_REPO:
    print('[WARNING]: DOCKER_REGISTRY_REPO has not been found. Skip pushing to docker private registry '
          'in reproducing stage')
if not DOCKER_REGISTRY_USERNAME:
    print('[WARNING]: DOCKER_REGISTRY_USERNAME has not been found. Skip pushing to docker private registry '
          'in reproducing stage')
if not DOCKER_REGISTRY_PASSWORD:
    print('[WARNING]: DOCKER_REGISTRY_PASSWORD has not been found. Skip pushing to docker private registry '
          'in reproducing stage')

# GitHub
# These GitHub tokens are hard-coded and can be used for token switching to minimize the time spent waiting for our
# GitHub quota to reset.
GITHUB_TOKENS = ["c7c79b12967ab0f52884197adc0b7cef360accbc"]
if not GITHUB_TOKENS:
    print('[ERROR]: GITHUB_TOKENS has not been set. Please input your credentials under common/credentials.py and '
          'rerun the bugswarm/provision.sh script.')
    sys.exit(1)

# Authentication tokens for the database.
DATABASE_PIPELINE_TOKEN = 'testDBPassword'
if not DATABASE_PIPELINE_TOKEN:
    print('[ERROR]: DATABASE_PIPELINE_TOKEN has not been found. Please input your credentials under '
          'common/credentials.py and rerun the bugswarm/provision.sh script.')
    sys.exit(1)

COMMON_HOSTNAME = '127.0.0.1:5000'
