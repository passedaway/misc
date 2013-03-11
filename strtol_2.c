/*
 * =====================================================================================
 *
 *       Filename:  strtol_2.c
 *
 *    Description:  strtol modify version
 *
 *        Version:  1.0
 *        Created:  2012年11月27日 15时31分05秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Zhao, Changqing (NO), changqing.1230@163.com
 *        Company:  iPanel TV inc.
 *
 * =====================================================================================
 */
long long mystrtol(char *str)
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

	end = str;
	while( *end != 0 )
	{
		if ( ((*end >= '0') && (*end <= '9')) ||
			((*end >= 'a') && (*end <= 'f' )) ||
			((*end >= 'A') && (*end <= 'F' ))  )
			end++;
		else
			break;
	}
	end--;

	while(end >= str)
	{
		if(*end >= '0' && *end <= '9')
			data += (*end - '0') * qen;
		else if( *end >= 'a' && *end <= 'f')
			data += (*end - 'a' + 0x0a) * qen;
		else if( *end >= 'A' && *end <= 'F')
			data += (*end - 'A' + 0x0a) * qen;
		else
			return data;

		end--;
		qen *= qenue;
	}

	return data;
}

