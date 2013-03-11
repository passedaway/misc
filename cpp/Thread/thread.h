//fork test fail:
//child thread just copy the main thread data, it's another memory
//child modify the data, the main data will not changed.

//pthread test OK
//method :
//public not static function called private static function,
//the private static function called private function
//the private function realaize the thread,do the thread thing.
#ifndef THREAD_H
#define THREAD_H
#include <pthread.h>
class Runable{
private:
	virtual void runFun() = 0;
};

class Thread : public Runable{
private:
	pthread_t pid;

	static void *run(void *arg);
	void runFun();
public:
	Thread();
	virtual ~Thread();

	virtual int startThread();
	void join();
	pthread_t getPthread();
};
#endif
