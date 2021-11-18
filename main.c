#include<signal.h>
#include<stdbool.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include"blist.h"
#include"buf.h"
#include"term.h"
#include"vec.h"

void display_slide(char*fn,Buf*file_buffer,Vec*positions,size_t i);
void die(int s);

Buf*file_buffer;
Vec*positions;

int main(int argc,char**argv)
{
	FILE*f;
	int running=true;
	int nm=0;

	file_buffer=buf_new();
	positions=vec_new();

	if(!file_buffer)
	{
		fprintf(stderr,"error: failed to allocate file buffer\n");
		return 5;
	}

	if(!positions)
	{
		fprintf(stderr,"error: failed to allocate vector\n");
		return 5;
	}

	signal(SIGINT,die);

	// Parse args
	if(argc<2)
	{
		fprintf(stderr,"usage: re FILENAME\n");
		return 1;
	}

	f=fopen(argv[1],"r");
	if(!f)
	{
		fprintf(stderr,"error: failed to open file '%s'\n",
				argv[1]);
		return 2;
	}

	// Read file into buffer
	while(!feof(f))
	{
		char c[512];
		size_t n=fread(c,1,512,f);
		buf_push(file_buffer,c,n);
	}
	fclose(f);

	// Mark offsets between paragraphs
	vec_push(positions,0);
	for(size_t i=1;i<file_buffer->n;++i)
	{
		if(file_buffer->b[i-1]=='\n'&&file_buffer->b[i]=='\n')
			vec_push(positions,i+1);// separate!
	}
	vec_push(positions,file_buffer->n);

	// Render -----
	// Print individual sections
	// As stored in file_buffer and
	// Divided by positions
	save_curs();
	save_screen();
	canon(false);
	echo(false);
	set_curs(false);
	for(size_t i=0;running;)
	{
		char c;
		display_slide(argv[1],file_buffer,positions,i);

		switch(c=getchar())
		{

			// Numeric modifier
			case '1':case '2':case '3':case '4':case '5':
			case '6':case '7':case '8':case '9':
				nm=c-'0';
				break;

			case 'g':
				i=0;
				nm=0;
				break;

			case 'G':
				if(nm==0)
					i=positions->n-2;
				else if(nm<positions->n)
					i=nm-1;
				nm=0;
				break;

			// Previous
			case 'b':
			case 'p':
			case 'k':
				if(i>0)
				{
					if(nm<2)
						--i;
					else if(nm<=i)
						i-=nm;
					else
						i=0;
				}
				nm=0;
				break;

			// Next
			case ' ':
			case 'n':
			case 'j':
				if(i<positions->n-2)
				{
					if(nm<2)
						++i;
					else if(i+nm<positions->n-2)
						i+=nm;
					else
						i=positions->n-2;
				}
				nm=0;
				break;

			// Quit
			case 27:
			case 'q':
				running=false;
				nm=0;
				break;

			default:
				//++i;
				nm=0;
				break;
		}
	}

	// Exit
	canon(true);
	echo(true);
	restore_curs();
	restore_screen();
	set_curs(true);
	vec_free(positions);
	buf_free(file_buffer);
}

void die(int s)
{
	fprintf(stderr,"freeing buffer...\n");
	fprintf(stderr,"exiting...\n");
	canon(true);
	echo(true);
	restore_curs();
	restore_screen();
	set_curs(true);
	vec_free(positions);
	buf_free(file_buffer);
	exit(55);
}

void display_slide(char*fn,Buf*file_buffer,Vec*positions,size_t i)
{
	size_t offset1=positions->b[i];
	size_t offset2=positions->b[i+1];
	char num[128]={0};
	const size_t max_filename_length=32;

	clear();
	move(2,1);
	write(1,file_buffer->b+offset1,offset2-offset1);

	// Print statusbar
	move(1,1);
	send_serial_single("[47m");
	send_serial_single("[30m");
	sprintf(num,"%lu",positions->n-1);
	if(strlen(fn)<max_filename_length)
	{
		write(1,fn,strlen(fn));
	}

	else
	{
		write(1,fn,max_filename_length-3);
		write(1,"...",3);
	}
	printf(" (%0*lu/%0*lu)",
			strlen(num),i+1,
			strlen(num),positions->n-1);
	fflush(stdout);
	clearline();
	send_serial_single("[49m");
	send_serial_single("[39m");
	fflush(stdout);
}
