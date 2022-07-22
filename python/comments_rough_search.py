#search bilibili comments of an account via name
from googlesearch import search; import time, json
print("enter a username to continue")
user_input = input(); data = []
with open('contains.json', "w") as contains:
    for url in search('"site:www.bilibili.com" %s' % user_input, stop=20):
        if "video" in url:
            url = "BV"+url.split("BV")[1]
        if "read" in url:
            url = "cv"+url.split("cv")[1]
        if url[-1] == "/":
            url = url.replace("/", "")
        data.append(url)
        time.sleep(0.1)
        print(url)
    json.dump(data, contains)
