/*
 * =====================================================================================
 *
 *       Filename:  server.c
 *
 *    Description: pass a file descriptor to another process  
 *
 *        Version:  1.0
 *        Created:  2013年11月15日 11时22分48秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:   zhln 
 *        Company:  
 *
 * =====================================================================================
 */

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <sys/time.h>
#include <sys/timeb.h>
#include <sys/types.h>
#include <dlfcn.h>
#include <time.h>
#include <stdarg.h>

#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <assert.h>
#include <signal.h>
#include <sys/param.h>
#include <sys/uio.h>
#include <stddef.h> // have offsetof

#include <sys/un.h>
#include <error.h>

static struct cmsghdr *cmptr = NULL;

#define CONTROLLEN (sizeof(struct cmsghdr) +sizeof(int))
#define QLEN 10

void unix_send_fd(int sock_fd, int send_fd)
{
  int retval;
  struct msghdr msg;
  struct cmsghdr* p_cmsg;
  struct iovec vec;
  char cmsgbuf[CMSG_SPACE(sizeof(send_fd))];
  int* p_fds;
  char sendchar = 0;
  msg.msg_control = cmsgbuf;
  msg.msg_controllen = sizeof(cmsgbuf);
  p_cmsg = CMSG_FIRSTHDR(&msg);
  p_cmsg->cmsg_level = SOL_SOCKET;
  p_cmsg->cmsg_type = SCM_RIGHTS;
  p_cmsg->cmsg_len = CMSG_LEN(sizeof(send_fd));
  p_fds = (int*)CMSG_DATA(p_cmsg);
  *p_fds = send_fd;
  msg.msg_controllen = p_cmsg->cmsg_len;
  msg.msg_name = NULL;
  msg.msg_namelen = 0;
  msg.msg_iov = &vec;
  msg.msg_iovlen = 1;
  msg.msg_flags = 0;
  /* "To pass file descriptors or credentials you need to send/read at
   * least on byte" (man 7 unix)
   */
  vec.iov_base = &sendchar;
  vec.iov_len = sizeof(sendchar);
  retval = sendmsg(sock_fd, &msg, 0);
  if (retval != 1)
  {
    perror("sendmsg");
  }
}

