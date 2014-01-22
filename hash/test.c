/*
 * =====================================================================================
 *
 *       Filename:  hash_test.c
 *
 *    Description:  test hash
 *
 *        Version:  1.0
 *        Created:  05/27/2013 07:45:02 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  echo "Q2hhbmdxaW5nLFpoYW8K" | base64 -d  (tain)
 *			Email:	echo "Y2hhbmdxaW5nLjEyMzBAMTYzLmNvbQo=" | base64 -d 
 *        Company:  FreedomIsNotFree.com
 *
 * =====================================================================================
 */
#include <stdio.h>

#include "hash.h"

int main(int argc, char **argv)
{
	hash_table_t hash_table;
#if 0
	char str1[] = "hello,";
	char str2[] = "world!";
#else
	char *str1 = "abc";
	char *str2 = "bac";
#endif

	hash_table_init(&hash_table);

	hash_insert_str(&hash_table, str1);
	hash_insert_str(&hash_table, str2);

	hash_find_str(&hash_table, str1);

	hash_find_str(&hash_table, str2);
	//printf("%s\n", 
	//printf("%s\n", hash_find_str(&hash_table, str2));

	hash_table_exit(&hash_table);
	return 0;
}

