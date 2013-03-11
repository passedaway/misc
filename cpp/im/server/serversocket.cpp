/******************************************************************************/
/*    Filename: serversocket.cpp                                              */
/*    Description: serversocket.class .h                                      */
/*                                                                            */
/*    Author:zhaocq (changqing.1230@163.com)  2011/2/30 (funny)               */
/******************************************************************************/
#include "serversocket.h"
#include "define.h"
#include "file.h"
#include "friendlist.h"
#include "userinfo.h"

#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <syslog.h>
#include <time.h>

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
#undef DEBUG

/***************************************************************************************************
����˵����
����˵����
	�����������
	�����������
	���أ���
***************************************************************************************************/
ServerSocket::ServerSocket(int port, int maxuser):port(port),maxuser(maxuser)
{
	struct sockaddr_in sinp;
	//const char *addr;
	//int ret;
	char abuf[INET_ADDRSTRLEN];

	if(port <= 1024 || port > 65535)
		this->port = port = SERVER_PORT;

	memset(&sinp, sizeof(sinp), 0);
	sinp.sin_family = AF_INET;
	sinp.sin_addr.s_addr = htonl(INADDR_ANY);
	sinp.sin_port = htons(port);

	saddr = new char [INET_ADDRSTRLEN];
	inet_ntop(AF_INET, &(sinp.sin_addr), saddr, INET_ADDRSTRLEN);

	fd = socket(sinp.sin_family, SOCK_STREAM, 0);

	int reuse = 1;
	setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(int));


	bind(fd, (struct sockaddr *)&sinp, sizeof(sinp));

	if(maxuser > SERVER_MAXUSER)
		this->maxuser = maxuser = SERVER_MAXUSER;
	listen(fd, maxuser);


	if( fd > 0)
	{
		cout<<"server listening port... "<<endl;
		clientList = new ClientList(maxuser);
	}

	//UnsendMessageList ��ʼ��
	//����Ƿ���usml�ļ�������У���򿪣�����δ���͵���Ϣ���뵽usml������
	cout<<"init unsendmessagelist"<<endl;
	usml = usml_init();
	char *buffer = new char[1024];
	File *usmlFile = new File("../server_data/usml");
	UnsendMessage *usm;
	while(1024 == usmlFile->readBuffer(buffer, 1024))
	{
		usm = (UnsendMessage *)malloc(sizeof(UnsendMessage));
		memset(usm, 0, sizeof(UnsendMessage));

		usm->ms = ms_init(NULL, NULL, NULL);

		memcpy(usm->ms->data, buffer, 1024);
		usml_add(usml, usm);
		cout<<".";
	}
	delete usmlFile;
	delete []buffer;
	cout<<"\nover"<<endl;
/*
//�����˺��Զ���һ�ķ�ʽ
	//if not exists the file "userid" ,create one ,then fill the number
	if( File::exists("../server_data/userid") == false)
	{
		File *file = new File("../server_data/userid");
		file->toStart();
		file->putInt(SERVER_START_USERNO);
		delete file;
	}
*/
}


/***************************************************************************************************
����˵����
����˵����
	�����������
	�����������
	���أ���
***************************************************************************************************/
ServerSocket::~ServerSocket()
{
	cout<<"server will shutdown..."<<endl;
	delete saddr;

	if(fd > 0)
	{
		close(fd);
	}

	delete clientList;


	if(usml)
	{
    	cout<<"save unsend message..."<<endl;
    	File *usmlFile = new File("../server_data/usml");
    	usmlFile->toStart();

		if(usml->head)
		{
        	UnsendMessage *usm = usml->head;

        	while(usm != NULL)
        	{
        		usmlFile->writeBuffer(usm->ms->data, 1024);
        		usm = usm->next;
        	}
   		}

   		usmlFile->trunc();
       	delete usmlFile;
    	usml_exit(usml);
	}
	cout<<"server shutdown."<<endl;
}


