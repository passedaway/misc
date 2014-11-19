/*
 * =====================================================================================
 *
 *       Filename:  types.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  11/20/2014 02:21:09 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Changqing
 *        Company:  
 *
 * =====================================================================================
 */
#include <stdio.h>

int main(int argc, char **argv)
{
#define TE(a)   { #a , sizeof(a) }
    struct {
        const char *str;
        int size;
    }types[] = {
        TE(char),
        TE(short int),
        TE(int),
        TE(long),
        TE(long long),
        TE(void *),
    };

	printf("Type-Size of %d-bits OS :\n", sizeof(char*)*8);
    int i = 0;
    for( ; i < sizeof(types) / sizeof(types[0]); i++)
    {
        printf("%10s : %d\n", types[i].str, types[i].size);
    }

    return 0;
}
