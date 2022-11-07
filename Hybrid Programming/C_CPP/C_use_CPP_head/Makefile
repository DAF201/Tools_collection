mixed: main.o head.o
	gcc -o mixed main.o head.o -lstdc++ 
main.o: main.c
	gcc -c main.c -o main.o
head.o:
	g++ -c cpp_to_c.cpp -o head.o
clean:
	rm -rf ./*.o
	rm -rf ./*.exe