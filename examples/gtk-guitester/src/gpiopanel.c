#include "gpiopanel.h"

static void gpio_callback_update(GtkWidget *widget, gpointer data[])
{
    int pin_number = atoi(gtk_entry_get_text(data[0]));
    gpio_config(pin_number, 0);
    int state = gpio_read(pin_number);
    char state_string[5];
    sprintf(state_string, "%s", (state == 0) ? "Low" : "High");
    gtk_label_set_text(data[1], state_string);
}

static void gpio_callback_high(GtkWidget *widget, GtkEntry *entry)
{
    int pin_number = atoi(gtk_entry_get_text(entry));
    gpio_config(pin_number, 1);
    gpio_write(pin_number, 1);
}
static void gpio_callback_low(GtkWidget *widget, GtkEntry *entry)
{
    int pin_number = atoi(gtk_entry_get_text(entry));
    gpio_config(pin_number, 1);
    gpio_write(pin_number, 0);
}

GtkWidget *guitester_panel_gpio()
{
    // Declaration
    GtkWidget *gpio_panel;
    GtkWidget *gpio_input_box;
    GtkWidget *gpio_input_subbox_1;
    GtkWidget *gpio_input_subbox_2;
    GtkWidget *gpio_output_box;
    GtkWidget *gpio_output_subbox_1;
    GtkWidget *gpio_output_subbox_2;

    GtkWidget *gpio_input_label;
    GtkWidget *gpio_input_state_label;
    GtkWidget *gpio_input_state_update;
    GtkWidget *gpio_input_state_pin;

    GtkWidget *gpio_output_label;
    GtkWidget *gpio_output_pin_entry;
    GtkWidget *gpio_output_pin_high;
    GtkWidget *gpio_output_pin_low;

    // Initialization
    gpio_panel = gtk_hbox_new(FALSE, 2);
    gpio_input_box = gtk_vbox_new(FALSE, 2);
    gpio_input_subbox_1 = gtk_hbox_new(FALSE, 2);
    gpio_input_subbox_2 = gtk_hbox_new(FALSE, 2);
    gpio_output_box = gtk_vbox_new(FALSE, 2);
    gpio_output_subbox_1 = gtk_hbox_new(FALSE, 2);
    gpio_output_subbox_2 = gtk_hbox_new(FALSE, 2);

    gpio_input_label = gtk_label_new("Input Pin");
    gpio_input_state_label = gtk_label_new("Unknown");
    gpio_input_state_update = gtk_button_new_with_label("Update");
    gpio_input_state_pin = gtk_entry_new();

    gpio_output_label = gtk_label_new("Output Pin");
    gpio_output_pin_entry = gtk_entry_new();
    gpio_output_pin_high = gtk_button_new_with_label("High");
    gpio_output_pin_low = gtk_button_new_with_label("Low");

    // Assigning Signals

    gpointer data[] = {gpio_input_state_pin, gpio_input_state_label};
    g_signal_connect(gpio_output_pin_high, "clicked", G_CALLBACK(gpio_callback_high), gpio_output_pin_entry);
    g_signal_connect(gpio_output_pin_low, "clicked", G_CALLBACK(gpio_callback_low), gpio_output_pin_entry);
    g_signal_connect(gpio_input_state_update, "clicked", G_CALLBACK(gpio_callback_update), data);

    // Packaging
    gtk_box_pack_start(GTK_BOX(gpio_input_subbox_1), gpio_input_label, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(gpio_input_subbox_1), gpio_input_state_pin, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(gpio_input_subbox_2), gpio_input_state_update, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(gpio_input_subbox_2), gpio_input_state_label, TRUE, TRUE, 0);

    gtk_box_pack_start(GTK_BOX(gpio_output_subbox_1), gpio_output_label, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(gpio_output_subbox_1), gpio_output_pin_entry, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(gpio_output_subbox_2), gpio_output_pin_low, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(gpio_output_subbox_2), gpio_output_pin_high, TRUE, TRUE, 0);

    gtk_box_pack_start(GTK_BOX(gpio_input_box), gpio_input_subbox_1, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(gpio_input_box), gpio_input_subbox_2, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(gpio_output_box), gpio_output_subbox_1, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(gpio_output_box), gpio_output_subbox_2, TRUE, TRUE, 0);

    gtk_box_pack_start(GTK_BOX(gpio_panel), gpio_input_box, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(gpio_panel), gpio_output_box, TRUE, TRUE, 0);

    return gpio_panel;
}