#ifndef MULTI_Thread_H
#define MULTI_Thread_H

#include "thread.h"

class MultiThread : public Thread{
private:
	void runFun(void);
public:
	MultiThread();
	~MultiThread();

	int startThread();
};
#endif
