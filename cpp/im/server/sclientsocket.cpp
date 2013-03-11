/******************************************************************************/
/*    Filename: sclientsocket.cpp                                             */
/*    Description: sclientsocket.class .h                                     */
/*                                                                            */
/*    Author:zhaocq (changqing.1230@163.com)  2011/2/30 (funny)               */
/******************************************************************************/
#include "sclientsocket.h"
#include "file.h"
#include "mystring.h"
#include "define.h"
#include "userinfo.h"
#include "serversocket.h"

#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

#include <iostream>
#include <iomanip>
using std::cout;
using std::endl;
using std::setw;
using std::right;
using std::left;

//from s.cpp
//sclientsockt talk need clientlist, then need serversocket talk
extern ServerSocket *g_ss;

#define DEBUG
#undef DEBUG

/***************************************************************************************************
功能说明：
参数说明：
	输入参数：无
	输出参数：无
	返回：无
***************************************************************************************************/
//SClientSocket
//to manager the client which has connecte with the server
SClientSocket::SClientSocket(int fd, char *addr, int port):ClientSocket(fd, addr, port),Thread(),next(NULL),isRun(false),userinfo(NULL),userStatus(0),fls(NULL)
{
}

/***************************************************************************************************
功能说明：
参数说明：
	输入参数：无
	输出参数：无
	返回：无
***************************************************************************************************/
SClientSocket::~SClientSocket()
{
	cout<<"SClientSocket::~SClientSocke()"<<endl;
	cout<<"saveUserinfoToFile()"<<endl;
	saveUserinfoToFile();

	cout<<"userinfo userinfo_exit()"<<endl;
	if(userinfo)
		userinfo_exit(userinfo);

	cout<<"fls friendlist_exit(fls)"<<endl;
	if(fls)
		friendlist_exit(fls);

	isRun = false;
	cout<<"SClientSocket::~SClientSocke() over"<<endl;
}

