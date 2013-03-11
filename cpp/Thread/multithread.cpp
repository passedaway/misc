#include "multithread.h"

#include <iostream>
using std::cout;
using std::endl;

void MultiThread::runFun(void)
{
	cout<<"virtual MultiThread::runFun()"<<endl;
	cout<<"threadid = "<<getPthread()<<endl;
}

MultiThread::MultiThread():Thread()
{
	cout<<"MultiThread::MultiThread()"<<endl;
}

MultiThread::~MultiThread()
{
	cout<<"MultiThread::~MultiThread()"<<endl;
}

int MultiThread::startThread()
{
	cout<<"MultiThread::startThread()"<<endl;
}
