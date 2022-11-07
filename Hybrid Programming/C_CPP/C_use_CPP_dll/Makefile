temp.o:
	g++ -c -o temp.o dll.cpp
dll.dll:temp.o
	g++ -o dll.dll -shared temp.o
cpp_to_c.o:
	g++ -c -o cpp_to_c.o cpp_to_c.cpp
temp_main.o:
	gcc -c -o temp_main.o main.c
main.exe: temp_main.o
	gcc -o main temp_main.o cpp_to_c.o dll.dll -lstdc++
clean:
	rm *.o