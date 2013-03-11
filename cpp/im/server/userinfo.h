/******************************************************************************/
/*    Filename: userinfo.h                                                                               */
/*    Description: userinfo type define,and funciton                                       */
/*                                                                                                                  */
/*    Author:zhaocq (changqing.1230@163.com)  2010/11/30                        */
/******************************************************************************/
#ifndef Userinfo_H
#define Userinfo_H

#ifndef USERNO_LEN
#define USERNO_LEN 6
#endif

#ifndef USERNAME_LEN
#define USERNAME_LEN 64
#endif

#ifndef PASSWD_MAX_LEN
#define PASSWD_MAX_LEN 32
#endif

#ifndef PASSWD_MIN_LEN
#define PASSWD_MIN_LEN 6
#endif

#ifndef EMAILE_LEN
#define EMAILE_LEN 32
#endif

typedef struct{
	char userno[USERNO_LEN + 1];
	//passwd
	char passwd[PASSWD_MAX_LEN + 1];
	//username
	char username[USERNAME_LEN + 1];
	//name
	char name[USERNAME_LEN + 1];
	//sex  male,female
	char sex[7];
	//emaile
	char emaile[EMAILE_LEN + 1];
}Userinfo;

#ifdef __cplusplus
extern "C" {
#endif
Userinfo *userinfo_init();
void userinfo_exit(Userinfo*);

#define GET_USERNO	1
#define GET_USERNAME	2
#define GET_NAME	3
#define GET_SEX	4
#define GET_EMAILE	5
#define GET_PASSWD	6
#define SET_USERNO	11
#define SET_USERNAME	12
#define SET_NAME		13
#define SET_SEX	14
#define SET_EMAILE	15
#define SET_PASSWD	16
#define CHECK_USERNO	21
#define CHECK_EMAILE		22
#define CHECK_PASSWD	23
#define CHECK_SEX		24
/********************opcode************************
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
16	set passwds

21	check userno is exists or format
22	check emaile
23	check passwd
24	check sex
****************************************************/
int userinfo_ioctl(Userinfo *uf, int opcode, void *arg);
int userinfo_checkPasswd(char *passwd);
int userinfo_checkUserno(char *userno);
int userinfo_checkEmaile(char *emaile);
int userinfo_checkSex(char *sex);

#ifdef __cplusplus
}
#endif

#endif
