#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <w1temp.h>

static char *w1temp_list[DOW_MAX_DEVICES];
static bool w1temp_isloaded = false;

inline char *w1temp_getid(int index)
{
    return (index > 0 && index < w1temp_getcount() && w1temp_isloaded) ? w1temp_list[index] : NULL;
}

int w1temp_init()
{

    if (!w1temp_isloaded)
    {
        return DOW_ALREADY_RUNNING_ERROR;
    }

    FILE *device_list = fopen("/sys/bus/w1/devices/w1_bus_master1/w1_master_slaves", "r");
    
    if (device_list != NULL)
    {
        int count = 0;
        char device[17];
        while (fgets(device, 17, device_list) != NULL)
        {
            device[15] = 0;
            char *dev = malloc(sizeof(char) * 17);
            strncpy(dev, device, 16);
            w1temp_list[count] = dev;
            count++;
        }
        fclose(device_list);
        return 0;
    }
    else
    {
        return DOW_DEVICE_ACCESS_ERROR;
    }
}


int w1temp_getcount()
{
    FILE *device_count = fopen("/sys/bus/w1/devices/w1_bus_master1/w1_master_slave_count", "r");
    int devices = 0;
    if (device_count != NULL)
    {
        fscanf(device_count, "%i", &devices);
        return devices;
    }
    else
    {
        return DOW_DEVICE_ACCESS_ERROR;
    }
}

double w1temp_get_temp_celsius(int index)
{
    if (index < 0 || index > w1temp_getcount())
    {
        return DOW_INVALID_DEVICE_ID_ERROR;
    }
    else
    {
        char path[64];
        memset(path, 0, strlen(path));
        strcat(path, "/sys/bus/w1/devices/w1_bus_master1/");
        strcat(path, w1temp_list[index]);
        strcat(path, "/w1_slave");
        strcat(path, "\0");
        FILE *device = fopen(path, "r");

        char file[512];
        fgets(file, 512, device);
        fgets(file, 512, device);
        fclose(device);

        return atof(strstr(file, "t=") + 2) / 1000;
    }
}

inline double w1temp_get_temp_fahrenheit(int index)
{
    return (w1temp_get_temp_celsius(index) * 1.8) + 32;
}