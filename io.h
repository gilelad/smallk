#ifndef __IO_H__
#define __IO_H__

#include "types.h"

/** outb:
 *	Sends the given data to the given I/O port.
 *	Defined in bio.s
 *
 *	@param port The I/O port to send the data to
 *	@param data The value to send
 */
extern void
outb (ushort port,
      uchar  data);

#endif /*__IO_H__*/
