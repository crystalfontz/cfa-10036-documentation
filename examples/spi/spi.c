#include <spi.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    spi_init(1, 8, 125000);

    char *hello_world = "Hello World";
    spi_write_chunk(hello_world, strlen(hello_world));

    return 0;
}