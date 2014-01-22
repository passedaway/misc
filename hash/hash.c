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

static void _grow_hash_table(hash_table_t *pht);

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
	pht->conf_num = 0;
}

unsigned int hash_gen(const char *name, int namelen)
{
	unsigned int hash = 0x123;
	unsigned char c = 0;

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
	int index, conf_num;

	if( pht->num >= (pht->size / 2) )
	{
		_grow_hash_table(pht);
	}

	index = hash % pht->size;
	conf_num = index;
	/* check conflict */
	while( pht->array[index].data )
	{
		if( pht->array[index].hash == hash )
		{
			/* conflict, follow next, unit next is -1, just for remmber the pre */
			if( -1 == pht->array[index].next )
			{
				conf_num = index;
				index = pht->conf_num;
			}
			else
				index = (index+1) % pht->size;
		}
		else
			index = (index+1) % pht->size;
	}

	pht->array[index].hash = hash;
	pht->array[index].data = ptr;
	pht->array[index].next = -1;
	pht->num++;
	if( conf_num != index )
	{
		pht->conf_num++;
	}

	printf("hash: insert ok. hash:%u index:%d conf_num:%d num:%d\n", 
			hash, index, pht->conf_num, pht->num);
	return &pht->array[index].data;
}

void **hash_find(hash_table_t *pht, unsigned int hash)
{
	int index = hash % pht->size;

	while( pht->array[index].data )
	{
		if( pht->array[index].hash == hash )
		{
			if( -1 == pht->array[index].next )
			{
				/* no conflict */
				return &pht->array[index].data;
			}

			/* conflict, follow next */
			index = pht->array[index].next;
		}

		index = (index+1)%pht->size;
	}

	return NULL;
}

void **hash_find_str(hash_table_t *pht, const char *str)
{
	unsigned int hash;
	int index;

	printf("hash: find str: %s\n", str);
	if( !pht->size )
		return NULL;

	hash = hash_gen(str, strlen(str));
	index = hash % pht->size;

	printf("hash: str's hash: %u\n", hash);
	while( pht->array[index].data )
	{
		if( pht->array[index].hash == hash )
		{
			printf("hash: match. next=%d\n", pht->array[index].next);
			if(-1 == pht->array[index].next)
			{
				/* no conflict */
				goto out;
			}

			/* conflict, follow next */
			index = pht->array[index].next;
		}

		index = (index+1)%pht->size;
	}

out:
	if( !pht->array[index].data )
		return NULL;
	if(0 == strcmp(str, (const char *)pht->array[index].data) )
		return &pht->array[index].data;
	return NULL;
}

void hash_remove(hash_table_t *pht, unsigned int hash)
{
	

}

void hash_remove_str(hash_table_t *pht, const char *str)
{

}

static void _grow_hash_table(hash_table_t *pht)
{
	int new_size, old_size = pht->size, i;
	hash_entry_t *array, *old_array = pht->array;

	if(0 == pht->size)
	{
		new_size = 1024 * sizeof(hash_entry_t);
	}else
		new_size = 2 * old_size;

	array = malloc(new_size);
	if( !array )
	{
		printf("hash: memory out\n");
		return ;
	}
	memset(array, 0, new_size);
	printf("hash: new memory 0x%x\n", new_size);

	/* swap */
	pht->size = new_size;
	pht->array = array;
	pht->num = 0;

	/* re-insert in new */
	if( old_array )
	{
		old_size = pht->size;
		for(i = 0; i < old_size; i++)
		{
			if( old_array[i].data )
			{
				hash_insert(pht, old_array[i].hash, old_array[i].data);
			}
		}

		/* free old data */
		printf("hash: free old 0x%x\n", new_size);
		free(old_array);
	}

	printf("hash: grow over\n");
}

