#include "cclientsocket.h"
#include "message.h"
#include "define.h"
#include "userinfo.h"

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

//000000:self
//999999:server

CClientSocket::CClientSocket(char *addr, int port):ClientSocket(0, addr, port),loginFlag(-1),user(NULL),status(0),isRunNet(true)
{
	struct sockaddr_in serveraddr;

	memset(&serveraddr, sizeof(serveraddr), 0);
	serveraddr.sin_family = AF_INET;
	inet_pton(AF_INET, addr, &serveraddr.sin_addr);
	serveraddr.sin_port = htons(port);

	int mfd = socket(AF_INET, SOCK_STREAM, 0);

	//connect with the server use the Exponential Backoff(zhishu buchang)
	for(int nsec = 1; nsec <= MAXSLEEP; nsec <<= 1)
	{
		if( connect(mfd, (struct sockaddr *)&serveraddr, sizeof(serveraddr)) == 0)
		{
			setFd(mfd);
			cout<<"connect with the server ("<<addr<<") success!"<<endl;
			return;
		}
		if(nsec <= MAXSLEEP/2)
		{
			sleep(nsec);
		}
	}

	if(getFd() == 0)
	{
		cout<<" conn't connected with the server!"<<endl;
		_exit(0);
	}
}


CClientSocket::~CClientSocket()
{
}

//analyse Command : cmd_...:exit,login,
int CClientSocket::analyseCmd(Message &ms)
{
	char *src = NULL, *dest = NULL, *info = NULL;
	src = ms.getSrc();
	dest = ms.getDest();
	info = ms.getInfo();

	if(strcmp(info, "cmd_exit") == 0 ){
		cout<<"exit"<<endl;
		this->exit();
	}else if(strcmp(info, "cmd_login") == 0){
		cout<<"login"<<endl;
		loginFlag = 0;
	}else if(strcmp(info, "cmd_apply") == 0){
		isRunNet = false;
		cout<<"apply id"<<endl;
		applyId();
		isRunNet = true;
	}
}

//1.analyse message
//2.server has exception, closed the connection
int CClientSocket::analyseMessage(Message &ms)
{
	char *src = NULL, *dest = NULL, *info = NULL;
	src = ms.getSrc();
	dest = ms.getDest();
	info = ms.getInfo();

	if(strcmp(src, "999999") == 0 && strcmp(info, "cmd_login_success") == 0){
		loginFlag = 1;
	}else if(strcmp(src, "999999") == 0 && strcmp(info, "cmd_login_failed") == 0){
		loginFlag = 0;
	}else if( strcmp(src, "999999") == 0 && strcmp(info, "re-apply") == 0 ){
		isRunNet = false;
	}else if(strcmp(src, "000000") == 0 && strcmp(dest, "000000") == 0 && strcmp(info, "0") == 0){
		//3.server has exception
		cout<<"Error : Sorry about this.\nThe Server has some exceptions, and disconnection to the client!\nPlease restart the client,and try agian!\n"<<endl;
		this->exit();
	}else{
		cout<<"src : "<<src<<"\tdest : "<<dest<<"\tinfo : "<<info<<endl;
	}

	return 0;
}

//receve message from the net socket
//then call analyMessage
void CClientSocket::runNet()
{
	while(isRunNet)
	{
		Message *ms = new Message();
#ifdef DEBUG
		cout<<"receve fd = "<<getFd()<<endl;
#endif
		if(recvMessage(*ms) == -1)
		{
			delete ms;
			ms = new Message("000000", "999999", "cmd_exit");
			analyseMessage(*ms);
			isRunNet = false;
			delete ms;
			this->exit();
		}
		analyseMessage(*ms);
		delete ms;
	}
}

//receve command from the host keybord or console
//then call analyMessage
void CClientSocket::runHost()
{
	char info[1025];
	char src[20] = "000000";
	char dest[20] = "999999";
	char choice;
	while(1)
	{
		if(loginFlag == -1)
		{
			cout<<"input command:\n";
			cin>>info;
			strcpy(src, "000000");
			strcpy(dest, "999999");
		}else if(loginFlag == 0)
		{
			cout<<"userno :";
			cin>>src;
			cout<<"password :";
			cin>>info;
			strcpy(dest, "999999");
		}else if(loginFlag == 1)
		{
			do
			{
				cout<<"input choice:\n1.command;\n2.talk with friend\n";
				cin>>choice;
				if(choice == '1')
				{
					cout<<"input Command:";
					cin>>info;	
					strcpy(dest, "000000");
				}else if(choice == '2'){
					cout<<"input friend number:";
					cin>>dest;
					cout<<"input info:";
					cin>>info;
				}else{
					cout<<"Error: cannot regconise command!"<<endl;
				}
			}while(choice != '1' && choice != '2');
		}

		Message *ms = new Message(src, dest, info);
#ifdef DEBUG
		cout<<"sending  fd = "<<getFd()<<endl;
#endif
		//sendMessage(*ms);
		analyseCmd(*ms);
		delete ms;
	}
}

int CClientSocket::applyId()
{
	cout<<"in applyId()"<<endl;
	Message *ms = new Message("000000", "999999", "apply");
	sendMessage(*ms);
	delete ms;

	cout<<"wait server answer...";
	ms = new Message();
	char *src = NULL, *dest = NULL, *info = NULL;

	do{
		recvMessage(*ms);
		cout<<".";

		src = ms->getSrc();
		dest = ms->getDest();
		info = ms->getInfo();
	}while( strcmp(info, "re-apply") == 0 );
	
	char username[30];
	char sex[8];
	char emaile[32];
	cout<<"\ninput username:"<<endl;
	cin>>username;
	cout<<"input sex:"<<endl;
	cin>>sex;
	cout<<"input emaile:"<<endl;
	cin>>emaile;

	user = new Userinfo();
	user->setUsername(username);
	user->setSex(sex);
	user->setEmaile(emaile);

	delete ms;
	ms = new Message("000000", "999999", (char *)user);
	cout<<"userinfo will be send:"<<user->getUsername()<<"\t"<<user->userno<<"\t"<<user->getSex()<<endl;
	sendMessage(*ms);
		
	recvMessage(*ms);
	src = ms->getSrc();
	dest = ms->getDest();
	if(strcmp(src, "999999") == 0 && strcmp(dest, "000000") != 0){
		delete user;
		user = (Userinfo *)ms->getInfo();
		cout<<"recve user: "<<user->getUsername()<<"\t"<<user->userno<<"\t"<<user->getSex()<<endl;
		return 0;
	}
}
