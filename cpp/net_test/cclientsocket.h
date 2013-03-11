#ifndef CClientSocket_H
#define CClientSocket_H
//CClientSocket extends ClientSocket
//CClientSocket extends Thread
//client use this class
#include "define.h"
#include "clientsocket.h"
#include "multithread.h"
#include "userinfo.h"

class CClientSocket : public ClientSocket, public MultiThread{
public:
	//client:create and connect with the socket
	CClientSocket(char *addr, int port);
	~CClientSocket();
//extends ClientSocket
	int analyseMessage(Message &ms);

	//apply id for server
	int applyId();

	int disCon(){
	}
	
	int talk(){
	}

	int login(){}
public:
	Userinfo *user;
	int status;
	//0 unlogin
	//1 online
	//2 busy
	//3 (yinshen)
	//4 offline

private:
//Multithread
//analyseCmd();
	int analyseCmd(Message &ms);
//extends ClientThread
	void runNet();
	void runHost();
private:
	//control the action, just use for the runNet and runHost
	//to diff the cmd, or the message
	//-1:cmd
	//0:loginning...
	//1:login success
	//2:apply Id
	int loginFlag;
	bool isRunNet;
};
#endif
