#ifndef SClientSocket_H
#define SClientSocket_H

#include "clientsocket.h"
#include "thread.h"
#include "userinfo.h"

//SCleintSocket extends ClientSocket
//server use this class to manager the client
class SClientSocket : public ClientSocket, public Thread{
public:
	//online userinfo
	Userinfo *user;
	//0 1 2 3 4
	//0 unlogin
	//1 online
	//2 busy
	//3 (yinshen)
	//4 offline
	int status;
private:
	//connected with the client,use ont thread
	//flag of the client that is the thread run,or in the clientlist
	bool isRun;
	//server : linklist, for the serversocket to manager
	SClientSocket *next;
public:
	//server:use this to manager the connecter client
	SClientSocket(int fd, char *addr, int port);
	~SClientSocket();

	bool isHasNext();
	bool isRuning();
	void setNext(SClientSocket *);
	SClientSocket *getNext();

//extends ClientSocket
	int analyseMessage(Message &ms);

	int applyId();
	int disCon();
	int talk();
	int login();

	bool saveUserinfoToFile();

//extends Thread
private:
	void run();
};
#endif
