#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>

int main(int argc, char **argv)
{
	int fd = 0;
	unsigned char buf[4096];
	int i = 0, j = 0;

	if(argc != 2)
	{
		fprintf(stderr, "Usage : %s <filename> \n", argv[0]);
		return -1;
	}

	if( (fd = open(argv[1], O_RDWR) ) < 0)
	{
		perror("Open File Error ");
		return -1;
	}

	memset(buf, 0, 4096);
	if( read(fd, buf, 4096) < 0 )
	{
		perror("Read Error ");
		close(fd);
		return -2;
	}

	for( i = 0; i < 4096; i++)
	{
		printf("%x ", buf[i]);
		
		if( ((i+1)%16) == 0)
		{
			for( j = i - 15; j < i; j++ )
				printf("%c ", buf[j]);

			printf("\n");
		}
	}

	close(fd);
	return 0;
}
