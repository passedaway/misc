
CC = g++
CFLAGS += -Wall 

EXE := test.exe

all:$(EXE)


$(EXE):main.o log.o
	@echo " LD $@"
	@$(CC) $^ -o $(EXE)

%.o:%.cpp
	@echo " CC $@"
	@$(CC) $^ -c $(CFLAGS) -o $@

.PHONY:clean
clean:
	-rm -rf *.o $(EXE)
