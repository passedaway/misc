#include "serversocket.h"

#include <iostream>

using std::endl;
using std::cout;

int main(void)
{
	ServerSocket *ss = new ServerSocket(8800, 128);

	ss->printServerInfo();

	ss->startThread();

//	ss->joinNet();
	ss->joinHost();

	delete ss;

	return 0;
}
