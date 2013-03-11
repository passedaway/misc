#ifndef _Alarm_
#define _Alarm_

#include "Signal.h"

#include <iostream>
using namespace std;

class Alarm : public Signal{

	private:
		void srun(int signo)
		{
			cout<<"Alarm:srun: signo "<<signo<<"\n\talarm.signo"<<this->signo<<endl;
		}

	public:
		Alarm(int signo):Signal(signo){
			cout<<"alarm init"<<endl;
		};

		~Alarm();
};
#endif
