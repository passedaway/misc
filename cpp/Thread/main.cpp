#include "multithread.h"
#include <iostream>
using std::cout;
using std::endl;

int main(void)
{
	Thread *th1 = new MultiThread;
	Thread *th2 = new MultiThread;

	th1->startThread();
	th2->startThread();

	th1->join();
	th2->join();

	delete th1, th2;

	return 0;
}
