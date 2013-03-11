/*
 * =====================================================================================
 *
 *       Filename:  test.c
 *
 *    Description:  for test keymgnr
 *
 *        Version:  1.0
 *        Created:  2012年11月01日 12时30分13秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Zhao, Changqing (NO), changqing.1230@163.com
 *        Company:  iPanel TV inc.
 *
 * =====================================================================================
 */

#include "keymgnr.h"

#include <stdio.h>

int main(void)
{
	union {
		short a;
		char c;
		int b;	
	} u;

u.b = 0x123456;
printf("u.a = %x u.b = %x u.c = %x\n", u.a, u.b, u.c);

	key_mgnr_init("abc.cfg", 0);

	printf("keynum = %d\n", key_mgnr_get_keynums());
	printf("Usercode = %x \n", key_mgnr_get_usercode());
	printf("Poerkey256 = %x \n", key_mgnr_get_input_key(256));
	printf("Poerkey257 = %x \n", key_mgnr_get_input_key(257));
	printf("Poerkey258 = %x \n", key_mgnr_get_input_key(258));

	printf("get ipanel_key 0xff48b7 = %d\n", key_mgnr_get_ipanel_key(0xff48b7));
	key_mgnr_exit();
	return 0;
}


