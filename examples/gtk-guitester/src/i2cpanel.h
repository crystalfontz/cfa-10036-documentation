#ifndef i2cpanel_h
#define i2cpanel_h

#include <gtk/gtk.h>
#include <stdlib.h>
#include <i2c.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

GtkWidget *guitester_panel_i2c();

#endif