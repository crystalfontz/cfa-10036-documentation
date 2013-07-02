#include "gpio.h"
#include "display.h"

const int OUTPUT = 22;
const int INPUT = 21;

void main(int argc,char* argv[]){
	gpio_init();
	gpio_config(OUTPUT,1);
	gpio_config(INPUT,0);
	display_fill(0x0);
	int count = 4;
	bool first = true;
	while(count>0){
		if(gpio_read(INPUT)){
			gpio_write(OUTPUT,0);
			display_writebuffer(0,0,"LED OFF");
			first = true;
		} else {
			if(first)
				count--;
			gpio_write(OUTPUT,1);
			display_writebuffer(0,0,"LED ON ");
			first = false;
		}
		display_send();
	}
	display_fill(0x0);
	display_send();
	gpio_write(OUTPUT,0);
	gpio_close();
}