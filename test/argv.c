/*
 * =====================================================================================
 *
 *       Filename:  argv.c
 *
 *    Description:  test for argv
 *
 *        Version:  1.0
 *        Created:  02/17/2016 05:08:48 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdio.h>
/*
 * more_args(arg1, arg2, arg3, arg4)
 * -- stack top
 * -- arg4 (4B)
 * -- arg3 (4B)
 * -- arg2 (4B)
 * -- arg1 (4B)
 * -- return address (4B)
 * -- stack bottom
 * 
 */

int more_args(char *arg1, ...)
{
	long *varg_start = &arg1;
	char *tmp;
	printf("in func %s\n", __FUNCTION__);
	printf("arg1: %p %s\n", arg1, arg1);
	printf("varg_start: %p %s\n", varg_start, (char*)(*varg_start));
	//varg_start --;
	varg_start ++;
	printf("second arg: %p %x %s\n", varg_start, (unsigned int *)(*varg_start), (char *)(*varg_start));

	return 0;
}

int main(int argc, char **argv)
{
	int i = 0;
	for(; i < argc ; i++)
	{
		printf("argv %d: %p @%p %s\n", i, argv[i], &argv[i], argv[i]);
	}

	more_args(argv[0], "4567890abcde", 1, "2");

	return 0;
}

