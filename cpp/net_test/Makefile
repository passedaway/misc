all=s c
object=s.o c.o serversocket.o message.o clientlist.o\
 clientsocket.o cclientsocket.o sclientsocket.o\
 multithread.o thread.o\
 userinfo.o mystring.o file.o
$(all):$(object)
	g++ s.o serversocket.o message.o clientsocket.o sclientsocket.o clientlist.o thread.o multithread.o file.o mystring.o userinfo.o -o s -lpthread
	g++ c.o clientsocket.o multithread.o file.o mystring.o userinfo.o cclientsocket.o message.o -o c -lpthread
s.o:s.cpp
	g++ s.cpp -c -o s.o
serversocket.o:serversocket.cpp 
	g++ serversocket.cpp -c -o serversocket.o
c.o:c.cpp
	g++ c.cpp -c -o c.o
clientsocket.o:clientsocket.cpp
	g++ clientsocket.cpp -c -o clientsocket.o
sclientsocket.o:sclientsocket.cpp
	g++ sclientsocket.cpp -c -o sclientsocket.o
multithread.o:multithread.cpp
	g++ multithread.cpp -c -o multithread.o
cclientsocket.o:cclientsocket.cpp
	g++ cclientsocket.cpp -c -o cclientsocket.o
clientlist.o:clientlist.cpp
	g++ clientlist.cpp -c -o clientlist.o
message.o:message.cpp
	g++ message.cpp -c -o message.o
thread.o:thread.cpp
	g++ thread.cpp -c -o thread.o
userinfo.o:userinfo.cpp
	g++ userinfo.cpp -c -o userinfo.o
mystring.o:mystring.cpp
	g++ mystring.cpp -c -o mystring.o
file.o:file.cpp
	g++ file.cpp -c -o file.o
.PHONY:clean
clean:
	-rm -rf $(object) $(all)
