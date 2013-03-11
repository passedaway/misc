#include <iostream>

#include "utils.h"

using std::cout;
using std::cin;
using std::left;
using std::right;
using std::endl;
//using std::string;

int main(int argc, char **argv)
{
	String s1("hello world");

	s1.show();
	cout<<endl;

	cout<<s1.getlen()<<endl;

	cout<<sizeof(s1)<<endl;

	if(argc != 2){
		cout<<"format error : \n./main pathname"<<endl;
		return -1;
	}

	char buf[100];

	File *fp = new File(argv[1], 0);

	cout<<"input the buffer:";
	cin>>buf;

	fp->mywrite(buf,mystrlen(buf));

	delete fp;
	return 0;
}
	
