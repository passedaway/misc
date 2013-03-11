/******************************************************************************/
/*    Filename: serversocket.h                                                */
/*    Description: server use this class                                      */
/*                                                                            */
/*    Author:zhaocq (changqing.1230@163.com)  2011/2/30 (funny)               */
/******************************************************************************/
#ifndef ServerSocket_H
#define ServerSocket_h

#include "clientlist.h"
#include "multithread.h"
#include "unsendmessage.h"

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
	UnsendMessageList *usml;

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

	void manageUserinfo();

	//sclientsocket call this,because the serversocket has the clientlist
	void talk(SClientSocket *scs, Message *ms);
	void sendUnsendMessage(SClientSocket *scs);

	//extends MultiThread
private:
	void runNet();
	void runHost();
};
#endif
