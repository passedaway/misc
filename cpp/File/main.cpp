#include <iostream>

#include <string.h>

#include <stdio.h>

#include "file.h"

using namespace std;

int main()
{
/*
	File *fp = new File("num");

	//cout<<"input the buffer:";
//	cin>>buf;
//	fp->mywrite(buf,strlen(buf));

	fp->putInt(0x62);
	fp->putInt(0x61);
	fp->putChar('d');

	//fp->toStart();
	fp->toWhere(-1);
	char c = fp->getChar();
	printf("%c\n",c);


	//int b = fp->getInt();
//	cout<<"b = "<<b<<endl;

	delete fp;
*/
	cout<<"file: num exsist "<<boolalpha<<File::exists("num")<<noboolalpha<<endl;

	File *fp = new File("hello");

/*	fp->toWhere(8);
	//fp->putChar('a');
	char c = fp->getChar(); 
	printf("%c\n",c);
	fp->toWhere(-2);
	c = fp->getChar();
	printf("%c\n",c);
*/

	fp->toStart();
	char *p = "Repaly:changqing.1230@163.com for account of the emaile\nContent : hi, how do you do!";
	fp->putCharP(p);

	fp->putCharP("changqing");
	fp->putCharP("772089115@qq.com");

	fp->toStart();

	char *buf = new char[1024];
	fp->getCharP(buf);
//	fp->readBuffer(buf, 128);
	cout<<buf<<"\t buflen = "<<strlen(buf)<<endl;
	delete buf;

	char *buf1 = new char[502];
	fp->getCharP(buf1);
	cout<<buf1<<"\t buflen = "<<strlen(buf1)<<endl;
	delete buf1;

	char *buf2 = new char[502];
	fp->getCharP(buf2);
	cout<<buf2<<"\t buflen = "<<strlen(buf2)<<endl;
	delete buf2;

	char *buf3 = new char[502];
	fp->getCharP(buf3);
	cout<<buf3<<"\t buflen = "<<strlen(buf3)<<endl;
	delete buf3;

	delete fp;

	return 0;
}
	
