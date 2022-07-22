import time
import os


def fileTime(file):
    return [time.ctime(os.path.getatime(file)),
            time.ctime(os.path.getctime(file)),
            time.ctime(os.path.getmtime(file))]
times = fileTime("C:\\Users\\16418\\Desktop\\something\\something.py")
#times = fileTime("ccc")
print(times)
