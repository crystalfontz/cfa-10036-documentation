#include <display.h>

int main(int argc,char* argv[]){
	display_fill(0x0);
	display_writebuffer(0,0,"Hello World!");
	display_send();

	system("sleep 3");

	display_writebuffer(0,0,"Good Bye World!");
	display_send();

	system("sleep 3");

	display_fill(0x0);
	display_send();
}