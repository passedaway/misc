/******************************************************************************/
/*    Filename: cclientsocket.h                                               */
/*    Description: client clientsocket, externed form                         */
/*                                                                            */
/*    Author:zhaocq (changqing.1230@163.com)  2010/11/30                      */
/******************************************************************************/
#include "cclientsocket.h"
#include "message.h"
#include "define.h"
#include "userinfo.h"
#include "friendlist.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <pthread.h>

#define MAXSLEEP 128
/*****************************************gloable variable******************************************/
int g_c_client_socket_fd;

Userinfo *user;
FriendList *fls;
	//0 unlogin
	//1 online
	//2 busy
	//3 (yinshen)
	//4 offline
int userStatus;


pthread_t	n_pid, l_pid;

/***************************************local variable*********************************************/
	//control the action, just use for the runNet and runHost
	//to diff the cmd, or the message
	//-1:cmd
	//0:loginning...
	//1:login success
	//2:apply Id
static int loginFlag = -1;
//1 run
// 0 pause
static int is_run_local;
static int is_run_net;

/*
login_status	说明
0				输入用户名和密码
1				用户名和密码错误，重新输入
*/
static int login_status = 0;

/***********************************************local function**************************************/
static int c_analyse_message(Message *ms);
static int c_apply_id();
static int c_dis_connect();
static int c_talk();
static int c_login();
static void c_modify_userinfo();
static int c_analyse_cmd(Message *ms);

static void c_run_net();
static void c_run_local();

