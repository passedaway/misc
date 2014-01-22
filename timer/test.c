/*
 * =====================================================================================
 *
 *       Filename:  test.c
 *
 *    Description:  test timer
 *
 *        Version:  1.0
 *        Created:  06/04/2013 06:16:02 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  echo "Q2hhbmdxaW5nLFpoYW8K" | base64 -d  (tain)
 *			Email:	echo "Y2hhbmdxaW5nLjEyMzBAMTYzLmNvbQo=" | base64 -d 
 *        Company:  FreedomIsNotFree.com
 *
 * =====================================================================================
 */
#include "timer.h"

#include <stdio.h>
#include <unistd.h>

static void _test_timer(int iarg, void *parg);

itimer_t timer = {
	.expires = 1,
	.function = _test_timer,
	.iarg = 12345,
};

void _test_timer(int iarg, void *parg)
{
	add_timer(&timer);
	printf("%s:iarg = %d jiffies=%ld\n", __FUNCTION__,  iarg, jiffies);
	timer.expires += HZ/10;
}

int main(int argc, char **argv)
{
	/* module init */
	timer_init();

	add_timer(&timer);

	while(1)
	{
		sleep(5);
		printf("runing jiffies=%ld\n", jiffies);
		break;
	}

	/* module exit */
	timer_exit();

	printf("module exit over\n");
	sleep(10);
	return 0;
}

