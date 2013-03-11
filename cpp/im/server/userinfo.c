/******************************************************************************/
/*    Filename: message.c                                                                              */
/*    Description: implement the function of the message.h                           */
/*                                                                                                                  */
/*    Author:zhaocq (changqing.1230@163.com)  2010/11/30                        */
/******************************************************************************/
#include "userinfo.h"
#include "define.h"
#include <stdlib.h>
#include <string.h>

/********************local function decalring*****************************************/
static int checkPasswd(char *passwd);
static int checkUserno(char *userno);
static int checkEmaile(char *emaile);


/***************************************************************************************************
功能说明：用户信息模块初始化
参数说明：
	输入参数：无
	输出参数：无
	返回：用户信息的首地址
***************************************************************************************************/
Userinfo *userinfo_init()
{
	Userinfo *uf = (Userinfo*)malloc(sizeof(Userinfo));
	if(uf)
	{
		memset(uf, 0, sizeof(Userinfo));
		return uf;
	}else{
		return NULL;
	}
}

/***************************************************************************************************
功能说明：用户信息反初始化
参数说明：
	输入参数：用户信息的首地址
	输出参数：无
	返回：无
***************************************************************************************************/
void userinfo_exit(Userinfo* uf)
{
	if(uf != NULL)
	{
		free(uf);
		uf = NULL;
	}
}

/***************************************************************************************************
功能说明：用户信息ioctl
参数说明：
	输入参数：用户信息的首地址,操作选项，输入输出参数
	输出参数：无
	返回：无

1	get userno
2	get username
3	get name
4	get sex
5	get	emaile
6	get passwd

11	set userno
12	set username
13	set name
14	set sex
15	set emaile
16	set passwd


21	check userno is exists or format
22	check emaile
23	check passwd
24	check sex
***************************************************************************************************/
int userinfo_ioctl(Userinfo *uf, int opcode, void *arg)
{
	if(uf)
	{
		switch(opcode)
		{
			case GET_USERNO:
				*(char **)arg = uf->userno;
				break;
			case GET_USERNAME:
				*(char **)arg = uf->username;
				break;
			case GET_NAME:
				*(char **)arg = uf->name;
				break;
			case GET_SEX:
				*(char **)arg = uf->sex;
				break;
			case GET_EMAILE:
				*(char **)arg = uf->emaile;
				break;
			case GET_PASSWD:
				*(char **)arg = uf->passwd;
				break;

			case SET_USERNO:
				if(checkUserno((char *)arg))
					strncpy(uf->userno, (char *)arg, USERNO_LEN);
				else
					return 0;
				break;
			case SET_USERNAME:
				strncpy(uf->username, (char *)arg, strlen((char*)arg));
				break;
			case SET_NAME:
				strncpy(uf->name, (char *)arg, strlen((char *)arg) );
				break;
			case SET_SEX:
				strncpy(uf->sex, (char *)arg, strlen((char *)arg));
				break;
			case SET_EMAILE:
				if(checkEmaile((char *)arg))
					strncpy(uf->emaile, (char *)arg, strlen((char *)arg));
				else
					return 0;
				break;
			case SET_PASSWD:
				if(checkPasswd((char *)arg))
					strncpy(uf->passwd, (char *)arg, strlen((char *)arg));
				else
					return 0;
				break;

			case CHECK_USERNO:
				return checkUserno((char *)arg);
			case CHECK_EMAILE:
				return checkEmaile((char *)arg);
			case CHECK_PASSWD:
				return checkPasswd((char *)arg);
			case CHECK_SEX:
				return userinfo_checkSex((char *)arg);
			default:
				return 0;
		}
	}else{
		return 0;
	}

	return 0;
}


int checkEmaile(char *emaile)
{
	int i = 0;
	int len = strlen(emaile);
	if(len > EMAILE_LEN)
	{
		return 0;
	}else{
		for(i = 1;i < len - 1; i++)
		{
			if(emaile[i] == '@')
			{
				return 1;
			}
		}
		return 0;
	}
}

int checkPasswd(char *passwd)
{
	int len = strlen(passwd);
	if(len < PASSWD_MIN_LEN || len > PASSWD_MAX_LEN)
	{
		return 0;
	}else{
		return 1;
	}
}

int checkUserno(char *userno)
{
	int len = strlen(userno);
	if(len != USERNO_LEN)
	{
		return 0;
	}else{
		while(*userno != '\0')
		{
			if(*userno >= '0' && *userno <= '9')
			{
				userno++;
			}else{
				return 0;
			}
		}
		return 1;
	}
}

int userinfo_checkSex(char *sex)
{
	if(sex == NULL)
		return 0;
	else if( !( strcmp(sex, "male") && strcmp(sex, "female") ) )
		return 1;
	return 0;
}

/*
bool Userinfo::isUserExists(char *userno)
{
	String *path = new String(SERVERDATA_PATH);
	*path = *path + String(userno);

	bool ret = File::exists(path->tocharp());
	delete path;
	return ret;
}
*/

int userinfo_checkEmaile(char *emaile)
{
	return checkEmaile(emaile);
}

int userinfo_checkUserno(char *userno)
{
	return checkUserno(userno);
}

int userinfo_checkPasswd(char *passwd)
{
	return checkPasswd(passwd);
}