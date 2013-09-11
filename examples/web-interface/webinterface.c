#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <gpio.h>
#include <display.h>

#define INPUT 22
#define OUTPUT 23

char *button_state = "";

char *strrep(char *str, char del)
{
    char *iter = str;
    while (iter != NULL && (*iter) != 0)
        *(iter++) = (*iter != del) ? *iter : ' ';
    return str;
}

int main(int argc, char *argv[])
{
    gpio_init();
    gpio_config(INPUT, 0);
    gpio_config(OUTPUT, 1);

    if (getenv("QUERY_STRING") != NULL)
    {
        char query[64];
        strcpy(query, getenv("QUERY_STRING"));

        if (strstr(query, "led-on") != NULL)
        {
            gpio_write(OUTPUT, 1);
        }
        else
        {
            gpio_write(OUTPUT, 0);
        }

        char *message = strrep(strstr(getenv("QUERY_STRING"), "message=") + 8, '+');
        if (message != NULL)
        {
            display_fill(0x0);
            display_writebuffer(0, 0, message);
            display_send();
        }
        else
        {
            display_fill(0x0);
            display_send();
        }

        if (!gpio_read(INPUT))
        {
            button_state = "Pressed";
        }
        else
        {
            button_state = "Not Pressed";
        }
    }
    else
    {
        gpio_write(OUTPUT, 0);
        display_fill(0x0);
        display_send();
    }

    printf("<h1>Web Interface</h1>");
    printf("Button State: %s", button_state);
    printf("<form action=\"webinterface.cgi\" method=\"get\"><br>");
    printf("Led On: <input type=\"checkbox\" name=\"led\"><br>");
    printf("Oled Message: <input type=\"text\" name=\"message\"><br>");
    printf("Submit: <input type=\"submit\"><br>");
    printf("</form>");
    printf("<br>");
    printf("QUERY_STRING: %s", getenv("QUERY_STRING"));

    return 0;
}