/***************************************************************************************************
功能说明：
参数说明：
	输入参数：无
	输出参数：无
	返回：无
***************************************************************************************************/
bool SClientSocket::isHasNext()
{
	if(next == NULL)
	{
		return false;
	}else{
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
bool SClientSocket::isRuning()
{
	return isRun;
}

/***************************************************************************************************
功能说明：
参数说明：
	输入参数：无
	输出参数：无
	返回：无
***************************************************************************************************/
void SClientSocket::setNext(SClientSocket *dest)
{
	this->next = dest;
}

/***************************************************************************************************
功能说明：
参数说明：
	输入参数：无
	输出参数：无
	返回：无
***************************************************************************************************/
SClientSocket* SClientSocket::getNext()
{
	return next;
}

/***************************************************************************************************
功能说明：
参数说明：
	输入参数：无
	输出参数：无
	返回：无
***************************************************************************************************/
//server has multi threads,every thread is run this
void SClientSocket::run()
{
	isRun = true;
	while(isRun)
	{
		Message *ms = ms_init(NULL, NULL, NULL);
		recvMessage(ms);

		analyseMessage(ms);
		ms_exit(ms);
	}
}

/***************************************************************************************************
功能说明：
参数说明：
	输入参数：无
	输出参数：无
	返回：无
***************************************************************************************************/
int SClientSocket::analyseMessage(Message *ms)
{
	char *dest = ms_get_dest(ms);
	char *src = ms_get_src(ms);
	char *info = ms_get_info(ms);

	//检测收到的消息是否是结束消息
	isClientExit(ms);
	cout<<"Message :"<<ms->data<<endl;

	if(userStatus == 0){
		if(strncmp(src, "000000", 6) == 0 && strncmp(dest, "999999", 6) == 0 && strcmp(info, "apply") == 0 )
		{
			//apply id statge 1
			cout<<"applyId()"<<endl;
			applyId();
		}else if(strncmp(src, "000000", 6) == 0 && strncmp(dest, "999999" ,6)== 0 && strcmp(info, "login") == 0)
		{
			cout<<"login()"<<endl;
			login();
		}
	}else{
		if( !strncmp(dest, "999999", 6) )
		{
			//info == modify || add+userno
			if( !strcmp(info, "modify"))
			{
					//modify userself infomation
					cout<<"modify()"<<endl;
					modify();
			}
			else if( !strncmp(info, "add", 3))
			{
				//add+userno
				if( !strncmp(info, "add_agree", 7))
				{
					//nickname 为64字节
					// 用户B同意用户A的好友申请
					//add_agree + a_userno + b_nickname + a_nickname
					//   同意userno的添加好友
					char a_userno[7];
					char b_nickname[64];
					char a_nickname[64];

					memset(b_nickname, 0, 64);
					memset(a_nickname, 0, 64);

					cout<<"add_agree_ms info:\n\t"<<info<<endl;

					info += strlen("add_agree+");
					memcpy(a_userno, info, 6);
					a_userno[6] = 0;

					info += 7;
					memcpy(b_nickname, info, 64);
					info += 65;
					memcpy(a_nickname, info, 64);

					char agree_info[256];
					sprintf(agree_info, "add_agree+%s+%s", userinfo->userno, b_nickname);

					//把同意消息发给申请者
					Message *agree_ms = ms_init(a_userno, (char *)"999999", agree_info);
					talk(agree_ms);
					ms_exit(agree_ms);


					//将用户A添加到用户B的好友列表（服务器端添加并保存，客户端的添加由客户端完成）
					Friend *fra = (Friend *)malloc(sizeof(Friend));
					memset(fra, 0, sizeof(Friend));
					memcpy(fra->userno, a_userno, 6);
					memcpy(fra->nickname, a_nickname, 64);

					friendlist_add(fls, fra);

					//将用户B添加到用户A的好友列表
					//如果用户A在线，则直接添加，如果不在线则打开文件并重新添加
					Friend *frb = (Friend *)malloc(sizeof(Friend));
					memset(frb, 0, sizeof(Friend));
					memcpy(frb->userno, userinfo->userno, 6);
					memcpy(frb->nickname, b_nickname, 64);

					SClientSocket *scsa = g_ss->clientList->searchClient(a_userno);
					if(scsa)
					{
						//用户A在线
						friendlist_add(scsa->fls, frb);
					}else{
						//用户A不在线
						char filename[30] = "../server_data/";
						strcat(filename, a_userno);

						File *file = new File((const char *)filename);
						file->toEnd();
						file->writeBuffer((char *)frb, sizeof(Friend) );
						free(frb);
						frb = NULL;

            			delete file;
					}

				}else if( !strncmp(info, "add_disagree", 7)){
					//add_disagree + userno  不同意userno的添加好友
					//用户B不同意用户A的好友请求
					//目前用户为用户B
					char a_userno[7];
					memcpy(a_userno, info+strlen("add_disagree+"), 6);
					a_userno[6] = 0;

					char dis_info[256];
					memset(dis_info, 0, 256);
					sprintf(dis_info, "add_disagree+%s", userinfo->userno);

					Message *disagree_ms = ms_init(a_userno, (char *)"999999", dis_info);
					talk(disagree_ms);
					ms_exit(disagree_ms);
				}

				if( !strncmp(info, "add+", 4))
				{
					//添加用户信息
					//nickname 为64字节
					//add+b_userno+b_nickname
					//将消息整合成“add+用户A_userno+B_nickname”的样式，然后发送给B
					char b_userno[7];
					char b_nickname[64];
					char info_buffer[256];

					memcpy(b_userno, info + 4, 6);
					b_userno[6] = 0;
					memset(b_nickname, 0, 64);
					memcpy(b_nickname, info + 11, 64);

					char filename[30] = {0};
					memset(filename, 0, 30);
					sprintf(filename, "../server_data/%s", b_userno);

					if( File::exists((const char *)filename) )
					{
						if(b_nickname[0] == 0)
						{
							File *file = new File((const char *)filename);
							Userinfo *uf_t = userinfo_init();
							file->readBuffer((char *)uf_t, sizeof(Userinfo));
							delete file;

							strcpy(b_nickname, uf_t->username);
						}
					}else{
						char add_error_info[256];

						memset(add_error_info, 0, 256);

						sprintf(add_error_info, "add_error+%s no such user! userno = %s", b_userno, b_userno);
						Message *add_error_ms = ms_init(userinfo->userno, (char *)"999999", add_error_info);

						sendMessage(add_error_ms);

						ms_exit(add_error_ms);
						return 1;
					}

					sprintf(info_buffer, "add+%s+%s", userinfo->userno, b_nickname);

					Message *add_ms = ms_init(b_userno, (char *)"999999", info_buffer);
					talk(add_ms);
					ms_exit(add_ms);
				}
			}
		}
		else
		{
			cout<<"talk"<<endl;
			talk(ms);
			cout<<"talk"<<endl;
		}
	}

	return 1;
}

/***************************************************************************************************
功能说明：与客户端的applyId向对应
流程如下：
1.client send apply
2.server send reapply
3.client send start
4.server produce a userno, then send to client
5.client produce Userinfo, then send to server
6.server save Userinfo to file
then apply over
参数说明：
	输入参数：无
	输出参数：无
	返回：无
***************************************************************************************************/
//anser for the cclientsocket applyId()
int SClientSocket::applyId()
{
	char src[] = {"999999"};
	char dest[] = {"000000"};
	char cmd[15] = {"re-apply"};

	int flag = 1;
	//statge 2
	Message *ms = ms_init(dest, src, cmd);
	sendMessage(ms);
	ms_exit(ms);

	//statge 3
	ms = ms_init(NULL, NULL, NULL);
	recvMessage(ms);

	//检测收到的消息是否是结束消息
	isClientExit(ms);

	if( strcmp(ms_get_info(ms), "start") ){
			//wrong
			ms_exit(ms);
			return -1;
	}


	//stage 4
	char userno[7] = {0};
	int i = 0;

	for(i = 0; i < 10; i++)
	{
		produceUserno(userno);

		char filename[30] = "../server_data/";
		strcat(filename, src);

		if( ! File::exists((const char *)filename) )
		{
			break;
		}
	}

	if(i == 10)
	{
		//产生了10个随机账号，都已经被占用了，请稍后再试
		char info[] = "\nAccounts may be have distribution over, please try again later. \nOr connect with the administrator!\nemaile:changqing.1230@163.mail\n";
		ms = ms_init(dest, src, info);
		sendMessage(ms);
		ms_exit(ms);
		return 0;
	}
	ms = ms_init(dest, src, userno);
	sendMessage(ms);
	ms_exit(ms);

	//statge 5
	ms = ms_init(NULL, NULL, NULL);
	recvMessage(ms);
	//检测收到的消息是否是结束消息
	isClientExit(ms);

	char *info = ms_get_info(ms);
	Userinfo *uf = userinfo_init();

	memcpy(uf, info, sizeof(Userinfo));
	printf("recv userinfo over! \nuserno:%s \npasswd:%s \nname:%s\nemaile:%s\n",
		uf->userno, uf->passwd, uf->name, uf->emaile);

	//statge 6
	char filename[50] = SERVERDATA_PATH;
	strcat(filename, userno);

	File *file = new File(filename);
	file->writeBuffer(info, sizeof(Userinfo));
	delete file;

	userinfo_exit(uf);
	ms_exit(ms);
	return 0;
}

/***************************************************************************************************
功能说明：用户登录
stage		对应动作
1			client发送login
2			server send re-login
3			client send userno + passwd
4			user check userno & passwd
			(如果用户已经登录，则给原来登录的IP地址发送“在异地登录”消息，然后让原来的那个断开服务器)
5			server send login-success | login-failed
如果login-failed，login结束
如果login-success
6			server send userinfo & friendlist
7			over
参数说明：
	输入参数：无
	输出参数：无
	返回：无
***************************************************************************************************/
int SClientSocket::login()
{
	char src[7] = {"999999"};
	char passwd[256] = {0};
	char dest[7] = {"000000"};
	char cmd[15] = {"re-login"};

	//statge 2
	Message *ms = ms_init(dest, src, cmd);
	sendMessage(ms);
	ms_exit(ms);

	ms = ms_init(NULL, NULL, NULL);
	recvMessage(ms);

	//检测收到的消息是否是结束消息
	isClientExit(ms);

	memcpy(src, ms->data + USERNO_LEN, 6);
	src[6] = '\0';

	strcpy(passwd, ms_get_info(ms));
	ms_exit(ms);

	/**
	查看server存的文件中是否有该用户，并且用户与密码是否匹配
	**/
	char filename[30] = "../server_data/";
	strcat(filename, src);

	if( File::exists((const char *)filename) )
	{
		if(File::match((const char *)filename, passwd))
		{

			//检查该userno是否已经在线,如果在线则发送“您的账号在另外一个地方被第二次登陆，您被迫下线!"
			SClientSocket *scs = NULL;
			scs = g_ss->clientList->searchClient(src);
			if(scs)
			{
				strcpy(dest, "000000");
				strcpy(src, "999999");
				char *relogin_info = (char *)"Your account in another place was second loginning, you are forced to logout!";

				Message *relogin_ms = ms_init(dest, src, relogin_info);
				scs->sendMessage(relogin_ms);
				ms_exit(relogin_ms);

				//到此客户端应该已经结束，为确保客户端已经结束，再次发送一个信息，让它结束
				//发送此消息确认让客户端结束
				relogin_ms = ms_init(NULL, NULL, NULL);
				relogin_ms->data[0] = '\0';
				scs->sendMessage(relogin_ms);
				ms_exit(relogin_ms);

				/*

				scs->isRun = false;
				pthread_t pid = scs->getPthread();
				scs->setPthread(0);
				cout<<"\nsclientsocket::login()one client is knick off\n\t"<<getAddr()<<" : "<<getPort()<<endl;

				//g_ss->clientList->deleteClient(scs);
				//scs->exit();
				*/
			}


			//login success
			strcpy(passwd, "login_success");

			strcpy(dest, "000000");
			strcpy(src, "999999");

			ms = ms_init(dest, src, passwd);
			sendMessage(ms);
			ms_exit(ms);

			File *file = new File(filename);
			char *buffer = new char[sizeof(Userinfo)];
			file->readBuffer(buffer, sizeof(Userinfo));

			userinfo = userinfo_init();
			memcpy(userinfo, buffer, sizeof(Userinfo));

			//send userinfo
			ms = ms_init(dest, src, NULL);
			memcpy(ms->data + 2*USERNO_LEN, buffer, sizeof(Userinfo));
			sendMessage(ms);
			ms_exit(ms);
			delete []buffer;
			userStatus = 1;

			//get friendlist from file to fls
			//buffer 大小为1024，所以每次最多送1014 / sizeof(Friend) = 15个
			//ms->data[0]用来存放一次发送的friend的个数加1
			cout<<"\nsend userinfo over\nsend friendlist\n"<<endl;
			fls = friendlist_init();

			int friend_size = sizeof(Friend);
			int friend_num = 0;
			Friend *tmp = NULL;
			char *friendlist_info = new char[1024];
			memset(friendlist_info, 0, 1024);
			buffer = new char[friend_size];
			friend_num = 0;
			while(friend_size == file->readBuffer(buffer, friend_size))
			{
				tmp = (Friend*)malloc(friend_size);
				memcpy(tmp, buffer, friend_size);
				friendlist_add(fls, tmp);

				//then send friendlist to client
				memcpy(friendlist_info + friend_num * friend_size, buffer, friend_size);
				friend_num++;

				if(friend_num == 1024 / friend_size)
				{
					ms = ms_init(dest, src, NULL);
					memcpy(ms->data + 2*USERNO_LEN, friendlist_info, 1012);
					ms->data[1] = friend_num + 1;
					sendMessage(ms);
					ms_exit(ms);
					friend_num = 0;
					memset(friendlist_info, 0, 1024);
				}
			}

			ms = ms_init(dest, src, NULL);
			memcpy(ms->data + 2*USERNO_LEN, friendlist_info, 1012);
			ms->data[1] = friend_num + 1;

			sendMessage(ms);
			ms_exit(ms);

			delete []friendlist_info;
			delete []buffer;
			delete file;

			cout<<"login\t"<<userinfo->userno<<endl;
			recvUnrecvMessage();
			return 1;
		}else{
			//not matched
			strcpy(passwd, "login_failed : userno and password not matched!");
		}
	}else{
		strcpy(passwd, "login_failed : no such userno!");
	}

	//login error;
	strcpy(dest, "000000");
	strcpy(src, "999999");

	ms = ms_init(dest, src, passwd);
	sendMessage(ms);
	ms_exit(ms);

	return 0;
}


/***************************************************************************************************
功能说明：用户修改个人信息模块
1		client send modify
2		server send re-modify
3		server send userinfo
4		client modify it or not
5		client send userinfo
6		over
参数说明：
	输入参数：无
	输出参数：无
	返回：无
***************************************************************************************************/
void SClientSocket::modify()
{
	char src[7] = {"999999"};
	char dest[7] = {"000000"};
	char cmd[15] = {"re-modify"};


	//stage 2
	Message *ms = ms_init(dest, src, cmd);
	sendMessage(ms);
	ms_exit(ms);

	//stage 3
	ms = ms_init(dest, src, NULL);
	memcpy(ms->data + 2 *USERNO_LEN, userinfo, sizeof(Userinfo));

	sendMessage(ms);
	ms_exit(ms);

	//stage 5
	ms = ms_init(NULL, NULL, NULL);
	recvMessage(ms);
	//检测收到的消息是否是结束消息
	isClientExit(ms);

	char *buffer = new char[sizeof(Userinfo)];
	memcpy(buffer, ms->data + 2 * USERNO_LEN, sizeof(Userinfo));

	//把当前的userinfo替换成新的userinfo
	memcpy(userinfo, buffer, sizeof(Userinfo));

	char filename[30];
	memset(filename, 0, 30);
	sprintf(filename, "../server_data/%s", userinfo->userno);

	File *file = new File(filename);
	file->writeBuffer(buffer, sizeof(Userinfo));
	delete file;

	delete []buffer;

	cout<<"modify over"<<endl;
}


/***************************************************************************************************
功能说明：
参数说明：
	输入参数：无
	输出参数：无
	返回：无
***************************************************************************************************/
int SClientSocket::disCon()
{
}

/***************************************************************************************************
功能说明：把当前消息转给serversocket，让serversocket查询clientlist，然后处理
参数说明：
	输入参数：无
	输出参数：无
	返回：无
***************************************************************************************************/
void SClientSocket::talk(Message *ms)
{
	//检查消息的dest是否有效，如果无效，发送该用户不在线
	char dest_userno[7];

	memcpy(dest_userno, ms->data, 6);
	dest_userno[6] = 0;

	char filename[30];
	memset(filename, 0, 30);
	sprintf(filename, "../server_data/%s", dest_userno);

	if( !File::exists( (const char *)filename ) )
	{
		Message *re_ms = ms_init(ms_get_src(ms), (char *)"999999", (char *)"send message error: no such user!" );
		sendMessage(re_ms);
		ms_exit(re_ms);
		return;
	}

	if(g_ss)
		g_ss->talk(this, ms);
	else
		cout<<"\n\n!!!error! please restart server!\n\n"<<endl;
}

/***************************************************************************************************
功能说明：
参数说明：把当前消息转给serversocket，让serversocket查询clientlist，然后处理
	输入参数：无
	输出参数：无
	返回：无
***************************************************************************************************/
void SClientSocket::recvUnrecvMessage()
{
	if(g_ss)
		g_ss->sendUnsendMessage(this);
	else
		cout<<"\n\n!!!error! please restart server!\n\n"<<endl;
}
/***************************************************************************************************
功能说明：
参数说明：
	输入参数：无
	输出参数：无
	返回：无
***************************************************************************************************/
bool SClientSocket::saveUserinfoToFile()
{
	cout<<"sclientsocket::saveuserinfoTofile()"<<endl;
	if(userinfo != NULL)
	{
		char filename[50] = SERVERDATA_PATH;
		strcat(filename, userinfo->userno);

		if( File::exists((const char *)filename) )
		{
			File *file = new File(filename);
			file->toStart();
			char *buffer = new char[sizeof(Userinfo)];
			memcpy(buffer, userinfo, sizeof(Userinfo));
			file->writeBuffer(buffer, sizeof(Userinfo));
			delete []buffer;
			buffer = NULL;

			//把friendlist写入文件
			if(fls && fls->head)
			{
				Friend *tmp = fls->head;
				for(;tmp != NULL; tmp = tmp->next)
				{
					file->writeBuffer((char *)tmp, sizeof(Friend));
				}
				cout<<"write friendlist to file"<<endl;
			}
			file->trunc();
			delete file;
			file = NULL;
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
void SClientSocket::show()
{
	cout<<right<<setw(15)<<getAddr()<<" : "<<left<<getPort();
	if(userStatus)
	{
		cout<<right<<setw(10)<<userinfo->userno<<"   "<<left<<setw(20)<<userinfo->username<<'\t';
		switch(userStatus)
		{
			case 1:
				cout<<"online"<<endl;
				break;
			case 2:
				cout<<"busy"<<endl;
				break;
			case 3:
				cout<<"yinshen"<<endl;
				break;
			case 4:
				cout<<"offline"<<endl;
				break;
			default:
				cout<<"nostatus"<<endl;
		}
	}
	cout<<endl;
}


/***************************************************************************************************
功能说明：随机产生六个数（0-9）
参数说明：
	输入参数：无
	输出参数：无
	返回：无
***************************************************************************************************/
void SClientSocket::produceUserno(char *buf)
{
	char i = 0;
	srand((unsigned)time(NULL));
	for(; i < 6; i++)
		buf[i] = '0' + rand() % 9;

	buf[i] = 0;
}

/***************************************************************************************************
功能说明：检测收到的消息是否是结束消息
		  如果是结束消息，终止该sclientsocket的运行
		  然后再serversocket的clientlist中移除。
参数说明：
	输入参数：Message *ms
	输出参数：无
	返回：无
***************************************************************************************************/
void SClientSocket::isClientExit(Message *ms)
{
	if(ms->data[0] == 0)
	{
		//该消息时TCP结束消息
		isRun = false;
		ms_exit(ms);
		cout<<"\none client exit\n\t"<<getAddr()<<" : "<<getPort()<<endl;
		g_ss->clientList->deleteClient(this);
		this->exit();
	}
}