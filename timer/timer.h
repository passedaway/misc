/*
 * =====================================================================================
 *
 *       Filename:  timer.h
 *
 *    Description:  implement timer(fake, or software)
 *
 *        Version:  1.0
 *        Created:  06/04/2013 05:50:59 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  echo "Q2hhbmdxaW5nLFpoYW8K" | base64 -d  (tain)
 * 			Email:	echo "Y2hhbmdxaW5nLjEyMzBAMTYzLmNvbQo=" | base64 -d 
 *        Company:  FreedomIsNotFree.com
 *
 * =====================================================================================
 */
#ifndef _TIMER_H_
#define _TIMER_H_
/* kernel's timer is fine, I like it, so I implement it
 * in user mode.
 * */

#define HZ 100	/* it's precision, 1s / 100 , 
				   that is 10ms, 
				   close to 10ms, 
				   but bigger then it */

#include "list.h"
typedef struct itimer_s{
	struct list_head list; /* list it */

	unsigned long expires;
	void(*function)(int iarg, void *parg);
	int iarg;
	void *parg;
}itimer_t;

void timer_init(void);
void timer_exit(void);

void add_timer(itimer_t *timer);
void del_timer(itimer_t *timer);
void del_timer_sync(itimer_t *timer);

unsigned long get_jiffies(void);
#define jiffies get_jiffies()

#endif

