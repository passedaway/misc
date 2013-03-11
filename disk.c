#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

const char *data = " #include <stdio.h>\n #include <unistd.h>\n #include <string.h>\n #include <fcntl.h>\n void dump_buf(unsigned char *buf, int);\n int main(int argc, char **argv)\n {\n int fd = 0;\n char buf[4096];\n int i = 0;\n if(argc == 1)\n";


void dump_buf(unsigned char *buf, int);

int main(int argc, char **argv)
{
	int fd = 0;
	char buf[4096];
	int i = 0;

	if(argc == 1)
	{
		fprintf(stderr, "Usage : %s <device name>\n", argv[0]);
		return -1;
	}

	if( (fd = open(argv[1], O_RDWR)) < 0)
	{
		fprintf(stderr, "Error : open device %s\n", argv[0]);
		return -2;
	}

#if 0
	if( lseek(fd, 4096*20, SEEK_SET) < 0)
	{
		fprintf(stderr, "Error : lseek on device %s\n", argv[0]);
		close(fd);
		return -2;
	}
#endif
	write(fd, data, 4096);
#if 0
	lseek(fd, -4096, SEEK_CUR);

	for(i = 0; i < 1; i++)
	{
		if(read(fd, buf, 4096) < 4096)
			return -1;
		dump_buf(buf, 4096);
	}
#endif

	close(fd);
	return 1;
}


void dump_buf(unsigned char *buf, int len)
{
	int i = 0;

	if(!buf || len < 0)
		return;

	printf("dump Buffer : %p\n", buf);
	while(len-- > 0)
	{
			printf("0x%02x ", *(buf+len));

			printf("%c ", (unsigned char )*(buf+len) > 'z' ? '.' : (unsigned char )*(buf+len) );
			i++;
			if( i == 8)
			{
				printf("\n");
				i = 0;
			}

	}
}
