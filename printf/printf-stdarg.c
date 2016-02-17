#include <stdarg.h>
#include <stddef.h>

#define TEST_PRINTF 1

#define printf os_printf
#define putchar os_putchar

static void printchar(char * *str, int c)
{
#if 0
	//test in unix for UPPER
	if( (c >= 'a') && (c <= 'z') )
		c -= 0x20;
#endif

    if (str) {
        **str = c;
        ++(*str);
    }
#ifdef TEST_PRINTF
    else {
		/*
		 * todo: this is the putchar's reference
		 */
        extern int putchar(int c);
        (void)putchar(c);
    }
#endif
}

#define PAD_RIGHT 1
#define PAD_ZERO  2

static int prints(char * *out, const char *string, int width, int pad, int limit)
{
    register int pc = limit, padchar = ' ';

    if (width > 0) {
        register int len = 0;
        register const char *ptr;
        for (ptr = string; *ptr; ++ptr) {
            ++len;
        }
        if (len >= width) {
            width = 0;
        } else {
            width -= len;
        }
        if (pad & PAD_ZERO) {
            padchar = '0';
        }
    }
    if (!(pad & PAD_RIGHT)) {
        for (; width > 0 && pc; --width) {
            printchar(out, padchar);
            --pc;
        }
    }
    for (; *string && pc; ++string) {
        printchar(out, *string);
        --pc;
    }
    for (; width > 0 && pc; --width) {
        printchar(out, padchar);
        --pc;
    }

    return limit - pc;
}

/* the following should be enough for 32 bit int */
#define PRINT_BUF_LEN 12

static int printi(char * *out, int i, int b, int sg, int width, int pad, int letbase, int limit)
{
    char print_buf[PRINT_BUF_LEN];
    register char *s;
    register int t, neg = 0, pc = limit;
    register unsigned int u = i;

    if (i == 0) {
        print_buf[0] = '0';
        print_buf[1] = '\0';
        return prints(out, print_buf, width, pad, limit);
    }

    if (sg && b == 10 && i < 0) {
        neg = 1;
        u   = -i;
    }

    s  = print_buf + PRINT_BUF_LEN - 1;
    *s = '\0';

    while (u) {
        t = u % b;
        if (t >= 10) {
            t += letbase - '0' - 10;
        }
        *--s = t + '0';
        u   /= b;
    }

    if (neg && pc) {
        if (width && (pad & PAD_ZERO)) {
            printchar(out, '-');
            --pc;
            --width;
        } else {
            *--s = '-';
        }
    }

    return (limit - pc) + prints(out, s, width, pad, pc);
}

static int print(int limit, char * *out, const char *format, va_list args)
{
    register int width, pad;
    register int pc = limit;
    char scr[2];

    for (; *format != 0 && pc; ++format) {
        if (*format == '%') {
            ++format;
            width = pad = 0;
            if (*format == '\0') {
                break;
            }
            if (*format == '%') {
                goto out;
            }
            if (*format == '-') {
                ++format;
                pad = PAD_RIGHT;
            }
            while (*format == '0') {
                ++format;
                pad |= PAD_ZERO;
            }
            for (; *format >= '0' && *format <= '9'; ++format) {
                width *= 10;
                width += *format - '0';
            }
            if (*format == 's') {
                register char *s = (char *)va_arg(args, int);
                pc -= prints(out, s ? s : "(null)", width, pad, pc);
                continue;
            }
            if (*format == 'd') {
                pc -= printi(out, va_arg(args, int), 10, 1, width, pad, 'a', pc);
                continue;
            }
            if (*format == 'x') {
                pc -= printi(out, va_arg(args, int), 16, 0, width, pad, 'a', pc);
                continue;
            }
            if (*format == 'X') {
                pc -= printi(out, va_arg(args, int), 16, 0, width, pad, 'A', pc);
                continue;
            }
            if (*format == 'u') {
                pc -= printi(out, va_arg(args, int), 10, 0, width, pad, 'a', pc);
                continue;
            }
            if (*format == 'c') {
                /* char are converted to int then pushed on the stack */
                scr[0] = (char)va_arg(args, int);
                scr[1] = '\0';
                pc    -= prints(out, scr, width, pad, pc);
                continue;
            }
        } else {
out:
            printchar(out, *format);
            --pc;
        }
    }
    if (out) {
        **out = '\0';
    }
    va_end(args);
    return limit - pc;
}

int printf(const char *format, ...)
{
    va_list args;

    va_start(args, format);
    return print(-1, 0, format, args);
}

int vprintf(const char *format, va_list args)
{
    return print(-1, 0, format, args);
}

int sprintf(char *out, const char *format, ...)
{
    va_list args;

    va_start(args, format);
    return print(-1, &out, format, args);
}

int vsprintf(char *out, const char *format, va_list args)
{
    char *_out;

    _out = out;
    return print(-1, &_out, format, args);
}

int snprintf(char *buf, size_t count, const char *format, ...)
{
    va_list args;

    va_start(args, format);
    return print(count, &buf, format, args);
}

int vsnprintf(char *buf, size_t count, const char *format, va_list args)
{
    return print(count, &buf, format, args);
}


/////////////////////////////////in unix test
#include <unistd.h>
int putchar(int c)
{
	//1 is stdout
	return write(1, &c, 1);
}

int main(int argc, char **argv)
{
	if( argv[1] )
		printf("hello, arg:%d first is:%s.\n", argc, argv[1]);
	else
		printf("hello.\n");
	return 0;
}
