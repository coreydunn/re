#include"term.h"

void send_serial_single(char*s)
{
	printf("\033%s",s);
	fflush(stdout);
}

void send_serial_double(uint32_t y,uint32_t x,char*s)
{
	printf("\033[%lu;%lu%s",y,x,s);
	fflush(stdout);
}

void echo(int b)
{
	struct termios state;

	tcgetattr(0,&state);
	if(b)
		state.c_lflag|=ECHO;
	else
		state.c_lflag&=~ECHO;
	tcsetattr(0,TCSAFLUSH,&state);
}

void canon(int b)
{
	struct termios state;

	tcgetattr(0,&state);
	if(b)
		state.c_lflag|=ICANON;
	else
		state.c_lflag&=~ICANON;
	tcsetattr(0,TCSAFLUSH,&state);
}
