CFLAGS += -c -Wall -g
LDFLAGS += -lpthread -g
CFG_DEBUG ?= 0

ifeq ($(strip ${CFG_DEBUG}),1)
	CFLAGS += -DDEBUG
else
	CFLAGS += -UDEBUG
endif

EXE ?= test

all:$(EXE)

$(EXE):timer.o test.o
	@echo " LD $@ "
	@cc $^ $(LDFLAGS) -o $(EXE)

%.o:%.c
	@echo " CC $@ "
	@cc $(CFLAGS) $^ -o $@

.PHONY:clean
clean:
	@echo "Cleaning..."
	@rm -rf *.o $(EXE)

