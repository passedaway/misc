#include "multithread.h"

#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

#include <iostream>
using std::cout;
using std::endl;

MultiThread::MultiThread():npid(0),hpid(0)
{
}

MultiThread::~MultiThread()
{
}

void *MultiThread::runn(void *arg)
{
	MultiThread *ct = (MultiThread *)arg;
	ct->runNet();
	return ct;
}

void *MultiThread::runh(void *arg)
{
	MultiThread *ct = (MultiThread *)arg;
	ct->runHost();
	return ct;
}

void MultiThread::startThread()
{
	if(npid == 0 && hpid == 0)
	{
		pthread_create(&npid, NULL, runn, (void *)this);
		pthread_create(&hpid, NULL, runh, (void *)this);
	}else {
		cout<<"Warning : thread already start,cannot start again!"<<endl;
	}
}

void MultiThread::joinNet()
{
	if(npid != 0)
	{
		pthread_join(npid, NULL);
	}
}

void MultiThread::joinHost()
{
	if(hpid != 0)
	{
		pthread_join(hpid, NULL);
	}
}

void MultiThread::exit()
{
	pthread_exit((void *)0);
	npid = 0;
	hpid = 0;
}

pthread_t MultiThread::getPthread()
{
	return pthread_self();
}

pthread_t MultiThread::getNetId()
{
	return npid;
}

pthread_t MultiThread::getHostId()
{
	return hpid;
}
