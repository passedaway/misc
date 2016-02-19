#include <stdio.h>

static void call_main(int);
int g = 2;
int main(void)
{

	printf("main\n");
	call_main(g--);

	printf("main over\n");
	
}

void call_main(int a)
{
	if(a)
	{
		printf("in call_main a=%d\n", a);
		main();
	}
}
