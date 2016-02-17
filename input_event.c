#include <unistd.h>
#include <fcntl.h>
#include <linux/input.h>
#include <stdio.h>
#include <string.h>


int main(int argc, char **argv)
{
	struct input_event event;
	int ret = 0;
	int fd = open(argv[1]?:"/dev/input/event1", O_RDWR );
	if( fd < 0 )
	{
		printf("open failed.\n");
		return -1;
	}

	while(1)
	{
		memset(&event, 0, sizeof(event));
		ret = read(fd, &event, sizeof(event));
		if( ret != sizeof(event) )
		{
			printf("read error ret=%d\n", ret);
			return -1;
		}

		printf("key: 0x%04x 0x%04x 0x%0x \n", 
				event.type, event.code, event.value);

	}


	return 0;
}
