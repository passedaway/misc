/*
 * =====================================================================================
 *
 *       Filename:  hash.c
 *
 *    Description:  name hash
 *
 *        Version:  1.0
 *        Created:  05/27/2013 10:31:49 AM
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
/* hash method from git-core */
/*
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

static unsigned int hash_name(const char *name, int namelen, int icase)
{
	unsigned int hash = 0x123;
	unsigned char c = 0;

	do {
		c = *name++;
		if( icase )
			c = icase_hash(c);
		hash = hash*101 + c;
	} while (--namelen);
	return hash;
}

/* from net */
static unsigned int bkdr_hash(const char *name, int namelen)
{
	const int seed = 131;//31 131 1313 13131 131313...
	unsigned int hash = 0;
	unsigned char c = 0;
	do{
		c = *name++;
		hash = (hash*seed) + c;
	}while(--namelen);
	return hash;
}

static unsigned int rs_hash(const char *name, int namelen)
{
	int b = 378551, a = 63689;
	unsigned int hash = 0;
	unsigned char c = 0;
	do{
		c = *name++;
		hash = hash * a + c;
		a = a*b;
	}while (--namelen);
	return hash;
}

static unsigned int js_hash(const char *name, int namelen)
{
	unsigned int hash = 1315423911;
	unsigned char c = 0;
	do{
		c = *name++;
		hash ^= ((hash<<5) + c + (hash>>2));
	}while( --namelen );
	return hash;
}

static unsigned int sdbm_hash(const char *name, int namelen)
{
	unsigned int hash = 0;
	unsigned char c = 0;
	do{
		c = *name++;
		hash = c + (hash<<6) + (hash<<16) - hash;
	}while( --namelen );
	return hash;
}

static unsigned int djb_hash(const char *name, int namelen)
{
	unsigned int hash = 5381;
	unsigned char c = 0;
	do{
		c = *name++;
		hash = c + (hash<<5) + hash;
	}while( --namelen );
	return hash;
}

static unsigned int dek_hash(const char *name, int namelen)
{
	unsigned int hash = namelen;
	unsigned char c = 0;
	do{
		c = *name++;
		hash = ((hash<<5)^(hash>>27))^c;
	}while( --namelen );
	return hash;
}

static unsigned int bp_hash(const char *name, int namelen)
{
	unsigned int hash = namelen;
	unsigned char c = 0;
	do{
		c = *name++;
		hash = hash<<7^c;
	}while( --namelen );
	return hash;
}
/* .... more */

int main(int argc, char **argv)
{
	unsigned int hash_code = 0, hash_code2 = 0;
	if ( NULL == argv[1] )
	{
		fprintf(stderr, "usage:\n\t%s string\n", argv[0]);
		return 0;
	}

	hash_code = hash_name( argv[1], strlen(argv[1]), 0);
	hash_code2 = js_hash(argv[1], strlen(argv[1]));
	printf("string: %s hash: %u\n", argv[1], hash_code);
	printf("string: %s hash: %u\n", argv[1], hash_code2);

	return 0;
}
