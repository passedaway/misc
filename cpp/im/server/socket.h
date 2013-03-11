#ifndef SOCKET_H
#define SOCKET_H

#ifndef BUFLEN
/*the message length */
#define BUFLEN 1024
#endif

#ifndef USERNO_LEN
/* user number length*/
#define USERNO_LEN 6
#endif

#ifndef SERVER_MAXLEN
/* server can service for the client number*/
#define SERVER_MAXUSER 128
#endif

#ifndef SERVER_PORT
/* server port*/
#define SERVER_PORT 8800
#endif

#ifndef HOST_NAME_MAX
/* host name max length */
#define HOST_NAME_MAX 256
#endif

class Message{
private:
	//soucer userno; who create the message
	char src[USERNO_LEN + 1]; 
	//destention userno; who will receve the messge
	char dest[USERNO_LEN + 1];
	//info
	char info[BUFLEN];
	//info length
	int length;
public:
	//default constructor
	Message();
	//construct with the arguments
	Message(char *src, char *dest, char *info);
	//copy construct
	Message(const Message &);
	//destrcutor
	~Message();

	//getters
	char *getSrc();
	char *getDest();
	char *getInfo();
	int getInfoLength();
};

//pthread test OK
//method :
//public not static function called private static function,
//the private static function called private function
//the private function realaize the thread,do the thread thing.

#include <pthread.h>
//has the runFun() defination, vitual = 0, private
class Runable{
private:
	virtual void runFun() = 0;
};

//Thread extends Runable ,and MUST rewrite the runFun()
class Thread : public Runable{
private:
	//thread pid
	pthread_t pid;

	//startThread called this function
	//this function called runFun()
	static void *run(void *arg);

//extends from Runable
	void runFun();
public:
	Thread();
	virtual ~Thread();

	//create thread
	virtual int startThread();

	//call the object to join with this thread
	void join();
	void exit();
	pthread_t getPthread();
};

//MultiThread : using this to start the two thread
//1.net : work for the net socket
//2.host : work for the host console
//wait for cmd or message,then analyse the msg,do the right thing
class MultiThread{
private:

	pthread_t npid, hpid;

	static void *runn(void *);
	static void *runh(void *);

	virtual void runNet() = 0;
	virtual void runHost() = 0;

public:
	MultiThread();
	virtual ~MultiThread();

	virtual void startThread();

	void joinNet();
	void joinHost();

	void exit();

	//get the current thread id
	pthread_t getPthread();
	//get the net thread id
	pthread_t getNetId();
	//get the host thread id
	pthread_t getHostId();
	

};


//has two children
//1.CClientSocket : client use the ClientSocket
//2.SClientSocket : server use the ClientSocket
class ClientSocket { 
private:
	//socket fd
	int fd;
	//1.client : server port 
	//2.server : client port conneted with the server
	int port;
	//1.client : server address
	//2.server : client address connetct with the server
	char *addr;
public:

	ClientSocket(int fd, char *addr, int port);

	//copy constructer
	ClientSocket(const ClientSocket &);

	virtual ~ClientSocket();

	//receve the message by the "fd"
	int recvMessage(Message &rms);
	//send message to the "fd"
	int sendMessage(const Message &wms);
	//1.server:conmunection with the client
	//2.client:conmunection with server
	virtual int analyseMessage(Message &ms) = 0;

	//apply for new ID
	virtual int applyId() = 0;
	//disconnect with the server
	virtual int disCon() = 0;
	//normal talking : send the message to other client
	virtual int talk() = 0;

	//getters and setters
	int getFd();
	int getPort();
	char *getAddr();
	//for the CCleintSocket child
	void setFd(int fd);
};

//CClientSocket extends ClientSocket
//CClientSocket extends Thread
//client use this class
class CClientSocket : public ClientSocket, public MultiThread{
public:
	//client:create and connect with the socket
	CClientSocket(char *addr, int port);
	~CClientSocket();
//extends ClientSocket
	int analyseMessage(Message &ms);

	int applyId(){
	}
	int disCon(){
	}
	int talk(){
	}

private:
//extends ClientThread
	void runNet();
	void runHost();
private:
	//control the action, just use for the runNet and runHost
	//to diff the cmd, or the message
	//-1:cmd
	//0:loginning...
	//1:login success
	int loginFlag;
};

//SCleintSocket extends ClientSocket
//server use this class to manager the client
class SClientSocket : public ClientSocket , public Thread{
private:
	//server : linklist, for the serversocket to manager
	SClientSocket *next;
public:
	//server:use this to manager the connecter client
	SClientSocket(int fd, char *addr, int port);
	~SClientSocket();

	bool isHasNext();
	void setNext(SClientSocket *);
	SClientSocket *getNext();

//extends ClientSocket
	int analyseMessage(Message &ms);

	int applyId();
	int disCon();
	int talk();

//extends Thread
//	void runFun();
};

class ClientList{
private:
	//current user in the list
	//getter only
	int curuser;
	//the list can listing the maxmaum number
	//users cannot see it,just for the program
	int maxuser;

public:
	SClientSocket *head;
	SClientSocket *end;

public:
	ClientList(int maxuser);
	~ClientList();

	//show all client conneted with the server
	void showClient();

	//manager Client which connected with the server
	SClientSocket* searchClient(char *addr);

	//add client
	//1.true: add client in the list successfully
	//2.false: this clientlist is already full
	bool addClient(int fd, char *addr, int port);

	bool deleteClient(int fd);

	bool deleteClient(SClientSocket *dest);

	int getCuruser();
};


//serversocket extends multithread
//1.console
//2.net
class ServerSocket : public MultiThread{
private:
	//listening socket fd
	int fd;
	//server port
	int port;
	//can listen max user
	int maxuser;

	//server address
	char *saddr;

//debug
public:
	//client list which connected with the server
	ClientList *clientList;

public:
	//create the server socket, not start the server!
	//need to call the startServer() to start the server
	ServerSocket(int port, int maxuser);
	~ServerSocket();

	//start server
	//1.accpet client
	//2.server for each client 
	//3.listen for cmd
	void startServer();

	int myread();
	int mywrite();

	//getters
	char *getSaddr();
	int getPort();
	int getMaxuser();

	//current user online
	//recorded in the clientList
	//int curuser;
	int getCuruser();

	//print online Client infomation 
	void printClientInfo();
	//print Server infomation
	void printServerInfo();
};
#endif
