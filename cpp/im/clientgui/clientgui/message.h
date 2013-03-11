/******************************************************************************/
/*    Filename: message.h                                                     */
/*    Description:message type define, and function                           */
/*                                                                            */
/*    Author:zhaocq (changqing.1230@163.com)  2010/11/30                      */
/******************************************************************************/
#ifndef Message_H
#define Message_H

#ifdef __cplusplus
extern "C"{
#endif

#include <sys/socket.h>
#include <sys/types.h>

typedef struct{
	char *data;
	int info_length;
}Message;

char *ms_get_src(Message *ms);
char *ms_get_dest(Message *ms);
char *ms_get_info(Message *ms);
int ms_get_info_length(Message *ms);
char *ms_get_cmd(Message *ms);

//receve the message by the "fd"
int ms_recv_message(int fd, Message *rms);
//send message to the "fd"
int ms_send_message(int fd, Message *wms);

int ms_send_message_to_server(int fd, char *ms);

int ms_is_ms_exit(Message *ms);

Message* ms_init(char *dest, char *src, char *info);

void ms_exit(Message *ms);

int socket_init(char *ipaddr, int port);
int socket_close(int socket_fd);
int socket_connect(int fd, const struct sockaddr, socklen_t addrlen);

#ifdef __cplusplus
}
#endif

#endif
