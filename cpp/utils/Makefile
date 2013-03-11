object=main.o string.o file.o
main:$(object)
	g++ -o main $(object)
main.o:main.cpp
string.o:string.cpp utils.h
file.o:file.cpp utils.h

.PHONY:clean
clean:
	-rm -rf main $(object)
