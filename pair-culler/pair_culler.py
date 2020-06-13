import json
import sys
import os

def main():
    argv = sys.argv
    pair_finder_path = argv[2]
    repo = argv[4]
    repo = repo.replace("/", "-")
    branch = argv[6]

    latest_id = 0
    with open(os.path.join(pair_finder_path, "intermediates/api-results", repo + "_builds.json")) as f:
        build_list = json.load(f)

        for build in build_list:
            latest_id = build['id']
            if build['state'] == "finished" and build['result'] == 0 and build['branch'] == "master":
                break
    # at this point we have the latest ID:
    if latest_id == 0:
        exit(1)
    print(latest_id)
    final_job_pair = None
    with open(os.path.join(pair_finder_path, "output", repo, repo + ".json"), "r") as f:
        job_pair_list = json.load(f)

        for job_pair in job_pair_list:
            if job_pair['passed_build']['build_id'] == latest_id:
                final_job_pair = job_pair
                break

    print(final_job_pair)
    if len(final_job_pair['jobpairs']) == 0:
        final_job_pair['jobpairs'] = [{"failed_job": {"job_id": final_job_pair['failed_build']['build_id']},"passed_job": {"job_id": latest_id},"build_system": "NA"}]

    with open(os.path.join(pair_finder_path, "output", repo, repo + ".json"), "w") as outfile:
        json.dump([final_job_pair], outfile)




if __name__ == '__main__':
    main()