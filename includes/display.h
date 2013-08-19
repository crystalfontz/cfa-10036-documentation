#ifndef display_h
#define display_h

/*						Display library for the cfa-10036
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 or later
 * as published by the Free Software Foundation.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 * 
 */
 
#include <stdio.h>
#include <string.h>

void display_send(void);
void display_fill(unsigned char byte);
void display_writebuffer(int col, int row, char *string);

#endif
