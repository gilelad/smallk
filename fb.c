#include "io.h"
#include "fb.h"

#define FB_BASE 0xB8000
#define FB_COMMAND_PORT 0x3D4
#define FB_DATA_PORT 0x3D5

enum {
	FB_BASE_ADDR_INDEX = 12,
	FB_CURSOR_POS_INDEX = 14
};

typedef uchar *fb_addr_t;				
static fb_addr_t fb = (fb_addr_t)FB_BASE;
static short crow = -1;

void
fb_puts (char *s);

static void
draw_char (uchar row,
	   uchar col,
	   char ch,
	   uchar fg,
           uchar bg);

static void
fb_putc (uchar row,
         uchar col,
         char ch,
         uchar fg,
         uchar bg);

static void
fb_io_write (uchar index,
	     ushort data)
{
	outb(FB_COMMAND_PORT, index); /* high byte */
	outb(FB_DATA_PORT, (data >> (8*sizeof(char))) & 0x00FF);
	outb(FB_COMMAND_PORT, index+1); /* low byte */
	outb(FB_DATA_PORT, data & 0x00FF);
}

static void
move_cursor (uchar row,
             uchar col)
{
	ushort pos = (row*FB_COLS) + col;
	fb_io_write(FB_CURSOR_POS_INDEX, pos);
}

static void
scroll ()
{
	if (crow < 23) {
		crow++;
	} else{
		ushort row, col;
		for (row=0 ; row<23 ; row++) {
			for (col=0 ; col<80 ; col++) {
				uint offset = 2*((row+1)*80+col);
				char ch = * (fb+offset);
				draw_char(row, col, ch, FB_LIGHT_GRAY, FB_BLACK);
			}
		}
		for (col=0 ; col<80 ; col++) {
			draw_char(row, col, ' ', FB_LIGHT_GRAY, FB_BLACK);
		}
	}
}

static void
draw_char (uchar row,
	   uchar col,
	   char ch,
	   uchar fg,
           uchar bg)
{
	uchar *pos = fb + 2 * ((row*FB_COLS) + col);
	*(pos++) = ch;
	*pos = ((bg & 0xF) << 4) | (fg & 0xF);
}

static void
fb_putc (uchar row,
         uchar col,
         char ch,
         uchar fg,
         uchar bg)
{
	move_cursor(row, col);
	draw_char(row, col, ch, fg, bg);
}

void
fb_puts_color (char *s,
	       uchar fg,
	       uchar bg)
{
	char col = 0;

	while (*s) {
		if (col == FB_COLS)
			col = 0;
		
		if (col == 0)
			scroll();

		fb_putc(crow, col, *s, fg, bg);
		s++;
		col++;
	}
}

void
fb_puts (char *s)
{
	fb_puts_color (s, FB_LIGHT_GRAY, FB_BLACK);
}
