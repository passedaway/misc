/*
 * =====================================================================================
 *
 *       Filename:  filetest.c
 *
 *    Description:  test file operation
 *
 *        Version:  1.0
 *        Created:  05/22/2011 05:40:30 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Zhao, Changqing (), changqing.1230@163.com
 *        Company:  
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>
/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  main
 *  Description:  
 * =====================================================================================
 */
	int
main ( int argc, char *argv[] )
{
	int fd;
	char *buf = "hello,world";

	fd = open("../im/obj/a.txt", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);

		
	write(fd, buf, strlen(buf));

	close(fd);
	return 1;
}				/* ----------  end of function main  ---------- */
