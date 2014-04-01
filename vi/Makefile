CFG_DEBUG	?= 0
CFG_LITTLE 	?= 1

src := $(wildcard *.c)
src_nodir := $(notdir $(src))

objs := $(src:%.c=%.o)    #this objs has src directory info

CFLAGS := -c -g -I.
LD_FLAGS := -lpthread 

ifeq ($(strip ${CFG_DEBUG}),1)
	CFLAGS += -DDEBUG -Wall
endif

ifeq ($(strip ${CFG_LITTLE}),1)
	CFLAGS += -DLITTLE_ENDIAN
endif

all:mvi
	@echo  compile success. 

mvi:$(objs)
	@echo " LD $(notdir $(objs)) ==> $@ "
	@cc -o $@ $^ $(LD_FLAGS)

$(filter %.o,$(objs)):%.o:%.c
	@echo " CC $(notdir $^) ==> $(notdir $@)	"
	@cc $(CFLAGS) $< -o $(notdir $@)

.PHONY:clean
clean:
	-rm -rf *.o mvi 

