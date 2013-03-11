#include <stdio.h>
#define NDEBUG
#include <assert.h>

int main(int argc, char **argv)
{
	printf("hello\n");

	assert(argv[1] != NULL);
	printf("end\n");
	return 1;
}
