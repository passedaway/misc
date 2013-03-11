/******************************************************************************/
/*    Filename: c.cpp                                                                                      */
/*    Description: client main function, client entry                                         */
/*                                                                                                                  */
/*    Author:zhaocq (changqing.1230@163.com)  2010/11/30                        */
/******************************************************************************/
#include "cclientsocket.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

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
		fprintf(stderr, "error: %s [ipaddress] [portnumber]\n", argv[0]);
		return -1;
	}

	printf("\tserver infomation\n\taddr : %s\n\tport : %d\n", addr, port);
	fprintf(stdout, "connecting with the server:");
	fflush(stdout);

	c_client_socket_init(addr, port);

	c_start_thread();

	c_join(HOST_THREAD);

	c_client_socket_exit();

	return 0;
}
