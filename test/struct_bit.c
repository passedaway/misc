#include <stdio.h>

struct test_s{
	short s; /* 2 */
	char c; /* 1 */
	int flip:1;
	int nybble:4;
	int septet:7;
	int pad1:4; /* total 16 bits */
	char pad2; /* 1 */
};

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

		printf("sizeof struct test_s : %d\n", sizeof(struct test_s));
		printf("sizeof (long double) : %d\n", sizeof(long double));

		return 0;
}
