
#include <stdio.h>

int main(int argc, char **argv)
{

	unsigned char a = 0x02, b=0x39, c=0x57;
	unsigned char h, m, s, s2;
	unsigned char htmp = 0, ltmp= 0;
	h = a&0x0f + ((a&0xf0)>>4) * 10; /* h is error too */
	htmp = ((b&0xf0)>>4) * 10;
	ltmp = b&0x0f;
	m = htmp + ltmp;
	s = (c&0x0f) + (((c&0xf0)>>4) * 10);
	s = (c&0x0f) + (((c&0xf0)>>4) * 10);
	s2 = c&0x0f + ((c&0xf0)>>4) * 10;/* s2 will error: + will do first, then is & */

	printf("a.b.c=%x:%x:%x lb=%d hb=%d\n", a, b, c, b&0x0f, ((b&0xf0)>>4)*10);
	printf("h.m.s=%d:%d:%d s2=%d\n", h, m, s, s2);

	return 0;

}
