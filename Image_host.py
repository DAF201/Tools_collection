import requests
URL = 'https://api.bilibili.com/x/dynamic/feed/draw/upload_bfs'
send_headers = {
    "User-Agent": "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/61.0.3163.100 Safari/537.36",
    "Connection": "keep-alive",
    "Accept": "text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,image/apng,*/*;q=0.8",
    "Accept-Language": "zh-CN,zh;q=0.8"}

param = {
    'csrf': '746f3ef49f165606acfa964d2e2888f5'#b_jet
}
cookie = {
    'SESSDATA': '6af072ae%2C1655664419%2C2cca8%2Ac1'
}
re = requests.post(url=URL, headers=send_headers,
                   params=param, cookies=cookie, files={'file_up': open(r'C:\Users\16418\Desktop\something\something.jpg', 'rb'), 'category': 'daily'}).text
print(re)
# {"code":0,"message":"0","ttl":1,"data":{"image_url":"http://i0.hdslb.com/bfs/album/45dd52f26370c928602f709a0ff970963519db6e.jpg","image_width":1280,"image_height":720}}
