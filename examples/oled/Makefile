CC=arm-none-linux-gnueabi-gcc
LD=arm-none-linux-gnueabi-gcc
CFLAGS=-Wall
LDFLAGS=-lcfa10036

display:display.o
	$(LD) display.o -o display $(LDFLAGS)

display.o:display.c 
	$(CC) display.c -c $(CFLAGS)
