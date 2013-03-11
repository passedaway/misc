#ifndef BUF_LEN
#define BUF_LEN 1024
#endif

#ifndef STRING_H
#define STRING_H

#include <iostream>
using std::ostream;

class String{
public:
	String(const char *);
	String(const String &other);
	
	String & operator= (const String &rhs);

	String operator+ (const String &rhs);

	friend ostream& operator<< (ostream &out, const String &rhs);

	bool operator== (const String &rhs);

	int getlen(void);
	char* tocharp(void);

	int writeToFile(int fd);
	String& readFromFile(int fd);

	~String(void);
private:
	char *m_data;
};

int mystrlen(const char *str);//���ַ�������
char * mystrcpy(char *dest,const char *src);//�����ַ���
char * mystrcat(char *dest,const char *src);//�����ַ���
int mystrcmp(const char *str1,const char *str2);//�Ƚ��ַ���
char * intocharp(int dat, char *dest);
#endif
