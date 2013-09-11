CC=arm-none-linux-gnueabi-gcc
LD=arm-none-linux-gnueabi-gcc
GTKDEPDIR=P:\gtk-dependencies
CFLAGS=-I$(GTKDEPDIR)\includes -Wall -std=c99 \
	-IP:\cfa-10036-documentation\includes
LDFLAGS=-LP:\CFA10036\ Libraries \
	-LP:\cfa-10036-documentation\libs \
	-lcfa10036 \
	-lgtk-x11-2.0 \
	-lgdk-x11-2.0 \
	-latk-1.0 \
	-lgio-2.0 \
	-lpangoft2-1.0  \
	-lpangocairo-1.0 \
	-lgdk_pixbuf-2.0 \
	-lcairo \
	-lpango-1.0 \
	-lfreetype \
	-lfontconfig \
	-lgobject-2.0 \
	-lglib-2.0 \
	-Wl,-rpath=P:\CFA10036\ Libraries

guitester:build/guitester.o build/oledpanel.o build/gpiopanel.o build/dowpanel.o build/i2cpanel.o
	$(LD) build/guitester.o build/oledpanel.o build/gpiopanel.o build/dowpanel.o build/i2cpanel.o -o guitester $(LDFLAGS) -lcfa10036

build/guitester.o:src/guitester.c
	$(CC) src/guitester.c -c -o build/guitester.o $(CFLAGS)

build/oledpanel.o:src/oledpanel.c src/oledpanel.h
	$(CC) src/oledpanel.c -c -o build/oledpanel.o $(CFLAGS)

build/gpiopanel.o:src/gpiopanel.c src/gpiopanel.h
	$(CC) src/gpiopanel.c -c -o build/gpiopanel.o $(CFLAGS)

build/dowpanel.o:src/dowpanel.c src/dowpanel.h
	$(CC) src/dowpanel.c -c -o build/dowpanel.o $(CFLAGS)

build/i2cpanel.o:src/i2cpanel.c src/i2cpanel.h
	$(CC) src/i2cpanel.c -c -o build/i2cpanel.o $(CFLAGS)

clean:
	-rm guitester
	-rm build/guitester.o
	-rm build/oledpanel.o
	-rm build/dowpanel.o
	-rm build/i2cpanel.o
	-rm build/gpiopanel.o