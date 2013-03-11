#include "test.h"
#include "string.h"

#include <unistd.h>
#include <fcntl.h>

#include <iostream>
using std::cout;
using std::left;
using std::right;
using std::endl;
using std::boolalpha;
using std::noboolalpha;
//using std::string;

int main(void)
{
	//read from file
	/*	
	char str[1024];
	int fd = open("info", O_RDWR, S_IRUSR | S_IWUSR);
	int ret = read(fd, str, 1024);
	close(fd);

	int str1_len = mystrlen(str);
	String s1(str);

	char *str2 = str + str1_len + 1;
	int str2_len = mystrlen(str2);
	String s2(str2);
	*/

	//String s1("hello world");
	//String s2("chang qing");

	String name("changqing");
	String passwd("zhao1230");
	String emaile("changqing.1230@163.com");

	Test *test = new Test(name, passwd, emaile);

	test->show();

/*
	s1.show();
	cout<<endl;
	s2.show();
	cout<<endl;

	cout<<s1.getlen()<<endl;
	cout<<s2.getlen()<<endl;


	bool cmp = s1 == s2;

	cout<<boolalpha<<cmp<<noboolalpha<<endl;
*/

//write string object to file
//
#if 0
	int fd = open("info", O_CREAT | O_APPEND | O_RDWR, S_IRUSR | S_IWUSR);
//	write(fd, &fd, sizeof(int));
	test->save(fd);
#else
	int fd = open("info", O_APPEND | O_RDWR);
	Test a = Test(fd);
	cout<<"read from file :"<<endl;
	a.show();
#endif
	close(fd);
//	
//
	cout << " test intp "<<endl;
	int i = 12345;
	char stri[6];
	intocharp(i,stri);
	cout<<stri<<endl;
	delete test;
	return 0;
}
