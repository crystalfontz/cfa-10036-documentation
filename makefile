CC=arm-none-linux-gnueabi-gcc
AR=arm-none-linux-gnueabi-ar
CFLAGS=-Wall

build: clean-lib ./libs/libcfa10036.a 

./libs/libcfa10036.a: ./build/display.o ./build/gpio.o ./build/i2c.o ./build/w1temp.o
	$(AR) -cvq ./libs/libcfa10036.a ./build/display.o ./build/gpio.o ./build/i2c.o ./build/w1temp.o
	$(AR) -t ./libs/libcfa10036.a

./build/display.o:./src/display.c
	$(CC) ./src/display.c -c -o ./build/display.o $(CFLAGS)

./build/gpio.o:./src/gpio.c
	$(CC) ./src/gpio.c -c -o ./build/gpio.o $(CFLAGS)

./build/i2c.o:./src/i2c.c
	$(CC) ./src/i2c.c -c -o ./build/i2c.o $(CFLAGS)

./build/w1temp.o:./src/w1temp.c
	$(CC) ./src/w1temp.c -c -o ./build/w1temp.o $(CFLAGS)

clean:
	-rm ./libs/libcfa10036.a
	-rm ./build/display.o
	-rm ./build/w1temp.o
	-rm ./build/i2c.o
	-rm ./build/gpio.o

clean-lib:
	-rm ./libs/libcfa10036.a