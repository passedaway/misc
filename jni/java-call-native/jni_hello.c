/*
 * =====================================================================================
 *
 *       Filename:  hello.c
 *
 *    Description:  hello.so
 *
 *        Version:  1.0
 *        Created:  04/01/2014 10:59:29 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  echo "Q2hhbmdxaW5nLFpoYW8K" | base64 -d  (tain)
 *          Email:  echo "Y2hhbmdxaW5nLjEyMzBAMTYzLmNvbQo=" | base64 -d 
 *        Company:  FreedomIsNotFree.com
 *
 * =====================================================================================
 */
#include <jni.h>
#include "Hello.h"

//JNI3 

//include other header files
#include <stdio.h>

JNIEXPORT void JNICALL Java_Hello_init(JNIEnv *env, jobject obj)
{
	fprintf(stderr, "hello_init over.\n");
}

JNIEXPORT void JNICALL Java_Hello_exit(JNIEnv *env, jobject obj)
{
	fprintf(stderr, "hello_exit over.\n");
}

#if 0
void hello_say(const char *fmt)
{
	fprintf(stderr, "hello_say: %s\n", fmt?fmt:"NULL");
}
#endif

