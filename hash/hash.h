/*
 * =====================================================================================
 *
 *       Filename:  hash.h
 *
 *    Description:  hash api
 *
 *        Version:  1.0
 *        Created:  05/27/2013 05:46:32 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  echo "Q2hhbmdxaW5nLFpoYW8K" | base64 -d  (tain)
 * 			Email:	echo "Y2hhbmdxaW5nLjEyMzBAMTYzLmNvbQo=" | base64 -d 
 *        Company:  FreedomIsNotFree.com
 *
 * =====================================================================================
 */
#ifndef _HASH_H_
#define _HASH_H_

/* this is internal implement, so comment is less
 * see hash's use before
 **/

typedef struct hash_entry_s{
	unsigned int hash;
	unsigned int next;/* save conflict(index in hash_table) */
	void *data;/* hash_data */
}hash_entry_t;

typedef struct hash_table_s{
	unsigned int size, num, conf_num;
	hash_entry_t *array;
}hash_table_t;

unsigned int hash_gen(const char *str, int len);

static inline void hash_table_init(hash_table_t *pht)
{
	/* first not do anything, when first insert, it will grow buf */
	pht->size = 0;
	pht->num = 0;
	pht->conf_num = 0;
	pht->array = 0;
}

void hash_table_exit(hash_table_t *pht);
void **hash_insert(hash_table_t *pht, unsigned int hash, void *ptr);
void **hash_insert_str(hash_table_t *pht, const char *str);
void **hash_find(hash_table_t *pht, unsigned int hash);
void **hash_find_str(hash_table_t *pht, const char *str);
void hash_remove(hash_table_t *pht, unsigned int hash);
void hash_remove_str(hash_table_t *pht, const char *str);
#endif

