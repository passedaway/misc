/*
 * ===========================================================================
 *
 *       Filename:  endian.c
 *
 *    Description:  print endian
 *
 *        Version:  1.0
 *        Created:  11/27/2014 05:48:29 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Changqing Zhao (tain), echo "Y2hhbmdxaW5nLjEyMzBAMTYzLmNvbQo=" | base64 -d
 *        Company:  FreedomIsNotFree.com
 *
 * ===========================================================================
 */
#include <stdio.h>

int main(int argc,char **argv)
{
	const char *res_endian[] = {"BE(Big Endian)", "LE(Little Endian)"};
	const char *res_bits[] = {"MSB(Most Significant Bit)", "LSB(Least Significant Bit)"};
	union{
		unsigned char c[4];
		int i;
	}test;
	union{
		union{
		unsigned int bit1:1;
		unsigned int res:7;
		}bit;
		unsigned char c;
	}test2;
	test.i = 0x00000001;
	test2.c = 0x01;

	printf("Endian : %s.\n Bits  : %s.\n", 
			res_endian[test.c[0]], 
			res_bits[test2.bit.bit1]);

	unsigned char a = 0x01;
	printf("0x01 bit0~7: %d%d%d%d%d%d%d%d\n",
			a&0x01, a&0x02, a&0x04, a&0x08,
			a&0x10, a&0x20, a&0x40, a&0x80);
	return 0;
}
