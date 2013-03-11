#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

void dumpbuf(unsigned char *buf);

int main(void)
{
	int fd = 0;
	int ret = 0;
	unsigned char buf[4096];
	unsigned long offset = 0;

	fd = open("/dev/mem", O_RDONLY | O_SYNC);
	if(fd < 0)
	{
		fprintf(stderr, "Error : open file /dev/mem");
		exit(-1);
	}

	while( (ret = read(fd, buf, 4096)) == 4096)
	{
		printf("addr : %x %d ", offset, offset);
		buf[4095] = 0;
		puts(buf);
		offset += ret;
		dumpbuf(buf);
	}

	close(fd);
	return 0;
}

void dumpbuf(unsigned char *buf)
{
	int i = 0;

	printf("dump buf : \n");
	for(; i < 4096; i++)
		fprintf(stdout, " %02x ", buf[i]);

	printf("\n");
}
