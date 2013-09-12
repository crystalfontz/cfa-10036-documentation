#include <spi.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    SPIDEV *s = spi_init(1, 8, 125000);

    char *hello_world = "\x0cHello World";
    spi_write_chunk(s, hello_world, strlen(hello_world));

    sleep(2);

    unsigned char c = 0x1F;
    spi_write_word(s,&c);

    return 0;
}