#include "Alarm.h"
#include <stdio.h>

int main(void)
{
	Alarm *alr = new Alarm(SIGALRM);
	alarm(2);

	getchar();
	return 0;
}
