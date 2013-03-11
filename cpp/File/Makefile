main:main.o file.o
	g++ -g main.o file.o -o main
main.o:main.cpp
	g++ -g -c main.cpp
file.o:file.cpp file.h
	g++ -g -c file.cpp

.PHONYL:clean
clean:
	-rm -rf *.o main
