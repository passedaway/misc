/*
 * =====================================================================================
 *
 *       Filename:  test.c
 *
 *    Description:  test for file encode
 *
 *        Version:  1.0
 *        Created:  12/16/2013 11:46:56 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Lihong.wang ()
 *          Email:  xiaowang73@163.com
 *        Company:  FreedomIsNotFree.com
 *
 * =====================================================================================
 */

#include "file_encode.h"

#include <stdio.h>

int main(int argc, char **argv)
{

	FILE *fp;
	char buf[1024];
	int file_size = 0;

	char *ubuf = NULL;
	int ulen;

	const char *code = NULL;
	const char *type = NULL;

	/* 1.open the file */
	if( (fp = fopen(argv[1], "r")) == NULL )
	{
		printf("Error: fopen the file fail.\n");
		return -1;
	}

	/* 2.fread the full file to buf. */
	if( (file_size = (fread(buf, 1,sizeof(buf),fp))) == 0 )
	{
		printf("Error: fread the file fail.\n");
		return -1;
	}
	/*3. identify the file encoding */
	if( (file_encoding(buf, file_size, &ubuf, &ulen, &code, &type)) == 0 )
	{
		printf("Error: get the encoding of file error.\n");
		return -1;
	}

	/* 4 print the infomation */
	printf("%s charset: code %s, type %s\n\t ubuf %s, ulen %d \n", argv[1], code, type,
		ubuf?ubuf:NULL, ulen);

	return 0;
}

