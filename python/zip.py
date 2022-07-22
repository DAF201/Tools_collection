import zipfile
from os.path import basename
with zipfile.ZipFile('path of zip', 'w')as zip:
    zip.write('path of the file to be zipped',basename('path of the file to be zippped'))
    # will not zip the dir
with zipfile.ZipFile('path of zip', 'r')as zip:
    zip.extractall('path to be extraced')
    # unzip all files to the path
