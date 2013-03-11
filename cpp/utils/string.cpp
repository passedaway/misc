#include <iostream>

#include "utils.h"

using std::cout;

String::String(const char *str)
{
	if (str == NULL)
	{
		this->m_data = new char[1];
		*m_data = '\0';
	} else {
		int length = mystrlen(str) + 1;
		m_data = new char [length + 1];
		mystrcpy(m_data, str);
	}
}

String::String(const String &other)
{
	int length = mystrlen(other.m_data);
	m_data = new char [length + 1];
	mystrcpy(m_data, other.m_data);
}
	
String & String::operator= (const String &rhs)
{
	if(this == &rhs){
		return *this;
	}//¼ì²é×Ô¸³Öµ

	delete []m_data;
	m_data = NULL;//ÊÍ·ÅÔ­¿Õ¼ä

	int length = mystrlen(rhs.m_data) + 1;
	m_data = new char[length];//ÉêÇëÐÂ¿Õ¼ä

	mystrcpy(m_data, rhs.m_data);//¸´ÖÆÊý¾Ý

	return *this;

}

String String::operator+ (const String &rhs)
{
	int len = mystrlen(this->m_data) + mystrlen(rhs.m_data) + 1;

	char *str = new char[len];

	mystrcpy(str,this->m_data);
	mystrcat(str,rhs.m_data);

	return 	String(str);
}

String::~String()
{
	delete []m_data;
}

void String::show(void)
{
	cout<<m_data;
}

int String::getlen(void)//ÇóstringµÄ³¤¶È
{
	int len = 0;
	while(*(m_data + len) != '\0')
	{
		len++;
	}	
	return len;

		//²»ÄÜÐÞ¸Äm_dataµÄÖµ
		//Ö»ÄÜ½èÖúÓÚm_data + lenÀ´ÊµÏÖÏÂÒÆÈ¡Öµ
		//È»ºóÅÐ¶ÏÊÇ·ñÎª'\0',Èô²»ÊÇ£¬len+1
		//Ñ­»·½áÊøºó£¬·µ»ØlenµÄÖµ£¬¼´Îª×Ö·û´®³¤¶È
}

char* String::tocharp(void)
{
	return this->m_data;
}

int mystrlen(const char *str)//Çó×Ö·û´®³¤¶È
{
	//Èç¹ûstrÎª¿Õ£¬·µ»Ø0
	if(str == NULL)
		return 0;

	//¼ÆËãstr¿ªÊ¼µÄÖ±µ½'\0'µÄ×Ö·û´®µÄ³¤¶È
	int i = 0;
	for(;*str != '\0';str++,i++)
		;
	//´Ë´¦str++¸Ä±äµÄÊÇstrµÄÖµ£¬¶ø²»ÊÇ×Ö·û´®µÄÖµ

	return i;
}

char * mystrcpy(char *dest,const char *src)//¸´ÖÆ×Ö·û´®
{
	//Èç¹ûdestÎª¿Õ£¬»òÕßsrcÎª¿Õ£¬¾ù²»ÄÜ¸´ÖÆ£¬Ö±½Ó·µ»Ødest
	//Èç¹ûdestµÄÖµ=srcµÄÖµ£¬Ôò¶þÕßÏàµÈ£¬Ö±½Ó·µ»Ødest
	if(dest == NULL || src == NULL || dest == src)
	{
		return dest;
	}

	//±£´æµ±Ç°destµÄÖµ
	char *start = dest;

	while((*start++ = *src++) != '\0')
		;
		//°ÑsrcËùÖ¸ÏòµÄÖµÈ¡³ö£¬¸³Öµ¸ødestËùÖ¸µÄµØ·½
		//È»ºó¶þÕß¾ù×ÔÔö
		//È»ºóÅÐ¶ÏÊÇ·ñÎª'\0'

	return dest;
}

char * mystrcat(char *dest,const char *src)//Á¬½Ó×Ö·û´®
{
	//ÅÐ¶Ï¶þÕßÖÐÊÇ·ñÓÐ¿Õ£¬ÈôÓÐ·µ»Ødest
	if(dest == NULL || src == NULL)
	{
		return dest;
	}

	//ÈÃ×Ö·ûÖ¸ÕëpdÖ¸Ïò×Ö·û´®µÄÄ©Î²´¦
	char *pd = dest;
	while( *pd++ != '\0')
		;
	pd--;

	//¸´ÖÆsrcÖÐµÄÄÚÈÝ
	while( (*pd++ = *src++) != '\0')
		;
	
	return dest;
}

int mystrcmp(const char *str1,const char *str2)
{
	//Èç¹û¶þÕßÏàµÈ£¬·µ»Ø0
	if(str1 == str2){
		return 0;
	}

	//¿ªÊ¼±È½Ï£¬Ö±µ½ÆäÖÐµÄÒ»¸öÏÈ½áÊø
	//Èô*str1 > *str2Ôò·µ»Ø1
	//Èô*str1 < *str2Ôò·µ»Ø-1
	while( (*str1 != '\0') && (*str2 != '\0') )
	{
		if(*str1 > *str2){
			return 1;
		}else if(*str1 < *str2){
			return -1;
		}

		str1++;
		str2++;
	}

	//ÅÐ¶ÏÊÇ·ñ*str1 = *str2 = '\0'£¬ÈôÊÇ·µ»Ø0
	//Èô*str1 = '\0'·µ»Ø-1
	//Èô*str2 = '\0',·µ»Ø1

	if(*str1 == *str2){
		return 0;
	}else if(*str1 == '\0'){
		return -1;
	}else{
		return 1;
	}

}
