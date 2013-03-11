CC= /opt/broadcom/toolchain/stbgcc-4.5.3-1.3/bin/mipsel-linux-gcc
CFLAGS=-g -O -Wall -I.. -D_REENTRANT
LIBPTHREAD=-lpthread

PROGS=multimac

all: $(PROGS)

.c:
	$(CC) $(CFLAGS) -o $* $*.c $(LIBPTHREAD)
#	killall multimac || true

$(PROGS):

clean:
	rm -f $(PROGS)
