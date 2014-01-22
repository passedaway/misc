/*
 * =====================================================================================
 *
 *       Filename:  vi.c
 *
 *    Description:  my vi
 *
 *        Version:  1.0
 *        Created:  01/21/2014 05:49:16 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  echo "Q2hhbmdxaW5nLFpoYW8K" | base64 -d  (tain)
 *          Email:  echo "Y2hhbmdxaW5nLjEyMzBAMTYzLmNvbQo=" | base64 -d 
 *        Company:  FreedomIsNotFree.com
 *
 * =====================================================================================
 */
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <signal.h>

#define DEBUG
#ifdef DEBUG
#define dbg(fmt, args...)	printf("[%s:%s:%d]"fmt, __FILE__, __FUNCTION__, __LINE__, ##args)
#else
#define dbg(fmt, args...)
#endif
/*  vt102 typical ESC sequence */
/* clear-end-of-line and clear-end-of-screen ESC sequence */
static const char *Ceol = "\033[0K";
static const char *Ceos = "\033[0J";
/* cursor motion up & down */
static const char *Cup = "\033[A";
static const char *Cdown = "\n";
/*  cursor coordinate(zuobiao) */
static const char *Cxy = "\033[%d;%dH";

static int get_term_width_height(int fd, unsigned *width, unsigned *height);
static void rawmode(void);
static void normalmode(void);
static void sig_handler(int signo);
typedef struct screen_s{
	unsigned int w, h;
	unsigned int x, y;
	char *buf;
}screen_t;
static screen_t gs;
/* course */
static void sc_cls(void);
static void sc_xy(int x, int y);
static void sc_right(void);
static void sc_left(void);
static void sc_down(void);
static void sc_up(void);

/* draw */
static void sc_draw_char(int, int, int c);
static void sc_put_char(int c);

/* get key */
static unsigned int get_key(void);

//test
static void draw_start(void);

//main entry
int main(int argc, char **argv)
{
	unsigned int key = 0;

	signal(SIGINT, sig_handler);
	signal(SIGHUP, sig_handler);
	signal(SIGTERM, sig_handler);
	signal(SIGKILL, sig_handler);

	get_term_width_height(0, &gs.w, &gs.h);

	rawmode();
	gs.buf = (char *)malloc(gs.w * gs.h+ gs.w);
	if( gs.buf == NULL )
		goto EXIT;

	memset(gs.buf, 0, gs.w * gs.h+ gs.w);

	draw_start();
	//start edit
	while(1)
	{
		key = get_key();
		if( key == 'q' || key == 'Q' )
			break;

		switch( key )
		{
			case 's':
			case 'S':
				sc_cls();
				break;

			case 'u':
			case 'U':
				sc_up();
				break;
			case 'd':
			case 'D':
				sc_down();
				break;

			case 'l':
			case 'L':
				sc_left();
				break;

			case 'R':
			case 'r':
				sc_right();
				break;
			
			default:
				sc_put_char(key);
				break;
		}

	}

	
	//free then exit
	free(gs.buf);
	normalmode();
EXIT:
	return 0;
}

/* local function */
static void sig_handler(int signo)
{
	fflush(stdout);
	normalmode();
	printf("Exit by Signal %d\n", signo);
	exit(0);
}

static int get_term_width_height(int fd, unsigned *width, unsigned *height)
{
	struct winsize win = {0,0,0,0};

	int ret = ioctl(fd, TIOCGWINSZ, &win);
	*width = win.ws_col;
	*height = win.ws_row;

#if 0
	{
		unsigned int *p = &win;
		dbg("%d %d %d %d\n", p[0], p[1], p[2], p[3]);
	}
#endif
	return ret;
}

static struct termios termios_orig, termios_raw;
static void rawmode(void)
{
	tcgetattr(0, &termios_orig);
	termios_raw = termios_orig;
	termios_raw.c_lflag &= (~ICANON & ~ECHO);
	termios_raw.c_iflag &= (~IXON & ICRNL);
	termios_raw.c_oflag &= (~ONLCR);
	termios_raw.c_cc[VMIN] = 1;
	termios_raw.c_cc[VTIME] = 0;
	//erase_char = termios_raw.c_cc[VERASE];
	tcsetattr(0, TCSANOW, &termios_raw);
}

static void normalmode(void)
{
	fflush(stdout);
	tcsetattr(0, TCSANOW, &termios_orig);
}

static void sc_cls(void)
{
	sc_xy(1,1);
	fputs(Ceos, stdout);
	fflush(stdout);
}

static void sc_up(void)
{
	fputs(Cup, stdout);
	fflush(stdout);
	if( gs.y > 0 )
		gs.y--;
}

static void sc_down(void)
{
	fputs(Cdown, stdout);
	fflush(stdout);
	gs.y++;
}

static void sc_left(void)
{
	if( gs.x > 0 )
		gs.x--;
	sc_xy(gs.x, gs.y);
}

static void sc_right(void)
{
	gs.x++;
	sc_xy(gs.x, gs.y);
}

static void sc_xy(int x, int y)
{
	static char tmp[64];
	sprintf(tmp, Cxy, y, x);/* row, col */
	fputs(tmp, stdout);
	fflush(stdout);
	gs.x = x;
	gs.y = y;
}

#if 0
static unsigned int sc_draw(draw_setting_t *pds);
#else
static void sc_draw_char(int x, int y, int c)
{
	sc_xy(x,y);
	printf("%c", c);
	fflush(stdout);
	gs.x++;
}
static void sc_put_char(int c)
{
	sc_xy(gs.x,gs.y);
	printf("%c",c);
	fflush(stdout);
	gs.x++;
}
#endif

static unsigned int get_key(void)
{
	unsigned int key = 0;
	read(0, &key, 4);
	return key;
}

static void draw_start(void)
{
	int x, y;
	/*  draw '*' range */
	sc_cls();

	for(x = 1; x <= gs.w; x++)
	{
		sc_draw_char(x, 1, '*');
		sc_draw_char(x, gs.h, '*');
	}
	for( y = 1; y <= gs.h; y++)
	{
		sc_draw_char(1, y, '*');
		sc_draw_char(gs.w, y, '*');
	}

	/* center */
	sc_xy(gs.w/2, gs.h/2);
}

