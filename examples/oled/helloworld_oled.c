#include <stdlib.h>

#include "display.h"

#define SSD1307_DISPLAY 1

int main(int argc, char *argv[])
{
    display_fill(0x0);
    display_writebuffer(0, 0, "Hello World!");
    display_send();

    system("sleep 3");

    display_writebuffer(0, 1, "Goodbye World!");
    display_send();

    system("sleep 3");

    display_writebuffer(0, 2, "Hello Again!");
    display_send();

    system("sleep 3");

//    display_fill(0x0);
//    display_send();

    return 0;
}
