/*
 * ===========================================================================
 *
 *       Filename:  shm_test.c
 *
 *    Description:  linux IPC shared-memory test
 *
 *        Version:  1.0
 *        Created:  12/09/2014 06:48:39 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Changqing Zhao (tain), echo "Y2hhbmdxaW5nLjEyMzBAMTYzLmNvbQo=" | base64 -d
 *        Company:  FreedomIsNotFree.com
 *
 * ===========================================================================
 */
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <error.h>
#include <errno.h>


#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int main(int argc, char **argv)
{
	key_t key;
	int shm_fd;
	unsigned char *pc = NULL;

	char *is_set = argv[1];
	int is_exit = 0;

	if( argv[1] && (strcmp(argv[1],"exit") == 0 ) )
	{
		is_exit = 1;
	}

	do{
		//get a key
		/*ftok(filename, proj_id):
		 * filename: must  exists 
		 */
		key = ftok("/dev/zero", 'a');
		if( key == -1 )
		{
			printf("error: ftok %s\n", strerror(errno));
			break;
		}

		//use the key to create a SHM handle
		if ( is_exit )
		{
			shm_fd = shmget(key, 0x1000, 0);
		}else{
			shm_fd = shmget(key, 0x1000, IPC_CREAT | IPC_PRIVATE );
		}
		if( shm_fd == -1 )
		{
			printf("error: shmget %s\n", strerror(errno));
			break;
		}

		if( is_exit )
		{
			printf("destory SHM key(%x).\n", key);
			if( -1 == shmctl(shm_fd, IPC_RMID, NULL) )
			{
				printf("error: shmctl IPC_RMID %s\n", strerror(errno));
				break;
			}
			break;
		}

		//attatch : get the pointer of the SHM ( get the referance)
		if( is_set )
		{
			//read write
			pc = shmat(shm_fd, NULL, 0);
		}else{
			//read only
			pc = shmat(shm_fd, NULL, SHM_RDONLY);
		}
		if( pc == (void*)-1 )
		{
			printf("error: shmat %s\n", strerror(errno));
			break;
		}

		//do process
		if( is_set )
		{
			//write
			printf("write to SHM:#%s#\n", is_set);
			strcpy(pc, is_set);
		}else{
			//read
			printf("read from SHM:#%s#\n", pc);
		}
		
		//de-tatch : release the pointer of the SHM( put the referance)
		shmdt(pc);

		return 0;
	}while(0);

	//error process
	return -1;
}

