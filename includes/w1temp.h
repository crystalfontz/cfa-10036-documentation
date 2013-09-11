#ifndef __w1temp_h__
#define __w1temp_h__

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define DOW_MAX_DEVICES 32
#define DOW_ALREADY_RUNNING_ERROR   (-1)
#define DOW_DEVICE_ACCESS_ERROR     (-2)
#define DOW_INVALID_DEVICE_ID_ERROR (-3)

int w1temp_init();
void w1temp_close();
int w1temp_getcount();
double w1temp_get_temp_celsius(int);
double w1temp_get_temp_fahrenheit(int);
char *w1temp_getid(int);

#endif