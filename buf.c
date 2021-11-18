#include"buf.h"

Buf*buf_new(void)
{
	Buf*b=malloc(sizeof(Buf));
	if(!b)return NULL;
	b->c=0;
	b->n=0;
	b->b=NULL;
	return b;
}

void buf_free(Buf*b)
{
	if(!b)return;
	if(b->b)
		free(b->b);
	b->c=0;
	b->n=0;
	b->b=NULL;
	free(b);
}

void buf_grow(Buf*b)
{
	if(!b)return;
	if(!b->b)
	{
		b->b=malloc(BBUFLEN*sizeof(char));
		b->c=BBUFLEN;
	}

	else
	{
		b->b=realloc(b->b,(b->c+BBUFLEN)*sizeof(char));
		b->c+=BBUFLEN;
	}
}

void buf_push(Buf*b,char*c,size_t n)
{
	if(n>BBUFLEN)
	{
		fprintf(stderr,"error: cannot write %lu bytes to buffer\n",n);
		return;
	}
	if(!b||!c||!n)return;
	if(!b->b||b->n+n>b->c)
		buf_grow(b);
	memcpy(b->b+b->n,c,n);
	b->n+=n;
}

void buf_print(Buf*b)
{
	if(!b)
	{
		printf("(nil)");
		return;
	}
	//fprintf(stderr,"b (%p): c: %lu n: %lu\n",b,b->c,b->n);
	write(1,b->b,b->n);
	fflush(stdout);
}
