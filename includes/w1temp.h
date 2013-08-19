#ifndef __w1temp_h__
#define __w1temp_h__

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define DEBUG false
#define MAXDEVIECES 32

void w1temp_init();
void w1temp_close();
int w1temp_getcount();
double w1temp_get_temp_celsius(int);
inline double w1temp_get_temp_fahrenheit(int);
inline char* w1temp_getid(int);

#endif