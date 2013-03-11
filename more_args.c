#include <stdio.h>
#include <stdarg.h>

void usage(const char *fmt, ...);

int main(int argc, char **argv)
{
	usage("Usage : %s <%s> <%s>\n", argv[0], argv[1], argv[2]);

	return 1;
}

void usage(const char *fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	vprintf(fmt, args);
	va_end(args);
	fflush(stdout);

}
