/*
 * =====================================================================================
 *
 *       Filename:  malloc_test.c
 *
 *    Description:  test malloc free, double free
 *
 *        Version:  1.0
 *        Created:  05/24/2011 11:33:13 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Zhao, Changqing (), changqing.1230@163.com
 *        Company:  
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  main
 *  Description:  
 * =====================================================================================
 */
int main ( int argc, char *argv[] )
{
	char *dest;
	int i;
	dest = (char *)malloc(10);
	printf("stack and heap size: 0x%lx, %ld\n", ((unsigned long)(&dest) - (unsigned long)dest), ((unsigned long)(&dest) -(unsigned long) dest));
	printf("heap %p\nstack %p\n", dest, &dest);
	
	for(i = 0; i < 10; i++)
		printf("0x%x ", *(dest + i));
	printf("\n\n");

	strcpy(dest, "1234567891234");

	free(dest);
	for(i = 0; i < 20; i++)
		printf("0x%x ", *(dest + i));
	printf("\n\n");

	sleep(1);
	free(dest);
	for(i = 0; i < 10; i++)
		printf("0x%x ", *(dest + i));
	printf("\n\n");


	return 1;
}				/* ----------  end of function main  ---------- */
