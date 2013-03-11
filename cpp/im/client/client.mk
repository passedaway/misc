all=c.o\
	cclientsocket.o\
	cmessage.o\
	cuserinfo.o\
	cfriendlist.o
$(all):c.c cclientsocket.c cmessage.c cuserinfo.c cfriendlist.c
	cc c.c -c -o c.o
	cc cclientsocket.c -c -o cclientsocket.o
	cc cmessage.c -c -o cmessage.o
	cc cuserinfo.c -c -o cuserinfo.o
	cc cfriendlist.c -c -o cfriendlsit.o

