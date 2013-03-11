/*
 * =====================================================================================
 *
 *       Filename:  time_test.c
 *
 *    Description:  test time ctime
 *
 *        Version:  1.0
 *        Created:  05/25/2011 12:14:07 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Zhao, Changqing (), changqing.1230@163.com
 *        Company:  
 *
 * =====================================================================================
 */

#include <stdio.h>

#include <time.h>
/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  main
 *  Description:  
 * =====================================================================================
 */
int main ( int argc, char *argv[] )
{

	time_t curtime;
	char buf[30];
	time(&curtime);
	sleep(1);
	printf("ctime\n");
	printf("%s\n", asctime(gmtime(&curtime)));
	sleep(1);
	
	printf("%s\n", asctime(localtime(&curtime)));
	return 1;
}				/* ----------  end of function main  ---------- */
