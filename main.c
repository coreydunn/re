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

void display_slide(Buf*file_buffer,Vec*positions,size_t i);
void die(int s);

Buf*file_buffer;
Vec*positions;

int main(int argc,char**argv)
{
	FILE*f;
	int running=true;

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
		display_slide(file_buffer,positions,i);

		switch(getchar())
		{

			case 'g':
				i=0;
				break;

			case 'G':
				i=positions->n-2;
				break;

			// Previous
			case 'b':
			case 'p':
			case 'k':
				if(i>0)
					--i;
				break;

			// Next
			case ' ':
			case 'n':
			case 'j':
				if(i<positions->n-2)
					++i;
				break;

			// Quit
			case 27:
			case 'q':
				running=false;
				break;

			default:
				//++i;
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

void display_slide(Buf*file_buffer,Vec*positions,size_t i)
{
	size_t offset1=positions->b[i];
	size_t offset2=positions->b[i+1];
	char num[128]={0};

	clear();
	move(2,1);
	write(1,file_buffer->b+offset1,offset2-offset1);

	move(1,1);
	sprintf(num,"%lu",positions->n-1);
	printf("(%0*lu/%0*lu)",
			strlen(num),i+1,
			strlen(num),positions->n-1);
}
