INC += -I/usr/lib/jvm/java-1.7.0-openjdk-i386/include
#LDPATH += -L/usr/lib/jvm/java-7-openjdk-i386/jre/lib/i386/jamvm
LDPATH += -L/usr/lib/jvm/java-7-openjdk-i386/jre/lib/i386/server
LDFLAGS += -ljvm
CFLAGS += -g
all:
	cc calljava.c $(CFLAGS) $(INC) $(LDPATH) $(LDFLAGS) 
#	 /usr/lib/jvm/java-7-openjdk-i386/jre/lib/i386/jamvm/libjvm.so 
#	cc calljava.c -I/usr/lib/jvm/java-1.7.0-openjdk-i386/include/ -L/usr/lib/jvm/java-7-openjdk-i386/jre/lib/i386 -ljava
clean:
	-rm -rf *.o a.out
