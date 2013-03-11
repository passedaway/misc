#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <sys/vfs.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char **argv)
{
	struct statfs statfs_buf;
	int fd = 0;

	if (argc < 2)
	{
		fprintf(stderr, "Usage : %s </dev/device name>\n", argv[0]);
		return 1;
	}

#if 1
	statfs(argv[1], &statfs_buf);
#else
	if( (fd = open(argv[1], O_RDWR) ) < 0)
	{
		perror("Open file Error ");
		return 1;
	}

	fstatfs(fd, &statfs_buf);
#endif

	printf("%s\n"
			"f_type : %ld\n"
			"all: %ld\n"
			"free: %ld\n"
			"use: %ld\n"
			"block size: %ld\n"
			, argv[1]
			, statfs_buf.f_type
			, statfs_buf.f_blocks
			, statfs_buf.f_bfree
			, statfs_buf.f_blocks - statfs_buf.f_bfree
			, statfs_buf.f_bsize
		  );

	return 0;
}
