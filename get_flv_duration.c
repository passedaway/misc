#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

static void usage(int argc, char **argv)
{
	fprintf(stderr, "Usage : \n %s <filename.flv> \n", argv[0]);
	exit(-1);
}

int main(int argc, char **argv)
{
	unsigned long last_tag = 0;
	unsigned long timestamp = 0;
	unsigned char buf[4];
	unsigned char *tmp = 0;
	int fd = 0;

	if( argc != 2 )
		usage(argc, argv);

	fd = open(argv[1], O_RDWR);
	if( fd < 0 )
	{
		printf("Error : open file %s \n", argv[1]);
		return -1;
	}

	//get last tag
	if( -1 == lseek(fd, -4, SEEK_END) )
	{
		printf("Error : cannot lseek!\n");
		return -2;
	}
	read(fd, buf, 4);

	//dbg
	printf("buf = 0x%02x %02x %02x %02x\n", buf[0], buf[1], buf[2], buf[3]);

	last_tag = buf[0]<<24 | buf[1]<<16 | buf[2]<<8 | buf[3];
	printf("last_tag = %d \n", last_tag);

	tmp = (unsigned char *)malloc(last_tag);
	if( !tmp )
	{
		printf("Error : cannot alloc memeory!\n");
		return -3;
	}

	memset(tmp, 0, last_tag);
	if( -1 == lseek(fd, -4-last_tag, SEEK_CUR) )
	{
		printf("Error : cannot lseek file 2!\n");
		return -2;
	}

	read(fd, tmp, last_tag);

	{
		int i = 0;
		unsigned char *_a = tmp;
		printf("\n");
		for(; i < last_tag; i++)
			printf("0x%02x%s", *_a++, (i+1)%16?" ":"\n");
		printf("\n");
	}


	printf("\n tmp[4] 5 6 7 0x%02x %02x %02x %02x \n", tmp[4], tmp[5], tmp[6], tmp[7]);
	timestamp = (tmp[4])<<16 | 
				tmp[5]<<8 |
				tmp[6] | 
				tmp[7]<<24;

	printf("\n timestamp = 0x%08x %d\ntime %d min %d sec\n", 
			timestamp, timestamp,
			timestamp/1000/60,
			(timestamp/1000)%60
			);

	if(tmp)
		free(tmp);
	if(fd >= 0)
		close(fd);

	return 0;
}
