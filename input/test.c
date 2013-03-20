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

#include "keymgr.h"

#include <stdio.h>

int main(int argc, char **argv)
{
	keymgr_init(argv[1]?argv[1]:"abc.cfg", 0);

	printf("config file: %s\n", keymgr_get_config_name());
	printf("keynum = %d\n", keymgr_get_keynums());
	printf("Usercode = %x \n", keymgr_get_usercode());

	{
		printf("Poerkey256 = %x \n", keymgr_get_input_key(256));
		printf("Poerkey257 = %x \n", keymgr_get_input_key(257));
		printf("Poerkey258 = %x \n", keymgr_get_input_key(258));
	}

	printf("get ipanel_key 0xff48b7 = %d\n", keymgr_get_ipanel_key(0xff48b7));
	printf("get ipanel_key 0x48b7 = %d\n", keymgr_get_ipanel_key(0x48b7));
	printf("get ipanel_key 0x48 = %d\n", keymgr_get_ipanel_key(0x48));
	keymgr_exit();
	return 0;
}


