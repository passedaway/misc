all=exe/c exe/s
SERVER_OBJ=server/s.o server/serversocket.o server/clientlist.o server/clientsocket.o server/sclientsocket.o\
	server/multithread.o server/thread.o server/mystring.o server/file.o\
	server/message.o server/userinfo.o server/friendlist.o server/unsendmessage.o

CLIENT_OBJ=client/c.o client/cclientsocket.o client/cmessage.o client/cuserinfo.o client/cfriendlist.o

$(all):$(CLIENT_OBJ) $(SERVER_OBJ)
	g++ $(SERVER_OBJ) -o exe/s -lpthread
	cc $(CLIENT_OBJ) -o exe/c -lpthread

$(SERVER_OBJ):
include server/server.mk

$(CLIENT_OBJ):
include client/client.mk

.PHONY:clean
clean:
	-rm -rf $(SERVER_OBJ) $(CLIENT_OBJ) $(COMMON_OBJ) $(all)
