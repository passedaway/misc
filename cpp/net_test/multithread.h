#ifndef MultiThread_H
#define MultiThread_H

#include <pthread.h>
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
#endif
