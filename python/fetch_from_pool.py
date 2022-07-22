#fetch sender info
import request
cid: str
character: str
av: str
p: str
url = ('https://fybgame.top:8000/web-1.0.0/bilibili/search?cid=%s&match=%s&av=%s&p=%s',
       (cid, character, av, p))
re=requestes.post(url).text
print(re)
