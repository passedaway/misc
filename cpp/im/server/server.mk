all= s.o\
	serversocket.o\
	sclientsocket.o\
	clientsocket.o\
	clientlist.o\
	friendlist.o\
	unsendmessage.o\
	message.o\
	userinfo.o\
	multithread.o\
	thread.o\
	file.o

$(all):s.cpp\
	serversocket.cpp\
	clientlist.cpp\
	sclientsocket.cpp\
	clientsocket.cpp\
	message.c\
	unsendmessage.c\
	userinfo.c\
	friendlist.c\
	multithread.cpp\
	thread.cpp\
	file.cpp
	g++	s.cpp -c -o s.o
	g++	serversocket.cpp -c -o serversocket.o
	g++	clientlist.cpp -c -o clientlist.o
	g++	sclientsocket.cpp -c -o sclientsocket.o
	g++	clientsockt.cpp -c -o clientsockt.o
	g++	multithread.cpp -c -o multithread.o
	g++	thread.cpp -c -o thread.o
	g++	message.c -c -o message.o
	g++ unsendmessage.c -c -o unsendmessage.o
	g++	userinfo.c -c -o userinfo.o
	g++	friendlist.c -c -o friendlist.o
	g++	file.cpp -c -o file.o