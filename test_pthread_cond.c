/*
 * ===========================================================================
 *
 *       Filename:  pthread_cond_test.c
 *
 *    Description:  test pthread_cond
 *
 *        Version:  1.0
 *        Created:  01/26/2015 05:21:39 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Changqing Zhao (tain), echo "Y2hhbmdxaW5nLjEyMzBAMTYzLmNvbQo=" | base64 -d
 *        Company:  FreedomIsNotFree.com
 *
 * ===========================================================================
 */
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

int main(int argc, char **argv)
{
	pthread_cond_t cond;
	pthread_mutex_t mutex;

	pthread_mutex_init(&mutex, NULL);
	pthread_cond_init(&cond, NULL);
	
	printf("signal cond 1\n");
	pthread_cond_signal(&cond);
	printf("signal cond 2\n");
	pthread_cond_signal(&cond);
	printf("signal cond 3\n");
	pthread_cond_signal(&cond);

	printf("wait cond 1\n");
	pthread_cond_wait(&cond, &mutex);
	printf("wait cond 2\n");
	pthread_cond_wait(&cond, &mutex);
	printf("run over.\n");
	printf("Test Over. pthread_cond_t signal N , then wait N, works OK.\n");

	return 0;

}

