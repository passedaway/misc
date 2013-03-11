/*
 * =====================================================================================
 *
 *       Filename:  print.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2012年10月20日 16时01分34秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Zhao, Changqing (NO), changqing.1230@163.com
 *        Company:  iPanel TV inc.
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

int dbg_printf(const char *fmt, ... )
{
	va_list args;
	char *ptr = NULL;
	int len = 0, usecolor = 1;

	static char *m_pbuf = NULL;

	if( m_pbuf == NULL )
	{
		m_pbuf = (char *)malloc(512);
		if( m_pbuf == NULL )
			return -1;
	}
	memset(m_pbuf, 0, 1024);
	ptr = m_pbuf;

#if 0
	switch( level )
	{
		case LY_DBG_ERR:
			len = sprintf(prt, "\033[31;1mError: ");
			break;
		case LY_DBG_WARN:
			len = sprintf(ptr, "\033[31;2mWarn: ");
			break;
		case LY_DBG_INFO:
			len = sprintf(ptr, "\033[32;2mInfo: ");
			break;

		case LY_DBG_VERB:
			len = sprintf(ptr, "\033[36;2mVerb: ");
			break;
		default:
			usecolor = 0;
	}
	ptr+=len;
#endif

	{
		char *tmp = getenv("DBG_PRINT");
		printf("getenv: DBG_PRINT = %s\n", tmp ? tmp : "NULL");
		if ( getenv("DBG_PRINT") == NULL )
		{
			return -1;
		}
	}

	va_start(args, fmt);
	len = vsprintf(ptr, fmt, args);
	va_end(args);
	ptr += len;

#if 0
	if( usecolor );
	{
		len = sprintf(ptr, "\033[0m\n\r");
		ptr += len;
	}
#endif
	*ptr = 0;
	fflush(stderr);
	fprintf(stderr, "%s", m_pbuf);
	return (int)(ptr-m_pbuf);
}


int main()
{
	while(1)
	{
		dbg_printf("hell0\n");
		sleep(1);
		fprintf(stdout, ".");
		fflush(stdout);
	}

	return 0;
}
