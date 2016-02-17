/*
 * ===========================================================================
 *
 *       Filename:  getkey.c
 *
 *    Description:  get key
 *
 *        Version:  1.0
 *        Created:  01/14/2015 06:33:19 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Changqing Zhao (tain), echo "Y2hhbmdxaW5nLjEyMzBAMTYzLmNvbQo=" | base64 -d
 *        Company:  FreedomIsNotFree.com
 *
 * ===========================================================================
 */
#include <termios.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <signal.h>
#include <fcntl.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static struct termios term;
static void set_console(int fd, int flag)
{
	if ( flag == 1 )
	{
		/* set to un normal mode */
		tcgetattr(fd, &term);
		term.c_lflag &= ~ECHO;
		term.c_lflag &= ~ICANON;
		tcsetattr(fd, TCSAFLUSH, &term);
	}else{
		/*  set to normal mode */
		tcgetattr(fd, &term);
		term.c_lflag |= ECHO;
		term.c_lflag |= ICANON;
		tcsetattr(fd, TCSAFLUSH, &term);
	}
}

unsigned int get_key()
{
	unsigned int data=0;
	set_console(0, 1);
	read(0, &data, 4);
	set_console(0, 0);
	return data;
}

int get_buffer(unsigned char *buf, int len)
{
	int i = 0;
	unsigned int data = 0;
	do{
		data = get_key();
		if( data == '\r' || data =='\n' )
			return i;

		if( data < 0x100 )
		{
			*(buf+i) = data;
			i++;
		}
		else
		{
			*(buf+i) = data & 0x0ff;
			i++;
			*(buf+i) = (data>>8) & 0x0ff;
			i++;
			*(buf+i) = (data>>16) & 0x0ff;
			i++;
			*(buf+i) = (data>>24) & 0x0ff;
			i++;
		}
		//printf("i=%d data=0x%x\n", i, data);

		if( i + 4 > len )
			return -1;
	} while( 1 );

	return 0;
}

int dump_hex(unsigned char *buf, int len)
{
	int i = 0;
	for(; i < len; i++)
	{
		printf("%02x ", buf[i]);
	}

	printf("\n");
	fflush(stdout);
	return 0;
}

int main( int argc, char **argv)
{
	unsigned char buf[256], buf1[256];
	int len, len1;
	printf("Changing password for test.\nnew password:");
	fflush(stdout);

	memset(buf, 0, sizeof(buf));
	len = get_buffer(buf, sizeof(buf));

	printf("\nAgain:");
	fflush(stdout);
	memset(buf1, 0, sizeof(buf1));
	len1 = get_buffer(buf1, sizeof(buf1));

	if( (len != len1) || memcmp(buf, buf1, len) )
	{
		printf("\nError:Not Same.\n");
		printf("First:%d#%s#\n", len, buf);
		dump_hex(buf, len);
		printf("Secon:%d#%s#\n", len1, buf1);
		dump_hex(buf1, len1);
		return 1;
	}

	printf("\nlen:%d\npasswd:%s\n", len, buf);
	return 0;
}

