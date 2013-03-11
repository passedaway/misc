/******************************************************************************/
/*    Filename: message.h                                                                              */
/*    Description:message type define, and function                                      */
/*                                                                                                                 */
/*    Author:zhaocq (changqing.1230@163.com)  2010/11/30                        */
/******************************************************************************/
#ifndef Message_H
#define Message_H

#ifndef MS_MESSAGE_LEN
#define MS_MESSAGE_LEN
#endif

typedef struct{
	char *data;
	int info_length;
}Message;

#ifdef __cplusplus
extern "C" {
#endif

char *ms_get_src(Message *ms);
char *ms_get_dest(Message *ms);
char *ms_get_info(Message *ms);
int ms_get_info_length(Message *ms);
char *ms_get_cmd(Message *ms);

//receve the message by the "fd"
int ms_recv_message(int fd, Message *rms);
//send message to the "fd"
int ms_send_message(int fd, Message *wms);

Message* ms_init(char *dest, char *src, char *info);

void ms_exit(Message *ms);

#ifdef __cplusplus
}
#endif

#endif
