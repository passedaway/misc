/*
 * =====================================================================================
 *
 *       Filename:  test.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2012年11月12日 17时47分19秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Zhao, Changqing (NO), changqing.1230@163.com
 *        Company:  iPanel TV inc.
 *
 * =====================================================================================
 */

#include <stdio.h>
int main(void)
{
	struct mybitfields
	{
		unsigned short a : 4;
		unsigned short b : 5;
		unsigned short c : 7;
		char d;
	}test;
	int i;
	test.a=2;
	test.b=3;
	test.c=0;
	i=*((short *)&test);
	printf("%d = 0x%x\n", i, i);

	printf ( " sizeof %d \n", sizeof(test));
}
