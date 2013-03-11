/*
 * =====================================================================================
 *
 *       Filename:  memory_unmap_chunk.c
 *
 *    Description:  test memory
 *
 *        Version:  1.0
 *        Created:  2012年12月05日 17时55分13秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Zhao, Changqing (NO), changqing.1230@163.com
 *        Company:  iPanel TV inc.
 *
 * =====================================================================================
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
	char *buf = NULL;

	buf = (char *)malloc(64);
	if( buf == NULL )
	{
		printf("error\n");
		return -1;
	}

	printf("argv[0]=%p\n&buf=%p \nbuf=%p\n", argv[0], &buf, buf);
	memset(buf, 0, 64);

	if( argv[1] )
		free(argv[1]);

	free(buf+4);


	return 0;
}

