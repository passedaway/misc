#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>

int main(int argc, char **argv)
{
	int fd = 0;
	unsigned char buf[4096];

	if(argc != 2)
	{
		fprintf(stderr, "Usage : %s <filename>\n", argv[0]);
		return -1;
	}

	if( (fd = open(argv[1], O_RDWR | O_CREAT | O_TRUNC, 0555)) < 0 )
	{
		perror("Create file Error : ");
		return -1;
	}

	memset(buf, 0xff, 4096);

	if( write(fd, buf, 4096) != 4096 )
	{
		perror("Write Error : ");
		return -1;
	}

	close(fd);

	return 0;
}
