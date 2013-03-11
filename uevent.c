#include <stdio.h>
#include <stdlib.h> /* malloc */
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <stddef.h> /* offsetof */

//#include <linux/types.h>
//#include <linux/netlink.h>
#include <sys/un.h>

#include <asm/types.h>
#include <linux/netlink.h>

void dump_buf(char *buf, int len)
{
	int i = 0,j, prcflag =0;
	char *ptr = buf;
	printf("\n\r");
	for(; i < len; i++)
	{
		printf("%02x ",*ptr++);
		prcflag = ((i+1)%16)==0?1:0;
		if( prcflag )
		{
			printf("| ");
			ptr = buf + (i+1)-16;
			for(j = 0; j < 16 ; j++, ptr++)
				printf("%c",*ptr>0x1F && *ptr<0x7F ? *ptr : '.');
			printf("\n");
		}
	}

	if ( len % 16 == 0 )
		return;

	//print space
	j = 16 - len%16;
	while(j--)
		printf("   ");

	printf("| ");
	j = len-len%16;
	ptr = buf + j;
	for( ; j < len; j++, ptr++)
		printf("%c",*ptr>0x1F && *ptr<0x7F ? *ptr : '.');

	printf("\n\r\n\r");
}

static int init_udev_socket_v1(void)
{
	int fd, ret;
	struct sockaddr_un saddr;
	socklen_t addrlen;

	fd = socket(AF_LOCAL, SOCK_DGRAM, 0);
	if( fd < 0 )
	{
		printf("error : cannot open socket ret=%d\n", fd);
		return -1;
	}

	memset(&saddr, 0, sizeof(saddr));
	saddr.sun_family = AF_LOCAL;
	strcpy(&saddr.sun_path[1], "/org/kernels/udev/udevd");
	addrlen = offsetof ( struct sockaddr_un, sun_path) + strlen(saddr.sun_path+1) + 1;
	
	ret = bind ( fd, (struct sockaddr *)&saddr, addrlen);
	if( ret < 0 )
	{
		printf ( "error : bind error. fd=%d ret=%d\n", fd, ret);
		close(fd);
		return -2;
	}

	return fd;
}

static int init_udev_socket_v2(void)
{
	int fd, ret;

	int bufsize = 1024;

	struct sockaddr_nl snl;
	memset( &snl, 0, sizeof( snl ) );
	snl.nl_family = AF_NETLINK;
	snl.nl_pid = getpid();
	snl.nl_groups = 1;

	fd = socket(PF_NETLINK, SOCK_DGRAM, NETLINK_KOBJECT_UEVENT);
	if( fd < 0 )
	{
		printf("error: open socket error ret=%d\n", fd);
		return -1;
	}

	ret = setsockopt ( fd, SOL_SOCKET, SO_RCVBUF, &bufsize, sizeof( int ) );
	if( ret < 0 )
	{
		printf ( "error : set sockopt error. fd=%d ret=%d\n", fd, ret);
		return -2;
	}

	ret = bind ( fd, (struct sockaddr *)&snl, sizeof(struct sockaddr_nl) );
	if( ret < 0 )
	{
		printf( " error : bind error. fd=%d ret=%d\n", fd, ret);
		return -3;
	}

	return fd;
}

int main(void)
{
	int fd = 0;
	char *buf;
	int readlen=0;
	int i = 100;

	fd = 
#if 0
		init_udev_socket_v1();
#else
		init_udev_socket_v2();
#endif
	if( fd < 0 )
	{
		printf("Error: init udev socket error ret=%d\n", fd);
		return -1;
	}

	buf = (char *)malloc(1024);
	if( buf == 0 )
	{
		printf ( "Error : memory out.\n");
		return -2;
	}
	memset(buf, 0, 1024);

	while( i-- )
	{
		printf("<<<<<<<<<<<<<<<<<<<<<<wait for udev message>>>>>>>>>>>>>>>>>>>>>\n");

		readlen = recv(fd, buf, 1024, 0);
		printf("readlen = %d\nbuf = \n\t%s\n", readlen, buf);
		dump_buf(buf, readlen);
	}

	return 0;
}

