CFLAGS += -g -rdynamic -O0 -ggdb
CC := cc
test:test.o sigsegv.o
	$(CC) test.o sigsegv.o -o test -rdynamic
.PHONY:clean
clean:
	rm -rf *.o test
