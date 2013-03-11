#ifndef _TALK_LIST_H_
#define _TALK_LIST_H_

#include "talk.h"

class TalkList{
	private:
		talk *head;
		talk *end;

	public:
		TalkList();
		~TalkList();

		void addItem(talk *);
		talk *searchItem(char *username_userno);
		int deleteItem(talk *);
};

#endif
