CC=arm-none-linux-gnueabi-gcc
LD=arm-none-linux-gnueabi-gcc
CFLAGS=-Wall
LDFLAGS=-L..\..\libs -lcfa10036

temp:temp.o
	$(LD) temp.o -o temp $(LDFLAGS)

temp.o:temp.c 
	$(CC) temp.c -c $(CFLAGS)