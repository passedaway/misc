/*
 * =====================================================================================
 *
 *       Filename:  testint.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  07/22/2011 11:49:46 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Zhao, Changqing (NO), changqing.1230@163.com
 *        Company:  NULL
 *
 * =====================================================================================
 */

#include <stdio.h>

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  main
 *  Description:  
 * =====================================================================================
 */
	int
main ( int argc, char *argv[] )
{
	int a = 0x7fffffff;
	printf(" a = 0x%x\tdec : %d\n", a, a);
	a++;

	printf("a++ ;\n a = 0x%x\tdec : %d\n", a, a);

	unsigned int i0 = 1, i1 = 1000;

	printf("u 1 = 0x%08x\n u 1000 = 0x%08x\n u 1 -1000 = 0x%08x %u\n",
			i0, i1, (unsigned int )(i0 - i1), (unsigned int )(i0 - i1));

	printf (" i-1 < u1: %d \n", (int)-1 < (unsigned int)1);

	return 0;
}				/* ----------  end of function main  ---------- */
