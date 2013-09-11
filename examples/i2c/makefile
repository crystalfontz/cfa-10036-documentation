CC=arm-none-linux-gnueabi-gcc
LD=arm-none-linux-gnueabi-gcc
CFLAGS=-Wall -I..\..\includes
LDFLAGS=-L..\..\libs -lcfa10036

i2c:i2c.o
	$(LD) i2c.o -o i2c $(LDFLAGS)

i2c.o:i2c.c 
	$(CC) i2c.c -c $(CFLAGS)