/*
 * ===========================================================================
 *
 *       Filename:  pidfile.c
 *
 *    Description:  pidfile 
 *
 *        Version:  1.0
 *        Created:  09/22/2014 04:19:37 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Changqing Zhao (tain), echo "Y2hhbmdxaW5nLjEyMzBAMTYzLmNvbQo=" | base64 -d
 *        Company:  FreedomIsNotFree.com
 *
 * ===========================================================================
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#include <errno.h>

static const char *_pidfile_name = NULL;
static void _pidfile_delete(void )
{
	printf("%s in. _pidfile_name = %s \n", 
			__FUNCTION__,
			_pidfile_name == NULL ? "NULL" : _pidfile_name);
	if( _pidfile_name )
		unlink(_pidfile_name);
}

static int pidfile_create(const char *name, pid_t pid)
{
	int fd = -1;
	FILE *pfd = NULL;

	//do not check file if exists
	//open file
	fd = open(name, O_RDWR | O_CREAT | O_TRUNC, 0666);
	if( fd < 0 )
	{
		printf("error: cannot open file %s\n", strerror(errno));
		goto err_out;
	}

	//get a FILE * handle
	pfd = fdopen(fd, "w+");
	if( pfd == NULL )
		goto err_out;

	//mark the filename
	_pidfile_name = name;

	//check pid
	if( !pid )
		pid = getpid();

	//write to file
	fprintf(pfd, "%d\n", pid);
	fflush(pfd);

	//register at_exit
	atexit(_pidfile_delete);

err_out:
	if( pfd )
		fclose(pfd);
	if( fd != -1 )
		close(fd);
		
	return (pfd == NULL) ? -1 : 0;
}

static void deamonize(void)
{
	//fork
	if( 0 != fork() )
	{
		//parrent exit
		exit(0);
	}

	//child goto run
	//1. setsid
	setsid();
	//2. chdir,cwd to root
	chdir("/");
	//3. close  stdin/out/err, reopen to /dev/null
	close(0);
	close(1);
	close(2);
	open("/dev/null", O_RDWR);
	dup2(0, 1);
	dup2(0, 2);
}

int main(int argc, char **argv)
{
	int ret = 0;

	deamonize();
	ret = pidfile_create("/var/run/test.pid", 0);
	printf("ret = %d\n", ret);

	printf("press Enter to exit.pid = %d\n", getpid());
	while(1)
	{
		sleep(10);
	}

	return 0;
}

