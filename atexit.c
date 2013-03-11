#include <stdio.h>

static void my_exit1(void);
static void my_exit2(void);


int main(int argc, char **argv)
{
	atexit(my_exit1);
	atexit(my_exit2);
	atexit(my_exit1);

	for(;argc<<1 != 0;argc++)
		printf(" . "), fflush(stdout) , sleep(1);

	return 0;
}

void my_exit1(void)
{
	printf("my_exit1 excu\n");
}

void my_exit2(void)
{
	printf("my_exit2 excu\n");
}
