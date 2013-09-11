#ifndef gpio_h
#define gpio_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define PINCOUNT 126
#define GPIO_EXPORT_ERROR       (-1)
#define GPIO_ACCESS_ERROR       (-2)
#define GPIO_DIRECTION_ERROR    (-3)
#define GPIO_VALUE_ERROR        (-4)
#define GPIO_PIN_NUMBER_ERROR   (-5)
#define GPIO_WRITE_ERROR        (-6)
#define GPIO_READ_ERROR         (-7)
#define GPIO_INIT_ERROR         (-8)

int gpio_init();
int gpio_config(unsigned int pin, unsigned int state);
int gpio_write(unsigned int portnum, unsigned int state);
int gpio_read(unsigned int portnum);
int gpio_close();

#endif