static int c_send_message_to_server(char *ms);
static void c_is_ms_exit(Message *ms);
//000000:self
//999999:server
/***************************************************************************************************
功能说明：客户端套接字初始化
参数说明：
	输入参数：ip地址，端口号
	输出参数：无
	返回：无
***************************************************************************************************/
void c_client_socket_init(char *addr, int port)
{
	struct sockaddr_in serveraddr;
	int  nsec = 0;

	//init user and fls
	user = NULL;
	fls = NULL;

	//init net pid and local pid
	n_pid = l_pid = 0;

	memset(&serveraddr, 0, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	inet_pton(AF_INET, addr, &serveraddr.sin_addr);
	serveraddr.sin_port = htons(port);

	g_c_client_socket_fd = socket(AF_INET, SOCK_STREAM, 0);

	//connect with the server use the Exponential Backoff(zhishu buchang)
	for(nsec = 1; nsec <= MAXSLEEP; nsec <<= 1)
	{
		if( connect(g_c_client_socket_fd, (struct sockaddr *)&serveraddr, sizeof(serveraddr)) == 0)
		{
			fprintf(stdout, "\nconnect with the server ( %s ) success!\n", addr);
			fflush(stdout);
			return;
		}
		if(nsec <= MAXSLEEP/2)
		{
			fprintf(stdout, ".");
			fflush(stdout);
			sleep(nsec);
		}
	}

	close(g_c_client_socket_fd);
	printf(" conn't connected with the server!\n");
	exit(0);
}

/***************************************************************************************************
功能说明：客户端套接字去初始化
参数说明：
	输入参数：
	输出参数：无
	返回：无
***************************************************************************************************/
void c_client_socket_exit()
{
	if(g_c_client_socket_fd)
		close(g_c_client_socket_fd);

	if(user)
		userinfo_exit(user);

	if(fls)
		friendlist_exit(fls);

	exit(0);
}

/***************************************************************************************************
功能说明：客户端启动两个线程（local，net）
参数说明：
	输入参数：
	输出参数：无
	返回：无
***************************************************************************************************/
void c_start_thread()
{
	if(n_pid == 0 && l_pid == 0)
	{
		is_run_local = 1;
		is_run_net = 1;
		pthread_create(&n_pid, NULL, (void *)c_run_net, 0);
		pthread_create(&l_pid, NULL, (void*)c_run_local, 0);
	}else {
		printf("Warning : thread already start,cannot start again!\n");
	}
}

/***************************************************************************************************
功能说明：join
参数说明：
	输入参数：
		1 join host
		2 join net
	输出参数：无
	返回：无
***************************************************************************************************/
void c_join(int op)
{
	pthread_t join_pid = 0;

	if(op == HOST_THREAD)
		join_pid = l_pid;
	else if(op == NET_THREAD)
		join_pid = n_pid;
	else
	{
		printf("Warning : join thread failed! not host, not net\n");
		return;
	}

	pthread_join(join_pid, NULL);
}

/*****************************************local function*******************************************/
/*****************************************locol function ******************************************/
/***************************************************************************************************
功能说明：客户端分析消息(来自网络)
参数说明：
	输入参数：消息的地址
	输出参数：无
	返回：无
***************************************************************************************************/
int c_analyse_message(Message *ms)
{
	char dest[7] = {0};
	char src[7] = {0};
	char *info;

	c_is_ms_exit(ms);

	memcpy(dest, ms->data, 6);
	dest[6] = 0;
	memcpy(src, ms->data + USERNO_LEN, 6);
	src[6] = 0;

	info = ms_get_info(ms);

	c_is_ms_exit(ms);

	if( strncmp(src, "999999", 6) == 0)
	{
    	if(	strncmp(info, "re-login", strlen("re-login")) == 0 )
    	{
    		c_login();
    		is_run_local = 1;
    	}

    	if( strcmp(info, "re-apply") == 0 )
    	{
    		//apply id stage 2
    		c_apply_id();
    		is_run_local = 1;
    	}

		if( !strcmp(info, "re-modify") )
		{
    		c_modify_userinfo();
    		is_run_local = 1;
    	}

    	if( !strncmp(info, "add+", 4))
    	{

    		//接收到添加好友请求
    		char a_userno[7];
    		char b_nickname[64];
    		char a_nickname[64];
			char choice = '0';
			char req_info[256];
			Message *req_ms = NULL;


			is_run_local = 0;

    		memcpy(a_userno, info + 4, 6);
    		a_userno[6] = 0;

			memset(b_nickname, 0, 64);
			memcpy(b_nickname, info + 11, 64);

    		req_ms = ms_init("999999", user->userno, NULL);

			do{
				printf("accept one friend(%s) requeset.\tagree(Y)/disagree(n)?", a_userno);
				fflush(stdout);
				scanf("%c", &choice);

    			if(choice == 'Y' || choice == 'y')
    			{
    				memset(a_nickname, 0, 64);
    				memset(req_info, 0, 256);

    				printf("input the nickname you want to set:\n");
    				scanf("%s", a_nickname);

    				strcpy(req_info, "add_agree+");
    				strcpy(req_info+10, a_userno);
    				req_info[10+6] = '+';
    				memcpy(req_info+17, b_nickname, 64);
    				req_info[17+64] = '+';
    				memcpy(req_info+17+65, a_nickname, 64);

    				printf("\nreq_info : %s\n", req_info);

    				memcpy(req_ms->data+2*USERNO_LEN, req_info, 256);
    			}

    			if( choice == 'n' || choice == 'N')
    			{
    				memset(req_info, 0, 256);
    				sprintf(req_info, "add_disagree+%s", a_userno);
    				memcpy(req_ms->data+2*USERNO_LEN, req_info, strlen(req_info));
    			}

    		}while(choice != 'Y' && choice != 'y' && choice != 'N' && choice != 'n');

    		ms_send_message(g_c_client_socket_fd, req_ms);

    		ms_exit(req_ms);

    		is_run_local = 1;
    	}

    	if( !strncmp(info, "add_", 4))
    	{
    		//添加好友结果
    		//1.add_agree
    		is_run_local = 0;

    		if( !strncmp(info, "add_agree", 7) )
    		{
    			char a_userno[7];
    			char a_nickname[64];
    			char b_nickname[64];
    			Friend *fr = NULL;

    			memset(a_nickname, 0, 64);
    			memset(b_nickname, 0, 64);

    			sscanf(info, "add_agree+%s+%s+%s", a_userno, b_nickname, a_nickname);

    			memcpy(a_userno, info+strlen("add_agree+"), 6);
    			a_userno[6] = 0;

    			memcpy(b_nickname, info+strlen("add_agree+") + 7, 64);

				fr = (Friend *)malloc(sizeof(Friend));
				memset(fr, 0, sizeof(Friend));
				memcpy(fr->userno, a_userno, 6);
				memcpy(fr->nickname, b_nickname, 64);

				if(fls)
					fls = friendlist_init();

				friendlist_add(fls, fr);


				printf("\nWARNING:\n\t%s is agree your friend-request!\n\n", a_userno);
    		}

    		//2.add_disagree
    		if( !strncmp(info, "add_disagree", 7) )
    		{
    			char a_userno[7];
    			memset(a_userno, 0, 7);

    			sscanf(info, "add_disagree+%s", a_userno);
    			printf("\nWARNING:\n\t%s is not agree your friend-request!\n\n", a_userno);
    		}

    		//3.add_error
    		if( !strncmp(info, "add_error", 7) )
    		{
    			char a_userno[7];
    			memset(a_userno, 0, 7);

    			sscanf(info, "add_errore+%s", a_userno);
    			printf("\nWARNING:\n\tfriend-request %s error!\n\t%s\n\n", a_userno, info+strlen("add_error+000000"));

    		}

    		is_run_local = 1;

    	}

    	if( !strncmp(info, "Your account in another place was second loginning, you are forced to logout!", 10) )
    	{
	    	printf("\n\nWARNING:\n\t%s", info);
	    	printf("\n\nplease restart the program, then re-login!\n\n");
	    	is_run_net = 0;
			is_run_local = 0;
			//client exit
			c_client_socket_exit();
    	}

    	printf("\nreceve message from server\n\t%s\n", info);

		return 0;
	}

	printf("\nreceve one message\n\tsrc:%s\n\tmessage:%s\n", src, info);

	return 0;
}

/***************************************************************************************************
功能说明：客户端分析命令，从控制台接受
参数说明：
	输入参数：消息的地址
	输出参数：无
	返回：无
***************************************************************************************************/
static int c_analyse_cmd(Message *ms)
{
	char *cmd = NULL;
	cmd = ms_get_cmd(ms);
	printf("cmd : %s\n", cmd);

	if(loginFlag == -1)
	{
    	if(strncmp(cmd, "exit", ms->info_length) == 0 ){
    		printf("\nexit\n");
    		c_client_socket_exit();
    	}else if(strncmp(cmd, "login", ms->info_length) == 0){
    		printf("\nlogin\n");
    		c_send_message_to_server("login");
    		is_run_local = 0;
    	}else if(strncmp(cmd, "apply", ms->info_length) == 0){
    		printf("\napply id\n");
    		//apply statge 1
    		c_send_message_to_server("apply");
    		is_run_local = 0;
    	}else{
    		printf("\nunregconised commond!\ncomond:\n\texit\n\tlogin\n\tapply\n\t\tTry again!\n");
    	}

    	return 0;
    }

    if(loginFlag == 1)
    {
    	//talk();
    	char dest[7];
    	memcpy(dest, ms->data, 6);
    	dest[6] = '\0';

    	if(!strncmp(dest, "999999", 6))
    	{
    		if( !strncmp(ms_get_info(ms), "modify", 6) )
    		{
    			//modify
    			c_send_message_to_server("modify");
    			is_run_local = 0;
    			return 0;
    		}

    		if( !strncmp(ms_get_info(ms), "add", 3) )
    		{
    			//add friend by userno
    			char userno[20];
    			char nickname[64];
    			char info[100];

    			memset(info, 0, 100);
    			Message *add_ms;

    			printf("\nadd friend by userno:\n");
    			do{
    				memset(userno, 0, 20);
    				memset(nickname, 0, 64);
    				printf("\tinput userno:");
    				scanf("%s", userno);
    				printf("\tinput friend nickname:");
    				scanf("%s", nickname);
    			}while( !userinfo_checkUserno(userno) );

				//add+friend_userno+friend_nickname
    			sprintf(info, "add+%s+%s", userno, nickname);

				printf("\ninfo : %s\n", info);
				c_send_message_to_server(info);

				return 0;
    		}

    	}else if( !strncmp(dest, user->userno, 6) ){
    		printf("WARNING: \n\tthis destnation of this message is yourself!\n\tCannot send this message!\n\n");
    		return 0;
    	}

    	printf("\ndest = %s\ninfo = %s\n", dest, ms_get_info(ms));
    	printf("\nms->data:%s\n", ms->data);
    	ms_send_message(g_c_client_socket_fd, ms);
    }

	return 0;
}

/***************************************************************************************************
功能说明：客户端处理申请账号模块,与服务器端协调工作
参数说明：
1.client send apply
2.server send reapply
3.client send start
4.server produce a userno, then send to client
5.client produce Userinfo, then send to server
6.server save Userinfo to file
then apply over
	输入参数：
	输出参数：无
	返回：无
***************************************************************************************************/
int c_apply_id()
{
	Message *ms = NULL;
	char *src = NULL, *dest = NULL, *info = NULL;
	char userno[7] = {0};
	char username[50];
	char name[50];
	char passwd[50];
	char passwd_bak[50];
	char sex[20];
	char emaile[50];
	Userinfo *user = NULL;
	int flag = 1;

	printf("in applyId()\n");
	//statge 3
	c_send_message_to_server("start");

	printf("wait server answer...");

	//statge 4
	ms = ms_init(src, dest, info);
	ms_recv_message(g_c_client_socket_fd, ms);
	c_is_ms_exit(ms);

	strcpy(userno, ms_get_info(ms));
	ms_exit(ms);

	if( !userinfo_checkUserno(userno) )
		printf("\n\t apply id wrong!Try again!\n userno : %s\n\n", userno);

	printf("\n\tYou userno is : %s\nplease Fill the Infomation\n", userno);

	//statge 5
	printf("\ninput username:");
	scanf("%s", username);

	do
	{
		memset(passwd, 0, 50);
    	memset(passwd_bak, 0, 50);

    	printf("\ninput password:");
    	scanf("%s", passwd);
    	printf("\ninput password again:");
    	scanf("%s", passwd_bak);

    	if(!strcmp(passwd, passwd_bak))
    	{
    		if(userinfo_checkPasswd(passwd))
    		{
    			flag = 0;
    			break;
    		}else{
    			printf("\npassword length %d - %d! Input again\n", PASSWD_MIN_LEN, PASSWD_MAX_LEN);
    			continue;
    		}
    	}

    	printf("\nThe two password input didnot same!Input again!\n");
    }while(flag);

	do{
		memset(sex, 0, 20);
		printf("\ninput sex(male or female):");
		scanf("%s", sex);
	}while( !userinfo_checkSex(sex) );

	do{
		printf("\ninput emaile:");
		scanf("%s", emaile);
	}while( !userinfo_checkEmaile(emaile) );

	printf("\ninput you name:");
	scanf("%s", name);

	user = userinfo_init();
	userinfo_ioctl(user, SET_USERNO, (void*)userno);
	userinfo_ioctl(user, SET_USERNAME, (void*)username);
	userinfo_ioctl(user, SET_PASSWD, (void*)passwd);
	userinfo_ioctl(user, SET_NAME, (void*)name);
	userinfo_ioctl(user, SET_SEX,  (void*)sex);
	userinfo_ioctl(user, SET_EMAILE, (void*)emaile);

	ms = ms_init("999999", "000000", NULL);
	memcpy(ms->data+2*USERNO_LEN, user,  sizeof(Userinfo));

	ms_send_message(g_c_client_socket_fd, ms);

	printf("\nuser apply success!\n \tuserno:%s \n\tpasswd:%s \n\tusername : %s\n\tsex:%s\n\tname:%s\n\temaile:%s\n\n",
		user->userno, user->passwd, user->username, user->sex, user->name, user->emaile);

	printf("\nyou can use the accounts to login.or for other command!\n");

	ms_exit(ms);

	return 1;
}


/***************************************************************************************************
功能说明：客户端与服务器断开连接
参数说明：
	输入参数：
	输出参数：无
	返回：无
***************************************************************************************************/
int c_dis_connect()
{
}


/***************************************************************************************************
功能说明：客户端聊天功能
参数说明：
	输入参数：
	输出参数：无
	返回：无
***************************************************************************************************/
int c_talk()
{
}

/***************************************************************************************************
功能说明：客户端修改个人信息模块
参数说明：
	输入参数：
	输出参数：无
	返回：无
***************************************************************************************************/
void c_modify_userinfo()
{
	char *buffer;
	char choice = '0';
	Message *ms = NULL;
	Userinfo *uf = userinfo_init();

	//statge 3 recv userinfo from server
	ms = ms_init(NULL, NULL, NULL);
	ms_recv_message(g_c_client_socket_fd, ms);
	c_is_ms_exit(ms);

	memcpy(uf, ms_get_info(ms), sizeof(Userinfo));

	printf("\tuserno : %s\n", uf->userno);

	//modify passwd
	do{
		getchar();
		printf("passwd : %s\tmodify?Y/n", uf->passwd);
		scanf("%c", &choice);


		if(choice == 'Y' || choice == 'y')
		{
			char passwd[50];
			char passwd_bak[50];

			memset(passwd, 0, 50);
			memset(passwd_bak, 0, 50);

			printf("\tnew passwd:");
			scanf("%s", passwd);
			printf("\tnew passwd again:");
			scanf("%s", passwd_bak);

			if(!userinfo_checkPasswd(passwd) || strcmp(passwd, passwd_bak) )
				choice = '0';
			else{
				strcpy(uf->passwd, passwd);
			}
		}
	}while(choice != 'Y' && choice != 'y' && choice != 'N' && choice != 'n');

	//modify username
	do{
		getchar();
		printf("username : %s\tmodify?Y/n", uf->username);
		scanf("%c", &choice);

		if(choice == 'Y' || choice == 'y')
		{
			char username[50];
			printf("\tnew username:");
			scanf("%s", username);

			strcpy(uf->username, username);
		}
	}while(choice != 'Y' && choice != 'y' && choice != 'N' && choice != 'n');

	//name
	do{
		getchar();
		printf("name : %s\tmodify?Y/n", uf->name);
		scanf("%c", &choice);

		if(choice == 'Y' || choice == 'y')
		{
			char name[60];
			printf("\tnew name:");
			scanf("%s", name);

			strcpy(uf->name, name);
		}
	}while(choice != 'Y' && choice != 'y' && choice != 'N' && choice != 'n');

	//modify sex
	do{
		getchar();
		printf("sex : %s\tmodify?Y/n", uf->sex);
		scanf("%c", &choice);

		if(choice == 'Y' || choice == 'y')
		{
			char sex[20];
			printf("\tnew sex(male or female):");
			scanf("%s", sex);
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
		getchar();
		printf("emaile : %s\tmodify?Y/n", uf->emaile);
		scanf("%c", &choice);

		if(choice == 'Y' || choice == 'y')
		{
			char emaile[50];
			printf("\tnew emaile:");
			scanf("%s", emaile);
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
		getchar();
		printf("\tcommit?Y/n");
		scanf("%c", &choice);

		ms = ms_init("999999", "000000", NULL);

		if(choice == 'y' || choice == 'Y')
		{
			memcpy(ms->data + 2*USERNO_LEN, (char *)uf, sizeof(Userinfo) );
		}else if(choice == 'n' || choice == 'N'){
			memcpy(ms->data + 2*USERNO_LEN, (char *)user, sizeof(Userinfo) );
		}
	}while(choice != 'Y' && choice != 'y' && choice != 'N' && choice != 'n');

	printf("send userinfo:ms :%s", ms->data);
	ms_send_message(g_c_client_socket_fd, ms);
	ms_exit(ms);
}

/***************************************************************************************************
功能说明：客户端登陆模块
参数说明：
	输入参数：
	输出参数：无
	返回：无
***************************************************************************************************/
int c_login()
{
	int flag = 1, i = 0;
	char src[20] = {0};
	char dest[] = {"999999"};
	char info[80] = {0};
	Message *ms ;

	int friend_num = 0;
	Friend *friend_tmp = NULL;

	printf("c_login in\n");

	do{
    	memset(src, 0, 20);
    	memset(info, 0, 80);

    	printf("login\n\tuserno:");
    	scanf("%s", src);
    	printf("\tpasswd:");
    	scanf("%s", info);

    	for(i = 0; i < strlen(info); i++)
    		printf("\b%c", '*');

    	for(i = 0; i < 6; i++)
    		if(src[i] <'0' || src[i] >'9')
    			break;

    	if(i != 6)
    	{
    		printf("\nuserno not format!please check and input again!\n");
    		continue;
    	}

    	for(i = 0; i< 30; i++)
    		if(info[i] == '\0')
    			break;

    	if( i == 0 || i == 30)
    	{
    		printf("\npassword not format!\n");
    		continue;
    	}

    	flag = 0;

	}while(flag);

	ms = ms_init(dest, src, info);
	ms_send_message(g_c_client_socket_fd, ms);
	printf("ms->data : %s\n", ms->data);
	ms_exit(ms);

	ms = ms_init(NULL, NULL, NULL);
	ms_recv_message(g_c_client_socket_fd, ms);
	c_is_ms_exit(ms);

	if( strncmp(ms_get_info(ms), "login_success", strlen("login_success")) == 0 )
	{
		loginFlag = 1;
		printf("\nlogin success\n");
		/*接受userinfo 信息*/

		ms_exit(ms);
		ms = ms_init(NULL, NULL, NULL);
		ms_recv_message(g_c_client_socket_fd, ms);
		c_is_ms_exit(ms);

		user = userinfo_init();
    	memcpy(user, ms->data + 2*USERNO_LEN, sizeof(Userinfo));
    	userStatus = 1;
    	ms_exit(ms);
    	loginFlag = 1;

    	//recv friendlist
    	printf("recv friendlist\n");
		fls = friendlist_init();

		do{
			ms = ms_init(NULL, NULL, NULL);
			ms_recv_message(g_c_client_socket_fd, ms);
			c_is_ms_exit(ms);

			friend_num = ms->data[1] - 1;
			printf("recv one times recvsize %d \n", friend_num);

			if(friend_num )
			{
				for(i = 0; i < friend_num; i++);
				{
            		friend_tmp = (Friend*)malloc(sizeof(Friend));
    				memcpy(friend_tmp, ms->data + 2 *USERNO_LEN + i * sizeof(Friend), sizeof(Friend));
    				friendlist_add(fls, friend_tmp);
				}
			}else{
				printf("no friend list\n");
				ms_exit(ms);
				break;
			}
		}while(friend_num == ( 1014 / sizeof(Friend) + 1));

    	printf("recv friendlist over\n");
    	return 1;
	}

	loginFlag = -1;
	printf("\nlogin failed!\n\t%s\ntry again\n", ms_get_info(ms));
	ms_exit(ms);

	printf("c_login out\n");
	return 1;
}


/***************************************************************************************************
功能说明：客户端网络线程函数
参数说明：
	输入参数：
	输出参数：无
	返回：无
***************************************************************************************************/
void c_run_net()
{
	Message *ms = NULL;
	while(1)
    	while(is_run_net)
    	{
    		ms =ms_init(NULL, NULL, NULL);

    		if(ms_recv_message(g_c_client_socket_fd, ms) == -1)
    		{
    			memset(ms->data, 0, 1024);
    			ms = ms_init("000000", "999999", "cmd_exit");
    			c_analyse_message(ms);
    			is_run_net = 0;
    			ms_exit(ms);

    			c_client_socket_exit();
    		}

    		c_analyse_message(ms);
    		ms_exit(ms);
    	}
}


/***************************************************************************************************
功能说明：客户端本地线程函数
参数说明：
	输入参数：
	输出参数：无
	返回：无
***************************************************************************************************/
void c_run_local()
{
	char info[1024];
	char src[20] = "000000";
	char dest[20] = "999999";
	char choice;
	Message *ms ;

	while(1)
      	while(is_run_local)
    	{
    		getchar();
    		memset(src, 0, 20);
    		memset(dest, 0, 6);
    		memset(info, 0, 1024);

    		if(loginFlag == -1)
    		{
    			printf("input command:\n");
    			scanf("%s", info);
    			strncpy(dest, "000000", 6);
    		}else if(loginFlag == 1)
    		{
    			do
    			{
    				getchar();
    				printf("\tinput choice:\n\t1.command;\n\t2.talk with friend\n\t3.add friend by userno\n\t4.modify userno infomatin\n");
    				scanf("%c", &choice);
    				switch(choice)
    				{
    					case '1':
    						printf("input Command:");
    						scanf("%s",info);
    						strncpy(dest, "000000", 6);
    						break;
    					case '2':
    						printf("input friend number:");
    						scanf("%s", dest);
    						printf("input info:");
    						scanf("%s", info);
    						break;
    					case '3':
    						//add friend
    						strncpy(dest, "999999", 6);
    						strcpy(info, "add");
    						break;
    					case '4':
    						//modify user infomation
    						strncpy(dest, "999999", 6);
    						strcpy(info, "modify");
    						break;
    					default:
    						printf("Error: cannot regconise command!");
    				}

    			}while(choice < '1' || choice > '4');
    		}

			if(loginFlag == 1)
				strcpy(src, user->userno);
			else
				strcpy(src, "000000");

    		ms = ms_init(dest, src, info);

    		c_analyse_cmd(ms);

    		ms_exit(ms);

			printf("\npress ENTER key to continue...\n");
    		getchar();
    	}
}

/***************************************************************************************************
功能说明：客户端发送消息到服务器，dest为“999999”，src位“000000”
参数说明：
	输入参数：发送的消息
	输出参数：无
	返回：无
***************************************************************************************************/
int c_send_message_to_server(char *ms)
{
	if(g_c_client_socket_fd > 0 || ms == NULL)
	{
		Message *ms_s;

		if(user && user->userno)
			ms_s = ms_init("999999", user->userno, ms);
		else
			ms_s = ms_init("999999", "000000", ms);

		ms_send_message(g_c_client_socket_fd, ms_s);

		ms_exit(ms_s);

		return 1;
	}

	return 0;
}

/***************************************************************************************************
功能说明：客户端收到消息后，检查该消息是不是服务器发来的结束消息，如果是，结束程序运行并给出提示信息
参数说明：
	输入参数：收到的消息
	输出参数：无
	返回：无
***************************************************************************************************/
void c_is_ms_exit(Message *ms)
{
	if(ms == NULL)
		return;

	if(ms->data[0] == 0)
    {
 		ms_exit(ms);
 		printf("\n\tError : Sorry about this.\nThe Server has some exceptions, and disconnection to the client!\nPlease restart the client,and try agian!\n");
 		is_run_net = 0;
 		is_run_local = 0;
 		//client exit
 		c_client_socket_exit();
 	}
}