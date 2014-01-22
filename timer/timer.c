/*
 * =====================================================================================
 *
 *       Filename:  timer.c
 *
 *    Description:  imple timer.h
 *
 *        Version:  1.0
 *        Created:  06/04/2013 05:55:32 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  echo "Q2hhbmdxaW5nLFpoYW8K" | base64 -d  (tain)
 *			Email:	echo "Y2hhbmdxaW5nLjEyMzBAMTYzLmNvbQo=" | base64 -d 
 *        Company:  FreedomIsNotFree.com
 *
 * =====================================================================================
 */
#include "timer.h"

#include <pthread.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

#include <stdio.h>

#define PEROID	((1000/HZ)*1000)

/* I want to get more precise precision, 
 * but result is not better 
 * */
#define _JIFFIES_THREAD_	0 
static unsigned long _jiffies;
unsigned long get_jiffies(void)
{
	return _jiffies;
}

/* local */
static pthread_t _timer_thread;
static int _task_run_flag;
static struct list_head _timer_list;
static void *_timer_task(void *pargs);
#if _JIFFIES_THREAD_
static pthread_t _jiffies_thread;
static int _jiffies_task_run_flag;
static void *_jiffies_task(void *pargs);
#endif

void timer_init(void)
{
	INIT_LIST_HEAD( &_timer_list );
	
#if _JIFFIES_THREAD_
	_jiffies_task_run_flag = 1;
	if( -1 == pthread_create(&_jiffies_thread, NULL, 
				_jiffies_task, NULL) )
	{
		_jiffies_task_run_flag = 0;
		return ;
	}
#endif
	_task_run_flag = 1;
	if( -1 == pthread_create(&_timer_thread, NULL, 
				_timer_task, NULL) )
	{
#if _JIFFIES_THREAD_
		_jiffies_task_run_flag = 0;
#endif
		_task_run_flag = 0;
		return ;
	}
}

void timer_exit(void)
{
	_task_run_flag = 0;
#if _JIFFIES_THREAD_
	_jiffies_task_run_flag = 0;
#endif
	usleep(PEROID);
}

void add_timer(itimer_t *timer)
{
	if( timer )
		list_add(&timer->list, &_timer_list);
}

void del_timer(itimer_t *timer)
{
	if( timer )
		list_del(&timer->list);
}

void del_timer_sync(itimer_t *timer)
{
	del_timer(timer);
}

/* local function */
void *_timer_task(void *pargs)
{
	struct timeval tv;
	struct list_head *pl;
	itimer_t *pitimer;

	while( _task_run_flag )
	{
		tv.tv_sec = 0;
		tv.tv_usec = PEROID;
		select(0, NULL, NULL, NULL, &tv);
#if !_JIFFIES_THREAD_
		_jiffies++;
#endif
		if( !list_empty(&_timer_list) )
		{
			pl = _timer_list.next; 
			while(pl != &_timer_list )
			{
				pitimer = container_of(pl, itimer_t, list);
				pl = pl->next;
				if( (_jiffies >= pitimer->expires) && (pitimer->function) )
				{
					list_del(&pitimer->list);
					pitimer->function(pitimer->iarg, pitimer->parg);
				}
			}
		}
	}

	return NULL;
}

#if _JIFFIES_THREAD_
void *_jiffies_task(void *pargs)
{
	struct timeval tv;

	while( _task_run_flag )
	{
		tv.tv_sec = 0;
		tv.tv_usec = PEROID;
		select(0, NULL, NULL, NULL, &tv);
		_jiffies++;
	}

	return NULL;
}
#endif

