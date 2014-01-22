/*
 * =====================================================================================
 *
 *       Filename:  getaddr.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2012年08月21日 16时11分31秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Zhao, Changqing (NO), changqing.1230@163.com
 *        Company:  iPanel TV inc.
 *
 * =====================================================================================
 */
#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/ioctl.h>

#include <net/if.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(int argc, char **argv)
{
    int fd = 0;
    struct ifreq ifr;
    struct sockaddr_in *ptr;
    int i = 0;

    if( argc <= 1 )
    {
        printf("error : %s [interface name]\n", argv[0]);
        return 0;
    }

    memset(&ifr, 0, sizeof(struct ifreq));
    strcpy(ifr.ifr_name, argv[1]);

    fd=socket(AF_INET, SOCK_DGRAM, 0);

    ioctl(fd, SIOCGIFADDR, &ifr);
    ptr = (struct sockaddr_in *)&(ifr.ifr_ifru.ifru_addr);
    printf(" %s : %s\n", argv[1], inet_ntoa(ptr->sin_addr));
    for(i=0; i < sizeof(ifr.ifr_ifru.ifru_addr.sa_data); i++)
        printf("%x ", ifr.ifr_ifru.ifru_addr.sa_data[i]);
    printf("\n");
    return 0;
}
