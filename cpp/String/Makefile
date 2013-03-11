main:main.o mystring.o test.o
	g++ main.o mystring.o test.o -o main
main.o:main.cpp
	g++ -c main.cpp -o main.o
mystring.o:mystring.cpp mystring.h
	g++ -c mystring.cpp -o mystring.o
test.o:test.cpp test.h
	g++ -c test.cpp -o test.o
.PHONY:clean
clean:
	rm -rf *.o main
