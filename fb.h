#ifndef __FB_H__
#define __FB_H__

#include "types.h"

#define FB_ROWS 24
#define FB_COLS 80

enum {
	FB_BLACK,
	FB_BLUE,
	FB_GREEN,
	FB_CYAN,
	FB_RED,
	FB_MAGENTA,
	FB_BROWN,
	FB_LIGHT_GRAY,
	FB_DARK_GRAY,
	FB_LIGHT_BLUE,
	FB_LIGHT_GREEN,
	FB_LIGHT_CYAN,
	FB_LIGHT_RED,
	FB_LIGHT_MAGENTA,
	FB_LIGHT_BROWN,
	FB_WHITE
};

void
fb_puts_color (char *s,
	       uchar fg,
	       uchar bg);

void
fb_puts (char *s);

#endif /*__FB_H__*/
