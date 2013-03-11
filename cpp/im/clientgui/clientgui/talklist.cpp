#include "talklist.h"

TalkList::TalkList():head(NULL), end(NULL)
{
}

TalkList::~TalkList()
{
	talk *tmp = head;
	while(tmp != NULL)
	{
		head = head->next;
		tmp->close();
		delete tmp;
		tmp = head;
	}
}


void TalkList::addItem(talk *tmp)
{
	if(head == NULL)
	{
		head = end = tmp;
		tmp->next = NULL;
	}else{
		end->next = tmp;
		end = tmp;
		tmp->next = NULL;
	}
}


talk *TalkList::searchItem(char *username_userno)
{


	if(head == NULL)
	{
		return NULL;
	}else{
		talk *tmp;

		tmp = head;
		while(tmp != NULL)
		{
			if( !strcmp(username_userno, tmp->username_userno) )
				return tmp;
			tmp = head->next;
		}
		return NULL;
	}
}

int TalkList::deleteItem(talk *tmp)
{
	tmp = 0;
	return 0;
}
