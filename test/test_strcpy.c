#include <string.h>
#include <stdio.h>

int main(void)
{
	char *str1 = "abcd";
	char buf[10];
	int i = 0;
	
	for(; i < 10; i++)
		buf[i] = i;

	strncpy(buf, str1, 10);

	for(i = 0; i < 10; i++)
		printf("%d ", buf[i]);

	printf("\n");

	return 0;
	
}
