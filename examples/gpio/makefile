CC=arm-none-linux-gnueabi-gcc
LD=arm-none-linux-gnueabi-gcc
CFLAGS=-I..\..\includes -Wall
LDFLAGS=-L..\..\libs -lcfa10036

gpio:gpio.o
	$(LD) gpio.o -o gpio $(LDFLAGS)

gpio.o:gpio.c 
	$(CC) gpio.c -c $(CFLAGS)