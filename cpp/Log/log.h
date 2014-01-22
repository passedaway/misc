/*
 * =====================================================================================
 *
 *       Filename:  log.h
 *
 *    Description:  implement log class
 *
 *        Version:  1.0
 *        Created:  06/29/2013 01:45:23 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  echo "Q2hhbmdxaW5nLFpoYW8K" | base64 -d  (tain)
 * 			Email:	echo "Y2hhbmdxaW5nLjEyMzBAMTYzLmNvbQo=" | base64 -d 
 *        Company:  FreedomIsNotFree.com
 *
 * =====================================================================================
 */

#ifndef _LOG_H_
#define _LOG_H_

class Log{
	public:
		Log();
		~Log();
		int print(const char *fmt, ...);
		const char *to_str(void);

	private:
		char *buf;
		int wpos, rpos, size;
};

#endif

