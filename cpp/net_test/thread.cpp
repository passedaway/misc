#include "thread.h"

#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/wait.h>

#include <iostream>

using std::cout;
using std::endl;

Thread::Thread()
{
//	cout<<"Thread()"<<endl;	
}

Thread::~Thread()
{
//	cout<<"virtual ~Thread()"<<endl;
}

inline pthread_t Thread::getPthread()
{
	return pid;
}

int Thread::startThread()
{
//	cout<<"Thread::startThread()"<<endl;
	pthread_create(&pid, NULL, runFun, (void*)this);
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
		pthread_exit((void *)0);
	}
}
