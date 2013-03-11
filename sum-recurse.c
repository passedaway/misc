#include <stdio.h>

static int recurse(int i, int sum)
{
	if( i == 999 )
	{
		sum += i;
		return sum;
	}
	else{
		sum += i%2? i : 0;
		sum = recurse(i+1, sum);
	}
}

int main(int argc, char **argv)
{

#if 0
	//13
	int a[10] = {1, 3, 5,7,9,11,13,15,17,19};
	int *b = &a[3];

	printf("\n %d\n", (b+2)[1]);
#elif 0
	//14
	char a = 90, b= 50, c, d;
	c = a+b;
	d = c+a;
	printf("c= %d, d= %d\n", c, d);
#elif 0
	//16
	char a[1001];
	int i;
	memset(a, 0, sizeof(a));
	for(i = 0; i < 1000; i++)
		a[i]=-2-i;

	printf("%d\n", strlen(a));
#elif 1
	int sum = 0;
	int i = 1;
	for( ; i < 1000;i+=2)
	{
		sum += i; 
	}
	printf("sum = %d\n", sum);

	sum = 0;

	sum = recurse(1, sum);
	printf("sum = %d\n", sum);
#endif

	printf("argc = %d\n", argc);

	return 0;
}

