/*
 * =====================================================================================
 *
 *       Filename:  hash.c
 *
 *    Description:  name hash
 *
 *        Version:  1.0
 *        Created:  05/27/2013 17:57:13 PM
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
#include <string.h>
#include <stdlib.h>

#include "hash.h"

#ifdef DEBUG
#ifdef DEBUG_HASH
#define MODULE_NAME		"hash"
#define dbg(fmt, args...)	printf(MODULE_NAME"[%s]: "fmt, __FUNCTION__, ##args )
#else
#define dbg(fmt, args...)	
#endif
#else
#define dbg(fmt, args...)	
#endif

static int _grow_hash_table(hash_table_t *pht);

/* hash method from git-core */
#if 0
/* ignore case
 * This removes bit 5 if bit 6 is set.
 *
 * That will make US-ASCII characters hash to their upper-case
 * equivalent. We could easily do this one whole word at a time,
 * but that's for future worries.
 */
static inline unsigned char icase_hash(unsigned char c)
{
	return c & ~((c &0x40) >> 1);
}
#endif

void hash_table_exit(hash_table_t *pht)
{
	if( pht->array )
	{
		free(pht->array);
		pht->array = NULL;
	}

	pht->size = 0;
	pht->num = 0;
#if CONFLICT
	pht->conf_num = 0;
#endif
}

unsigned int hash_gen(const char *name, int namelen)
{
	unsigned int hash = 0x123;
	unsigned char c = 0;
	if(namelen <= 0)
		return 0;

	do {
		c = *name++;
		//c = icase_hash(c);
		hash = hash*101 + c;
	} while (--namelen);
	return hash;
}

void **hash_insert_str(hash_table_t *pht, const char *str)
{
	unsigned int hash = hash_gen(str, strlen(str));
	return hash_insert(pht, hash, (void*)str);
}

void **hash_insert(hash_table_t *pht, unsigned int hash, void *ptr)
{
	int index;
#if CONFLICT
	int conf_num;
#endif

#if CONFLICT
	dbg("in hash=%u size=%d num=%d conf=%d\n", hash, pht->size, pht->num, pht->conf_num);
#else
	dbg("in hash=%u size=%d num=%d\n", hash, pht->size, pht->num);
#endif
	if( pht->num >= (pht->size / 2) )
	{
		if( -1 == _grow_hash_table(pht) )
		{
			if(0 == pht->size )
				return NULL;
		}
	}

	index = hash % pht->size;
#if CONFLICT
	conf_num = index;
#endif
	/* check conflict */
	while( pht->array[index].data )
	{
		if( pht->array[index].hash == hash )
		{
#if CONFLICT
			/* hash conflict, follow next, unit next is -1, just for remmber the pre */
			if( -1 == pht->array[index].next )
			{
				conf_num = index;
				index = pht->size - pht->conf_num;
			}
			else
				index = (index+1) % pht->size;
#else
			/* two thing's hash is same, means the two thing is same,
			 * this may be not happen, just the same thing */
			dbg("insert fail(already exists). hash:%u index:%d num:%d size=%d\n", 
				hash, index, pht->num, pht->size);
			return NULL;
#endif
		}
		else
			/* index conflict, just follow next */
			index = (index+1) % pht->size;
	}

	pht->array[index].hash = hash;
	pht->array[index].data = ptr;
#if CONFLICT
	pht->array[index].next = -1;
#endif
	pht->num++;
#if CONFLICT
	if( conf_num != index )
	{
		pht->conf_num++;
	}
#endif

#if CONFLICT
	dbg("insert ok. hash:%u index:%d conf_num:%d num:%d size=%d\n", 
			hash, index, pht->conf_num, pht->num, pht->size);
#else
	dbg("insert ok. hash:%u index:%d num:%d size=%d\n", 
			hash, index, pht->num, pht->size);
#endif
	return &pht->array[index].data;
}

void **hash_find(hash_table_t *pht, unsigned int hash)
{
	int index = hash % pht->size;

	dbg("hash=%u\n", hash);
	while( pht->array[index].data )
	{
		if( pht->array[index].hash == hash )
		{
#if CONFLICT
			if( -1 == pht->array[index].next )
#endif
				/* no conflict */
				return &pht->array[index].data;

#if CONFLICT
			/* hash conflict, follow next */
			index = pht->array[index].next;
#endif
		}

		/* index conflict */
		index = (index+1)%pht->size;
	}

	return NULL;
}

void **hash_find_str(hash_table_t *pht, const char *str)
{
	unsigned int hash;
	int index;

	dbg("find str: %s\n", str);
	if( !pht->size )
		return NULL;

	hash = hash_gen(str, strlen(str));
	index = hash % pht->size;

	dbg("str's hash: %u\n", hash);
	while( pht->array[index].data )
	{
		if( pht->array[index].hash == hash )
		{
#if CONFLICT
			dbg("match. next=%d\n", pht->array[index].next);
			if(-1 == pht->array[index].next)
#endif
				/* no conflict */
				goto out;

#if CONFLICT
			/* hash conflict, follow next */
			index = pht->array[index].next;
#endif
		}

		/* index conflict */
		index = (index+1)%pht->size;
	}

out:
	if( !pht->array[index].data )
		return NULL;
	if(0 == strcmp(str, (const char *)pht->array[index].data) )
		return &pht->array[index].data;
	return NULL;
}

static int _grow_hash_table(hash_table_t *pht)
{
	int new_size, old_size, i;
	hash_entry_t *array, *old_array;

	old_size = pht->size;
	if(0 == pht->size)
	{
		new_size = 512 * sizeof(hash_entry_t);
	}else
		new_size = 2 * old_size * sizeof(hash_entry_t);

	array = malloc(new_size);
	if( NULL == array )
	{
		dbg("memory out\n");
		return -1;
	}
	memset(array, 0, new_size);
	dbg("new memory 0x%x\n", new_size);

	/* set new size & array */
	old_array = pht->array;
	pht->size = new_size/sizeof(hash_entry_t);
	pht->array = array;
	pht->num = 0;

	/* re-insert in new */
	if( old_array )
	{
		for(i = 0; i < old_size; i++)
		{
			if( old_array[i].data )
			{
				hash_insert(pht, old_array[i].hash, old_array[i].data);
			}
		}

		/* free old data */
		dbg("free old 0x%x\n", old_size);
		if(old_array)
			free(old_array);
	}

	dbg("grow over\n");
	return 0;
}

