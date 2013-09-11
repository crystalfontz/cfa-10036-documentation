#ifndef __dowtemp_h__
#define __dowtemp_h__

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define DOW_MAX_DEVICES 32
#define DOW_ALREADY_RUNNING_ERROR   (-1)
#define DOW_DEVICE_ACCESS_ERROR     (-2)
#define DOW_INVALID_DEVICE_ID_ERROR (-3)

int dowtemp_init();
void dowtemp_close();
int dowtemp_getcount();
double dowtemp_get_celsius(int);
double dowtemp_get_fahrenheit(int);
char *dowtemp_getid(int);

#endif