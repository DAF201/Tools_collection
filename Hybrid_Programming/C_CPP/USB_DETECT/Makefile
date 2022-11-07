main:c_main.o head.o
	gcc -o main c_main.o head.o -lstdc++ 
	make clean
c_main.o: main.c
	gcc -c main.c -o c_main.o

head.o:
	g++ -c usb_drive_for_c.cpp -o head.o

clean:
	rm -rf ./*.o
	rm -rf ./*.out
