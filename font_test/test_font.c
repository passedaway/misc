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

#define CHINA_DAT "HZK16.dat"
#define ASCII_DAT "ASC168.dat"

static void usage(void)
{
	printf("\nbecause the vim is use unicode, not gb2312, \n"
			"so I use windows NotePad to create a tmp file, then use the font gb2312\n"
			"then write some chinese word, then use the UE to reopen it, and check its HEX data\n"
			"then use here\n\n");
}

static void show_china(unsigned char *data);
static void show_ascii(unsigned char c);
static int show_char(unsigned char *data);

int main(int argc, char **argv)
{
	unsigned char data[] = {
		0xce, 0xd2, /* wo */
		0xd4, 0xda, /* zai */
		0xd0, 0xb4, /* xie */
		0xb4, 0xfa, /* dai */
		0xc2, 0xeb, /* ma */
		0xa3, 0xa1 /* ! */
		,'I', 0x61, 0x6d,
		'C', 'o', 'D', 'I', 'N', 'G', '!'
		,0
	};
	unsigned char *str = data;
	int ret = 0;

	usage();
	
	printf("str = %s\n", data);
	while(1){
		ret = show_char(str);
		if ( ret == 0 )
			break;

		str += ret;
		printf("\n");
	}

	return 0;
}

static int show_char(unsigned char *data)
{
	if(data && *data)
	{
		if(*data < 0x80)
		{
			show_ascii(*data);
			return 1;
		}else if( *data > 0xA0 )
		{
			show_china(data);
			return 2;
		}

		return 0;
	}

	return 0;
}

static void show_china(unsigned char *data)
{
	unsigned char buf[32];
	int fd, i, j, k, offset;
	fd = open(CHINA_DAT, O_RDWR);
	if( fd < 0 )
	{
		perror("cannot open file");
		exit(-1);
	}
	offset = (94 * (data[0] - 0xa0 - 1) + (data[1] - 0xa0 - 1))*32;

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
					printf("$");
				else
					printf(" ");

			}
		}
		printf("\t0x%02x 0x%02x\n", buf[i*2], buf[i*2+1]);
	}
}

static void show_ascii(unsigned char c)
{
	unsigned char buf[16];
	int fd, i, j, offset;

	fd = open(ASCII_DAT, O_RDWR);
	if( fd < 0 )
	{
		perror("cannot open file");
		exit(-1);
	}
	offset = c * 16;

	lseek(fd, offset, SEEK_SET);
	read(fd, buf, 16);
	close(fd);

	/*  8 * 16 */
	for(i=0; i < 16; i++)
	{
		for(j = 0; j < 8; j++)
		{
			if( buf[i] & (0x80>>j) )
				printf("#");
			else
				printf(" ");
		}
		printf("\t\t0x%02x\n", buf[i]);
	}
}
