#include <stdio.h>

#include <string.h>
#include <stdlib.h>

#if 1
typedef struct{
	union{
		unsigned char mac;
		long freq;
	};

	union{
		unsigned char tmp;
		int freq;
	}a;
	
//	int freq;/* this will be error, because the first union not have name, so the freq is second define in here */
}test_t;
#endif

void show_boy(void)
{
	test_t test;
	char *ptr = NULL;
	char *buf=malloc(2048);
	ptr = buf;
	if( ptr == NULL )
		return;
	memset(buf,0, 2048);

#if 1
	test.mac = 1;
	printf("test mac=%d test.freq = %d\n", test.mac, test.freq);
#endif
	
	ptr +=sprintf(buf,"                                 \\\\\\|///\n");
	ptr +=sprintf(ptr,"                               \\\\  - -  //\n");
	ptr +=sprintf(ptr,"                                (  @ @  )\n");
	ptr +=sprintf(ptr,"          ____________________oOOo_(_)_oOOo_________________________\n");
	ptr +=sprintf(ptr,"         |                                                          |\n");
	ptr +=sprintf(ptr,"         |            Welcome to xXxxxx Xxxxxxxxxx Xxxxxx           |\n");
	ptr +=sprintf(ptr,"         |                              Oooo                        |\n");
	ptr +=sprintf(ptr,"         |______________________ oooO___(   )_______________________|\n");
	ptr +=sprintf(ptr,"                                (   )    ) /\n");
	ptr +=sprintf(ptr,"                                 \\ (    (_/\n");
	ptr +=sprintf(ptr,"                                 \\_)\n");

	*ptr = 0;

	fprintf(stdout, "%s", buf);
	fflush(stdout);
	free(buf);
	buf = NULL;
}

int main(int argc, char **argv)
{
	printf("argc = %d\n",argc);
	show_boy();
	return 0;
}