/***************************************************************************************************
����˵����
����˵����
	�����������
	�����������
	���أ���
***************************************************************************************************/
//server for each
void ServerSocket::serverClient()
{
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


	cout<<"\naccept one client:\n\taddr "<<claddr<<"\tport "<<port<<endl;

	delete []claddr;
}


/***************************************************************************************************
����˵����
����˵����
	�����������
	�����������
	���أ���
***************************************************************************************************/
//getters
int ServerSocket::getPort()
{
	return this->port;
}

/***************************************************************************************************
����˵����
����˵����
	�����������
	�����������
	���أ���
***************************************************************************************************/
int ServerSocket::getMaxuser()
{
	return this->maxuser;
}

/***************************************************************************************************
����˵����
����˵����
	�����������
	�����������
	���أ���
***************************************************************************************************/
char * ServerSocket::getSaddr()
{
	return this->saddr;
}

/***************************************************************************************************
����˵����
����˵����
	�����������
	�����������
	���أ���
***************************************************************************************************/
int ServerSocket::getCuruser()
{
	return clientList->getCuruser();
}

/***************************************************************************************************
����˵����
����˵����
	�����������
	�����������
	���أ���
***************************************************************************************************/
void ServerSocket::printClientInfo()
{
	if(getCuruser() == 0){
		cout<<"empty : no client connecteed with the server!"<<endl;
		return;
	}else{
		cout<<right<<setw(15)<<"IP"<<" : "<<left<<"port"<<endl;
		clientList->showClient();
		return;
	}
}

/***************************************************************************************************
����˵����
����˵����
	�����������
	�����������
	���أ���
***************************************************************************************************/
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

/***************************************************************************************************
����˵����
����˵����
	�����������
	�����������
	���أ���
***************************************************************************************************/
void ServerSocket::commandListen()
{
	char choice = '0';
	do{
		getchar();
		system("clear");
		cout<<"\tCommand\n\t1.show server infomation\n\t2.online users infomation\n\t3.online user countes\n\t4.manger user info\n\t0.exit"<<endl;
		cout<<"input your choice:";
		cin>>choice;

		switch(choice)
		{
			case '0':
				exit();
			case '1':
				printServerInfo();
				break;
			case '2':
				printClientInfo();
				break;
			case '3':
				cout<<"users number = "<<getCuruser()<<endl;
				break;

			case '4':
				//����ĳһ���û���Ϣ
				manageUserinfo();
				break;
			default:
				cout<<"\ninput error!again!\n"<<endl;
		}

		cout<<"\npress ENTER to continue..."<<endl;
		getchar();
	}while(choice < '0' || choice > '4');
}

/***************************************************************************************************
����˵����
����˵����
	�����������
	�����������
	���أ���
***************************************************************************************************/
//extends Multithread
//for net
void ServerSocket::runNet()
{
	cout<<"start Server..."<<endl;
	sleep(1);
	while(1)
	{
		serverClient();
	}
}


/***************************************************************************************************
����˵����
����˵����
	�����������
	�����������
	���أ���
***************************************************************************************************/
//extends Multithread
//for host command
void ServerSocket::runHost()
{
	while(1)
	{
		commandListen();
	}
}



