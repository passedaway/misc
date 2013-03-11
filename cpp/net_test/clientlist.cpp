#include "clientlist.h"

#include <iostream>
#include <iomanip>
using std::cout;
using std::endl;
using std::setw;
using std::left;
using std::right;

ClientList::ClientList(int maxuser):curuser(0),maxuser(maxuser),head(NULL),end(NULL)
{
}

ClientList::~ClientList()
{
	cout<<"delete Client : ";
	for(int i = 0;i < curuser; i++)
	{
		end = head;
		head = head->getNext();
		delete end;

		cout<<".";
	}
	cout<<"\tover"<<endl;
}

void ClientList::showClient()
{
	this->deleteClient();

	SClientSocket *tmp = head;

	for(int i = 0; i < curuser && tmp != NULL; i++)
	{
		cout<<right<<setw(15)<<tmp->getAddr()<<" : "<<left<<tmp->getPort()<<endl;
		tmp = tmp->getNext();
	}
}

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
	}else if(curuser > maxuser)
	{
		delete tmp;
		return false;
	}else{
		end->setNext(tmp);
		end = tmp;

		curuser++;

		end->startThread();

		return true;
	}
}

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
			delete dest;
			curuser--;

			return true;
		}else{
			return false;
		}
	}

}
/*
SClientSocket* ClientList::searchClient(char *addr)
{
}
*/

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

int ClientList::getCuruser()
{
	deleteClient();
	return curuser;
}
