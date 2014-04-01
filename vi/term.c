/*
 * =====================================================================================
 *
 *       Filename:  term.c
 *
 *    Description:  term ops
 *
 *        Version:  1.0
 *        Created:  01/28/2014 12:34:39 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  echo "Q2hhbmdxaW5nLFpoYW8K" | base64 -d  (tain)
 *          Email:  echo "Y2hhbmdxaW5nLjEyMzBAMTYzLmNvbQo=" | base64 -d 
 *        Company:  FreedomIsNotFree.com
 *
 * =====================================================================================
 */
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <sys/ioctl.h>

#include "term.h"

struct term_ops_s{
	unsigned x, y;
	unsigned w, h;

	unsigned oldx, oldy;
	struct termios raw;
	struct termios normal;

	unsigned char *buf;
};

term_t term_init(void)
{
	term_t pterm;
	struct winsize win;

	pterm = (term_t)malloc(sizeof(term_t));
	if( !pterm )
		return NULL;

	memset(pterm, 0, sizeof(term_t));

	if( -1 == ioctl(0, TIOCGWINSZ, &win) )
		goto EXIT1;

	pterm->w = win.ws_col;
	pterm->h = win.ws_row;

	pterm->oldx = win.ws_xpixel;
	pterm->oldy = win.ws_ypixel;

	pterm->buf = (unsigned char *)malloc(pterm->w * pterm->h);
	if( !pterm->buf )
	{
		goto EXIT2;
	}


	return pterm;

EXIT:

EXIT2:
	if( pterm->buf )
		free(pterm->buf);
EXIT1:
	if( pterm )
		free(pterm);

	return NULL;
}

