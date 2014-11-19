/*
 * ===========================================================================
 *
 *       Filename:  bus_error.c
 *
 *    Description:  test bus error
 *
 *        Version:  1.0
 *        Created:  09/16/2014 10:55:44 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:   (NO), 
 *        Company:  
 *
 * ===========================================================================
 */
#include <stdio.h>

/*
 * bus-error: un-align memory access
 * in RISC cpu(link Sparc, ARM etc) will cause this;
 * but in X86, it test ok.
 * 
 */

union {
	char a[10];
	int i;
}bus_test;

int main(int argc, char **argv)
{
	int *p = (int *)&bus_test.a[2];

	printf("p = %p\n", p);

	*p = 16;

	printf("test bus error: *p=%d\n", *p);

	return 0;
}

