/*
 * =====================================================================================
 *
 *       Filename:  sigsegv.c
 *
 *    Description:  sig segv dump stack just in linux
 *
 *        Version:  1.0
 *        Created:  2012年12月18日 10时59分30秒
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

#include "sigsegv.h"

static signal_callback_t user_callbak;

static inline void _dump_stack(void)
{
	void *array[64];
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

	fprintf(stderr, "stack trace (All layer %d, and %d layer in your code):\n", size, size-5);
	if( flag == 0 )
	{
		/* has addr2line, use this methord, will get better result  */
		char *pos = cmd + strlen(cmd);
		FILE *fp = NULL;

		sprintf(pos, " -f -e /proc/%d/exe | awk 'BEGIN{i=0; tmp=0} {i++; if(i%%2){tmp=$0;} else {printf(\"%%d: %%30s ---> %%s\\n\",i/2, tmp, $0);}}'", getpid());
		fp = popen(cmd, "w");
		
		/* front-three line of array is this module-func, 
		 * 		so it not visable to user 
		 * and last two info, is system-func, 
		 * 		so it not visable to user , too
		 * so int i from 3. modify to 0, can see all info
		 * and size modify to size-2
		 * */
		for( i = 3; i < size-2; i++)
			fprintf(fp, "%p\n", array[i]);
		fclose(fp);
	}else{
		strings = backtrace_symbols(array, size);

		for( i = 0; i < size; i++)
			fprintf(stderr, "%3d: %s\n", i+1, strings[i]);

		free(strings);
	}
	fprintf(stderr, "end of stack trace\n");
}

static inline void sigsegv_handler(int signo)
{
	if( signo == SIGSEGV )
	{
		fprintf(stderr, "********************* SEGMENT FAULT *******************\n");
		_dump_stack();
		if( user_callbak )
			user_callbak();
		exit(-1);
	}
}

void setup_sigsegv(signal_callback_t cb)
{
	signal(SIGSEGV, sigsegv_handler);
	user_callbak = cb;
}

void default_sigsegv(void)
{
	signal(SIGSEGV, SIG_DFL);
}


