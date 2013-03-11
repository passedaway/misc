/******************************************************************************/
/*    Filename: unsendmessage.h                                               */
/*    Description: save the message which didnot send                         */
/*                                                                            */
/*    Author:zhaocq (changqing.1230@163.com)  2011/5/24                       */
/******************************************************************************/
#ifndef _UNSEND_MESSAGE_H_
#define _UNSEND_MESSAGE_H_

#include "message.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct UnsendMessage{
	Message *ms;
	struct UnsendMessage *next;
}UnsendMessage;

typedef struct{
	UnsendMessage *head;
	UnsendMessage *end;
}UnsendMessageList;

UnsendMessageList *usml_init();
void usml_exit(UnsendMessageList *usml);

int usml_add(UnsendMessageList *usml, UnsendMessage *usm);
int usml_del(UnsendMessageList *usml, UnsendMessage *usm);

UnsendMessage *usml_search_by_destuserno(UnsendMessageList *usml, char *userno);

#ifdef __cplusplus
}
#endif
#endif