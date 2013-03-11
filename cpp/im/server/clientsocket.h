/******************************************************************************/
/*    Filename: clientsocket.h                                                */
/*    Description: clientsocket                                               */
/*                                                                            */
/*    Author:zhaocq (changqing.1230@163.com)  2011/2/30 (funny)               */
/******************************************************************************/
#ifndef ClientSocket_H
#define ClientSocket_H

#include "message.h"

//has two children
//1.CClientSocket : client use the ClientSocket
//2.SClientSocket : server use the ClientSocket
class ClientSocket {
private:
	//socket fd
	int fd;
	//1.client : server port
	//2.server : client port conneted with the server
	int port;
	//1.client : server address
	//2.server : client address connetct with the server
	char *addr;
public:

	ClientSocket(int fd, char *addr, int port);

	//copy constructer
	ClientSocket(const ClientSocket &);

	virtual ~ClientSocket();

	//receve the message by the "fd"
	int recvMessage(Message *rms);
	//send message to the "fd"
	int sendMessage(Message *wms);
	//1.server:conmunection with the client
	//2.client:conmunection with server
	virtual int analyseMessage(Message *ms) = 0;

	//apply for new ID
	virtual int applyId() = 0;
	//disconnect with the server
	virtual int disCon() = 0;
	//normal talking : send the message to other client
	virtual void talk(Message *ms) = 0;

	//getters and setters
	int getFd();
	int getPort();
	char *getAddr();
	//for the CCleintSocket child
	void setFd(int fd);
};
#endif
