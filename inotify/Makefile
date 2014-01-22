CFLAGS += -c -Wall -g
LDFLAGS += -lpthread -g
CFG_DEBUG ?= 0
CFG_DEBUG_HASH ?= 0
CFG_DEBUG_WATCH ?= 0

ifeq ($(strip ${CFG_DEBUG}),1)
	CFLAGS += -DDEBUG
else
	CFLAGS += -UDEBUG
endif
ifeq ($(strip ${CFG_DEBUG_HASH}),1)
	CFLAGS += -DDEBUG_HASH
endif
ifeq ($(strip ${CFG_DEBUG_WATCH}),1)
	CFLAGS += -DDEBUG_WATCH
endif

EXE ?= test

all:$(EXE)

$(EXE):hash.o watch.o test.o
	@echo " LD $@ "
	@cc $^ $(LDFLAGS) -o $(EXE)

%.o:%.c
	@echo " CC $@ "
	@cc $(CFLAGS) $^ -o $@

.PHONY:clean
clean:
	@echo "Cleaning..."
	@rm -rf *.o $(EXE)

