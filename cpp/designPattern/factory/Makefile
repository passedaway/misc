
extends := product

EXE:=factory

all:$(EXE)


$(EXE):main.o $(EXE).o $(extends).o
	@echo "LD $^ ==> $@"
	@g++ $^ -o $@ 

%.o:%.cpp
	@echo "CPP $^ --> $@"
	@g++ -o $@ -c $^

.PHONY:clean
clean:
	-rm -rf *.o $(exe)

