/*
 * ===========================================================================
 *
 *       Filename:  test_attribute.c
 *
 *    Description:  test attribute
 *
 *        Version:  1.0
 *        Created:  02/10/2015 10:05:10 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Changqing Zhao (tain), echo "Y2hhbmdxaW5nLjEyMzBAMTYzLmNvbQo=" | base64 -d
 *        Company:  FreedomIsNotFree.com
 *
 * ===========================================================================
 */

#include <stdio.h>

#define _init __attribute__((constructor))my_init
#define _deinit __attribute__((destructor))my_deinit

int hello_init(void )
{
	printf("hello_init\n");
	return 0;
}

void hello_exit(void)
{
	printf("hello_exit\n");
}

_init(hello_init);
_deinit(hello_deinit);

int main(int argc,char **argv)
{
	printf("main init\n");
	printf("main exit.\n");
	return 0;
}
