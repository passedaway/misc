#include "message.h"

#include <string.h>

//open Debug mode
//Debug mode:has print
#define DEBUG
#undef DEBUG

//default constructor
Message::Message()
{
	strcpy(src, "000000");
	strcpy(dest, "000000");
	strcpy(info, "0");
}

//constructor with the arguments
Message::Message(char *src, char *dest, char *info)
{
	int len = strlen(src);
	if(len > USERNO_LEN)
		len = USERNO_LEN;
	strncpy(this->src, src, len);
	this->src[len] = '\0';

	len = strlen(dest);
	if(len > USERNO_LEN)
		len = USERNO_LEN;
	strncpy(this->dest, dest, len);
	this->dest[len] = '\0';

	len = strlen(info);
	if(len > BUFLEN)
		len = BUFLEN;
	strncpy(this->info, info, len);
	this->info[len] = '\0';

	this->length = len;
}

Message::Message(const Message &ms)
{
	strcpy(src, ms.src);
	strcpy(dest, ms.dest);
	strcpy(info, ms.info);
	length = ms.length;
}

Message::~Message()
{
}

char* Message::getSrc()
{
	return this->src;
}

char* Message::getDest()
{
	return this->dest;
}

char* Message::getInfo()
{
	return this->info;
}

int Message::getInfoLength()
{
	return this->length;
}
