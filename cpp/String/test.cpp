#include "test.h"

#include <iostream>
using std::cout;
using std::endl;

Test::Test(String name, String passwd, String emaile):name(name),passwd(passwd),emaile(emaile)
{
}

Test::Test(int fd):name(""),passwd(""),emaile("")
{
	int flag = 0;
	char *buf = new char[1025];

	int ret = read(fd, buf, 1024);

	if(ret == 1024)
	{
		flag = 1;
		buf[ret] = '\0';
	}else{
		flag = 0;
		//file ended
	}

	const char *cname, *cpasswd, *cemaile;
	int len = mystrlen(buf);
	if(len < ret)
	{
		cname = buf;
		name = String(cname);

		cpasswd = cname + (len + 1);
		ret -= (len + 1);
		len = mystrlen(cpasswd);
		if(len < ret)
		{
			passwd = String(cpasswd);

			cemaile = cpasswd + (len + 1);
			ret -= (len+1);
			emaile = String(cemaile);
		}
	}
}

Test::~Test()
{
}

void Test::show()
{
	cout<<name<<'\t'<<passwd<<'\t'<<emaile<<endl;
}

void Test::save(int fd)
{
	name.writeToFile(fd);
	passwd.writeToFile(fd);
	emaile.writeToFile(fd);
}

