#ifndef __gpio_h__
#define __gpio_h__

/*						GPIO library for the cfa-10036
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 or later
 * as published by the Free Software Foundation.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <gpio_pindefs.h>

#define DEBUG false
#define PINCOUNT 96


/**
  *	pins_config map
  *
  *	-3 = Can't set direction
  * -2 = Can't export
  * -1 = Exported, but direction has not been set
  * 0 = Exported, and direction has been set to input
  * 1 = Exported, and direction has been set to output
 **/
int pins_config[PINCOUNT];
FILE* pins_value[PINCOUNT];

/**
  *	Converts an int into a string
  * 
  * @param {int} val The integer to be converted
  * @return {char*} The converted integer
 **/
char* itoa(int val)
{
	static char buf[32] = {0};
	int base = 10;

	int i = 30;

	for(; val && i ; --i, val /= base)
		buf[i] = "0123456789abcdef"[val % base];

	return &buf[i+1];
}


/**
  * Initializes the library by exporting all of the gpio
 **/
bool gpio_init(){
	int workingpins=0;
	FILE* fout;
	int i;
	for(i=0;i<PINCOUNT;i++){
		fout = fopen("/sys/class/gpio/export","w");
		if(fout!=NULL){
			fprintf(fout,"%i\n",i);
			if(DEBUG) printf("Exported pin %i\n",i);
			workingpins++;
			pins_config[i] = -1;
			fclose(fout);
		} else {
			printf("Couldn't open %i\n",i);
			pins_config[i] = -2;
		}
	}
	if(workingpins==0){
		return false;
	} else {
		return true;
	}
}
/**
  * Loads all of the filepointers into memory
 **/
void gpio_config_loader(unsigned int pin,int state){
	char dirstring[64];
	if(pins_value[pin]!=NULL)
		fclose(pins_value[pin]);

	memset(&dirstring,'\0',64);
	strcat(dirstring,"/sys/class/gpio/gpio");
	strcat(dirstring,itoa(pin));
	strcat(dirstring,"/value");
	
	if(state == 1){
		pins_value[pin] = fopen(dirstring,"w");
	} else if(state == 0){
		pins_value[pin] = fopen(dirstring,"r");
	} else {
		pins_value[pin] = NULL;
	}
}


/**
  * Configures a gpio port as either input or output
  *
  * @param {int} pin The port to be configured 
  * @param {int} state Determines if the port will be configured as input (state==0) or output (state==1)
  * @return {bool} Returns true if the port configuration was succesful, false if it was not.
 **/
bool gpio_config(unsigned int pin,unsigned int state){
	if(pin < PINCOUNT && pins_config[pin] >= -1)
	{
		FILE* fout;
		char dirstring[64];
		dirstring[63] = '\0';
		sprintf(dirstring,"/sys/class/gpio/gpio%i/direction",pin);
		fout = fopen(dirstring,"w");
		if(fout!=NULL){
			if(state==1){
				fprintf(fout,"out\n");
				if(DEBUG)printf("Set pin %i output\n",pin);
				pins_config[pin] = 1;
			} else if(state==0){
				fprintf(fout,"in\n");
				if(DEBUG)printf("Set pin %i input\n",pin);
				pins_config[pin] = 0;
			}
			fclose(fout);
			gpio_config_loader(pin,state);
			return true;
		} else {
			if(DEBUG)printf("Couldn't set direction %i\n",pin);
			pins_config[pin] = -3;
			return false;
		}
	} else {
		return false;
	}
}


/**
  * Writes to a gpio port, setting it to either high (1), or low (0). The port is required to be configured for output
  * 
  * @param {int} portnum The port to be configured
  * @param {int} state The state that the port will be set to high (1) or low (0)
  * @return {bool} Returns true if the state was set succesfully, false if it failed to set the state
 **/
bool gpio_write(unsigned int portnum,unsigned int state){
	if(portnum < PINCOUNT && pins_config[portnum] == 1)
	{
		FILE* fout = pins_value[portnum];
		// Initialize everything in the state string except the port high, or low
		char state_string[3];
		state_string[1] = 0;
		state_string[2] = 0;
		if(fout!=NULL){
			// 14.8 kz currently with all of the files open
			// 13.9 kz if fopen/fclose are excluded
			// 405 hz with fprintf(fout,"%i\n",(state!=0)?1:0);
			// 411 hz with fwrite()
			state_string[0]=state?'1':'0';
			fwrite(state_string,1,2,fout);
			fflush(fout);
			if(DEBUG)printf("Set pin %i %s\n",portnum,(state!=0)?"High":"Low");
			return true;
		} else {
			if(DEBUG) printf("Couldn't set pin %i %s\n",portnum,(state!=0)?"High":"Low");
			return false;
		}
	} else {
		return false;
	}
}


/**
  * Reads the state of a pin. Unlike gpio_write, the pin can be set to input, or output.
  *
  * @param {int} portnum The port to be read
  * @return {int} The state of the port that was read
 **/
int gpio_read(unsigned int portnum){
	if((pins_config[portnum] == 0 || pins_config[portnum] == 1) && portnum < PINCOUNT)
	{
		FILE* fin = pins_value[portnum];
		if(fin!=NULL){
			int res = (fgetc(fin)=='1')?1:0;
			gpio_config_loader(portnum,0);
			return res;
		} else {
			if(DEBUG) printf("Couldn't read pin %i\n", portnum);
			return -1;
		}
	} else {
		return -1;
	}
}

#endif

/**
  * Frees all of the system resources up
  *
 **/
void gpio_close(){
	int i;
	for(i=0;i<PINCOUNT;i++){
		if(pins_value[i]!=NULL)
			fclose(pins_value[i]);
	}
}