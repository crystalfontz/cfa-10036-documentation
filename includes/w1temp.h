#ifndef __w1temp_h__
#define __w1temp_h__

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define DEBUG false
#define MAXDEVIECES 32

static char* w1temp_list[MAXDEVIECES];
static bool w1temp_isloaded = false;

void w1temp_init();
void w1temp_close();
int w1temp_getcount();
double w1temp_gettemp_celsius(int);
inline double w1temp_gettemp_farenheit(int);
inline char* w1temp_getid(int);

inline char* w1temp_getid(int index){
	return (index>0 && index<w1temp_getcount() && w1temp_isloaded)?w1temp_list[index]:NULL;
}

void w1temp_init(){
	
	if(!w1temp_isloaded)
		w1temp_close();

	FILE *device_list = fopen("/sys/bus/w1/devices/w1_bus_master1/w1_master_slaves","r");
	if(device_list!=NULL)
	{
		int count = 0;
		char device[17];
		while(fgets(device,17,device_list)!=NULL){
			device[15] = 0;
			char *dev = malloc(sizeof(char)*17);
			strncpy(dev,device,16);
			w1temp_list[count] = dev;
			if(DEBUG)printf("Device %i:\t\"%s\"\n",count,w1temp_list[count]);
			count++;
		}
		fclose(device_list);
	} else {
		if(DEBUG)printf("Couldn't open the file\n");
	}
}

void w1temp_close(){
	int count = 0;
	if(w1temp_isloaded)
		while(w1temp_list[count]!=NULL)
			free(w1temp_list[count]);
}

int w1temp_getcount(){
	FILE *device_count = fopen("/sys/bus/w1/devices/w1_bus_master1/w1_master_slave_count","r");
	int devices=0;
	if(device_count!=NULL)
		fscanf(device_count,"%i",&devices);
	return devices;
}

double w1temp_gettemp_celsius(int index){
	if(index<0 || index>w1temp_getcount()){
		return -1;
	} else {
		char path[64];
		memset(path,0,strlen(path));
		strcat(path,"/sys/bus/w1/devices/w1_bus_master1/");
		strcat(path,w1temp_list[index]);
		strcat(path,"/w1_slave");
		strcat(path,"\0");
		FILE *device = fopen(path,"r");
		
		char file[512];
		fgets(file,512,device);
		fgets(file,512,device);
		fclose(device);

		return atof(strstr(file,"t=")+2)/1000;
	}

	return -1;
}

inline double w1temp_gettemp_farenheit(int index){
	return (w1temp_gettemp_celsius(index)*1.8)+32;
}

#endif