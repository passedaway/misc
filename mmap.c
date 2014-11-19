
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char **argv)
{
	int fd = 0;
	unsigned char *m_start, *m_end;
	size_t map_len = 128;
	int page_size;

	off_t offset = 0;

	offset = argv[1] ? strtol(argv[1], NULL, 0): 0x001086060;
	printf("offset : %ld %lx\n", offset, offset);

#if 0
	fd = open("/dev/mem", O_RDWR | O_SYNC);
#else
	fd = open("/dev/mem", O_RDWR );
#endif
	if( fd < 0 )
	{
		perror("open mem error");
		return -1;
	}

	page_size = getpagesize();
	map_len = map_len & ( ~(page_size - 1) );
	if( map_len == 0 )
		map_len = page_size;

	offset = offset & ( ~(page_size - 1));
	
	printf("page_size = 0x%x map_len = %d , fd = %d , offset = 0x%lx\n", 
	page_size, map_len, fd, offset);

	m_start = mmap(NULL, map_len, PROT_READ | PROT_WRITE , MAP_SHARED, fd, offset); 
	if( m_start == MAP_FAILED )
	{
		perror("mmap error");
		return -2;
	}
printf("mmap ok: m_start = %p\n", m_start);
printf("mmap: *m_start = %x\n", *m_start);

	{
		int i = 0;
		unsigned char * tmp = m_start;
		for(; i < map_len; i++)
		{
			printf("%04d: %d %c \n", i, *tmp, *tmp);
			tmp++;
			if( ( i % 60 ) == 0 )
			{
				printf("--More--");fflush(stdout);getchar();
			}
		}
		printf("\n");
	}

	if( m_start )
	{
		munmap(m_start, map_len);
		close(fd);
	}


	return 0;
}
