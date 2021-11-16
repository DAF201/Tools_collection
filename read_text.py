import playsound
import requests
text: str
text = ''  # utf-8
url = 'https://api.oick.cn/txt/apiz.php?text=%s&spd=1' % (text)
a = requests.get(url).content
with open('example.mp3', 'wb')as file:
    file.write(a)
playsound.playsound('example.mp3', True)
