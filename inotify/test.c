/*
 * =====================================================================================
 *
 *       Filename:  test.c
 *
 *    Description:  test watch api
 *
 *        Version:  1.0
 *        Created:  05/26/2013 02:37:54 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  echo "Q2hhbmdxaW5nLFpoYW8K" | base64 -d  (tain)
 *			Email:	echo "Y2hhbmdxaW5nLjEyMzBAMTYzLmNvbQo=" | base64 -d 
 *        Company:  FreedomIsNotFree.com
 *
 * =====================================================================================
 */
#include <stdio.h>
#include <unistd.h>

#include "watch.h"

/* *********************local var*************** */
static const char *dir_name = ".";
/* *********************local function declare*************** */
static int _my_handler(int file_fd, const char *path, E_CHANGE_MODE_t change_mode);

/* ***********************main entry************************* */
int main(int argc, char **argv)
{
	int watch_fd = 0;

	if( argv[1] )
		dir_name = argv[1];

	printf("watch on: %s\n", dir_name);

	/* watch init */
	if( watch_init(8) )
	{
		printf("watch init error\n");
		return 0;
	}

	/* watch on dir, can call more times */
	watch_fd = watch_on(dir_name, WATCH_ALL);
	if(-1 == watch_fd )
	{
		printf("watch on error\n");
		goto err_out;
	}

	/* install hander */
	watch_install_handler(watch_fd, (watch_handler_t)_my_handler);

	/* wait for event */
	printf("wait for event (2min)\n");
	sleep(120);
	
err_out:
	printf("watch exit\n");
	if(-1 != watch_fd )
		watch_off(watch_fd);

	watch_exit(1);
	return 0;
}

/* ***********************local function************************* */
static int _my_handler(int file_fd, const char *path, E_CHANGE_MODE_t change_mode)
{
	printf("changed: file_fd=%d %s %s\n", file_fd, path, change_mode_2_str(change_mode));
	return 0;
}

