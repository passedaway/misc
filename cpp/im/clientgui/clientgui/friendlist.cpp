/******************************************************************************/
/*    Filename: friendlist.cpp                                                */
/*    Description: have the friend name, every sclientsocket has one firnelist*/
/*                                                                            */
/*    Author:zhaocq (changqing.1230@163.com)  2011/5/24                       */
/******************************************************************************/
#include "friendlist.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/***************************************************************************************************
功能说明：初始化friendlist
参数说明：
	输入参数：无
	输出参数：无
	返回：friendlist
***************************************************************************************************/
FriendList* friendlist_init()
{
	FriendList *flt = (FriendList *)malloc(sizeof (FriendList));
	flt->head = NULL;
	flt->end = NULL;
	return flt;
}

/***************************************************************************************************
功能说明：去初始化friendlist
参数说明：
	输入参数：friendlist
	输出参数：无
	返回：无
***************************************************************************************************/
void friendlist_exit(FriendList *flt)
{
	if(flt == NULL)
		return;
	else if(flt->head == NULL)
	{
		free(flt);
		flt = NULL;
		return;
	}
	else{
		Friend *tmp = flt->head;
		while(tmp != NULL)
		{
			tmp = flt->head;
			flt->head = flt->head->next;

			free(tmp);
			tmp = NULL;
		}

		free(flt->end);
		flt->head = flt->end = NULL;

		free(flt);
		flt = NULL;
	}
}

/***************************************************************************************************
功能说明：friendlist 添加friend链
参数说明：
	输入参数：friend
	输出参数：无
	返回：成功 1,错误 0
***************************************************************************************************/
int friendlist_add(FriendList *flt, Friend *fr)
{
	if(fr == NULL  || flt == NULL)
		return 0;
	else{
		if(flt->head == NULL)
		{
			flt->head = fr;
			flt->end = flt->head;
			flt->end->next = NULL;
		}else{
			flt->end->next = fr;
			flt->end = fr;
			fr->next = NULL;
		}

		return 1;
	}

	return 0;
}

/***************************************************************************************************
功能说明：friendlist 删除friend链
参数说明：
	输入参数：friend
	输出参数：无
	返回：成功 1,错误 0
***************************************************************************************************/
int friendlsit_del(FriendList *flt, char *userno)
{
	Friend *dest = NULL;

	if(userno == NULL || flt == NULL)
		return 0;
	else if(flt->head == NULL)
		return 0;

	for(dest = flt->head; dest != NULL; dest = dest->next)
		if(!strncmp(userno, dest->userno, 6))
			break;

	if(dest)
	{
		if(dest == flt->head)
		{
			//删除头
			if(flt->head == flt->end)
				flt->head = flt->end = NULL;
			else
				flt->head = flt->head->next;

			free(dest);

			return 1;
		}else{
			Friend *pre = NULL;
			for(pre = flt->head; pre->next != NULL && pre->next != dest; pre = pre->next)
			;

			if(pre->next == dest)
			{
				pre->next = dest->next;
				free(dest);
				return 1;
			}
		}

	}

	return 0;
}

Friend *friendlist_search(FriendList *flt, char *userno)
{
	if(flt == NULL || userno == NULL)
	{
		return NULL;
	}else{
		Friend *tmp = flt->head;
		while(tmp != NULL)
		{
			if( !strncmp(tmp->userno, userno, 6) )
			{
				return tmp;
			}
			tmp = tmp->next;
		}
	}

	return NULL;
}
