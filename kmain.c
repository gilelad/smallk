#include "fb.h"

void
kmain ()
{
	int n = 1000;
	while (n--) fb_puts ("Hello World!");
	fb_puts("Done.");
	for (;;);
}
