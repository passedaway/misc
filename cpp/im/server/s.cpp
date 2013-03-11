/******************************************************************************/
/*    Filename: s.cpp                                                         */
/*    Description: server entry                                               */
/*                                                                            */
/*    Author:zhaocq (changqing.1230@163.com)  2011/2/30 (funny)               */
/******************************************************************************/
#include "serversocket.h"

#include <iostream>

using std::endl;
using std::cout;

ServerSocket *g_ss = NULL;

int main(void)
{
	g_ss = new ServerSocket(8800, 128);

	g_ss->printServerInfo();

	g_ss->startThread();

//	g_ss->joinNet();
	g_ss->joinHost();

	delete g_ss;

	return 0;
}
