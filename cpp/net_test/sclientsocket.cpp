#include "sclientsocket.h"
#include "file.h"
#include "mystring.h"
#include "define.h"
#include "userinfo.h"

#include <string.h>

#include <iostream>
using std::cout;
using std::endl;

#define DEBUG
#undef DEBUG

//SClientSocket
//to manager the client which has connecte with the server
SClientSocket::SClientSocket(int fd, char *addr, int port):ClientSocket(fd, addr, port),next(NULL),isRun(false),user(NULL),status(0)
{
}

SClientSocket::~SClientSocket()
{
	if(user != NULL)
	{
		String path(SERVERDATA_PATH);
		path = path + String(user->userno);
		if(File::exists(path.tocharp()) )
		{
			File *file = new File(path.tocharp());
			file->writeBuffer((char *)user, sizeof(Userinfo));
			delete file;
		}
		delete user;
	}
}

bool SClientSocket::isHasNext()
{
	if(next == NULL)
	{
		return false;
	}else{
		return true;
	}
}

bool SClientSocket::isRuning()
{
	return isRun;
}

void SClientSocket::setNext(SClientSocket *dest)
{
	this->next = dest;
}

SClientSocket* SClientSocket::getNext()
{
	return next;
}

//server has multi threads,every thread is run this
void SClientSocket::run()
{
	isRun = true;
	while(isRun)
	{
		Message *ms = new Message();
		recvMessage(*ms);
		analyseMessage(*ms);
		//sendMessage(*ms);
		delete ms;
	}
}


int SClientSocket::analyseMessage(Message &ms)
{
	char *src = ms.getSrc();
	char *dest = ms.getDest();
	char *info = ms.getInfo();

	if(strcmp(src, "000000") == 0 && strcmp(dest, "000000")== 0 && strcmp(info, "0")== 0)
	{
		isRun = false;
		this->exit();
	}else if(status == 0){
		if(strcmp(src, "000000") == 0 && strcmp(dest, "999999") == 0 && strcmp(info, "apply") == 0 )
		{
			cout<<"applyId()"<<endl;
			applyId();	
			//apply user
		}else if(strcmp(src, "000000") == 0 && strcmp(dest, "999999")== 0 && strcmp(info, "login") == 0)
		{
			login();
		}
	}

	cout<<"Message \nsrc : "<<src<<"\tdest : "<<dest<<"\tinfo : "<<info<<endl;
}

//anser for the cclientsocket applyId()
int SClientSocket::applyId()
{
	Message *ms = new Message("999999", "000000", "re-apply");
	sendMessage(*ms);
	delete ms;
	ms = new Message("999999", "000000", "start");
	sendMessage(*ms);
	delete ms;
	
	File *file = new File("/etc/zz/userid");
	file->toStart();
	int userid = file->getInt();
	file->putInt(userid + 1);
	delete file;

	ms = new Message();
	recvMessage(*ms);
	char *info = ms->getInfo();
	user = (Userinfo *)info;
	status = 0;

	cout<<"userid = "<<userid<<endl;
	intocharp(userid, user->userno);

	Message *ms2 = new Message("999999", user->userno, (char *)user);
	sendMessage(*ms2);

	saveUserinfoToFile();
	user = NULL;

	delete ms;
	delete ms2;
	return 0;
}

int SClientSocket::login()
{
}

int SClientSocket::disCon()
{
}

int SClientSocket::talk()
{
}

bool SClientSocket::saveUserinfoToFile()
{
	if(user == NULL)
	{
		return false;
	}else{
		String path(SERVERDATA_PATH);
		path = path + String("/") + String(user->userno);

		File *file = new File(path.tocharp());
		file->toStart();
		file->writeBuffer((char *)user, sizeof(Userinfo));
		delete file;
		return true;
	}
}
