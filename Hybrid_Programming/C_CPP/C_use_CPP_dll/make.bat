g++ -c -o temp.o dll.cpp
g++ -o dll.dll -shared temp.o
g++ -c -o cpp_to_c.o cpp_to_c.cpp
gcc -c -o temp_main.o main.c
gcc -o main temp_main.o cpp_to_c.o dll.dll -lstdc++ 
powershell rm *.o