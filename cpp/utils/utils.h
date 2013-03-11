#ifndef UTILS_H
#define UTILS_H


/*
*Class String define
*/
#ifndef STRING_H
#define STRING_H
class String{
public:
	String(const char *);
	String(const String &other);
	
	String & operator= (const String &rhs);

	String operator+ (const String &rhs);

	void show(void);
	int getlen(void);
	char* tocharp(void);

	~String(void);
private:
	char *m_data;
};

int mystrlen(const char *str);
char * mystrcpy(char *dest,const char *src);
char * mystrcat(char *dest,const char *src);
int mystrcmp(const char *str1,const char *str2);
#endif

/*
*Class File define
*/
#ifndef FILE_H
#define FILE_H
class File{
private:
	int fd;
public:
	File(const char *path, int mode = 0);
	~File();

	int myread(char *buf, unsigned int size);
	int mywrite(const char *buf, unsigned int size);

	int mylseek(int offset, int whence);
};
#endif

/*
*Class Socket definenation
*/
#endif
