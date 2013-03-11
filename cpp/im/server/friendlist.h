/******************************************************************************/
/*    Filename: friendlist.h                                                  */
/*    Description: have the friend name, every sclientsocket has one firnelist*/
/*                                                                            */
/*    Author:zhaocq (changqing.1230@163.com)  2011/5/24                       */
/******************************************************************************/
#ifndef _FRIEND_LIST_H_
#define _FRIEND_LIST_H_

#ifdef __cplusplus
extern "C" {
#endif

typedef struct Friend{
	char userno[7];
	char nickname[64];
	struct Friend *next;
}Friend;

typedef struct{
	Friend *head;
	Friend *end;
}FriendList;

FriendList *friendlist_init();

void friendlist_exit(FriendList *flt);

int friendlist_add(FriendList *flt, Friend *fr);
int friendlsit_del(FriendList *flt, char *userno);

#ifdef __cplusplus
}
#endif
#endif