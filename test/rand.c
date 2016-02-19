/*
 * ===========================================================================
 *
 *       Filename:  test_rand.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  10/10/2015 02:55:22 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Changqing Zhao (tain), echo "Y2hhbmdxaW5nLjEyMzBAMTYzLmNvbQo=" | base64 -d
 *        Company:  FreedomIsNotFree.com
 *
 * ===========================================================================
 */
#include <stdio.h>

int main(void)
{
	int i = 0;
	for(; i < 10; i ++)
	{
		printf("%d : %d\n", i, rand());
	}

	return 0;
}

