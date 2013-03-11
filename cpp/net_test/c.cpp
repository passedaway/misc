#include "cclientsocket.h"
//#include <string.h>
#include <stdlib.h>

#include <iostream>
using namespace std;

int main(int argc ,char *argv[])
{
	char *addr = NULL;
	int port;
	if(argc == 1)
	{
		addr = "127.0.0.1";
		port = 8800;
	}else if(argc == 2){
		addr = argv[1];
		port = 8800;
	}else if(argc == 3){
		addr = argv[1];
		port = atoi(argv[2]);
	}else{
		cout<<"error:"<<argv[0]<<" ipaddress portnumber"<<endl;
		return -1;
	}

	CClientSocket *ccs = new CClientSocket(addr, port);

	ccs->startThread();
	
	ccs->joinHost();
	
	delete ccs;

	return 0;
}
