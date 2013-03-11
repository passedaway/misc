/*
 * =====================================================================================
 *
 *       Filename:  memcpy-test.c
 *
 *    Description:  test memcpy
 *
 *        Version:  1.0
 *        Created:  2013年01月21日 10时23分54秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Zhao, Changqing (NO), changqing.1230@163.com
 *        Company:  iPanel TV inc.
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>

static struct timespec start,end;
#define get_start_time()  clock_gettime(CLOCK_MONOTONIC, &start)
#define get_end_time()  clock_gettime(CLOCK_MONOTONIC, &end)
static unsigned long get_diff_time()
{
	if(start.tv_nsec > end.tv_nsec )
		return (end.tv_sec - start.tv_sec - 1)*1000000 + (1000000 + start.tv_nsec - end.tv_nsec);

	return (end.tv_sec - start.tv_sec)*1000000 + end.tv_nsec - start.tv_nsec;
}

static void usage(char **argv)
{
	fprintf(stderr, "usage:\n\t%s [times] [size K/M]\n", argv[0]);
	exit(0);
}

static int _atoi(char *arg)
{
	int ret = 0;
	int len;
	int qene = 10;
	char *pos = 0;

	len = strlen(arg);
	if( len == 0 )
		return 0;

	pos = arg;
	if( len > 2 )
	{
		if((arg[0]=='0') && ((arg[1]=='x') || (arg[1]=='X')) )
		{
			qene = 16;
			pos = arg+2;
		}
	}

	while(1)
	{
		if((*pos >= '0') && (*pos <= '9'))
			len = *pos - '0';
		else if( (*pos >= 'A') && (*pos <= 'F') )
			len = *pos - 'A' + 10;
		else if( (*pos >= 'a') && (*pos <= 'f') )
			len = *pos - 'a' + 10;
		else
			return ret;

		ret = ret*qene + len;
		pos++;
	}

	return ret;
}

int main(int argc, char **argv)
{
	int times = 0, i;
	int size = 0;
	char *src, *dest, *mempool;

	char *tmp;
	int tmp_len;

	unsigned long this_time, all_time=0;

	if( argc != 3 )
		usage(argv);

	times = _atoi(argv[1]);
	size = _atoi(argv[2]);

	tmp_len = strlen(argv[2]);
	tmp = argv[2] + tmp_len - 1;
	switch( *tmp )
	{
		case 'M':
		case 'm':
			size *= 1024;
		case 'K':
		case 'k':
			size *= 1024;
		default:break;
	}

	printf("%s:size=%d times=%d\n", argv[0], size, times);
	if( !times || !size )
		usage(argv);
	
	mempool = (char *)malloc(2*size);
	if( mempool == NULL )
	{
		printf("memory out. %d\n", 2*size);
		return 0;
	}
	memset(mempool, 0, 2*size);
	
	for(i = 0; i< times; i++)
	{
		if( i%2 )
		{
			src = mempool;
			dest = mempool + size - 1;
		}else
		{
			src = mempool + size - 1;
			dest = mempool;
		}

		get_start_time();
		memcpy( dest, src, size);
		get_end_time();
		this_time = get_diff_time();
		all_time += this_time;
		printf("test times %6d use-time: %8ld\n", times, this_time);
	}

	printf("\nresult:alltime=%ld average time=%ld\n%s:test over\n", 
			all_time, all_time/times, argv[0]);
	return 0;
}

