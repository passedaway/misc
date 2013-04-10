/*
 * =====================================================================================
 *
 *       Filename:  test_font.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年04月10日 13时42分14秒
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
#include <fcntl.h>
#include <stdlib.h>

static void usage(void)
{
	printf("\nbecause the vim is use unicode, not gb2312, \n"
			"so I use windows NotePad to create a tmp file, then use the font gb2312\n"
			"then write some chinese word, then use the UE to reopen it, and check its HEX data\n"
			"then use here\n\n");
}

int main(int argc, char **argv)
{
	unsigned char buf[32];
	int fd, i, j, k, offset;
	char *filename = argv[1]?argv[1]:"HZK16.dat";

#if 1
	//unsigned char str[] = {0xCE, 0xD2};/* wo */
	unsigned char str[] = {0xd0, 0xb4};/* xie */
	//unsigned char str[] = {0xA3, 0xA1};/* ! */

	//房 0xB7BF gb2311
#else
	unsigned char *str = argv[2] ? argv[2] : "我";
#endif

	usage();
	
	fd = open(filename, O_RDWR);
	if( fd < 0 )
	{
		perror("cannot open file");
		exit(-1);
	}

	printf("str=%s sizeof(str） = %d 0x%02x 0x%02x\n", str, sizeof(str), *str, *(str+1));
#if 1
	offset = (94 * (str[0] - 0xa0 - 1) + (str[1] - 0xa0 - 1))*32;
#else
	offset = (94 * (0xB7 - 0xa0 - 1) + (0xBF - 0xa0 - 1))*32;
#endif

	lseek(fd, offset, SEEK_SET);
	read(fd, buf, 32);
	close(fd);

	/*  16 * 16 */
	for(i=0; i < 16; i++)
	{
		/* 2bytes is 16 bit*/
		for(j = 0; j < 2; j++)
		{
			for(k = 0; k < 8; k++)
			{
				if( buf[i*2+j] & (0x80>>k) )
					printf("%s", "$");
				else
					printf("%s", " ");

			}
		}
		printf("\n");
	}

	return 0;
}

