#include <stdio.h>
#include <string.h>

int main(int argc, char **argv)
{
	int  n = 10;
	char buf[10];

	strcpy(buf, argv[1]);
	n = strlen(buf);
	printf("argc = %p\nmain = %p\n", &argc, &main);
	printf("argv[0] = %p argv[1] = %p \n", argv[0], argv[1]);
	printf("&argv = %p\n", &argv);

	printf("n = %p\nbuf=%p\n", &n , buf);

	return 0;

}
