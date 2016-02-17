#include <stdio.h>

static char color[] = {0x11, 0x21, 0x31, 0x41, 0x51, 0x62, 0x72, 0x11, 0x3, 9, 9, 2};

#if 0
#define set_color(x) fprintf(stderr, "\033[%d;3%dm", color[x]>>4, color[x]&15)
#else
#define set_color(x,y) fprintf(stderr, "\033[%d;3%dm",x,y)
#endif
#define reset_color() fprintf(stderr, "\033[0m \n")

int main(int argc, char **argv)
{
#if 0
	if( argc != 3 )
	{
		printf("%s mode string\n", argv[0]);
		return 0;
	}
	printf("=====================\n");
	set_color(atoi(argv[1]));
	fprintf(stderr, "%s\n", argv[2]);
#else
	int i = 0;
	for(; i < 30;i++ )
	{
		printf("======%d==============\n",i);
		int j = 0;
		for(j = 0; j <= 9; j++)
		{
			set_color(i,j);
#endif
			fprintf(stderr, "hello,world!");

			reset_color();
		}
	}
	printf("\033[32;1m A006 $ \033[0m\n");
	return 0;
}
