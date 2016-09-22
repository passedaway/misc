#define TEST_PRINTF 1

/* *********************
 * shoulde put declare in print.h
 **/
#define __OS_API_PREFIX	"os_"
#define OS_PREFIX(api) OS_##api
#define strlen OS_PREFIX(strlen)
#define printf OS_PREFIX(printf)
#define sprintf OS_PREFIX(sprintf)
unsigned int strlen(char *str);
int printf(const char *format, ...);
int sprintf(char *out, const char *format, ...);
/* print.h over */

#define OS_UNIX 1
// ****************************************************************************
// base function is putchar
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

// ****************************************************************************
unsigned int strlen(char *str)
{
    unsigned int slen = 0;
    if (str == 0) {
        return 0;
    }
    while (*str != 0) {
        slen++;
        str++;
    }
    return slen;
}

// ****************************************************************************
// This version returns the length of the output string.
// It is more useful when implementing a walking-string function.
// ****************************************************************************
static const double round_nums[8] = {
    0.5L,
    0.05L,
    0.005L,
    0.0005L,
    0.00005L,
    0.000005L,
    0.0000005L,
    0.00000005L
};

//
static unsigned char use_leading_plus = 0;

static unsigned dbl2stri(char *outbfr, double dbl, unsigned dec_digits)
{
    unsigned int mult = 1;
    unsigned int idx;
    unsigned int wholeNum;
    unsigned int decimalNum;
    static char local_bfr[128];
    char tbfr[40];
    char *output = (outbfr == 0) ? local_bfr : outbfr;

    // *******************************************
    // extract negative info
    // *******************************************
    if (dbl < 0.0L) {
        *output++ = '-';
        dbl *= -1.0L;
    } else {
        if (use_leading_plus) {
            *output++ = '+';
        }
    }

    // handling rounding by adding .5LSB to the floating-point data
    if (dec_digits < 8) {
        dbl += round_nums[dec_digits];
    }

    // **************************************************************************
    // construct fractional multiplier for specified number of digits.
    // **************************************************************************
    for (idx = 0; idx < dec_digits; idx++) {
        mult *= 10;
    }

    // printf("mult=%u\n", mult) ;
	wholeNum = (unsigned int)dbl;
	decimalNum = (unsigned int)((dbl - wholeNum) * mult);

    // *******************************************
    // convert integer portion
    // *******************************************
    idx = 0;
    while (wholeNum != 0) {
        tbfr[idx++] = '0' + (wholeNum % 10);
        wholeNum   /= 10;
    }
    // printf("%.3f: whole=%s, dec=%d\n", dbl, tbfr, decimalNum) ;
    if (idx == 0) {
        *output++ = '0';
    } else {
        while (idx > 0) {
            *output++ = tbfr[idx - 1]; // lint !e771
            idx--;
        }
    }
    if (dec_digits > 0) {
        *output++ = '.';

        // *******************************************
        // convert fractional portion
        // *******************************************
        idx = 0;
        while (decimalNum != 0) {
            tbfr[idx++] = '0' + (decimalNum % 10);
            decimalNum /= 10;
        }
        // pad the decimal portion with 0s as necessary;
        // We wouldn't want to report 3.093 as 3.93, would we??
        while (idx < dec_digits) {
            tbfr[idx++] = '0';
        }
        // printf("decimal=%s\n", tbfr) ;
        if (idx == 0) {
            *output++ = '0';
        } else {
            while (idx > 0) {
                *output++ = tbfr[idx - 1];
                idx--;
            }
        }
    }
    *output = 0;

    // prepare output
    output  = (outbfr == 0) ? local_bfr : outbfr;
    return strlen(output);
}

// ****************************************************************************
#define  PAD_RIGHT 1
#define  PAD_ZERO  2

static int prints(char * *out, const char *string, int width, int pad)
{
    register int pc = 0, padchar = ' ';

    if (width > 0) {
        int len = 0;
        const char *ptr;
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
        for (; width > 0; --width) {
            printchar(out, padchar);
            ++pc;
        }
    }
    for (; *string; ++string) {
        printchar(out, *string);
        ++pc;
    }
    for (; width > 0; --width) {
        printchar(out, padchar);
        ++pc;
    }
    return pc;
}

// ****************************************************************************
/* the following should be enough for 32 bit int */
#define PRINT_BUF_LEN 12
static int printi(char * *out, int i, int b, int sg, int width, int pad, int letbase)
{
    char print_buf[PRINT_BUF_LEN];
    char *s;
    int t, neg = 0, pc = 0;
    unsigned u = (unsigned)i;

    if (i == 0) {
        print_buf[0] = '0';
        print_buf[1] = '\0';
        return prints(out, print_buf, width, pad);
    }
    if (sg && b == 10 && i < 0) {
        neg = 1;
        u   = (unsigned)-i;
    }
    // make sure print_buf is NULL-term
    s  = print_buf + PRINT_BUF_LEN - 1;
    *s = '\0';


    while (u) {
        t = u % b; // lint !e573  Warning 573: Signed-unsigned mix with divide
        if (t >= 10) {
            t += letbase - '0' - 10;
        }
        *--s = t + '0';
        u   /= b;  // lint !e573  Warning 573: Signed-unsigned mix with divide
    }
    if (neg) {
        if (width && (pad & PAD_ZERO)) {
            printchar(out, '-');
            ++pc;
            --width;
        } else {
            *--s = '-';
        }
    } else {
        if (use_leading_plus) {
            *--s = '+';
        }
    }
    return pc + prints(out, s, width, pad);
}

