#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <errno.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>
#include <stdlib.h>


/**
 * @file     Serial.c
 * @brief    This is the serial operation api.
 * @author   Feiran
 */

/*  add by zhaocq */
static struct termios oldtio;
static void rollback_serial_opt(int fd)
{
	if( fd )
		if(0 != tcsetattr(fd, TCSANOW, &oldtio) )
			perror("com set error\n");
}
#if 0
/*  this is not used, because when in the serial "raw" mode, the Ctrl+C will not sent to it */
#include <signal.h>
/*  when exit or sigint, shoule reset the termial */
static int serial_fd = 1;


static void signal_hanler(int signo)
{
	if( signo == SIGINT || signo == SIGKILL || signo == SIGSTOP )
	{
		rollback_serial_opt(serial_fd);
		printf("\n\rProgarm Exit catch signo=%d\n\r", signo);
		exit(0);
	}
}
#endif
/***************************************************************************
						           函数声明
 **************************************************************************/
/*
 * name: open_serial_port
 * brief: 打开一个指定的串口，返回文件句柄。
 * parameters：
 *		comport -> 串口端口号[0, 1, 2, ……]
 * return：返回文件句柄
 */
static int open_serial_port (int comport);

/*
 * name: set_serial_opt
 * brief: 设置串口的属性
 * parameters:
 *		fd -> open_serial_port 返回的文件描述符
 *		nSpeed -> 波特率
 *		nBits -> 数据位(一般为 8 bits)
 *		nEvent -> 设置奇偶校验['O'(Odd), 'N'(None), 'E'(Event)]
 *		nStop -> 停止位
 */
static int set_serial_opt(int fd,int nSpeed, int nBits, char nEvent, int nStop);

int main (void)
{
	int fd = -1;
	char buf[64];
	int n;
	/* open serial port tty0 */
	/* --------------------- */
	if((fd=open_serial_port (0))<0)
	{
		perror("open_serial_port 1 error\n");
		return 0;
	}
	/* set serial opt */
	/* -------------- */
	if(set_serial_opt(fd, 115200, 8, 'N', 2) < 0)
	{
		perror("set_serial_opt error\n");
		return 0;
	}

#if 0
	/* for signal exit, recover the serial attr */
	serial_fd = fd;
	signal(SIGKILL, signal_hanler);
	signal(SIGINT, signal_hanler);
	signal(SIGSTOP, signal_hanler);
#endif

	while (1)
	{
		n = -1;
		n = write(fd, "\n\r\tttyS0 ok\n\t\r", 10);
		printf("write:num=%d\n\r", n);

		sleep(5);

		n = -1;
		n = read(fd, buf, sizeof(buf));
		if (n > 0)
		{
			int i = 0;
			printf("read:num=%d\n\r", n);
			for(; i<n;i++)
			{
				printf("%02x%s",buf[i], (i+1)%16?" ":"\n\r");
			}
			printf("\n\r");

			break;
		}
	}

	printf("done!\n\n\n");
	rollback_serial_opt(fd);
	close (fd);
	return 0;
}

/*
 * name: open_serial_port
 * brief: 打开一个指定的串口，返回文件句柄。
 * parameters：
 *		comport -> 串口端口号[0, 1, 2, ……]
 * return：返回文件句柄
 */
static int open_serial_port (int comport)
{
	char *dev[]={"/dev/ttyS0","/dev/ttyS1","/dev/ttyS2","/dev/ttyS3","/dev/ttyS4"};
	int fd = -1;

	printf ("--->dev number is %d\n", sizeof(dev)/sizeof(char *));

	fd = open (dev[comport], O_RDWR|O_NOCTTY|O_NDELAY);
	if(fd == -1)
	{
		perror(" open Serial port ");
		printf("%s failed!\n", dev[comport]);
		return -1;
	}
	/*      */
	/* ---- */
	if(fcntl(fd, F_SETFL, 0) < 0)
		printf("fcntl fails\n");
	else
		printf("fcntl=%d\n",fcntl(fd,F_SETFL,0));
	/*      */
	/* ---- */
	if(isatty(STDIN_FILENO)==0)
		printf("standard input is not a terminal device\n");
	else
		printf("isatty success\n");

	printf("fd-open=%d\n",fd);
	return fd;
}

/*
 * name: set_serial_opt
 * brief: 设置串口的属性
 * parameters:
 *		fd -> open_serial_port 返回的文件描述符
 *		nSpeed -> 波特率
 *		nBits -> 数据位(一般为 8 bits)
 *		nEvent -> 设置奇偶校验['O'(Odd), 'N'(None), 'E'(Event)]
 *		nStop -> 停止位
 */
static int set_serial_opt(int fd, int nSpeed, int nBits, char nEvent, int nStop)
{
	struct termios newtio;
	if(tcgetattr(fd, &oldtio) != 0)
	{
		perror("Setup Serial 1");
		return -1;
	}
	/* reset struct newtio */
	/* ------------------- */
	bzero(&newtio, sizeof(newtio));

	newtio.c_cflag |= CLOCAL|CREAD;
	newtio.c_cflag &= ~CSIZE;
	/* setting stop bits */
	/* ----------------- */
	switch(nBits)
	{
		case 7:
			newtio.c_cflag|=CS7;
			break;
		case 8:
			newtio.c_cflag|=CS8;
			break;
	}
	/* setting parity bit */
	/* ------------------ */
	switch(nEvent)
	{
		case 'O':
			newtio.c_cflag |= PARENB;
			newtio.c_cflag |= PARODD;
			newtio.c_iflag |= (INPCK|ISTRIP);
			break;
		case 'E':
			newtio.c_iflag|=(INPCK|ISTRIP);
			newtio.c_cflag|=PARENB;
			newtio.c_cflag&=~PARODD;
			break;
		case 'N':
			newtio.c_cflag &= ~PARENB;
			break;
	}
	/* set baudrate */
	/* ------------ */
	switch(nSpeed)
	{
		case 9600:
			cfsetispeed(&newtio,B9600);
			cfsetospeed(&newtio,B9600);
			break;
		case 19200:
			cfsetispeed(&newtio,B19200);
			cfsetospeed(&newtio,B19200);
			break;
		case 38400:
			cfsetispeed(&newtio,B38400);
			cfsetospeed(&newtio,B38400);
			break;
		case 57600:
			cfsetispeed(&newtio,B57600);
			cfsetospeed(&newtio,B57600);
			break;
		case 115200:
			cfsetispeed(&newtio,B115200);
			cfsetospeed(&newtio,B115200);
			break;
	}
	/* setting stop bits */
	/* ----------------- */
	if(nStop==1)
		newtio.c_cflag &= ~CSTOPB;
	else
		newtio.c_cflag |= CSTOPB;
	/* deng dai shi jian & min jieshou fu */
	/* ---------------------------------- */
	newtio.c_cc[VTIME] = 0;/* 50 */
	newtio.c_cc[VMIN] = 0;/* 14 */

	/* handle byes time+out */
	/* -------------------- */
	tcflush(fd, TCIFLUSH);

	/* activate newtio */
	/* --------------- */
	if( (tcsetattr(fd, TCSANOW, &newtio))!=0)
	{
		perror("com set error\n");
		return -1;
	}

	printf("set done\n");
	return 0;
}
