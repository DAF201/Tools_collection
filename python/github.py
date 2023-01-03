from github import Github
from requests import get

user=Github(login_or_token="SOME TOKEN").get_user()
repo=user.get_repo("SOME REPO")

#upload/create file
res = github_repo.create_file("file path", "message", binarty_raw_data, "Branch name")

#download
down_load_url = github_repo.get_contents(file_name).raw_data['download_url']
raw_data = get(url=down_load_url).content
