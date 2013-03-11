/*
 * =====================================================================================
 *
 *       Filename:  rand.c
 *
 *    Description:  rand number
 *
 *        Version:  1.0
 *        Created:  05/22/2011 09:11:27 PM
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
#include <stdlib.h>

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  main
 *  Description:  
 * =====================================================================================
 */
	int
main ( int argc, char *argv[] )
{
	char buf[7] = {0};
	int i = 0;

	srand((unsigned)time(NULL));

	for(i = 0; i < 6; i++)
		buf[i] = '0' + rand()%9;

	buf[i] = '\0';

	printf("%s\n", buf);

	return 0;
}				/* ----------  end of function main  ---------- */
