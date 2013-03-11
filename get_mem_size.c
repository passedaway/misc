#include <stdio.h>
#include <stdlib.h>

void dumpptr(unsigned char *begin, int size);

int main(int argc, char **argv)
{
	char *p = NULL;
	char *begin = NULL;

	int size = 0;
	int getsize = 0;

	if(argc != 2)
	{
		fprintf(stderr, "Usage : %s <want mem size>\n");
		return 0;
	}

	size = atoi(argv[1]);
	printf("want size : %d\n", size);
	
	p = (char *)malloc( size * sizeof(char) );
	if( !p )
	{
		fprintf(stderr, "Error : malloc\n");
		return -1;
	}

	begin = p - 11 - 1 - sizeof(int);
	
	getsize = *(int *)(begin + 11 + 1);
	printf("get size : %d\n", getsize);

	printf("p = %p\nbegin = %p\n", p, begin);

	dumpptr((unsigned char *)begin, getsize);

	free(p);

	return 0;
}

void dumpptr(unsigned char *begin, int size)
{
	printf("dump ptr : %p\n", begin);

	while(size--)
		printf("%c 0x%02x ", *(begin + size - 1), *(begin + size - 1) );

	printf("\n");
}
