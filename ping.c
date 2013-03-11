#include <stdio.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <netinet/ip_icmp.h>
#include <netdb.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

/* *****************definetion************************* */
#define PACKET_SIZE	4096
#define MAX_WAIT_TIME	3
#define MAX_NO_PACKETS	3

/* *****************gloable variable******************* */
char send_packet[PACKET_SIZE];
char recv_packet[PACKET_SIZE];

int sock_fd, datalen = 56;
int nsend = 0, nreceived = 0;

struct sockaddr_in dest_addr;
struct sockaddr_in from_addr;
pid_t pid;

/* *****************local function************************* */
static unsigned short check_sum(unsigned short *addr, int len);
static int unpack(char *buf, int len);
static int pack(int pack_no);
static void* statistics(void);

int main(int argc, char **argv)
{
	struct timeval time_recv;
	struct hostent *host;
	struct protoent *protocol;

	unsigned long inaddr = 0;
	int waittime = MAX_WAIT_TIME;
	int size = 50*1024;
	int n = 0;

	socklen_t len = 0;

	pid = getpid();

	if(argc < 2)
	{
		fprintf(stderr, "Usage : %s <hostname / ip address>\n", argv[0]);
		return -1;
	}

	//get protocol
	if( ( protocol = getprotobyname("icmp") ) == NULL )
	{
		perror("getprotobyname Error : ");
		return -2;
	}

	//get raw socket
	if( (sock_fd = socket(AF_INET, SOCK_RAW, protocol->p_proto)) < 0)
	{
		perror("socket(raw) Error : ");
		return -2;
	}
	
	//increase the buf of socket receive
	//incase of full of receive buffer
	setsockopt(sock_fd, SOL_SOCKET, SO_RCVBUF, &size, sizeof(size) );

	//fill info of dest
	bzero( &dest_addr, sizeof(dest_addr) );
	dest_addr.sin_family = AF_INET;

	if( (inaddr = inet_addr(argv[1])) == INADDR_NONE)
	{
		if( (host=gethostbyname(argv[1])) == NULL)
		{
			perror("gethostbyname Error : ");
			return -2;
		}

		memcpy( (char *)&dest_addr.sin_addr, host->h_addr, host->h_length);
	}else
		memcpy( (char *)&dest_addr.sin_addr, (char *)&inaddr, sizeof(inaddr));

	//send packet
	while(nsend < MAX_NO_PACKETS)
	{
		nsend++;

		pack(nsend);

		if( sendto(sock_fd, send_packet, 8+datalen, 0, (struct sockaddr*)&dest_addr, sizeof(dest_addr) ) < 0 )
		{
			perror("sendto Error : ");
			return -3;
		}

		usleep(500 * 1000);
	}
	
	//recv packet
	signal(SIGALRM,(void*) statistics);
	len = sizeof(from_addr);
	while( nreceived < nsend )
	{
		alarm(MAX_WAIT_TIME);

		if ( ( n = recvfrom(sock_fd, recv_packet, sizeof(recv_packet), 0, (struct sockaddr *)&from_addr , &len) ) < 0)
		{
			perror(" recvfrom Error : ");
			return -4;
		}

		gettimeofday(&time_recv, NULL);
		
		if( -1 == unpack(recv_packet, n) )
			continue;

		nreceived ++;
	}
	
	
	
	//statistics
	statistics();
	
	return 0;
}

unsigned short check_sum(unsigned short *addr, int len)
{
	int left = len;
	int sum = 0;
	unsigned short *pos = addr;
	unsigned short ret = 0;

	while(len > 1)
	{
		sum += *pos++;
		len -= 2;
	}

	if(len == 1 )
	{
		*(unsigned char *)(&ret) = *(unsigned char *)pos;
		sum += ret;
	}

	sum = (sum>>16) + (sum & 0xffff);
	sum += (sum>>16);
	ret = ~sum;
	return ret;
}

void* statistics(void)
{
	printf("--------------ping statistics---------------\n");
	printf("send %d packets\n"
			"receied %d\n"
			"lost %d%%100\n",
			nsend,
			nreceived,
			(nsend - nreceived) / nsend * 100);

	close(sock_fd);

	exit(1);
}

int unpack(char *buf, int len)
{
	int i, iphdrlen;
	struct ip *ip;
	struct icmp *icmp;
	struct timeval *tvsend;
	double rtt;

	ip = (struct ip*)buf;

	iphdrlen = ip->ip_hl<<2;
	icmp = (struct icmp *)(buf + iphdrlen);
	len -= iphdrlen;

	if( len < 8 )
	{
		printf("ICMP packets length is less than 8\n");

		return -1;
	}


	if( (icmp->icmp_type == ICMP_ECHOREPLY)  && (icmp->icmp_id == pid) )
	{
	//	tvsend = (struct timeval *)icmp->icmp_data;
		
		printf("%d bytes from %s: icmp_seq = %u ttl=%d \n", len,
				inet_ntoa(from_addr.sin_addr),
				icmp->icmp_seq,
				ip->ip_ttl);
	}
}

int pack(int pack_no)
{
	int i , packsize;

	struct icmp *icmp;
	struct timeval *tval;

	icmp = (struct icmp *)send_packet;
	icmp->icmp_type = ICMP_ECHO;
	icmp->icmp_code = 0;
	icmp->icmp_cksum = 0;
	icmp->icmp_seq = pack_no;
	icmp->icmp_id = pid;
	packsize = 8 + datalen;

	tval = (struct timeval *)icmp->icmp_data;
	gettimeofday(tval, NULL);
	icmp->icmp_cksum = check_sum((unsigned short *)icmp, packsize);

	return packsize;
}