// ****************************************************************************
static int print(char * *out, int *varg)
{
    int post_decimal;
    int width, pad;
    unsigned dec_width = 6;
    int pc = 0;
    char *format = (char *)(*varg++);
    char scr[2];

    use_leading_plus = 0; // start out with this clear
    for (; *format != 0; ++format) {
        if (*format == '%') {
            dec_width = 6;
            ++format;
            width     = pad = 0;
            if (*format == '\0') {
                break;
            }
            if (*format == '%') {
                goto out_lbl;
            }
            if (*format == '-') {
                ++format;
                pad = PAD_RIGHT;
            }
            if (*format == '+') {
                ++format;
                use_leading_plus = 1;
            }
            while (*format == '0') {
                ++format;
                pad |= PAD_ZERO;
            }
            post_decimal = 0;
            if (*format == '.' ||
                (*format >= '0' && *format <= '9')) {
                while (1) {
                    if (*format == '.') {
                        post_decimal = 1;
                        dec_width    = 0;
                        format++;
                    } else if ((*format >= '0' && *format <= '9')) {
                        if (post_decimal) {
                            dec_width *= 10;
                            dec_width += *format - '0';
                        } else {
                            width *= 10;
                            width += *format - '0';
                        }
                        format++;
                    } else {
                        break;
                    }
                }
            }
            if (*format == 'l') {
                ++format;
            }
            switch (*format) {
            case 's':
            {
                // char *s = *((char **) varg++);   //lint !e740
                char *s = (char *)*varg++; // lint !e740 !e826  convert to double pointer
                pc += prints(out, s ? s : "(null)", width, pad);
                use_leading_plus = 0; // reset this flag after printing one value
            }
            break;
            case 'd':
                pc += printi(out, *varg++, 10, 1, width, pad, 'a');
                use_leading_plus = 0; // reset this flag after printing one value
                break;
            case 'x':
                pc += printi(out, *varg++, 16, 0, width, pad, 'a');
                use_leading_plus = 0; // reset this flag after printing one value
                break;
            case 'X':
                pc += printi(out, *varg++, 16, 0, width, pad, 'A');
                use_leading_plus = 0; // reset this flag after printing one value
                break;
            case 'u':
                pc += printi(out, *varg++, 10, 0, width, pad, 'a');
                use_leading_plus = 0; // reset this flag after printing one value
                break;
            case 'c':
                /* char are converted to int then pushed on the stack */
                scr[0] = *varg++;
                scr[1] = '\0';
                pc    += prints(out, scr, width, pad);
                use_leading_plus = 0; // reset this flag after printing one value
                break;

            case 'f':
            {
                // http://wiki.debian.org/ArmEabiPort#Structpackingandalignment
                // Stack alignment
                //
                // The ARM EABI requires 8-byte stack alignment at public function entry points,
                // compared to the previous 4-byte alignment.
                char bfr[81];
                double dbl;
#define USE_NEWLIB 1 /* ARM stm32 need use 1 2016-09-22 20:10:37 zhaocq */
#ifdef USE_NEWLIB
                char *cptr = (char *)varg; // lint !e740 !e826  convert to double pointer
                unsigned int caddr = (unsigned int)cptr;
                double *dblptr;
                if ((caddr & 0xF) != 0) {
                    cptr += 4;
                }
				dblptr = (double *)cptr; // lint !e740 !e826  convert to double pointer
#else
                double *dblptr = (double *)varg; // lint !e740 !e826  convert to double pointer
#endif
				dbl = *dblptr++;   // increment double pointer
                varg = (int *)dblptr; // lint !e740  copy updated pointer back to base pointer
                // unsigned slen =
                dbl2stri(bfr, dbl, dec_width);
                // stuff_talkf("[%s], width=%u, dec_width=%u\n", bfr, width, dec_width) ;
                pc += prints(out, bfr, width, pad);
                use_leading_plus = 0; // reset this flag after printing one value
            }
            break;

            default:
                printchar(out, '%');
                printchar(out, *format);
                use_leading_plus = 0; // reset this flag after printing one value
                break;
            }
        } else {
            // if (*format == '\\') {
            //
            // } else
out_lbl:
            printchar(out, *format);
            ++pc;
        }
    } // for each char in format string
    if (out) { // lint !e850
        **out = '\0';
    }
    return pc;
}

// ****************************************************************************
int stringf(char *out, const char *format, ...)
{
    // create a pointer into the stack.
    // Thematically this should be a void*, since the actual usage of the
    // pointer will vary.  However, int* works fine too.
    // Either way, the called function will need to re-cast the pointer
    // for any type which isn't sizeof(int)
    int *varg = (int *)(char *)(&format);

    return print(&out, varg);
}

int printf(const char *format, ...)
{
    int *varg = (int *)(char *)(&format);

    return print(0, varg);
}

int sprintf(char *out, const char *format, ...)
{
    int *varg = (int *)(char *)(&format);

    return print(&out, varg);
}

#ifdef TEST_PRINTF

#if OS_UNIX
//this is in unix
#include <unistd.h>
int putchar(int c)
{
	//1 is stdout
	return write(1, &c, 1);
}
#endif

int main(int argc, char **argv)
{
	if( argv[1] )
		printf("hello, arg:%d first is:%s.\n", argc, argv[1]);
	else
		printf("hello.\n");
	return 0;
}

#endif
