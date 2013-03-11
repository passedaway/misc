#include <stdio.h>
#include <setjmp.h>
#include <pthread.h>

jmp_buf jmptest;

void test(void);

void* child1(void*);

int main(int argc, char **argv)
{
	char i = 1;
	pthread_t pid1 = 0;

	pthread_create(&pid1, NULL, child1, NULL);

	while(i > 0)
	{
		usleep(500000);
		printf("%d\n", i);
		i++;
	}
//	pthread_create(&pid1, NULL, child1, NULL);

	pthread_join(pid1, NULL);

	return 0;
}

void test(void)
{
	printf("this is test\n");
	longjmp(jmptest, 1);

	printf("test after longjmp\n");
}

void* child1(void* args)
{
	int i = 0;

	setjmp(jmptest);

	sleep(2);
	if( i == 0 )
	{
		fprintf(stderr, "this is if i == 0, call test func\n");
		i++;
		test();
	}else{
		fprintf(stderr, "This is else\n");
	}
}
