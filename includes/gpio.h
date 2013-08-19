#ifndef gpio_h
#define gpio_h

/*						GPIO library for the cfa-10036
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
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

bool gpio_init();
bool gpio_config(unsigned int pin,unsigned int state);
bool gpio_write(unsigned int portnum,unsigned int state);
int gpio_read(unsigned int portnum);
void gpio_close();

#endif