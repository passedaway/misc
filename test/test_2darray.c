#include <stdio.h>

int main(int argc, char **argv)
{
	char *_array[] = {
		"hello",
		"world",
		"test",
		"just"
	};

	printf("sizeof(argv):%d\n", sizeof(argv));

	printf("sizeof(array):%d\n", sizeof(_array));
	printf("arrary size (array):%d\n", sizeof(_array)/sizeof(_array[0]));
	return 0;
}
