/******************************************************************************/
/*    Filename: clientlist.h                                                  */
/*    Description: sclientsocket list                                         */
/*                                                                            */
/*    Author:zhaocq (changqing.1230@163.com)  2011/2/30 (funny)               */
/******************************************************************************/
#ifndef ClientList_H
#define ClientList_H

#include "sclientsocket.h"

class ClientList{
private:
	//current user in the list
	//getter only
	int curuser;
	//the list can listing the maxmaum number
	//users cannot see it,just for the program
	int maxuser;

public:
	SClientSocket *head;
	SClientSocket *end;

public:
	ClientList(int maxuser);
	~ClientList();

	//show all client conneted with the server
	void showClient();

	//manager Client which connected with the server
	SClientSocket* searchClient(char *userno);

	//add client
	//1.true: add client in the list successfully
	//2.false: this clientlist is already full
	bool addClient(int fd, char *addr, int port);

public:
	//delete the dest sclientsocket
	bool deleteClient(SClientSocket *dest);
	//search whoes next is the nextis
	SClientSocket* searchClient(SClientSocket *nextis);

	int getCuruser();

private:
	//delete not running sclient socket
	bool deleteClient();
};
#endif
