/*
 * =====================================================================================
 *
 *       Filename:  uclient.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2013年11月14日 12时56分37秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:   (NO),
 *        Company:
 *
 * =====================================================================================
 */
#include <sys/socket.h>
#include <sys/un.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include<sys/stat.h> //S_IRWXU
#include <fcntl.h>

#define CLI_PATH "/var/tmp"
#define CLI_PERM S_IRWXU
#define offsetof(TYPE, MEMBER) ((int)&((TYPE *)0)->MEMBER)

int client_recv_fd(const int sock_fd);

static struct sockaddr_un servaddr, localaddr;

void unix_send_fd(int sock_fd, int send_fd)
{
  int retval;
  struct msghdr msg;
  struct cmsghdr* p_cmsg;
  struct iovec vec;
  char cmsgbuf[CMSG_SPACE(sizeof(send_fd))];
  int* p_fds;
  char sendchar = 'a';

  memset(&msg, 0, sizeof(msg));

#if 0
  msg.msg_control = cmsgbuf;
  msg.msg_controllen = sizeof(cmsgbuf);
  p_cmsg = CMSG_FIRSTHDR(&msg);
  p_cmsg->cmsg_level = SOL_SOCKET;
  p_cmsg->cmsg_type = SCM_RIGHTS;
  p_cmsg->cmsg_len = CMSG_LEN(sizeof(send_fd));
  p_fds = (int*)CMSG_DATA(p_cmsg);
  *p_fds = send_fd;
  msg.msg_controllen = p_cmsg->cmsg_len;
#endif
  msg.msg_name = &servaddr;
  msg.msg_namelen = sizeof(servaddr);
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
int main(void)
{
	int fd,  get_fd, read_size;
	char buf[1024], s[]="hello china";
	ssize_t n;
	int send_fd;
	int len;

	if((fd = socket(AF_UNIX, SOCK_DGRAM, 0))<0)
	{
		perror("socket error");
		return -1;
	}

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sun_family = AF_LOCAL;
#define PATH "/var/tmp/foo1.sock"
#define PATH2 "/var/tmp/foo2.sock"
	strcpy(servaddr.sun_path, PATH);
	bzero(&localaddr, sizeof(localaddr));
	localaddr.sun_family = AF_LOCAL;
	strcpy(localaddr.sun_path, PATH2);
	len = offsetof(struct sockaddr_un, sun_path) + strlen(servaddr.sun_path);

	if(bind(fd,(struct sockaddr *)&localaddr, len) < 0)
		perror("bind error");

#if 1
	if(connect(fd, (struct sockaddr *)&servaddr, len)<0)
	{
		perror("connect error");
		return -1;
	}
#endif

#if 0
	get_fd = client_recv_fd(fd);
	memset(buf, 0, sizeof(buf));
	read_size = read(get_fd, buf, 100);
	printf("read_size = %d, %s\n", read_size, buf);
#endif
#if 0
	char recv_buff[1024];
	memset(recv_buff, 0, 1024);
	int ret = recvfrom(fd, recv_buff, 1024, 0, NULL, NULL);
	if(ret < 1)
	{
		perror("recvfrom");
	}
#endif

#if 1
		send_fd = open("hello.c", O_CREAT | O_RDWR, 0666);
		if( send_fd < 0 )
		{
			perror("open hello.c");
		}
		unix_send_fd(fd, send_fd);

		printf("press enter to exit\n");
		getchar();
		close(send_fd);
#endif

#if 0
	if(sendto(fd, s, strlen(s), 0, (struct sockaddr *)&servaddr, sizeof(servaddr)) == -1)
	{
		perror("sendto");
	}
	//if(n = read(fd, buf, sizeof(buf)) == -1)
	socklen_t len = sizeof(servaddr);
	n = recvfrom(fd, buf, sizeof(buf), 0, (struct sockaddr *)&servaddr, &len);
	if(n == -1)
	{
		perror("read");
	}
	/*
	if(n = write(STDOUT_FILENO, buf, n) != n)
	{
		preeor("write");
	}
	 * */
#endif
	return 0;
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

