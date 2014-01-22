/*
 * =====================================================================================
 *
 *       Filename:  log.cpp
 *
 *    Description:  implement log class
 *
 *        Version:  1.0
 *        Created:  06/29/2013 01:46:48 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  echo "Q2hhbmdxaW5nLFpoYW8K" | base64 -d  (tain)
 *			Email:	echo "Y2hhbmdxaW5nLjEyMzBAMTYzLmNvbQo=" | base64 -d 
 *        Company:  FreedomIsNotFree.com
 *
 * =====================================================================================
 */

#include "log.h"
#include <stdarg.h>
#include <string.h>

Log::Log()
{
	size = 4096;
	buf = new char[4096];
	wpos = rpos = 0;
}

Log::~Log()
{
	if( buf )
		delete []buf;
}

int Log::print(const char *fmt, ...)
{
	char c;
	int flag = 0;
	va_list args;

	va_start(args, fmt);
	while(*fmt)
	{
		c = *fmt++;
		switch(c)
		{
			case '\b':
				continue;
			case '%':
				flag = 1;
				continue;

			case 's':
				if( flag )
				{
					char *tmp = va_arg(args, char *);
					int len = strlen(tmp);
					strncpy(buf+wpos, tmp, len);
					wpos += len;
					goto CLEAR_FLAG;
				}
				break;
		}

		buf[wpos++] = c;
CLEAR_FLAG:
		flag = 0;
	}
	va_end(args);

	buf[wpos] = 0;
	return wpos - rpos;
}

const char *Log::to_str(void)
{
	return buf+rpos;
}

