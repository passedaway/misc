#include <stdio.h>
#include <string.h>

int main(int argc, char **argv)
{
	int flag = 0;
	char passwd[10];

	memset(passwd, 0, 10);

	strcpy(passwd, argv[1]);

	printf("flag %p\npasswd %p\n", &flag, passwd);

	if( 0 == strcmp(passwd, "abcd") )
	{
		flag = 1;
	}

	if( flag )
	{
		printf("correct\n");
	}else
		printf("In correct\n");

	printf("flag = 0x%x\n", flag);

	return 0;
}
