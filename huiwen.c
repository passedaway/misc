#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv)
{
    char *head = NULL, *end = NULL;

    if(argc != 2)
    {
        fprintf(stderr, "usage: %s [inputstring]\n", argv[0]);
        return -1;
    }

    head = argv[1];
    end = argv[1] + strlen(argv[1]) - 1;

    while((head < end) && (*head == *end))
        head++, end--;

#if 0
    head >= end ? fprintf(stdout, "%s is HUIWENSHU\n", argv[1]):\
    	fprintf(stdout, "%s is not HUIWENSHU\n", argv[1]);
#endif

	fprintf(stderr, "%s is%s HUIWENSHU\n", argv[1], head >= end ? "":" not");

    return 0;
}
