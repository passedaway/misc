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

	return 0;
}				/* ----------  end of function main  ---------- */
