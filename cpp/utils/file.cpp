#include "utils.h"

#include <fcntl.h>
#include <unistd.h>

#include <iostream>
using namespace std;


File::File(const char *path, int mode)
{
	int ret = 0;
	ret = open(path, O_RDWR | O_CREAT | O_APPEND, mode);

	if(ret == -1)
	{
		cout<<"open error!"<<endl;
		return;
	}else{
		cout<<"open success!"<<endl;
		fd = ret;
	}
}

File::~File()
{
	close(fd);
	cout<<"close success!"<<endl;
}

int File::myread(char *buf, unsigned int size)
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

int File::mywrite(const char *buf, unsigned int size)
{
	if(buf == NULL)
	{
		cout<<"write error : buffer is NULL"<<endl;
		return -2;
	}

	int buflen = mystrlen(buf);
	if(buflen < size){
		size = buflen;
	}

	int ret = write(fd, buf, buflen);
	if(ret != size){
		cout<<"write error : error code "<<ret<<endl;
	}

	return ret;
}

int File::mylseek(int offset, int whence)
{
	int ret = lseek(fd, offset, whence);
	
	if(ret == -1){
		cout<<"connot seek!"<<endl;
	}

	return ret;
}
