import os
import re

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
    if not os.path.exists(file_path):
        return None
    project_name = project_meta_path.replace("/home/anandsaw/bugswarm/pair-culler/files/", "")
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


def process_make_file(project_name):
    project_path = find_project_path(project_name)
    if project_path == "":
        return ""
    makefiles = []
    for root,dirs,files in os.walk(project_path):
        for file in files:
            if "make" in file.lower():
                makefiles.append(os.path.join(root, file))
    optmization_operators = process_make_files(makefiles)
    if len(optmization_operators) > 0:
        return select_highest_opt_level(optmization_operators)
    return""


def select_highest_opt_level(optmization_operators):
    order = ["-O0", "-O", "-O1", "-O2", "-O3", "-O4", "-O5", "-Os", "-Ofast"]
    highest = 0
    for opt in optmization_operators:
        index = order.index(opt)
        if index > highest:
            highest = index
    return order[highest]


def process_make_files(makefiles):
    optmization = []
    for makefile in makefiles:
        with open(makefile, 'r', errors='ignore') as f:
            lines = f.readlines()
            for line in lines:
                if not line.startswith("#"):
                    s = re.findall(r"-O[0-9|fast|s|g]", line)
                    for opt in s:
                        optmization.append(opt)
    return optmization


def find_project_path(project_name):
    if os.path.exists(os.path.join("/hdd8/decom_travis/Repos1_bionic/", project_name)):
        return os.path.join("/hdd8/decom_travis/Repos1_bionic/", project_name)
    if os.path.exists(os.path.join("/hdd8/decom_travis/Repos1_xenial/", project_name)):
        return os.path.join("/hdd8/decom_travis/Repos1_xenial/", project_name)
    if os.path.exists(os.path.join("/hdd8/decom_travis/Repos1_trusty/", project_name)):
        return os.path.join("/hdd8/decom_travis/Repos1_trusty/", project_name)
    if os.path.exists(os.path.join("/hdd8/decom_travis/Repos1_others/", project_name)):
        return os.path.join("/hdd8/decom_travis/Repos1_others/", project_name)
    return ""


def main():
    project_base_meta_path = "/home/anandsaw/bugswarm/pair-culler/files/"
    projects = []
    for root,dirs,files in os.walk(project_base_meta_path):
        for dir in dirs:
            projects.append(os.path.join(root, dir))
    print("Found %d projects" % len(projects))
    with open("parsed_versions.csv", 'w') as f:
        f.write("project_name,project_path,os_used,dist,gcc_version,gpp_version,clang_version,optimization_level,build_language\n")
        count = 0
        for project in projects:
            config = parse_meta_file(project)
            if config is not None:
                if getattr(config, "optimization_level") is "":
                    process_make_file(getattr(config, "project_name"))
                f.write(str(config) + "\n")
            print("Done with %d" % count)
            count += 1


if __name__ == "__main__":
    main()