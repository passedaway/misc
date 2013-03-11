/******************************************************************************/
/*    Filename: message.c                                                                              */
/*    Description: implement the function of the message.h                           */
/*                                                                                                                  */
/*    Author:zhaocq (changqing.1230@163.com)  2010/11/30                        */
/******************************************************************************/
#include "message.h"
#include "define.h"

#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <arpa/inet.h>
#include <netdb.h>

/***************************************************************************************************
����˵��������Ϣ�л��src�ֶ�
����˵����
	�����������Ϣ�ĵ�ַ
	�����������
	���أ���Ϣ��src���׵�ַ
***************************************************************************************************/
char *ms_get_src(Message *ms)
{
	if(ms->data == NULL)
		return NULL;
	else
		return ms->data + USERNO_LEN;
}

/***************************************************************************************************
����˵��������Ϣ�л��dest�ֶ�
����˵����
	�����������Ϣ�ĵ�ַ
	�����������
	���أ���Ϣ��dest�ֶε��׵�ַ
***************************************************************************************************/
char *ms_get_dest(Message *ms)
{
	if(ms->data == NULL)
		return NULL;
	else
		return ms->data;
}

/***************************************************************************************************
����˵��������Ϣ�л��info�ֶ�
����˵����
	�����������Ϣ�ĵ�ַ
	�����������
	���أ���Ϣ��info�ֶε��׵�ַ
***************************************************************************************************/
char *ms_get_info(Message *ms)
{
	if(ms->data == NULL)
		return NULL;
	else
		return ms->data + 2*USERNO_LEN;
}

/***************************************************************************************************
����˵�������info�ֶεĳ���
����˵����
	�����������Ϣ�ĵ�ַ
	�����������
	���أ�info�ֶεĳ���
***************************************************************************************************/
int ms_get_info_length(Message *ms)
{
	return ms->info_length;
}

/***************************************************************************************************
����˵��������Ϣ�л��cmd����ʱinfo_length�ֶα�ʶ�ĳ�����cmd�ĳ��ȣ�
����˵����
	�����������Ϣ�ĵ�ַ
	�����������
	���أ���Ϣ��cmd���׵�ַ
***************************************************************************************************/
char *ms_get_cmd(Message *ms)
{
	if(ms->data == NULL)
		return NULL;
	else
		return ms->data + 2*USERNO_LEN;
}


/***************************************************************************************************
����˵������ʼ����Ϣ
����˵����
	���������dest��src��info
	�����������
	���أ���Ϣ�ĵ�ַ
***************************************************************************************************/
Message* ms_init(char *dest, char *src, char *info)
{
	Message *ms;

	ms = (Message *)malloc(sizeof(Message));
	memset(ms, 0, sizeof(Message));

	if(ms)
	{
		ms->data = (char *)malloc(sizeof(char) * 1024);

		memset(ms->data, 0, 1024);

		if(dest == NULL &&  src == NULL && info == NULL)
		{
			ms->info_length = -1;
			return ms;
		}

		if(ms->data)
		{
			if(dest)
				memcpy(ms->data, dest, USERNO_LEN);

			if(src)
				memcpy(ms->data+USERNO_LEN, src, USERNO_LEN);

			if(info)
			{
				ms->info_length = strlen(info);
				if(ms->info_length > 1024-2*USERNO_LEN-1)
					ms->info_length = 1024-2*USERNO_LEN;
				memcpy(ms->data+2*USERNO_LEN, info, ms->info_length + 1);
			}

			return ms;
		}
		//�����ڴ�δ�ɹ�data
		free(ms->data);
	}

	//�����ڴ�δ�ɹ�ms
	free(ms);
	return NULL;
}


/***************************************************************************************************
����˵����ȥ��ʼ����Ϣ
����˵����
	�����������Ϣ�ĵ�ַ
	�����������
	���أ���
***************************************************************************************************/
void ms_exit(Message *ms)
{
	if(ms)
	{
		if(ms->data)
			free(ms->data);

		free(ms);
		ms = NULL;
		return;
	}
	return;
}

/***************************************************************************************************
����˵����receve the message by the "fd"
����˵����
	�����������Ϣ�ĵ�ַ,fd
	�����������
	���أ�
***************************************************************************************************/
int ms_recv_message(int fd, Message *rms)
{
	if(fd)
		if(rms)
			return read(fd, rms->data, 1024);

	return -1;
}


/***************************************************************************************************
����˵����send message to the "fd"
����˵����
	�����������Ϣ�ĵ�ַ,fd
	�����������
	���أ�
***************************************************************************************************/
int ms_send_message(int fd, Message *wms)
{
	if(fd)
		if(wms)
			return send(fd, wms->data, 1024, 0);

	return -1;
}




int ms_send_message_to_server(int socket_fd, char *ms)
{
	if(socket_fd > 0 && ms != NULL)
	{
		Message *ms_s;

		ms_s = ms_init((char *)"999999", (char *)"000000", ms);

		ms_send_message(socket_fd, ms_s);

		ms_exit(ms_s);

		return 1;
	}

	return 0;
}


int ms_is_ms_exit(Message *ms)
{
	if(ms == NULL)
		return 0;

	if(ms->data[0] == 0)
	{
		return 1;
	}

	return 0;
}




int socket_close(int socket_fd)
{
	if(socket_fd)
		return close(socket_fd);
	else
		return 1;
}

int socket_connect(int fd, const struct sockaddr *serv_addr, socklen_t addrlen)
{
	return connect(fd, serv_addr, addrlen);
}

//success return fd
//error return 0
int socket_init(char *ipaddr, int port)
{
	struct sockaddr_in serveraddr;
	int  nsec = 0;
	int ret_fd = 0;

	memset(&serveraddr, 0, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	inet_pton(AF_INET, ipaddr, &serveraddr.sin_addr);
	serveraddr.sin_port = htons(port);

	ret_fd = socket(AF_INET, SOCK_STREAM, 0);

	//connect with the server use the Exponential Backoff(zhishu buchang)
	for(nsec = 1; nsec <= 4; nsec <<= 1)
	{
		if( connect(ret_fd, (struct sockaddr *)&serveraddr, sizeof(serveraddr)) == 0)
		{
			return ret_fd;
		}
		if(nsec <= 4/2)
		{
			sleep(nsec);
		}
	}

	close(ret_fd);
	ret_fd = 0;

	return ret_fd;
}
