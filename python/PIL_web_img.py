from PIL import Image
import requests
from io import BytesIO

response = requests.get(
    'http://i0.hdslb.com/bfs/album/45dd52f26370c928602f709a0ff970963519db6e.jpg')
img = Image.open(BytesIO(response.content))
img.show()
