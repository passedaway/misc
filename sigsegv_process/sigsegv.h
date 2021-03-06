/*
 * =====================================================================================
 *
 *       Filename:  sigsegv.h
 *
 *    Description:  process signal segv, dump current stack
 *
 *        Version:  1.0
 *        Created:  2012年12月18日 10时57分03秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Zhao, Changqing ,changqing.1230@163.com
 *        Company:  iPanel TV inc.
 *
 * =====================================================================================
 */

#ifndef _SIGSEGV_H_
#define _SIGSEGV_H_

typedef void(*signal_callback_t)(void);

void setup_sigsegv(signal_callback_t cb);
void default_sigsegv(void);

#endif

