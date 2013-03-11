#include "message.h"
#include "clientsocket.h"

#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>

#include <iostream>
using namespace std;

#define MAXSLEEP 128

#define DEBUG
#undef DEBUG

//clientsocket
ClientSocket::ClientSocket(int fd, char *addr, int port):fd(fd),port(port)
{
	int len = strlen(addr);
	this->addr = new char[len + 1];
	strncpy(this->addr, addr, len + 1);
}

//copy constructer
ClientSocket::ClientSocket(const ClientSocket &dest)
{
	//fd = dup(fd);
	fd = dest.fd;

	int len = strlen(dest.addr);
	addr = new char[len + 1];
	strncpy(addr, dest.addr, len + 1);
}


ClientSocket::~ClientSocket()
{
	delete addr;

	if(fd > 0)
	{
		close(fd);
		fd = -1;
	}
}

int ClientSocket::getFd()
{
	return fd;
}

void ClientSocket::setFd(int fd)
{
	this->fd = fd;
}

int ClientSocket::getPort()
{
	return port;
}

char* ClientSocket::getAddr()
{
	return addr;
}


int ClientSocket::recvMessage(Message &rms)
{
#ifdef DEBUG
	cout<<"Debug ClientSocket::recvMessage()"<<endl;
#endif
	int len = sizeof(rms);
	char *buf = (char *)&rms;
	int n = 0;
	
	while( (n = read(fd, buf, len)) > 0)
	{
#ifdef DEBUG
		cout<<"Debug in while() len ="<<len<<endl;
#endif
		buf += n;
		len -= n;
	}

#ifdef DEBUG
	cout<<"Debug ClientSocket::recvMessage() over"<<endl;
#endif
	if(n == 0)
	{
		return sizeof(rms);
	}else{
		return -1;
	}
}

int ClientSocket::sendMessage(const Message &wms)
{
#ifdef DEBUG
	cout<<"Debug ClientSocket::sendMessage()"<<endl;
#endif
	char *buf = (char *)&wms;
	int len = sizeof(wms);

	int ret = write(fd, buf, len);

#ifdef DEBUG
	cout<<"Debug ClientSocket::sendMessage() over: ret = "<<ret<<endl;
#endif
	return ret;
}
