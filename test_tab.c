#include <stdio.h>

int main(int argc, char **argv)
{
	int a = 0;

	printf("\\t %d\n", '\t');

	while(1)
	{
	printf("input : ");
	scanf("%c", &a);

	printf("\n%x %c\n", a, a);
	}
	return 1;
}
