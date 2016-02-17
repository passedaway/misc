/*
 * ===========================================================================
 *
 *       Filename:  test_sem.c
 *
 *    Description:  test sem
 *
 *        Version:  1.0
 *        Created:  01/26/2015 06:04:35 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Changqing Zhao (tain), echo "Y2hhbmdxaW5nLjEyMzBAMTYzLmNvbQo=" | base64 -d
 *        Company:  FreedomIsNotFree.com
 *
 * ===========================================================================
 */

#include <stdio.h>
#include <semaphore.h>

int main(int argc, char **argv)
{
	sem_t sem;
	sem_init(&sem, 0, 3);

	printf("sem init with 3\n");
	sem_post(&sem);
	sem_post(&sem);
	sem_post(&sem);
	sem_post(&sem);

	printf("Try get 1:\n");
	sem_wait(&sem);
	printf("Try get 2:\n");
	sem_wait(&sem);
	printf("Try get 3:\n");
	sem_wait(&sem);

#if 1
	printf("Try get 4:\n");
	sem_wait(&sem);
#endif

	printf("Put 1:\n");
	sem_post(&sem);
	printf("get:\n");
	sem_wait(&sem);
	
	return 0;
}
