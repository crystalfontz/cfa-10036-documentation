#ifndef spi_h
#define spi_h

#define SPI_INVALID_PARAMETER   (-1)
#define SPI_INVALID_DEVICE      (-2)
#define SPI_DEVICE_ACCESS_ERROR (-3)
#define SPI_MODE_SET_ERROR      (-4)
#define SPI_BITS_SET_ERROR      (-5)
#define SPI_SPEED_SET_ERROR     (-6)
#define SPI_WRITE_ERROR         (-7)

int spi_init(int devno, int bpw, int speed);
int spi_write_word(void *data);
int spi_write_chunk(void *data, int count);

#endif
