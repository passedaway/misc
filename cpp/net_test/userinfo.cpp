#include "userinfo.h"
#include "file.h"
#include "mystring.h"
#include "define.h"

#include <string.h>

#include <iostream>
using std::cout;
using std::endl;

Userinfo::Userinfo()
{
	strcpy(userno, "000000");
	strncpy(passwd, userno, 7);
	strncpy(username, userno,7);

	strcpy(name, "000000");
	strcpy(sex, "female");
	strcpy(emaile, "address@emaile.cncom");
}

Userinfo::Userinfo(char *userno, char *passwd, char *username, char *sex, char *emaile)
{
	strcpy(this->userno, userno);
	strcpy(this->passwd, passwd);
	strcpy(this->username, username);
	strcpy(this->sex, sex);
	strcpy(this->emaile, emaile);
}

Userinfo::Userinfo(char *userno)
{
	String path("/etc/zz/serverdata/");
	path = path + String(userno); 
	if(File::exists(path.tocharp()))
	{
		File *file = new File(path.tocharp());
		file->getCharP(this->passwd);
		file->getCharP(this->username);
		file->getCharP(this->sex);
		file->getCharP(this->emaile);
		delete file;
	}else{
		cout<<"no such user"<<endl;
	}
}


//getters and setters
char* Userinfo::getUserno()
{
	return userno;
}

char* Userinfo::getUsername()
{
	return username;
}

char* Userinfo::getName()
{
	return name;
}

char* Userinfo::getSex()
{
	return sex;
}

char* Userinfo::getEmaile()
{
	return emaile;
}

char* Userinfo::getPasswd()
{
	return passwd;
}

bool Userinfo::setPasswd(char *passwd)
{
	bool ret = checkPasswd(passwd);
	if(ret){
		strcpy(this->passwd, passwd);
	}

	return ret;
}

bool Userinfo::setUsername(char *username)
{
	strcpy(this->username, username);
	return true;
}

bool Userinfo::setName(char *name)
{
	strcpy(this->name, name);
	return true;
}

bool Userinfo::setSex(char *sex)
{
	String *str = new String(sex);
	if(*str == "male" || *str == "female")
	{
		strcpy(this->sex, sex);
		delete str;
		return true;
	}else{
		delete str;
		return false;
	}
}

bool Userinfo::setEmaile(char *emaile)
{
	bool ret = checkEmaile(emaile);
	if(ret)
	{
		strcpy(this->emaile, emaile);
	}
	return ret;
}


//static methods
//check
bool Userinfo::checkEmaile(char *emaile)
{
	int len = strlen(emaile);
	if(len > EMAILE_LEN)
	{
		return false;
	}else{
		for(int i = 1;i < len; i++)
		{
			if(emaile[i] == '@')
			{
				return true;
			}
		}
		return false;
	}
}

bool Userinfo::checkPasswd(char *passwd)
{
	int len = strlen(passwd);
	if(len < PASSWD_MIN_LEN || len > PASSWD_MAX_LEN)
	{
		return false;
	}else{
		return true;
	}
}

bool Userinfo::checkUserno(char *userno)
{
	int len = strlen(userno);
	if(len != USERNO_LEN)
	{
		return false;
	}else{
		while(*userno != '\0')
		{
			if(*userno >= '0' && *userno <= '9')
			{
				userno++;
			}else{
				return false;
			}
		}
		return true;
	}
}

bool Userinfo::isUserExists(char *userno)
{
	String *path = new String(SERVERDATA_PATH);
	*path = *path + String(userno);

	bool ret = File::exists(path->tocharp());
	delete path;
	return ret;
}
