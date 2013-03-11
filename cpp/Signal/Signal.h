#ifndef _SIGNAL_
#define _SIGNAL_

#include <signal.h>
#include <unistd.h>

#include <iostream>
using namespace std;

class Runnable{
	private:
		virtual void srun(int signo)=0;
};

class Signal : public Runnable{
	private:
		static void sigHandler(void *args, int signo)
		{
			srun(signo);
		}

		void srun(int signo)
		{
			cout<<"Signal:srun:signo "<<signo<<endl;
		}

	public:
		int signo;

		Signal(int signo):signo(signo){
			signal(signo, &sigHandler);
		}

		~Signal(){
		}
};
#endif
