/******************************************************************************/
/*    Filename: clientlist.cpp                                                */
/*    Description: server use this class to manager the client                */
/*                 which connect with the server                              */
/*                                                                            */
/*    Author:zhaocq (changqing.1230@163.com)  2011/2/30 (funny)               */
/******************************************************************************/
#include "clientlist.h"

#include <string.h>
#include <iostream>
#include <iomanip>
using std::cout;
using std::endl;
using std::setw;
using std::left;
using std::right;

/***************************************************************************************************
功能说明：
参数说明：
	输入参数：无
	输出参数：无
	返回：无
***************************************************************************************************/
ClientList::ClientList(int maxuser):curuser(0),maxuser(maxuser),head(NULL),end(NULL)
{
}

/***************************************************************************************************
功能说明：
参数说明：
	输入参数：无
	输出参数：无
	返回：无
***************************************************************************************************/
ClientList::~ClientList()
{
	cout<<"delete Client : ";
	SClientSocket *tmp = head;
	if(head)
    	while( head->getNext() )
    	{
    		tmp = head;
    		head = head->getNext();
    		delete tmp;

    		cout<<".";
    	}
	cout<<"\tover"<<endl;
}

/***************************************************************************************************
功能说明：
参数说明：
	输入参数：无
	输出参数：无
	返回：无
***************************************************************************************************/
void ClientList::showClient()
{
	this->deleteClient();

	SClientSocket *tmp = head;

	for(int i = 0; i < curuser && tmp != NULL; i++, tmp = tmp->getNext())
	{
		//cout<<right<<setw(15)<<tmp->getAddr()<<" : "<<left<<tmp->getPort()<<endl;
		tmp->show();
	}
}

/***************************************************************************************************
功能说明：
参数说明：
	输入参数：无
	输出参数：无
	返回：无
***************************************************************************************************/
bool ClientList::addClient(int fd, char *addr, int port)
{
	SClientSocket *tmp = new SClientSocket(fd, addr, port);

	if(head == NULL)
	{
		head = tmp;
		end = tmp;
		curuser = 1;

		end->startThread();

		return true;
	}else if(curuser > maxuser){
		delete tmp;
		return false;
	}else{
		end->setNext(tmp);
		end = tmp;
		end->setNext(NULL);

		curuser++;

		end->startThread();

		return true;
	}
}

/***************************************************************************************************
功能说明：
参数说明：
	输入参数：无
	输出参数：无
	返回：无
***************************************************************************************************/
//delete didnot Runing Client
bool ClientList::deleteClient()
{
	for(SClientSocket *tmp = head; tmp != NULL; tmp = tmp->getNext())
	{
		if( !tmp->isRuning() )
		{
			if( !deleteClient(tmp))
			{
				cout<<"Error : delete SClientSocket error!"<<endl;
				return false;
			}
		}
	}

	return true;
}

/***************************************************************************************************
功能说明：
参数说明：
	输入参数：无
	输出参数：无
	返回：无
***************************************************************************************************/
bool ClientList::deleteClient(SClientSocket *dest)
{
	if(dest == head)
	{
		if(end == head)
		 {
			delete head;
			end = head = NULL;

			curuser = 0;

			return true;
		 }else{
			head = head->getNext();
			delete dest;
			curuser--;

			return true;
		 }
	}else{
		SClientSocket *pre = searchClient(dest);
		if(pre != NULL)
		{
			pre->setNext( dest->getNext() );
			if(dest == end)
				end = pre;
			delete dest;
			curuser--;

			return true;
		}else{
			return false;
		}
	}

}

/***************************************************************************************************
功能说明：根据userno查找clientlist中是否有该sclientsocket，如果有，则返回该sclientsocket的地址
			没有返回null
参数说明：
	输入参数：userno
	输出参数：无
	返回：sclientsocket
***************************************************************************************************/
SClientSocket* ClientList::searchClient(char *userno)
{
	if(head)
	{
		SClientSocket *tmp = head;

		for(; tmp != NULL; tmp = tmp->getNext())
		{
			if(tmp->userStatus)//userno在线
			{
				if( !strncmp(tmp->userinfo->userno, userno, USERNO_LEN))
					return tmp;
			}
		}
	}

	return NULL;
}


/***************************************************************************************************
功能说明：
参数说明：
	输入参数：无
	输出参数：无
	返回：无
***************************************************************************************************/
SClientSocket* ClientList::searchClient(SClientSocket *nextis)
{
	if(head == NULL)
	{
		return NULL;
	}else{
		SClientSocket *tmp = head;

		for(; tmp->getNext() != nextis && tmp != NULL; tmp = tmp->getNext())
			;

		if(tmp->getNext() == nextis)
		{
			return tmp;
		}else{
			return NULL;
		}
	}
}

/***************************************************************************************************
功能说明：
参数说明：
	输入参数：无
	输出参数：无
	返回：无
***************************************************************************************************/
int ClientList::getCuruser()
{
	deleteClient();
	return curuser;
}
