#include <stdio.h>

#include <string.h>
#include <stdlib.h>

void show_boy(void)
{
	char *ptr = NULL;
	char *buf=malloc(2048);
	ptr = buf;
	if( ptr == NULL )
		return;
	memset(buf,0, 2048);
	
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

int main(void)
{
	show_boy();
	return 0;
}
