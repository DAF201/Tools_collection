from os import chdir
from glob import glob
from ctypes import cdll
cmd = cdll.LoadLibrary("./dlls/cmd.dll")
chdir("./src/cpp")
for file in glob("*.cpp"):
    name = file.replace(".cpp", "")
    cmd.cmd(b"g++ -shared -o ../../dlls/%b.dll %b" %
            (name.encode(), file.encode()))
