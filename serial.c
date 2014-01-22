/*
 * =====================================================================================
 *
 *       Filename:  serial.c
 *
 *    Description:  serial in linux to read and write serial
 *
 *        Version:  1.0
 *        Created:  2011年07月05日 15时31分14秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Zhao, Changqing (NO), changqing.1230@163.com
 *        Company:  NULL
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <errno.h>

int open_dev(char *devname);
void set_speed(int fd, int databits, int stopbits, int parity);
int set_baudrate(int fd, int baudrate);


int main(int argc, char **argv)
{
  	int fd = 0;
	int nread = 0;
	char buf[512];

	if(argc != 2)
	{
	  fprintf(stderr, "usage: %s [serial_port]\n", argv[0]);
	  return 0;
	}

	fd = open_dev(argv[1]);

	if(0 > fd)
	{
	  fprintf(stderr, "open serial error!");
	  return 0;
	}

	set_baudrate(fd, 115200);
	set_speed(fd, 8, 1, 'n');

	while(1)
	{
	  /*
		while((nread = read(fd, buf, 512) ) > 0)
		{
		  buf[nread] = 0;
		  printf("recv:\n%s\nsend:\n",buf);
		}
		*/
		memset(buf, 0, 512);
		printf("send:");
		scanf("%s", buf);
		write(fd, buf, 512);
	}

	close(fd);
	return -2;
}


int open_dev(char *devname)
{
  return open(devname, O_RDWR);
}


int set_baudrate(int fd, int baudrate)
{

  int speed_addr[] = { B1200, B4800, B9600,B19200, B115200}; 
  int name_addr[] = { 1200, 4800, 9600, 19200, 115200}; 

  int i;
  int status;
  struct termios opt;
  
  tcgetattr(fd, &opt);

  tcflush(fd, TCIOFLUSH);

  for( i = 0; i< sizeof(speed_addr) /sizeof(int); i++)
  {
	if(baudrate == name_addr[i])
	{
  		cfsetispeed(&opt, speed_addr[i]);
	  	cfsetospeed(&opt, speed_addr[i]);
		printf("baud rate : %d\n", baudrate);

		tcsetattr(fd, TCSANOW, &opt);

		tcflush(fd, TCIOFLUSH);
		return;
	}
  }

  fprintf(stderr, "error: cannot set baudrate!\n");
  exit(-1);
}

void set_speed(int fd, int databits, int stopbits, int parity)
{
  struct termios opt;

  tcgetattr(fd, &opt);

  opt.c_cflag &= ~CSIZE;
  switch(databits)
	{
	  case 7:
		opt.c_cflag |= CS7;
		break;
	  case 8:
		opt.c_cflag |= CS8;
		break;
	  default:
		fprintf(stderr, "error: databits cannot set!\n");
		exit(-1);
	}

  switch(parity)
  {
	case 'n':
	case 'N'://mei you jiao yan
	  opt.c_cflag &= ~PARENB;
	  opt.c_cflag &= ~INPCK;
	  break;

	case 'o':
	case 'O':
	  //ji jiao yan
	  break;

	case 'e':
	case 'E'://o jiao yan
	  break;
  }

  switch(stopbits)
  {
	case 1:
	  opt.c_cflag &= ~CSTOPB;
	  break;
	case 2:
	  opt.c_cflag |= CSTOPB;
	  break;
	default:
	  fprintf(stderr, "set stop bit error!\n");
	  exit(-1);

  }
}
