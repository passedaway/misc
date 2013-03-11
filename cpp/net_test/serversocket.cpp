#include "serversocket.h"
#include "define.h"
#include "file.h"

#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <syslog.h>

#include <iostream>
#include <iomanip>
using std::cout;
using std::cin;
using std::endl;
using std::left;
using std::right;
using std::setw;

//open Debug mode
//Debug mode:has print
#define DEBUG
//#undef DEBUG

ServerSocket::ServerSocket(int port, int maxuser):port(port),maxuser(maxuser)
{
#ifdef DEBUG
	cout<<"Debug ServerSocket(port = "<<port<<", maxuser = "<<maxuser<<")"<<endl;
#endif
	struct sockaddr_in sinp;
	//const char *addr;
	//int ret;
	char abuf[INET_ADDRSTRLEN];

	if(port <= 1024 || port > 65535)
		this->port = port = SERVER_PORT;
#ifdef DEBUG
	cout<<"Debug in the for: port = "<<port<<endl;
#endif

	memset(&sinp, sizeof(sinp), 0);
	sinp.sin_family = AF_INET;
	sinp.sin_addr.s_addr = htonl(INADDR_ANY);
	sinp.sin_port = htons(port);

	saddr = new char [INET_ADDRSTRLEN];
	inet_ntop(AF_INET, &(sinp.sin_addr), saddr, INET_ADDRSTRLEN);

	fd = socket(sinp.sin_family, SOCK_STREAM, 0);
#ifdef DEBUG
	cout<<"Debug socket() fd = "<<fd<<" addr: "<<saddr<<endl;
#endif

	int reuse = 1;
	setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(int));
#ifdef DEBUG
	cout<<"Debug setsockopt() success"<<endl;
#endif

	bind(fd, (struct sockaddr *)&sinp, sizeof(sinp));
#ifdef DEBUG
	cout<<"Debug bind() success"<<endl;
#endif

	if(maxuser > SERVER_MAXUSER)
		this->maxuser = maxuser = SERVER_MAXUSER;
	listen(fd, maxuser);
#ifdef DEBUG
	cout<<"Debug listen() success"<<endl;
#endif


	if( fd > 0)
	{
		cout<<"server listening port... "<<endl;
		clientList = new ClientList(maxuser);
	}

	//if not exists the file "userid" ,create one ,then fill the number
	if( File::exists("/etc/zz/userid") == false)
	{
		File *file = new File("/etc/zz/userid");
		file->toStart();
		file->putInt(SERVER_START_USERNO);
		delete file;
	}
}

ServerSocket::~ServerSocket()
{
	cout<<"server will shutdown..."<<endl;
	delete saddr;
//	sleep(3);
	if(fd > 0)
	{
		close(fd);
	}

	delete clientList;
	cout<<"server shutdown."<<endl;
}

//server for each
void ServerSocket::serverClient()
{
#ifdef DEBUG
	cout<<"serverClient()server for each client"<<endl;
#endif
	struct sockaddr_in clientaddr;
	socklen_t addrlen = sizeof(clientaddr);

	int clfd = accept(fd, (struct sockaddr *)&clientaddr, &addrlen);

	char *claddr = new char [INET_ADDRSTRLEN];
	inet_ntop(AF_INET, &clientaddr.sin_addr, claddr, INET_ADDRSTRLEN);
	int port = ntohs(clientaddr.sin_port);

	//SClientSocket *cstmp = new SClientSocket(clfd, claddr, port);
	if(clientList->addClient(clfd, claddr, port) == false)
	{
		cout<<"Error : server has full of client!\n Please wait for a moument, then try to connect with the server!"<<endl;
	}
	
#ifdef DEBUG
	cout<<"accept one client: addr "<<claddr<<" port "<<port<<endl;
#endif
	delete claddr;
}


//getters
int ServerSocket::getPort()
{
	return this->port;
}

int ServerSocket::getMaxuser()
{
	return this->maxuser;
}

char * ServerSocket::getSaddr()
{
	return this->saddr;
}

int ServerSocket::getCuruser()
{
	return clientList->getCuruser();
}

void ServerSocket::printClientInfo()
{
	if(getCuruser() == 0){
		cout<<"empty : no client connecteed with the server!"<<endl;
		return;
	}else{
		clientList->showClient();
		return;
	}
}

void ServerSocket::printServerInfo()
{
	cout<<right<<setw(30)<<"server infomation"<<endl;
	cout<<setw(15)<<"address : "<<saddr<<endl;
	cout<<setw(15)<<"port : "<<port<<endl;
	cout<<setw(15)<<"maxuser : "<<maxuser<<endl;
	cout<<setw(15)<<"curuser : "<<getCuruser()<<left<<endl;

	if(getCuruser() != 0)
	{
		cout<<right<<setw(15)<<"Client List : "<<left<<endl;
		printClientInfo();
	}
}

void ServerSocket::commandListen()
{
	getchar();
	getchar();
	char choice = '0';
	do{
		cout<<"\t\tCommand\n1.show server infomation\n2.online users infomation\n3.online user countes\n0.exit"<<endl;
		cin>>choice;
	
		if(choice == '1')
		{
			printServerInfo();
		}else if(choice == '2'){
			printClientInfo();
		}else if(choice == '3'){
			cout<<"users number = "<<getCuruser()<<endl;
		}else if(choice == '0'){
			exit();
		}
	}while(choice < '0' || choice > '3');
	
}
//extends Multithread
//for net
void ServerSocket::runNet()
{
	cout<<"start Server..."<<endl;
	while(1)
	{
		serverClient();
	}
}

//extends Multithread
//for host command
void ServerSocket::runHost()
{
	while(1)
	{
		commandListen();
	}
}