int client_recv_fd(const int sock_fd)
{
  int retval;
  struct msghdr msg;
  char recvchar;
  struct iovec vec;
  int recv_fd;
  char cmsgbuf[CMSG_SPACE(sizeof(recv_fd))];
  struct cmsghdr* p_cmsg;
  int* p_fd;
  vec.iov_base = &recvchar;
  vec.iov_len = sizeof(recvchar);
  msg.msg_name = NULL;
  msg.msg_namelen = 0;
  msg.msg_iov = &vec;
  msg.msg_iovlen = 1;
  msg.msg_control = cmsgbuf;
  msg.msg_controllen = sizeof(cmsgbuf);
  msg.msg_flags = 0;
  /* In case something goes wrong, set the fd to -1 before the syscall */
  p_fd = (int*)CMSG_DATA(CMSG_FIRSTHDR(&msg));
  *p_fd = -1;
  retval = recvmsg(sock_fd, &msg, 0);
  printf("retval == %d\n", retval);
  if (retval != 1)
  {
    puts("recvmsg");
  }
  p_cmsg = CMSG_FIRSTHDR(&msg);
  if (p_cmsg == NULL)
  {
    puts("p_cmsg == NULL no passed fd");
  }
  /* We used to verify the returned cmsg_level, cmsg_type and cmsg_len here,
   * but Linux 2.0 totally uselessly fails to fill these in.
   */
  p_fd = (int*)CMSG_DATA(p_cmsg);
  recv_fd = *p_fd;
  if (recv_fd == -1)
  {
    puts("no passed fd");
  }
  return recv_fd;
}
int main(void)
{
	int listensock, connsock, send_fd, size;
 	
	struct sockaddr_un servaddr, cliaddr;
	int ret;
	char buf[1024];
	ssize_t n;
	socklen_t len = sizeof(cliaddr);
	int get_fd;
	int read_size;
//	while(1)
	{
#if 0
		send_fd = open("hello.c", O_CREAT | O_RDWR);
#else
		//bug
		send_fd = open("hello.c", O_CREAT | O_RDWR, 0666);
#endif
		listensock = socket(AF_LOCAL, SOCK_DGRAM, 0);
		if(listensock < 0)
		{
			perror("socket");
			return -1;
		}
		memset(&servaddr, 0, sizeof(servaddr));
#define PATH	"/var/tmp/foo1.sock"
		unlink(PATH);
		servaddr.sun_family = AF_LOCAL;
		strcpy(servaddr.sun_path, PATH);
		len = offsetof(struct sockaddr_un, sun_path) + strlen(servaddr.sun_path);
	
		if(bind(listensock,(struct sockaddr *)&servaddr, len) < 0)
			perror("bind error");
	
#if 0
		//test recv
		{
			char buf[1024];
			int ret = 0;

			memset(buf, 0, sizeof(buf));
			ret = recv(listensock, buf, 1024, 0);
			printf("ret = %d buf[0]=%d %c\n", ret, buf[0], buf[0]);
		}
#else
		while(1)
		{
			struct msghdr msg;
			struct iovec vec;
			char buf[1024];
			int ret;

			memset(&msg, 0, sizeof(msg));
			memset(&vec, 0, sizeof(vec));
			vec.iov_base = &buf;
			vec.iov_len = 1024;
			msg.msg_iovlen = 1;
			msg.msg_iov = &vec;
			msg.msg_name = &servaddr;
			msg.msg_namelen = sizeof(servaddr);
			printf("wait for msg:\n");
			ret = recvmsg(listensock, &msg, 0);
			printf("ret = %d\n", ret);
			if( ret > 0 )
			{
				printf("msg->iovlen: %d, vec.iov_base:%x\n", 
						msg.msg_iovlen, vec.iov_base);
				printf("msg->iovlen : %d iovbase[0].[0] = %d\n", msg.msg_iovlen,
						*(char*)(msg.msg_iov[0].iov_base));
			}

#define PATH2	"/var/tmp/foo2.sock"
			strcpy(servaddr.sun_path, PATH2);
			msg.msg_name = &servaddr;
			msg.msg_namelen = sizeof(servaddr);
			buf[0] = 'b';
			vec.iov_len = 1;
			ret = sendmsg(listensock, &msg, 0);
			if( ret < 0  )
			{
				perror("send msg error");
			}
			printf("send msg over: ret=%d\n", ret);

			{
				static int i = 0;
				i++;
				if( i == 3 )
				{
					printf("normal exit.\n");
					_exit(0);
				}
			}
		}
#endif
#if 0
		if(connect(listensock, (struct sockaddr *)&servaddr, len)<0)
		{
			perror("connect error");
		}
#endif
#if 0	
		listen(listensock, QLEN);
		len = sizeof(un);
		if((connsock = accept(listensock, (struct sockaddr *)&un, &len))<0)
		{
			perror("accept error");
		}
		else	
		{	
			unix_send_fd(connsock, send_fd);
		}	
#endif	
	#if 0
//		unix_send_fd(listensock, send_fd);
		len = strlen(un.sun_path) + sizeof(un.sun_family);
		memset(send_buff, 0, 1024);
		sprintf(send_buff, "hello world");
		ret = sendto(listensock, send_buff, strlen(send_buff), 0, (struct sockaddr*)&un, len);
	
		if(ret < 0)
		{
			perror("sendto");
		}
		
		//unix_send_fd(listensock, send_fd);
	
#endif
		get_fd = client_recv_fd(listensock);
		memset(buf, 0, sizeof(buf));
		read_size = read(get_fd, buf, 100);
		printf("read_size = %d, %s\n", read_size, buf);
#if 0
		n = recvfrom(listensock, buf, sizeof(buf), 0, (struct sockaddr *)&servaddr, &len);
		//n = recvfrom(listensock, buf, sizeof(buf), 0, (struct sockaddr *)&cliaddr, &len);
		if(n = -1)
		{
			perror("recvfrom");
		}
		printf("buf == %s\n", buf);
		//if(sendto(listensock, buf, n, 0, (struct sockaddr *)&cliaddr, sizeof(cliaddr) != n))
		if(sendto(listensock, buf, n, 0, (struct sockaddr *)&servaddr, sizeof(servaddr) != n))
		{
			perror("sendto");
		}
#endif
		close(send_fd);	
//		close(connsock);
		close(listensock);
	}
	return 0;
}
