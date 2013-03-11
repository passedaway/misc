/* test for close stdout, then printf something, then reopen stdout 
 *
 * such as : close(stdout); printf(safa); open stdout;
 * 
 * the code as :
 * 			fd = dup(stdout);
 *
 * 			close(stdout);
 *
 * 			printf("asfaa");
 *
 * 			dup2(fd, stdout);
 *
 */

#include <stdio.h>
#include <unistd.h>

int main()
{
	int fdout = 0, fderr = 0;

	fdout = dup(STDOUT_FILENO);
	fderr = dup(STDERR_FILENO);
	printf("stdout_fileno %d \n stderr_fileno %d\n\n", STDOUT_FILENO, STDERR_FILENO);
	printf("hello,world. 1\n");

	close(STDOUT_FILENO);
	close(STDERR_FILENO);

	printf("hello, world. 2\n");

	dup2(fdout, STDOUT_FILENO);
	dup2(fderr, STDERR_FILENO);

	printf("hello, world. 3\n");
	
	return 0;
}
