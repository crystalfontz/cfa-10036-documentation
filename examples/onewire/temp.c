#include <w1temp.h>
#include <stdio.h>
#include <display.h>

char *buffer[3];

void shift(int index){
	if(index>2)
		free(buffer[2]);
	if(index>1)
		buffer[2] = buffer[1];
	if(buffer>0)
		buffer[1] = buffer[0];

	buffer[0] = malloc(sizeof(char)*16);
	sprintf(buffer[0],"Temp %i:%f",index,w1temp_get_temp_fahrenheit(index));

}

void display(){
	display_fill(0x0);
	display_writebuffer(0,0,buffer[0]);
	display_writebuffer(0,1,buffer[1]);
	display_writebuffer(0,2,buffer[2]);
	display_send();
}

void init(){	
	buffer[0] = "";
	buffer[1] = "";
	buffer[2] = "";
}

void loopall(){
	int iter=0,count = w1temp_getcount();
	while(iter<count){
		shift(iter++);
		display();
		system("sleep 1");
	}
}

void cleanup(){
	system("sleep 1");
	display_fill(0x0);
	display_send();

	if(buffer[0]!=NULL)
		free(buffer[0]);
	if(buffer[1]!=NULL)
		free(buffer[1]);
	if(buffer[2]!=NULL)
		free(buffer[2]);
}

int main(void){
	w1temp_init();
	init();
	
	loopall();
	cleanup();
	w1temp_close();
	return 0;
}