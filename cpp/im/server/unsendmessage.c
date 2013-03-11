/******************************************************************************/
/*    Filename: unsendmessage.c                                               */
/*    Description: servercoket use this to manage the unsendmessage           */
/*                                                                            */
/*    Author:zhaocq (changqing.1230@163.com)  2011/5/24                       */
/******************************************************************************/
#include "unsendmessage.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/***************************************************************************************************
功能说明：初始化UnsendMessageList
参数说明：
	输入参数：无
	输出参数：无
	返回：UnsendMessageList
***************************************************************************************************/
UnsendMessageList *usml_init()
{
	UnsendMessageList *usml = (UnsendMessageList *)malloc(sizeof(UnsendMessageList));
	usml->head = usml->end = NULL;
	return usml;
}

/***************************************************************************************************
功能说明：去初始化UnsendMessageList
参数说明：
	输入参数：UnsendMessageList
	输出参数：无
	返回：无
***************************************************************************************************/
void usml_exit(UnsendMessageList *usml)
{
	if(usml == NULL)
		return;

	if(usml->head == NULL)
	{
		free(usml);
		usml = NULL;
		return;
	}
	else
	{
		UnsendMessage *tmp;
		while(usml->head != usml->end)
		{
			tmp = usml->head;
			ms_exit(tmp->ms);
			free(tmp);
			tmp = NULL;
			usml->head = usml->head->next;
		}

		ms_exit(usml->end->ms);
		free(usml->end);
		usml->head = usml->end = NULL;

		free(usml);
		usml = NULL;
	}
}

/***************************************************************************************************
功能说明：UnsendMessageList添加Unsendmessage链
参数说明：
	输入参数：friend
	输出参数：无
	返回：成功 1,错误 0
***************************************************************************************************/
int usml_add(UnsendMessageList *usml, UnsendMessage *usm)
{
	if(usm == NULL  || usml == NULL)
		return 0;
	else{
		if(usml->head == NULL)
		{
			usml->head = usm;
			usml->end = usml->head;
			usml->end->next = NULL;
		}else{
			usml->end->next = usm;
			usml->end = usm;
			usm->next = NULL;
		}
		return 1;
	}

	return 0;
}

/***************************************************************************************************
功能说明：UnsendMessageList 删除UnsendMessage链
参数说明：
	输入参数：UnsendMessageList, UnsendMessage
	输出参数：无
	返回：成功 1,错误 0
***************************************************************************************************/
int usml_del(UnsendMessageList *usml, UnsendMessage *usm)
{
	UnsendMessage *dest = NULL;

	if(usm == NULL || usml == NULL)
		return 0;
	else if(usml->head == NULL)
		return 0;

	for(dest = usml->head; dest != NULL; dest = dest->next)
		if( !strncmp( usm->ms->data, dest->ms->data, strlen(usm->ms->data) ) )
			break;

	if(dest)
	{
		if(dest == usml->head)
		{
			//删除头
			if(usml->head == usml->end)
				usml->head = usml->end = NULL;
			else
				usml->head = usml->head->next;

			free(dest);
			dest = NULL;

			return 1;
		}else{
			UnsendMessage *pre = NULL;
			for(pre = usml->head; pre->next != NULL && pre->next != dest; pre = pre->next)
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


/***************************************************************************************************
功能说明：根据destuserno在UnsendMessageList中查找UnsendMessage
参数说明：
	输入参数：UnsendMessageList, userno（dest）
	输出参数：无
	返回：成功 UnsendMessage,错误 NULL
***************************************************************************************************/
UnsendMessage *usml_search_by_destuserno(UnsendMessageList *usml, char *userno)
{
	UnsendMessage *ret = NULL;

	if(usml == NULL || userno == NULL)
		return NULL;
	else if(usml->head == NULL)
		return NULL;

	for(ret = usml->head; ret != NULL; ret = ret->next)
	{
		if(ret->ms)
		{
			if(ret->ms->data)
				if(!strncmp(ret->ms->data, userno, 6))
					return ret;
		}
		else
			return NULL;
	}

	return NULL;
}
