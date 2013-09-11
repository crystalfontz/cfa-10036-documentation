#include "dowpanel.h"


static void dow_callback(GtkWidget *widget, gpointer data[])
{
    int device_count = w1temp_getcount();
    char device_count_string[10];
    sprintf(device_count_string, "%d", device_count);
    gtk_label_set_text(data[0], device_count_string);
    int active_device = atoi(gtk_entry_get_text(data[1]));
    double active_device_temperature = w1temp_get_temp_fahrenheit(active_device);
    char active_device_temperature_string[10];
    sprintf(active_device_temperature_string, "%f", active_device_temperature);
    gtk_label_set_text(data[2], active_device_temperature_string);
}

GtkWidget *guitester_panel_dow()
{
    // Declaration
    GtkWidget *dow_panel;
    GtkWidget *dow_settings_box;
    GtkWidget *dow_settings_subbox_2;
    GtkWidget *dow_settings_subbox_1;
    GtkWidget *dow_information_box;

    GtkWidget *dow_information_label;
    GtkWidget *dow_information_count_label;

    GtkWidget *dow_settings_label;
    GtkWidget *dow_settings_device_number_entry;

    GtkWidget *dow_settings_temperature_label;
    GtkWidget *dow_settings_temperature_reading;
    GtkWidget *dow_settings_update;

    // Initialization
    dow_panel = gtk_hbox_new(FALSE, 2);
    dow_settings_box = gtk_vbox_new(FALSE, 2);
    dow_information_box = gtk_vbox_new(FALSE, 2);
    dow_settings_subbox_2 = gtk_hbox_new(FALSE, 2);
    dow_settings_subbox_1 = gtk_hbox_new(FALSE, 2);

    dow_information_label = gtk_label_new("Device Count");
    dow_information_count_label = gtk_label_new("Unknown");

    dow_settings_label = gtk_label_new("Device Number");
    dow_settings_device_number_entry = gtk_entry_new();

    dow_settings_temperature_label = gtk_label_new("Fahrenheit");
    dow_settings_temperature_reading = gtk_label_new("Unknown");
    dow_settings_update = gtk_button_new_with_label("Update");

    // Assigning Signals
    gpointer data[] = {dow_information_count_label, dow_settings_device_number_entry, dow_settings_temperature_reading};
    g_signal_connect(dow_settings_update, "clicked", G_CALLBACK(dow_callback), data);

    // Packaging
    gtk_box_pack_start(GTK_BOX(dow_information_box), dow_information_label, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(dow_information_box), dow_information_count_label, TRUE, TRUE, 0);

    gtk_box_pack_start(GTK_BOX(dow_settings_subbox_2), dow_settings_temperature_label, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(dow_settings_subbox_2), dow_settings_temperature_reading, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(dow_settings_subbox_2), dow_settings_update, TRUE, TRUE, 0);

    gtk_box_pack_start(GTK_BOX(dow_settings_subbox_1), dow_settings_label, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(dow_settings_subbox_1), dow_settings_device_number_entry, TRUE, TRUE, 0);

    gtk_box_pack_start(GTK_BOX(dow_settings_box), dow_settings_subbox_1, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(dow_settings_box), dow_settings_subbox_2, TRUE, TRUE, 0);

    gtk_box_pack_start(GTK_BOX(dow_panel), dow_information_box, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(dow_panel), dow_settings_box, TRUE, TRUE, 0);
    return dow_panel;
}