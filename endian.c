/*
 * ===========================================================================
 *
 *       Filename:  endian.c
 *
 *    Description:  print endian
 *
 *        Version:  1.0
 *        Created:  11/27/2014 05:48:29 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Changqing Zhao (tain), echo "Y2hhbmdxaW5nLjEyMzBAMTYzLmNvbQo=" | base64 -d
 *        Company:  FreedomIsNotFree.com
 *
 * ===========================================================================
 */
#include <stdio.h>

int main(int argc,char **argv)
{
	union{
		char c[4];
		int i;
	}test;
	const char *res = "Big Endian(BE)";

	test.i = 0x00000001;

	
	if( test.c[0] == 0x01 )
		res = "Little Endian(LE)";

	printf("System is %s.\n", res);

	return 0;
}
