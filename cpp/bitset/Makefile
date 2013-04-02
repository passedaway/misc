a.out:main.o bitset.o
	@echo "  LD	$@	"
	@g++ $^ -o $@ 

%.o:%.cpp
	@echo "  CC	$^	"
	@g++ -c $^ -o $@

.PHONY:clean
clean:
	-rm -rf *.o a.out

