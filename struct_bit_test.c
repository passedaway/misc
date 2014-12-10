#include <stdio.h>

int main(void)
{
		union{
			unsigned char c;
			struct {
				unsigned char bit1:1;
				unsigned char bit2:2;
				unsigned char bit3:3;
				unsigned char bit4;
			}s;
		} a;

		a.c = 0x55;

		printf("a.c = %x %d \na.s.bit1 = %x %d\n"
				"a.s.bit2 = %x %d\n" "a.s.bit3 = %x %d\n"
				"a.s.bit4 = %x %d\n",
				a.c, a.c , a.s.bit1, a.s.bit1,
				a.s.bit2, a.s.bit2, a.s.bit3, a.s.bit3,
				a.s.bit4, a.s.bit4);


		return 0;
}
