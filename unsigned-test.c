#include <stdio.h>

int main(void)
{
	int a = -20;
	unsigned int b = 5;

	(a+b > 6 ) ?puts(">6") : puts("<=6");

	printf("a+b = %x  a=u %u \n", a+b, a);

	return 0;
}
