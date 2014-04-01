/*
 * =====================================================================================
 *
 *       Filename:  term.h
 *
 *    Description:  terminal operation 
 *
 *        Version:  1.0
 *        Created:  01/22/2014 10:23:22 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  echo "Q2hhbmdxaW5nLFpoYW8K" | base64 -d  (tain)
 *          Email:  echo "Y2hhbmdxaW5nLjEyMzBAMTYzLmNvbQo=" | base64 -d 
 *        Company:  FreedomIsNotFree.com
 *
 * =====================================================================================
 */
#ifndef _TERM_OPS_H_
#define _TERM_OPS_H_

/* image ops */
typedef struct  image_s {
	int x, y, w, h;
	unsigned char *buf;
}image_t;
image_t *image_create(int x, int y, int w, int h);
void image_destory(image_t *pimage);
void image_fill(image_t *pimage, char c);


/* term ops */

typedef struct term_ops_s * term_t;

term_t term_init(void);
void term_exit(term_t term);
void term_get_cursor(term_t term, unsigned int *x, unsigned int *y);
void term_place_cursor(term_t term, unsigned int x, unsigned int y);
void term_clean_screen(term_t term);
void term_clean_line(term_t term, int offset);
void term_cursor_up(term_t term, int offset);
void term_cursor_down(term_t term, int offset);
void term_cursor_left(term_t term, int offset);
void term_cursor_right(term_t term, int offset);
void term_put_char(term_t term, char c);
void term_put_printf(term_t term, const char *fmt, ...);

void term_draw_image(term_t term, image_t *pimage);


#endif

