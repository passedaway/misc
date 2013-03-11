#ifndef Message_H
#define Message_H

#include "define.h"

class Message{
private:
	//soucer userno; who create the message
	char src[USERNO_LEN + 1]; 
	//destention userno; who will receve the messge
	char dest[USERNO_LEN + 1];
	//info
	char info[BUFLEN];
	//info length
	int length;
public:
	//default constructor
	Message();
	//construct with the arguments
	Message(char *src, char *dest, char *info);
	//copy construct
	Message(const Message &);
	//destrcutor
	~Message();

	//getters
	char *getSrc();
	char *getDest();
	char *getInfo();
	int getInfoLength();
};
#endif
