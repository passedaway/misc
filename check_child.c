/*
 * =====================================================================================
 *
 *       Filename:  check_child.c
 *
 *    Description:  test for check child
 *
 *        Version:  1.0
 *        Created:  07/30/2013 05:16:56 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  echo "Q2hhbmdxaW5nLFpoYW8K" | base64 -d  (tain)
 *          Email:  echo "Y2hhbmdxaW5nLjEyMzBAMTYzLmNvbQo=" | base64 -d 
 *        Company:  FreedomIsNotFree.com
 *
 * =====================================================================================
 */
#include <unistd.h>
#include <stdio.h>
#include <signal.h>

int main(int argc, char **argv)
{
	pid_t child;
	int exit_status;
	printf("main start:%s \n", argv[0]);

	child = fork();
	if( child == 0 )
	{
		/* child */
		/* do it special things */
		sleep(1);
		printf("child: return 0\n");
		exit(1);
		return 2;
	}else if( child < 0){
		/* parrent error */
		printf("main : create child error\n");
		return 0;
	}

	waitpid(0, &exit_status, 0);
	printf("child exit: %d\n", exit_status);

	return 0;
}

