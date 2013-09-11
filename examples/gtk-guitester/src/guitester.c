#include <gtk/gtk.h>
#include <display.h>
#include <gpio.h>
#include <i2c.h>
#include <w1temp.h>
#include "oledpanel.h"
#include "gpiopanel.h"
#include "dowpanel.h"
#include "i2cpanel.h"

static void guitester_ondestroy()
{
    gpio_close();
    w1temp_close();
}

static void guitester_oncreate()
{
    gpio_init();
    w1temp_init();
}

static gboolean delete_event(GtkWidget *widget, GdkEvent *event, gpointer data)
{
    return FALSE;
}

static void destroy(GtkWidget *widget, gpointer data)
{
    gtk_main_quit();
}

int main(int argc, char *argv[])
{
    guitester_oncreate();

    GtkWidget *window;
    GtkWidget *oled_panel;
    GtkWidget *dow_panel;
    GtkWidget *i2c_panel;
    GtkWidget *gpio_panel;
    GtkWidget *panel_box;

    gtk_init(&argc, &argv);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_container_set_border_width(GTK_CONTAINER(window), 10);
    g_signal_connect(window, "delete-event", G_CALLBACK(delete_event), NULL);
    g_signal_connect(window, "destroy", G_CALLBACK(destroy), NULL);

    oled_panel = guitester_panel_oled();
    dow_panel = guitester_panel_dow();
    i2c_panel = guitester_panel_i2c();
    gpio_panel = guitester_panel_gpio();
    panel_box = gtk_vbox_new(FALSE, 2);

    gtk_box_pack_start(GTK_BOX(panel_box), i2c_panel, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(panel_box), oled_panel, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(panel_box), gpio_panel, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(panel_box), dow_panel, TRUE, TRUE, 0);

    gtk_container_add(GTK_CONTAINER(window), panel_box);

    gtk_widget_show_all(window);
    gtk_main();

    guitester_ondestroy();
    return 0;
}
