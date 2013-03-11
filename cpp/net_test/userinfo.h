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

#ifndef Userinfo_H
#define Userinfo_H
class Userinfo{
public:
	//userno
	char userno[USERNO_LEN + 1];
private:
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

public:
	Userinfo();//null,default
	Userinfo(char *userno, char *passwd, char *username, char *sex, char *emaile);//from the var
	Userinfo(char *userno);//from file

//getters and setters
	char *getUserno();
	char *getUsername();
	char *getName();
	char *getSex();
	char *getEmaile();
	char *getPasswd();

	bool setPasswd(char *);
	bool setUsername(char *);
	bool setName(char *);
	bool setSex(char *);
	bool setEmaile(char *);
public:
	//check the user is exists in the file in the server
	static bool isUserExists(char *userno);
	//check the emaile is valueable
	static bool checkEmaile(char *emaile);
	//check the passwd is valueable
	static bool checkPasswd(char *passwd);
	//check the userno
	static bool checkUserno(char *userno);
};
#endif
