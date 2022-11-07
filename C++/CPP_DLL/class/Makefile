test.exe: cpp_dll
	g++ test.cpp cpp_dll.dll
cpp_dll:temp_obj
	g++ -shared -o cpp_dll.dll temp_obj.obj
temp_obj:
	g++ -o temp_obj.obj dll.cpp
clean:
	rm *.obj