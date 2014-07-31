/*
 * =====================================================================================
 *
 *       Filename:  test.c
 *
 *    Description:  test sigsegv
 *
 *        Version:  1.0
 *        Created:  2012年12月18日 11时04分05秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Zhao, Changqing (NO), changqing.1230@163.com
 *        Company:  iPanel TV inc.
 *
 * =====================================================================================
 */
#include "sigsegv.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void test_func(int i)
{
	if( i == 1 )
	{
		*(unsigned char *)10 = 10;
		return;
	}
	else
		test_func(i-1);
}

void func1(void)
{
	/* do some other things */
	int i = 0;

	i += 10;
	i /= 10;
	i -= 10;
	printf("i = %d\n", i);
	strcpy(0, "hello,world\n");
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
	setup_sigsegv(NULL);

	printf("\ntest_func5\n");
	test_func(5);

	printf("\nfunc4\n");
	func4();

	return 0;
}

