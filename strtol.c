/*
 * =====================================================================================
 *
 *       Filename:  strtol.c
 *
 *    Description:  0x string convert to long
 *
 *        Version:  1.0
 *        Created:  07/29/2011 07:57:05 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Zhao, Changqing (NO), changqing.1230@163.com
 *        Company:  NULL
 *
 * =====================================================================================
 */
#include <string.h>
#include <stdio.h>

long long strtol(char *str);

int main(int argc, char **argv)
{
	long long data = 0;

	if( argc != 2 )
	{
		fprintf(stderr, "Usage : %s [0x....]\n", argv[0]);
		return -1;
	}
	
	data = strtol(argv[1]);	

	if( data == -1 )
	{
		fprintf(stderr, "Error : data not 0x.. or 0X...\n");
		return -1;
	}

	printf("%s : %lld \t 0x%llx\n", argv[1], data, data);
	return 0;
}

long long strtol(char *str)
{
	char *end = 0;
	long long data = 0;
	long long qen = 1, qenue = 0;

	while( *str != 0 )
	{
		if( *str == ' ' || *str == '\t' )
			str++;
		else
			break;
	}

	if(*str == '0' && ( *(str + 1) == 'x' || *(str+1) == 'X'))
	{
		qenue = 16;
		str += 2;
	}
	else
		qenue = 10;

	end = str + strlen(str) - 1;

	while(end >= str)
	{
		if(*end >= '0' && *end <= '9')
			data += (*end - '0') * qen;
		else if( *end >= 'a' && *end <= 'f')
			data += (*end - 'a' + 0x0a) * qen;
		else if( *end >= 'A' && *end <= 'F')
			data += (*end - 'A' + 0x0a) * qen;
		else
			return -1;

		end--;
		qen *= qenue;
	}

	return data;
}
