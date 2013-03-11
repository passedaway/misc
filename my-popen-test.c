/*
 * =====================================================================================
 *
 *       Filename:  popen.c
 *
 *    Description:  write my popen
 *
 *        Version:  1.0
 *        Created:  2012年11月19日 13时29分19秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Zhao, Changqing (NO), changqing.1230@163.com
 *        Company:  iPanel TV inc.
 *
 * =====================================================================================
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main(int argc, char **argv)
{
	int pipefd[2] = {0};
	pid_t child_pid;
	FILE *file;
	char buf[120];
	int size = 0, status;

	pipe(pipefd);

	printf("fork point before. pid=%d, ppid=%d\n", getpid(), getppid());
	child_pid = fork();
	printf("fork point after. pid=%d, ppid=%d\n", getpid(), getppid());
	if( child_pid == 0 )
	{
		printf("in child\n");
		//child thread
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		//dup2(pipefd[1], STDERR_FILENO);
		close(pipefd[1]);

		//exec("/bin/sh",
		sleep(1);
		fprintf(stderr, "hello, world. this is stderr.\n");
		perror("has error?");

		fprintf(stdout, "hello, world. this is stdout.\n");
		printf("child exit\n");
		perror("has error?");

		execl("/bin/sh", "sh", "-c", "cat /proc/1/cmdline", (char *)0);
		/* exec family, will not back */
//		exit(0); /* if not use exec, should use exit, that will not run parrent code */
	}else{
		//parent thread
		close(pipefd[1]);

		file = fdopen(pipefd[0], "r");
		if ( file == NULL )
		{
			printf("open file error\n");
		}else{
#if 0
			while( NULL != fgets(buf, 120, file) )
				printf("parent:buf = %s\n", buf);
#else
			printf("close file ret= %d\n", fclose(file));
#endif
		}

		printf("wait child\n");

		waitpid(child_pid, &status, 0);
		printf("parrnet exit. status=%d 0x%x\n", status, status);
	}

	printf("main exit.pid=%d\n", getpid());

	return 10;
}

