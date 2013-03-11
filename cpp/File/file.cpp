#include "file.h"

#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#include <iostream>
using namespace std;

//char point is have '\0' in the already knows number
bool isHaveEnd(char *p, int num);

bool isHaveEnd(char *p, int num)
{
	int i = 0;
	for(; i < num; i++)
	{
		if(*p++ == '\0')
		{
			return true;
		}
	}
	return false;
}

File::File(const char *path)
{
	int ret = 0;
	ret = open(path, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);

	if(ret == -1)
	{
		cout<<"open error!"<<endl;
		return;
	}else{
//		cout<<"open success!"<<endl;
		fd = ret;
	}
}

File::~File()
{
	close(fd);
//	cout<<"close success!"<<endl;
}

bool File::exists(const char *path)
{
	int fd = open(path, O_RDONLY | O_EXCL);

	if(fd > 0){
		close(fd);
		return true;
	}else{
		return false;
	}
}

int File::readBuffer(char *buf, unsigned int size)
{
	if(buf == NULL){
		cout<<"read error : buffer is NULL"<<endl;
		return -2;
	}

	int ret = read(fd, buf, size);

	if(ret == -1){
		cout<<"read error : error code -1"<<endl;
	}

	return ret;
}

int File::writeBuffer(const char *buf, unsigned int size)
{
	if(buf == NULL)
	{
		cout<<"write error : buffer is NULL"<<endl;
		return -2;
	}

	int ret = write(fd, buf, size);
	if(ret != size){
		cout<<"write error : error code "<<ret<<endl;
	}

	return ret;
}
//charPoint read and write
//read a char point from file
char *File::getCharP(char *p)
{
	if(p == NULL){
		return NULL;
	}

	int len = 32;

	int ret = read(fd, p, len) ;
	cout<<"ret = "<<ret<<endl;

	while(ret <= len && ret != 0)
	{
		if(ret < len)
		{
			if(isHaveEnd(p, ret))
			{
				toWhere(1 + strlen(p) - ret);
				return p;
			}else{
				p[ret] = '\0';
				return p;
			}
		}else {

			if(isHaveEnd(p, ret))
			{
				cout<<"toWherer(1 + strlen(p) - len)"<<endl;
				toWhere(1 + strlen(p) - ret);
				cout<<"strlen(p) = "<<strlen(p)<<" ret = "<<ret<<endl;
				cout<<"over"<<endl;

				return p;
			}else{
				cout<<"toWhere(-ret)  ret = "<<ret<<endl;
				toWhere(-ret);
				len *= 2;
				ret = read(fd, p, len);
				cout<<"ret = "<<ret<<" len = "<<len<<endl;
			}
		}
	}

	p[ret] = '\0';
	return NULL;
}

//write a string (char point foramt) to file
bool File::putCharP(const char *p)
{
	if(p != NULL)
	{
		write(fd, p, strlen(p) + 1);
		return true;
	}else{
		return false;
	}
}

//read a char from file
char File::getChar()
{
	char buf[1];
	read(fd, buf, sizeof(char));
	char c = buf[0];
	return c;
}

//write a char to file
bool File::putChar(char c)
{
	char tc = c;
	char *p = (char *)&tc;
	write(fd, p, sizeof(char));
	return true;
}
	

//read a Int from file
int File::getInt()
{
	char buf[4];
	read(fd, buf, sizeof(int));
	int *pi;
	pi = (int *)&buf;
	
	int i = *pi;
	return i;
}

//write a Int to file
bool File::putInt(int a)
{
	int i = a;
	char *p = (char *)&i;
	write(fd, p, sizeof(int));

	return true;
}


//lseek
//set the offset with the current
int File::toWhere(int offset)
{
	int ret = lseek(fd, offset, SEEK_CUR);
	
	if(ret == -1){
		cout<<"connot seek!"<<endl;
	}

	return ret;
}

//move to the end
int File::toEnd()
{
	int ret = lseek(fd, 0, SEEK_END);
	if(ret == -1){
		cout<<"connot seek!"<<endl;
	}
	return ret;
}

//move to the start
int File::toStart()
{
	int ret = lseek(fd, 0, SEEK_SET);
	if(ret == -1){
		cout<<"connot seek!"<<endl;
	}
	return ret;
}