/***************************************************************************************************
����˵����sclientsocket���øú�������ȡ��Ϣ�е�dest��src��Ȼ����Ϣ�͸�dest�û�
		  ������û������ߣ�����Ϣ�������Ϣ�ļ��У���ظ���srcһ����Ϣ
		  �� "���û������ߣ�������Ϣ�������Ѿ���������
����˵����
	���������Message *ms
	�����������
	���أ���
***************************************************************************************************/
void ServerSocket::talk(SClientSocket *scs, Message *ms)
{
	cout<<"ServerSocket::talk"<<endl;
	cout<<"ms->data:\n\t"<<ms->data<<endl;

	SClientSocket *tmp = NULL;
	char dest[7] = {0};
	char src[7] = {0};
	char *info = NULL;

	memcpy(dest, ms->data, 6);
	dest[6] = 0;
	memcpy(src, ms->data + USERNO_LEN, 6);
	src[6] = 0;
	info = ms_get_info(ms);

	tmp = clientList->searchClient(dest);

	if(tmp)
	{
		//send message to dest
		Message *ms_tmp = ms_init(dest, src, info);
		tmp->sendMessage(ms_tmp);
		ms_exit(ms_tmp);

		//save to file
		//д��Ϣ��ms+src�ļ���
		char *buffer = new char[1536];
		memset(buffer, 0, 1536);
		time_t curtime;
		time(&curtime);

		sprintf(buffer, "\nTime : %s\ndest : %s\nsrc : %s\ninfo:%s\n", asctime(localtime(&curtime)), dest, src, info);

		char filename[50] = "../server_data/ms";
		strcat(filename, scs->userinfo->userno);

		File *msFile = new File(filename);
		msFile->toEnd();
		msFile->writeBuffer(buffer, 1536);
		delete msFile;

		//д��Ϣ��ms+dest�ļ���
		char dest_filename[50] = "../server_data/ms";
		strcat(dest_filename, dest);

		msFile = new File(dest_filename);
		msFile->toEnd();

		msFile->writeBuffer(buffer, 1536);
		delete msFile;

		delete []buffer;
		cout<<"send message over"<<endl;
	}else{
		//1.save unsend message to UnsendMessageList
		UnsendMessage *usm = (UnsendMessage *)malloc(sizeof(UnsendMessage));
		memset(usm, 0, sizeof(UnsendMessage));
		usm->ms = ms_init(dest, src, info);
		usml_add(usml, usm);

		File *usmlFile = new File("../server_data/usml");
		usmlFile->toEnd();
		usmlFile->writeBuffer(usm->ms->data, 1024);
		delete usmlFile;

		//2.send "user did not online, server has processed your message!"
		info = (char *)"user did not online, server has processed your message!";
		Message *tmpms = ms_init(scs->userinfo->userno, (char *)"999999", info);
		scs->sendMessage(tmpms);
		ms_exit(tmpms);

		cout<<"message unsend!saved over!"<<endl;
	}

	cout<<"ServerSocket::talk over"<<endl;
}


/***************************************************************************************************
����˵����sclientsocket���øú�������unsendmessage�в����Ƿ��и�sclientsocket����Ϣ
		  ���������Ϣ���͸����û���������Ϣ����Ϣ�б���ɾ����ֱ��δ������Ϣ�б��У�
		  û�и��û���δ������Ϣ
����˵����
	���������Message *ms
	�����������
	���أ���
***************************************************************************************************/
void ServerSocket::sendUnsendMessage(SClientSocket *scs)
{
	cout<<"ServerSocket::sendUnsendMessage"<<endl;

	//1.save unsend message to UnsendMessageList
	if(usml == NULL || usml->head == NULL)
		return;

	if(scs->userinfo->userno == NULL)
		return;

	UnsendMessage *usm = NULL;
	Message *ms = NULL;

	do{
		usm = usml_search_by_destuserno(usml, scs->userinfo->userno);
		cout<<"usml_search_by_destuserno "<<scs->userinfo->userno<<endl;
		if(usm == NULL)
			return;

		ms = ms_init(NULL, NULL, NULL);
		memcpy(ms->data, usm->ms->data, 1024);

		scs->sendMessage(ms);

		cout<<"ms->data:\n\t"<<ms->data<<endl;

		//������֮�󣬽�����Ϣ��unsendmessagelist��ɾ��
		usml_del(usml, usm);

		ms_exit(ms);

	}while(usm);

	cout<<"ServerSocket::sendUnsendMessage over"<<endl;
}


