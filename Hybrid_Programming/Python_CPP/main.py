from ctypes import *

dll = CDLL(r".\Hybrid_Programming\Python_CPP\PY_DLL\x64\Debug\PYDLL.dll")
print(dll.sum(1, 2))
