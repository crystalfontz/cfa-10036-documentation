#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/types.h>
#include <linux/spi/spidev.h>
#include <stdbool.h>
#include <math.h>
#include <spi.h>
#include <unistd.h>

struct _spi
{
    char *device;
    uint8_t mode;
    uint8_t bits;
    uint32_t speed;
    int fd;
};

SPIDEV *spi_init(int dev_no, int bpw, int speedl)
{
    if (dev_no < 0 || bpw < 1 || speedl < 0)
    {
        perror("SPI_INVALID_PARAMETER");
        return NULL;
    }

    SPIDEV *s = malloc(sizeof(SPIDEV));

    s->mode = 0;
    static char k[128];
    int ret = 0;
    s->speed = speedl;
    s->bits = bpw;
    memset(k, 0, 128);

    sprintf(k, "/dev/spidev32766.%i", dev_no);
    if (access(k, F_OK) != -1)
    {
        s->device = k;
    }
    else
    {
        perror("SPI_INVALID_DEVICE");
        return NULL;
    }

    s->fd = open(s->device, O_RDWR);
    if (s->fd < 0)
    {
        perror("SPI_DEVICE_ACCESS_ERROR");
        return NULL;
    }
    // Configure SPI Mode
    //mode |= SPI_3WIRE;
    ret = ioctl(s->fd, SPI_IOC_WR_MODE, &(s->mode));
    if (ret == -1)
    {
        perror("SPI_MODE_SET_ERROR");
        return NULL;
    }

    /*
     * bits per word
     */
    ret = ioctl(s->fd, SPI_IOC_WR_BITS_PER_WORD, &(s->bits));
    if (ret == -1)
    {
        perror("SPI_BITS_SET_ERROR");
        return NULL;
    }

    /*
     * max speed hz
     */
    ret = ioctl(s->fd, SPI_IOC_WR_MAX_SPEED_HZ, &(s->speed));
    if (ret == -1)
    {
        perror("SPI_SPEED_SET_ERROR");
        return NULL;
    }

    return s;
}

int spi_write_word(SPIDEV *s, void *data)
{
    int bit_count = (s->bits+0x07)>>3;
    int i = write(s->fd, data, bit_count);
    if (i == -1)
    {
        return SPI_WRITE_ERROR;
    }

    return 0;
}

int spi_write_chunk(SPIDEV *s, void *data, int count)
{
    int byte_size = (s->bits+0x07)>>3;
    for (int i = 0; i < count; i++)
    {
        int j = spi_write_word(s,data + (byte_size * i));
        if (j == -1)
            return SPI_WRITE_ERROR;
    }

    return 0;
}