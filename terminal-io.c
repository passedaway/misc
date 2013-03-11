#include <stdio.h>
#include <unistd.h>
#include <termios.h>

int main(void)
{
	int i = 0;
	struct termios term;
	char data[] = "0write0\n";
	int fd = 0;
	printf("printf 1\n");

	fd = dup(STDOUT_FILENO);
	/* ioctl set echo is null */
	tcgetattr(STDOUT_FILENO, &term);
	printf("c_lflag = %x\n", term.c_lflag);
	term.c_lflag &= ~ECHO; /*  this is for input */
	printf("c_lflag = %x\n", term.c_lflag);

//	term.c_oflag &= ~OPOST;
	tcsetattr(STDOUT_FILENO, TCSAFLUSH, &term);

	close(STDOUT_FILENO);

	printf("printf 2\n");
	
	write(fd, data, 7); 
			
	term.c_lflag |= ECHO;
	term.c_oflag |= OPOST;
	tcsetattr(fd, TCSAFLUSH, &term);

	dup2(fd, STDOUT_FILENO);
	printf("printf 3\n");

	return 0;
}
