import os

class ProjectConfig(object):
    def __init__(self, project_name, project_path, os_used="", dist="", gcc_version="", gpp_version="", clang_version="", optimization_level="", build_language=""):
        self.project_name = project_name
        self.project_path = project_path
        self.os_used = os_used
        self.dist = dist
        self.gcc_version = gcc_version
        self.gpp_version = gpp_version
        self.clang_version = clang_version
        self.optimization_level = optimization_level
        self.build_language = build_language

    def __str__(self):
        return self.project_name + "," + self.project_path + "," \
               + self.os_used + "," + self.dist + "," + self.gcc_version \
               + "," + self.gpp_version + "," + self.clang_version + "," \
               + self.optimization_level + "," + self.build_language


def parse_meta_file(project_meta_path):
    print("Processing: " + project_meta_path)
    file_path = os.path.join(project_meta_path, "docker-log.txt")
    project_name = project_meta_path.replace("/home/anandsaw/bugswarm/pair_culler/files/", "")
    with open(file_path, 'r') as f:
        lines = f.readlines()
        lang = ""
        dist = ""
        os_used = ""
        gcc_version = ""
        gpp_version = ""
        clang_version = ""
        optimization_level = ""
        for index, line in enumerate(lines):
            # print(line)
            if line.startswith("Build language:"):
                split = line.split(" ")
                lang = split[2].strip()

            if line.startswith("Build dist:"):
                split = line.split(" ")
                dist = split[2].strip()

            if "Operating System Details" in line:
                os_used = lines[index + 2].replace("Description:", "").strip()

            if "gcc version" in line:
                gcc_version = lines[index+1].strip()

            if "g++ --version" in line:
                gpp_version = lines[index + 1].strip()

            if line.startswith("clang version"):
                clang_version = line.strip()

            if line.startswith("gcc") or line.startswith("g++"):
                split = line.split(" ")
                for token in split:
                    if token.startswith("-O"):
                        optimization_level = token

        return ProjectConfig(project_name, file_path, os_used, dist, gcc_version, gpp_version, clang_version, optimization_level, lang)


def main():
    project_base_meta_path = "/home/anandsaw/bugswarm/pair_culler/files/"
    projects = []
    for root,dirs,files in os.walk(project_base_meta_path):
        for dir in dirs:
            projects.append(os.path.join(root, dir))
    with open("parsed_versions.csv", 'w') as f:
        f.write("project_name,project_path,os_used,dist,gcc_version,gpp_version,clang_version,optimization_level,build_language")
        for project in projects:
            config = parse_meta_file(project)
            f.write(str(config))


if __name__ == "__main__":
    main()