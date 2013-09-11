CC=arm-none-linux-gnueabi-gcc
LD=arm-none-linux-gnueabi-gcc
CFLAGS=-I..\..\includes -Wall
LDFLAGS=-L..\..\libs -lcfa10036

Hello:Hello.o
	$(LD) Hello.o -o Hello $(LDFLAGS)

Hello.o:Hello.c 
	$(CC) Hello.c -c $(CFLAGS)