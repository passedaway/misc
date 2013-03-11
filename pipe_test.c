/*
 * =====================================================================================
 *
 *       Filename:  pipe_test.c
 *
 *    Description:  test pipe such as ps aux | grep tain | more
 *
 *        Version:  1.0
 *        Created:  2012年12月06日 11时30分06秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Zhao, Changqing (NO), changqing.1230@163.com
 *        Company:  iPanel TV inc.
 *
 * =====================================================================================
 */

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>	/* exit */

/* should call this in child */
int do_cmd_in_pipe(int *argc_v, char ***argv_v, int argcc)
{
	int *argc = argc_v;
	char ***argv = argv_v;
	char **argp = *argv;
	int i = 0;

	printf("%s argc c=%d in\n", __FUNCTION__, argcc);
	
#if 0
	while( *argc )
	{
		printf("argc=%d\n", *argc++);
	}

	while( *argv )
	{
		i++;
		argp = *argv;
		while( *argp )
		{
			printf("i=%d argp = %s\n",i, *argp++);
		}

		argv++;
	}
#endif

	/* if argcc <= 1 error */
	if( argcc <= 1 )
		return -1;

	/*  do pipe fork
	 * then child do argc1,argv1; 
	 * if argcc > 3, parrten call do_cmd_in_pipe 
	 * if argcc == 2, recurse should be termineted 
	 */
	{
		int fd[2];
		pid_t pid;

		pipe(fd);

		pid = fork();
		if( pid < 0 )
		{
			printf("error\n");
			return 0;
		}
		if( pid > 0 )
		{
			
			/* parrent */
			char ***_argv = argv_v;
			int *_argc = argc_v;

			_argv++;
			_argc++;

			/* process pipe in fd */
			close(fd[1]);/* close write fd */
			dup2(fd[0], 0);

			/* if argcc == 2, recurse should be termineted */
			if( argcc == 2 )
			{
				/* do cmd2 & argv2 */
				execvp(**_argv, *_argv);
				return 0;
			}

			/* prepare args for do_cmd_in_pipe, then recurse */
			do_cmd_in_pipe(_argc, _argv, argcc-1);

		}else{
			char **argv = *argv_v;
			/* child */
			printf("child run:%s\n", *argv);
			/* dup fd */
			close(fd[0]);
			dup2(fd[1], 1);/* process pipe out fd, send to parrent */
			dup2(fd[1], 2);

			/* do cmd1 & argv1 */
			execvp(*argv, argv);
		}
	}

	return 0;
}

int main(int argc, char **argv)
{
	pid_t pid = 0;
	pid = fork();
	if( pid == 0 )
	{
		int fd[2];
		pid_t child_child_pid = 0;

		int argc1=2, argc2=4;
		char *argv1[] = {
			"ps",
			"aux",
			NULL
		};

		char *argv2[] = {
			"grep",
			"tain",
			NULL
		};

		char *argv3[] = {
			"grep",
			"0",
			"-inr",
			NULL
		};

		char *argv4[] = {
			"more",
			NULL
		};

		int argc_v[] = {
			argc1,
			argc2,
			3,
			1,
			0
		};

		char **argv_v[] = {
			argv1,
			argv2,
			argv3,
			argv4,
			NULL
		};

		do_cmd_in_pipe(argc_v, argv_v, 4);
#if 0
		printf("child\n");
		pipe(fd);
		child_child_pid = fork();
		if( child_child_pid == 0 )
		{
			printf("child_child:do dup fd\n");
			close(fd[0]);
			dup2(fd[1], 1);
			dup2(fd[1], 2);

			printf("child_child:do ps aux(will not see, because dup)\n");
#if 0
			if( 0 > execlp("ps", "ps",  "-aux", (char *)0) )
#else
			if( 0 > execvp("ps", argv1) )
#endif
			{
				printf("child_child error : %s\n", strerror(errno));
			}
		}else{
			printf("child: do dup fd\n");
			close(fd[1]);
			dup2(fd[0], 0);
			printf("child: get child_child input\n");

			if( 0 > execlp("grep", "grep", "tain", (char *)0) )
			{
				printf("child error : %s\n", strerror(errno));
			}
		}
#endif
		exit(0);

	}else{
#if 0
		int i = 1;
		char buf[256] = {0};
		FILE *filep = fdopen(fd[0], "r");

		printf("parrent\n");
		while( NULL != fgets(buf, 256, filep) )
		{
			printf("parrent %d:%s\n", i++, buf);
		}
#else
		int status = 0;
		printf("parrent wait child exit\n");
		waitpid(0, &status, 0 );
		printf("waitpid status=%d\n", status);
#endif
		
	}

	printf("exit: pid=%d getpid=%d\n", pid ,getpid());
	exit(0);

	return 0;
}

