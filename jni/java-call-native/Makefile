
all:
	javac Hello.java

so:
	cc -c jni_hello.c -I/usr/lib/jvm/java-7-openjdk-i386/include -I.
	cc -o libhello.so -shared jni_hello.o

clean:
	rm *.o libhello.so

