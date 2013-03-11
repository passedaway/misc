#include <stdio.h>
#include <string.h>

int passwd_check(void);

int main(int argc, char **argv)
{
	int ret = 0;

	ret = passwd_check();

	printf(" ret : %d\n\t%s\n", ret, ret?"Error":"Success");

	return 1;
}

int passwd_check(void)
{
	int times = 5;
	char *passwd = "123456";

	while(times--)
	{
		int pos = 0;
		char input_buf[80];
		char ch = 0;

		memset(input_buf, 0, 80);
		printf("***INPUT PASSWORD FOR CFE : \n");

		do{
			ch = fgetc(stdin);

			if( ch == 0)
				continue;

			if( ch == '\r' || ch == '\n')
				break;

			input_buf[pos++] = ch;

			if(pos == 80)
				break;

		}while(1);

		if(pos == 80)
		{
			printf("Error : password is too long!\nTry again!\n");
			continue;
		}

		input_buf[pos] = '\0';

		printf(">>>Debug INFO \ninput_password : %s\npasswd : %s\n>>>over\n", input_buf, passwd);

		if( !strcmp(input_buf, passwd) )
			return 0;

	}

	return 1;
}
