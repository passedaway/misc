#include <stdio.h>

#define SQR(x) (x)*(x)

int main(void)
{
	int i = 3, j = 3;

	printf("[%s] [%d] [%s]\n", __FILE__, __LINE__, __FUNCTION__);
	printf("sqr(3) = %d\nsqr(i++) = %d\nsqr(++i) = %d\n", SQR(3), SQR(i++), SQR(++j) );
	return 0;
}
