#include "oledpanel.h"

static void oled_callback(GtkWidget *widget, gpointer data[])
{
    display_fill(0x0);
    display_writebuffer(0, 0, data[2]);
    display_writebuffer(0, 1, data[1]);
    display_writebuffer(0, 2, data[0]);
    display_send();
}

GtkWidget *guitester_panel_oled()
{
    // Declaration
    GtkWidget *oled_label;

    GtkWidget *oled_high_entry_label;
    GtkWidget *oled_high_entry;
    GtkWidget *oled_mid_entry_label;
    GtkWidget *oled_mid_entry;
    GtkWidget *oled_low_entry_label;
    GtkWidget *oled_low_entry;

    GtkWidget *oled_send_button;

    GtkWidget *oled_text_box;
    GtkWidget *oled_line_box;
    GtkWidget *oled_box;

    // Initialization
    oled_send_button = gtk_button_new_with_label("Update");
    oled_label = gtk_label_new("Oled");

    oled_high_entry_label = gtk_label_new("Top");
    oled_high_entry = gtk_entry_new();
    oled_mid_entry_label = gtk_label_new("Middle");
    oled_mid_entry = gtk_entry_new();
    oled_low_entry_label = gtk_label_new("Bottom");
    oled_low_entry = gtk_entry_new();

    oled_line_box = gtk_vbox_new(FALSE, 2);
    oled_box = gtk_hbox_new(FALSE, 2);
    oled_text_box = gtk_vbox_new(FALSE, 2);

    // Asigning Signals
    gpointer data[] = {oled_low_entry, oled_mid_entry, oled_low_entry};
    g_signal_connect(oled_send_button, "clicked", G_CALLBACK(oled_callback), data);

    // Packaging
    gtk_box_pack_start(GTK_BOX(oled_text_box), oled_label, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(oled_text_box), oled_send_button, TRUE, TRUE, 0);

    gtk_box_pack_start(GTK_BOX(oled_line_box), oled_high_entry_label, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(oled_line_box), oled_high_entry, TRUE, TRUE, 0);

    gtk_box_pack_start(GTK_BOX(oled_line_box), oled_mid_entry_label, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(oled_line_box), oled_mid_entry, TRUE, TRUE, 0);

    gtk_box_pack_start(GTK_BOX(oled_line_box), oled_low_entry_label, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(oled_line_box), oled_low_entry, TRUE, TRUE, 0);

    gtk_box_pack_start(GTK_BOX(oled_box), oled_text_box, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(oled_box), oled_line_box, TRUE, TRUE, 0);

    return oled_box;
}