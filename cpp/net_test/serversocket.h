#ifndef ServerSocket_H
#define ServerSocket_h

#include "clientlist.h"
#include "multithread.h"

class ServerSocket : public MultiThread{
private:
	//listening socket fd
	int fd;
	//server port
	int port;
	//can listen max user
	int maxuser;

	//server address
	char *saddr;

//debug
public:
	//client list which connected with the server
	ClientList *clientList;

public:
	//create the server socket, not start the server!
	//need to call the startServer() to start the server
	ServerSocket(int port, int maxuser);
	~ServerSocket();

//two thread
//1.startServer
//2.commandlisten
	//start server
	//1.accpet client
	//2.server for each client 
	void serverClient();
	//command listen
	//listen for cmd
	void commandListen();

	int myread();
	int mywrite();

	//getters
	char *getSaddr();
	int getPort();
	int getMaxuser();

	//current user online
	//recorded in the clientList
	//int curuser;
	int getCuruser();

	//print online Client infomation 
	void printClientInfo();
	//print Server infomation
	void printServerInfo();


	//extends MultiThread
private:
	void runNet();
	void runHost();
};
#endif
