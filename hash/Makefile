all:hash.o test.o
	cc $^ -g -o a.out

%.o:%.c
	cc -c -Wall -g $^ -o $@

.PHONY:clean
clean:
	-rm *.o a.out


