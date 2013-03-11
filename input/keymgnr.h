/*
 * =====================================================================================
 *
 *       Filename:  keymgnr.h
 *
 *    Description:  key manager for ipanel input
 *
 *        Version:  1.0
 *        Created:  2012年11月01日 12时03分57秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Zhao, Changqing ,changqing.1230@163.com
 *        Company:  iPanel TV inc.
 *
 * =====================================================================================
 */
#ifndef _IPANEL_KEY_MGNR_H_
#define _IPANEL_KEY_MGNR_H_

int key_mgnr_init(const char *ir_cfg_name, int print_flag);
void key_mgnr_exit(void);

int key_mgnr_get_usercode(void);
int key_mgnr_get_ipanel_key(unsigned int keycode);
int key_mgnr_get_input_key(unsigned int ipanel_key);
int key_mgnr_get_keynums(void);

#endif

