#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

/*
    I keep the file descriptors in memory to speed up transactions.
*/
static FILE *accel_input_x_scale;
static FILE *accel_input_x_raw;
static FILE *accel_input_y_scale;
static FILE *accel_input_y_raw;
static FILE *accel_input_z_scale;
static FILE *accel_input_z_raw;

/*
    Initializes the library. It returns true if the lib was initialized properly, and false if it was unable to.
*/
bool accel_init()
{
    accel_input_x_scale = fopen("/sys/bus/i2c/devices/0-0019/iio:device1/in_accel_x_scale", "r");
    accel_input_x_raw = fopen("/sys/bus/i2c/devices/0-0019/iio:device1/in_accel_x_raw", "r");

    accel_input_y_scale = fopen("/sys/bus/i2c/devices/0-0019/iio:device1/in_accel_y_scale", "r");
    accel_input_y_raw = fopen("/sys/bus/i2c/devices/0-0019/iio:device1/in_accel_y_raw", "r");

    accel_input_z_scale = fopen("/sys/bus/i2c/devices/0-0019/iio:device1/in_accel_z_scale", "r");
    accel_input_z_raw = fopen("/sys/bus/i2c/devices/0-0019/ii:device1/in_accel_z_raw", "r");

    return (accel_input_x_scale != NULL &&
            accel_input_x_raw != NULL &&
            accel_input_y_scale != NULL &&
            accel_input_y_raw != NULL &&
            accel_input_z_scale != NULL &&
            accel_input_z_raw != NULL);
}
/*
    Helper function that reads a accel_input*_scale file and returns its' value in double format.
*/
static double accel_get_double(FILE *fin)
{
    char buf[12];
    return atof(fgets(buf, 11, fin));
}

/*
    Helper function that reads a accel_input*_raw file and returns its' value in integer format.
*/
static double accel_get_int(FILE *fin)
{
    char buf[8];
    return atoi(fgets(buf, 7, fin));
}

/*
    Each of the following functions get the different axis's values in scale or raw.
*/
double accel_get_x_scale()
{
    return accel_get_double(accel_input_x_scale);
}

int accel_get_x_raw()
{
    return accel_get_int(accel_input_x_raw);
}

double accel_get_y_scale()
{
    return accel_get_double(accel_input_y_scale);
}

int accel_get_y_raw()
{
    return accel_get_int(accel_input_y_raw);
}

double accel_get_z_scale()
{
    return accel_get_double(accel_input_z_scale);
}

int accel_get_z_raw()
{
    return accel_get_int(accel_input_z_raw);
}