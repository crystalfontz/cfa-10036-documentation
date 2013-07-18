#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include "i2c-dev.h"

#define ADDRESS 0x2A
#define DISPLAY_HIDE 0x02
#define DISPLAY_SHOW 0x03
#define DISPLAY_INFO 0x1F
#define DISPLAY_CLEAR 0x0C

int file;

int main(void){
	printf("Selecting the Bus\n");
	file = open("/dev/i2c-1", O_RDWR);
	if(file < 0){
		printf("Error Selecting the Bus\n");
		exit(1);
	}

	printf("Selecting the Device\n");
	if(ioctl(file, I2C_SLAVE, ADDRESS) < 0){
		printf("Error Selecting the Bus\n");
		exit(1);
	}

	if(i2c_smbus_write_byte(file,DISPLAY_CLEAR) < 0){
		printf("Error Sending Data on I2C\n");
	}

	sleep(2);

	if(i2c_smbus_write_byte(file,DISPLAY_INFO) < 0){
		printf("Error Sending Data on I2C\n");
	}

	sleep(2);

	if(i2c_smbus_write_byte(file,DISPLAY_CLEAR) < 0){
		printf("Error Sending Data on I2C\n");
	}

	sleep(2);

	char *str = "Hello World";
	int i;
	for(i=0;i<strlen(str);i++){
		if(i2c_smbus_write_byte(file,str[i]) < 0){
			printf("Error Sending Data on I2C\n");
		}
	}

	return 0;
}