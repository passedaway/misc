object=main.o thread.o multithread.o
main:$(object)
	g++ $(object) -o main -lpthread
main.o:main.cpp
	g++ -c main.cpp -o main.o
thread.o:thread.cpp thread.h
	g++ -c thread.cpp -o thread.o
multithread.o:multithread.cpp multithread.h
	g++ -c multithread.cpp -o multithread.o
.PHONY:clean
clean:
	-rm -rf $(object) main
