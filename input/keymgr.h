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

int keymgr_init(const char *ir_cfg_name, int print_flag);
void keymgr_exit(void);

const char *keymgr_get_config_name(void);
int keymgr_get_usercode(void);
int keymgr_get_ipanel_key(unsigned int keycode);
int keymgr_get_input_key(unsigned int ipanel_key);
int keymgr_get_keynums(void);

#endif

