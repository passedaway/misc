/*
 * =====================================================================================
 *
 *       Filename:  calljava.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  04/01/2014 03:40:19 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  echo "Q2hhbmdxaW5nLFpoYW8K" | base64 -d  (tain)
 *          Email:  echo "Y2hhbmdxaW5nLjEyMzBAMTYzLmNvbQo=" | base64 -d 
 *        Company:  FreedomIsNotFree.com
 *
 * =====================================================================================
 */
///usr/lib/jvm/java-7-openjdk/include
#include <jni.h>

#define MY_CLASS_PATH "."

int main(int argc, char **argv)
{
	JNIEnv *env = NULL;
	JavaVM *jvm = NULL;
	jint res;
	jclass cls;
	jmethodID mid;
	jstring jstr;
	jclass stringClass;
	jobjectArray args;
	JavaVMInitArgs vm_args;
	const char *class_name = "Hello";

#if 0
	//jdk version 1.1
	char classPath[1024];//new class path, add my class path

	//set vm create args
	vm_args.version = 0x010007;//jdk 1.7
	JNI_GetDefaultJavaVMInitArgs(&vm_args);
	//add user class path
	printf("C:default classPath is:%s\n", vm_args.classPath);
	sprintf(classPath, "%s;%s", vm_args.classPath, MY_CLASS_PATH);
	vm_args.classPath = classPath;
#else
	//jdk version 1.2 & upper
	JavaVMOption options[1];

	//set vm create args
	options[0].optionString = "-Djava.class.path=" MY_CLASS_PATH;
	vm_args.options = options;
	vm_args.nOptions = 1;
	vm_args.ignoreUnrecognized = JNI_TRUE;
	//JNI_GetDefaultJavaVMInitArgs(&vm_args);
	vm_args.version = JNI_VERSION_1_6;//jdk 1.6
#endif

	//create JVM
	res = JNI_CreateJavaVM(&jvm, &env, (void **)(&vm_args));
	if( res < 0 )
	{
		fprintf(stderr, "C:Error: create JVM error. ret=%d.\n", res);
		goto EXIT;
	}
	fprintf(stderr, "C: jvm Create Success.\n");

	//find my class
	if( argv[1] )
		class_name = argv[1];
	cls = (*env)->FindClass(env, class_name);
	if( cls == NULL )
	{
		fprintf(stderr, "C:Error: could not file %s.class\n", class_name);
		goto EXIT;
	}

	//get main function id from class
	mid = (*env)->GetStaticMethodID(env, cls, "main", 
			"([Ljava/lang/String;)V"); //function: (args)return-type
	if( mid == NULL )
	{
		fprintf(stderr, "C:Error: in %s.class didnot find main function.\n", class_name);
		goto EXIT;
	}

	//prepare for args;
	//
	//call function
	fprintf(stderr, "C: from now on in JVM.====\n");
	(*env)->CallStaticVoidMethod(env, cls, mid, NULL);
	fprintf(stderr, "****C: from now on out of JVM.\n");


EXIT:
	//destory jvm
	if( env )
	{
		if( (*env)->ExceptionOccurred(env) ) 
		{
			(*env)->ExceptionDescribe(env);
		}
	}

	if( jvm )
	{
		(*jvm)->DestroyJavaVM(jvm);
	}

	fprintf(stderr, "exit.\n");
	return 0;
}

