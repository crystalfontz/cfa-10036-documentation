#include "i2cpanel.h"

static void i2c_callback(GtkWidget *widget, gpointer data[])
{
    int i2c_device_address = atoi(gtk_entry_get_text(data[0]));
    int i2c_device_command = atoi(gtk_entry_get_text(data[1]));

    int file = open("/dev/i2c-1", O_RDWR);
    if (file < 0)
    {
        printf("Error Selecting the Bus\n");
        return;
    }
    else
    {
        printf("Selecting the Device\n");
        if (ioctl(file, I2C_SLAVE, i2c_device_address) < 0)
        {
            printf("Error Selecting the Bus\n");
        }
        else
        {
            if (i2c_smbus_write_byte(file, i2c_device_command) < 0)
            {
                printf("Error Sending Data on I2C\n");
            }
        }
        close(file);
    }
}

GtkWidget *guitester_panel_i2c()
{
    // Declaration
    GtkWidget *i2c_box;

    GtkWidget *i2c_top_box;
    GtkWidget *i2c_device_address_label;
    GtkWidget *i2c_device_address_entry;

    GtkWidget *i2c_bottom_box;
    GtkWidget *i2c_device_message_label;
    GtkWidget *i2c_device_message_entry;
    GtkWidget *i2c_device_message_submit;

    // Initialization
    i2c_box = gtk_vbox_new(FALSE, 2);
    i2c_top_box = gtk_hbox_new(FALSE, 2);
    i2c_bottom_box = gtk_hbox_new(FALSE, 2);

    i2c_device_address_label = gtk_label_new("Device Address");
    i2c_device_message_submit = gtk_button_new_with_label("Submit");
    i2c_device_message_label = gtk_label_new("Message");
    i2c_device_message_entry = gtk_entry_new();
    i2c_device_address_entry = gtk_entry_new();

    // Assigning Signals
    gpointer data[] = {i2c_device_address_entry, i2c_device_message_entry};
    g_signal_connect(i2c_device_message_submit, "clicked", G_CALLBACK(i2c_callback), data);

    // Packaging
    gtk_box_pack_start(GTK_BOX(i2c_top_box), i2c_device_address_label, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(i2c_top_box), i2c_device_address_entry, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(i2c_bottom_box), i2c_device_message_label, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(i2c_bottom_box), i2c_device_message_entry, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(i2c_bottom_box), i2c_device_message_submit, FALSE, FALSE, 0);

    gtk_box_pack_start(GTK_BOX(i2c_box), i2c_top_box, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(i2c_box), i2c_bottom_box, TRUE, TRUE, 0);
    return i2c_box;
}