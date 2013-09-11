CC=arm-none-linux-gnueabi-gcc
LD=arm-none-linux-gnueabi-gcc
CFLAGS=-IP:\cfa-10036-documentation\includes -Wall
LDFLAGS=-LP:\cfa-10036-documentation\libs -lcfa10036

webinterface:webinterface.o
	$(LD) webinterface.o -o webinterface $(LDFLAGS)

webinterface.o:webinterface.c 
	$(CC) webinterface.c -c $(CFLAGS)