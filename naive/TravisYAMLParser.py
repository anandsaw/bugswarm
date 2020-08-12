import yaml


def parse_yml(file_path):
    with open("sample_travis_distcc.yml", 'r') as stream:
        try:
            print(yaml.safe_load(stream))
        except yaml.YAMLError as exc:
            print(exc)