#ifndef accel_h
#define accel_h

bool accel_init();
double accel_get_x_scale();
int accel_get_x_raw();
double accel_get_y_scale();
int accel_get_y_raw();
double accel_get_z_scale();
int accel_get_z_raw();

#endif