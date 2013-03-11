/*
 * =====================================================================================
 *
 *       Filename:  backtrace.c
 *
 *    Description:  test print stack trace just in linux
 *
 *        Version:  1.0
 *        Created:  2012年12月17日 15时40分51秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Zhao, Changqing (NO), changqing.1230@163.com
 *        Company:  iPanel TV inc.
 *
 * =====================================================================================
 */
#include <execinfo.h> /* backtrace, backtrace_symbols, backtrace_symbols_fd  */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>

void print_stack_info(void)
{
	void *array[32];
	size_t size;
	char **strings;
	size_t i;

	int flag = 0;
	char cmd[512] = {0};
	const char *path[] = {
		"/bin/addr2line",
		"/usr/bin/addr2line",
		"/sbin/addr2line",
		"/usr/sbin/addr2line"
	};

	size = backtrace(array, sizeof(array)/sizeof(array[0]));

	for( i=0; i < sizeof(path)/sizeof(path[0]); i++)
	{
		flag = access(path[i], F_OK);
		if( flag == 0 )
		{
			strcpy(cmd, path[i]);
			break;
		}
	}

	fprintf(stderr, "stack trace %d :\n", size);
	if( flag == 0 )
	{
		/* has addr2line, use this methord, will get better result  */
		char *pos = cmd + strlen(cmd);
		FILE *fp = NULL;

		sprintf(pos, " -f -e /proc/%d/exe | awk 'BEGIN{i=0; tmp=0} {i++; if(i%%2){tmp=$0;} else {printf(\"%%d: %%s ---> %%s\\n\",i/2, tmp, $0);}}'", getpid());
		fprintf(stderr, "cmd = %s\n", cmd);
		fp = popen(cmd, "w");
		
		for( i = 0; i < size; i++)
			fprintf(fp, "%p\n", array[i]);
		fclose(fp);
	}else{
#if 1
		strings = backtrace_symbols(array, size);

		for( i = 0; i < size; i++)
			fprintf(stderr, "%3d: %s\n", i+1, strings[i]);

		free(strings);
#else
		/* use this func, it just print the info to the stdout, will not malloc */
		backtrace_symbols_fd(array, size, STDERR_FILENO);
#endif
	}
	fprintf(stderr, "end of stack trace\n");
}

void test_func(int i)
{
	if( i == 1 )
	{
		*(unsigned char *)10 = 10;
		return;
		print_stack_info();
	}
	else
		test_func(i-1);
}

static void signal_handler(int signo)
{
	if( signo == SIGSEGV )
	{
		printf("signal SIGSEGV\n");
		print_stack_info();
		exit(0);
	}
}


void func1(void)
{
	print_stack_info();
}

void func2(void)
{
	char *ptr = NULL;
	char *buf=malloc(2048);
	ptr = buf;
	if( ptr == NULL )
		return;
	memset(buf,0, 2048);

	ptr +=sprintf(buf,"                                 \\\\\\|///\n");
	ptr +=sprintf(ptr,"                               \\\\  - -  //\n");
	ptr +=sprintf(ptr,"                                (  @ @  )\n");
	ptr +=sprintf(ptr,"          ____________________oOOo_(_)_oOOo_________________________\n");
	ptr +=sprintf(ptr,"         |                                                          |\n");
	ptr +=sprintf(ptr,"         |            Welcome to xXxxxx Xxxxxxxxxx Xxxxxx           |\n");
	ptr +=sprintf(ptr,"         |                              Oooo                        |\n");
	ptr +=sprintf(ptr,"         |______________________ oooO___(   )_______________________|\n");
	ptr +=sprintf(ptr,"                                (   )    ) /\n");
	ptr +=sprintf(ptr,"                                 \\ (    (_/\n");
	ptr +=sprintf(ptr,"                                 \\_)\n");

	*ptr = 0;

	fprintf(stdout, "%s", buf);
	fflush(stdout);
	free(buf);
	buf = NULL;

	func1();
}

void func3(void)
{
	func2();
}

void func4(void)
{
	func3();
}

int main(int argc , char **argv )
{
	signal(SIGSEGV, signal_handler);

	printf("\nfunc4\n");
	func4();

	printf("\ntest_func5\n");
	test_func(5);

	return 0;
}

