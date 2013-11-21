CC=arm-none-linux-gnueabi-gcc
LD=arm-none-linux-gnueabi-gcc
CFLAGS=-Wall

display:display.o
	$(LD) helloworld.o -o helloworld_oled $(LDFLAGS)

display.o:display.c 
	$(CC) helloworld_oled.c display.c $(CFLAGS)
