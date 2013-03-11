#include "thread.h"

#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/wait.h>

#include <iostream>

using std::cout;
using std::endl;

Thread::Thread():pid(0)
{
//	cout<<"Thread()"<<endl;
}

Thread::~Thread()
{
//	cout<<"virtual ~Thread()"<<endl;
}

pthread_t Thread::getPthread()
{
	return pid;
}

void Thread::setPthread(pthread_t pid2)
{
	pid = pid2;
}

int Thread::startThread()
{
	int oldstate = 0;
	pthread_create(&pid, NULL, runFun, (void*)this);
	/*
	//使线程出于可cancel状态
	pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, &oldstate);
	pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, &oldstate);
	*/
}

void Thread::join()
{
	if (pid != 0)
	{
		pthread_join(pid, NULL);
	}
}

//realize the "run" funciton.
//create one pthread
void *Thread::runFun(void *arg)
{
	//make sure the other is run faster than this one
	//sleep(1);
//	cout<<"Thread::run(static private)"<<endl;
	Thread *rs = (Thread *)arg;
	rs->run();
	return rs;
}

void Thread::exit()
{
	if(pid > 0)
	{
		pid = 0;
		pthread_exit((void *)0);
	}
}
