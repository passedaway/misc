/*
 * =====================================================================================
 *
 *       Filename:  date.c
 *
 *    Description:  get the date from system
 *
 *        Version:  1.0
 *        Created:  2011年08月15日 11时36分55秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Zhao, Changqing (NO), changqing.1230@163.com
 *        Company:  NULL
 *
 * =====================================================================================
 */
#include <time.h>
#include <stdio.h>

int main(void)
{
	time_t curtime;
	struct tm *tm_time = NULL;
	
	time(&curtime);

	//tm_time = (struct tm *)malloc(sizeof (struct tm));
	//tm_time = gmtime(&curtime);
	tm_time = localtime(&curtime);

	if(tm_time)
	{
		printf(	"sunday ~ sataday : 0 ~ 6\n");
		printf(	"tm_sec : %d\ntm_min : %d\n"
				"tm_hour : %d\ntm_mday : %d\n"
				"tm_mon : %d\ntm_year : %d\n"
				"tm_wday : %d\ntm_ydy : %d\n"
				"tm_isdst : %d\n",
				tm_time->tm_sec,
				tm_time->tm_min,
				tm_time->tm_hour,
				tm_time->tm_mday,
				tm_time->tm_mon + 1,
				tm_time->tm_year + 1900,
				tm_time->tm_wday,
				tm_time->tm_yday,
				tm_time->tm_isdst );
	}else{
		fprintf(stderr, "gmtime error\n");
		return -1;
	}

	return 0;
}
