/******************************************************************************/
/*    Filename: sclientsocket.h                                               */
/*    Description: sclientsocket.class .h                                     */
/*                                                                            */
/*    Author:zhaocq (changqing.1230@163.com)  2011/2/30 (funny)               */
/******************************************************************************/
#ifndef SClientSocket_H
#define SClientSocket_H

#include "clientsocket.h"
#include "thread.h"
#include "userinfo.h"
#include "friendlist.h"

//SCleintSocket extends ClientSocket
//server use this class to manager the client
class SClientSocket : public ClientSocket, public Thread{
public:
	//online userinfo
	Userinfo *userinfo;
	//0 1 2 3 4
	//0 unlogin
	//1 online
	//2 busy
	//3 (yinshen)
	//4 offline
	int userStatus;
	FriendList *fls;

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

	void show();

//extends ClientSocket
	int analyseMessage(Message *ms);

	int applyId();
	int disCon();
	int login();
	void modify();

	void talk(Message *ms);
	void recvUnrecvMessage();

	bool saveUserinfoToFile();

//extends Thread
private:
	void run();

	void produceUserno(char *buf);
	void isClientExit(Message *ms);
};
#endif