/***************************************************************************************************
����˵���������û���Ϣ����鿴ĳһ�û�����Ϣ�����ѣ������¼���޸ĸ�����Ϣ
����˵����
	���������Message *ms
	�����������
	���أ���
***************************************************************************************************/
void ServerSocket::manageUserinfo()
{
	char choice = '0';
	do{
		getchar();
		system("clear");
		cout<<"\n\tManager Userinfo\n"<<"\t1.show all users\n\t2.show user information\n\t3.show user chat log\n\t4.modify user infomation\n\t5.delete user\n\t0.exit User Manager\n"<<endl;
		cout<<"input you choice:"<<endl;

		cin>>choice;

		switch(choice)
		{
			case '1':
				//show all user info
				system("ls ../server_data/ | grep '^[0-9]' | more");
				break;
			case '2':
				//show user information
				{
					char userno[30];
					cout<<"show user information\ninput userno:"<<endl;
					cin>>userno;

					char filename[30] = "../server_data/";
					strncat(filename, userno, 6);

					cout<<"\tInfomation"<<endl;
					if(File::exists((const char *)filename))
					{
						File *ufFile = new File((const char *)filename);
						char *buffer = new char[sizeof(Userinfo)];
						Userinfo *uf = userinfo_init();

						//get userinfo
						ufFile->readBuffer(buffer, sizeof(Userinfo));

						uf = userinfo_init();
						memcpy(uf, buffer, sizeof(Userinfo));
						delete []buffer;

						//get friendlist
						FriendList *fl = friendlist_init();
						Friend *fr = NULL;
						int friend_size = sizeof(Friend);
						buffer = new char[friend_size];
						while(friend_size == ufFile->readBuffer(buffer, friend_size))
						{
							fr = (Friend*)malloc(friend_size);
							memcpy(fr, buffer, friend_size);
							friendlist_add(fl, fr);
						}

						cout<<setw(20)<<"\tuserno"<<": "<<uf->userno<<"\n"
							<<setw(20)<<"\tpasswd"<<": "<<uf->passwd<<"\n"
							<<setw(20)<<"\tusername"<<": "<<uf->username<<"\n"
							<<setw(20)<<"\tname"<<": "<<uf->name<<"\n"
							<<setw(20)<<"\tsex"<<": "<<uf->sex<<"\n"
							<<setw(20)<<"\temaile"<<": "<<uf->emaile<<"\n"<<endl;

						cout<<"\tFriendList\n\t"<<setw(10)<<"userno"<<"nickname"<<endl;
						if(fl == NULL || fl->head == NULL)
							cout<<"\tNO Friend List\n"<<endl;
						else
						{
							for(fr = fl->head; fr != NULL; fr = fr->next)
							{
								cout<<"\t"<<setw(10)<<fr->userno<<fr->nickname<<endl;
							}
							cout<<endl;
						}

						delete []buffer;
						delete ufFile;
						friendlist_exit(fl);
					}else{
						cout<<"WARNING: no such user!"<<endl;
					}
				}
				break;
			case '3':
				//show chat log
				{
					char userno[30];

					cout<<"show user chat log\ninput userno:"<<endl;
					cin>>userno;

					char filename[30] = "../server_data/ms";
					strncat(filename, userno, 6);

					if(File::exists((const char *)filename))
					{
						char cmd[100];
						sprintf(cmd, "cat ../server_data/ms%s | more", userno);
						system(cmd);
						cout<<"cmd "<<cmd<<endl;
					}else{
						cout<<"WARNING: user did not have chat log\n"<<endl;
					}
				}
				break;
			case '4':
				//modify user information
				{
					char userno[30];

					cout<<"Modify user information\ninput userno:"<<endl;
					cin>>userno;

					char filename[30] = "../server_data/";
					strncat(filename, userno, 6);

					if(File::exists((const char *)filename))
					{

						File *ufFile = new File((const char *)filename);
						char *buffer = new char[sizeof(Userinfo)];
						Userinfo *uf = userinfo_init();

						//get userinfo
						ufFile->readBuffer(buffer, sizeof(Userinfo));
						uf = userinfo_init();
						memcpy(uf, buffer, sizeof(Userinfo));
						delete []buffer;

						cout<<"\tuserno : "<<uf->userno<<endl;

						char choice = '0';
						//modify passwd
						do{
							cout<<"passwd : "<<uf->passwd<<"\tmodify?Y/n";
							cin>>choice;

							if(choice == 'Y' || choice == 'y')
							{
								char passwd[50];
								cout<<"\tnew passwd:";
								cin>>passwd;
								if(!userinfo_checkPasswd(passwd))
									choice = '0';
								else{
									strcpy(uf->passwd, passwd);
								}
							}
						}while(choice != 'Y' && choice != 'y' && choice != 'N' && choice != 'n');

						//modify username
						do{
							cout<<"username : "<<uf->username<<"\tmodify?Y/n";
							cin>>choice;

							if(choice == 'Y' || choice == 'y')
							{
								char username[50];
								cout<<"\tnew username:";
								cin>>username;

								strcpy(uf->username, username);
							}
						}while(choice != 'Y' && choice != 'y' && choice != 'N' && choice != 'n');

						//name
						do{
							cout<<"name : "<<uf->name<<"\tmodify?Y/n";
							cin>>choice;

							if(choice == 'Y' || choice == 'y')
							{
								char name[60];
								cout<<"\tnew name:";
								cin>>name;

								strcpy(uf->name, name);
							}
						}while(choice != 'Y' && choice != 'y' && choice != 'N' && choice != 'n');

						//modify sex
						do{
							cout<<"sex : "<<uf->sex<<"\tmodify?Y/n";
							cin>>choice;

							if(choice == 'Y' || choice == 'y')
							{
								char sex[20];
								cout<<"\tnew sex (male or female):";
								cin>>sex;
								if(!userinfo_checkSex(sex))
								{
									choice = '0';
									memset(sex, 0, 20);
								}
								else{
									strcpy(uf->sex, sex);
								}
							}
						}while(choice != 'Y' && choice != 'y' && choice != 'N' && choice != 'n');

						//modify emaile
						do{
							cout<<"emaile : "<<uf->emaile<<"\tmodify?Y/n";
							cin>>choice;

							if(choice == 'Y' || choice == 'y')
							{
								char emaile[50];
								cout<<"\tnew emaile:";
								cin>>emaile;
								if(!userinfo_checkEmaile(emaile))
								{
									choice = '0';
									memset(emaile, 0, 50);
								}
								else{
									strcpy(uf->emaile, emaile);
								}
							}
						}while(choice != 'Y' && choice != 'y' && choice != 'N' && choice != 'n');

						//commit
						do{
							cout<<"\tcommit?Y/n";
							cin>>choice;

							if(choice == 'y' || choice == 'Y')
							{
								buffer = new char[sizeof(Userinfo)];
								memcpy(buffer, uf, sizeof(Userinfo));

								ufFile->toStart();
								ufFile->writeBuffer(buffer, sizeof(Userinfo));
								delete []buffer;
							}
						}while(choice != 'Y' && choice != 'y' && choice != 'N' && choice != 'n');

						delete ufFile;
					}else{
						cout<<"WARNING: no such user!"<<endl;
					}


				}
				break;
			case '5':
				//delete user
				{
					char userno[30];
					char cmd[100];
					char choice = '0';
					cout<<"\tdelete user \ninput userno:"<<endl;
					cin>>userno;

					char filename[30] = "../server_data/";
					strncat(filename, userno, 6);
					if(! File::exists((const char *)filename))
					{
						cout<<"no such user"<<endl;
						break;
					}

					do{
						cout<<"WARNING:\n\tdo you realy want to delete this user?Y/n";
						cin>>choice;
					}while(choice != 'Y' && choice != 'y' && choice != 'n' && choice != 'N');

					cout<<"\n";
					if(choice == 'Y' || choice == 'y')
					{
						sprintf(cmd, "rm -rf ../server_data/%s ../server_data/ms%s", userno, userno);
						system(cmd);
						cout<<"WARNING:\n\t deleted the user and releted information"<<endl;
					}
				}
				break;
			case '0':
				//exit for userinfo
				cout<<"exit Userinfo Manager"<<endl;
				return;
		}

	cout<<"press ENTER to continue..."<<endl;
	getchar();
	}while(choice != '0');
}
