#include <stdio.h>

#ifdef __cplusplus
#warning "define cpp, use the default bool defination"
#else
/* define type bool */
typedef enum { 
	false = 0,
	true = 1
}bool;
#endif

int main(void)
{
	bool run = false;

	if( run == false )
		printf("run is false\n");
	else
		printf("run is true\n");

	printf("run=%d\n", run);

	return 0;
}
