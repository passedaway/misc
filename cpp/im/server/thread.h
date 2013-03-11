#ifndef THREAD_H
#define THREAD_H

#include <pthread.h>

class Thread{
private:
	pthread_t pid;

	static void *runFun(void *arg);
	virtual void run() = 0;
public:
	Thread();
	virtual ~Thread();

	virtual int startThread();
	void join();
	void exit();
	pthread_t getPthread();
	void setPthread(pthread_t pid);
};
#endif
