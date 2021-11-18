#include"vec.h"

Vec*vec_new(void)
{
	Vec*v=malloc(sizeof(Vec));
	if(!v)return NULL;
	v->c=0;
	v->n=0;
	v->b=NULL;
	return v;
}

void vec_free(Vec*v)
{
	if(!v)return;
	if(v->b)
		free(v->b);
	v->b=NULL;
	v->c=0;
	v->n=0;
	free(v);
}

void vec_grow(Vec*v)
{
	if(!v)return;
	if(!v->b)
	{
		v->b=malloc(VVECLEN*sizeof(int));
		if(!v->b)return;
		v->c=VVECLEN;
	}

	else
	{
		v->b=realloc(v->b,(v->c+VVECLEN)*sizeof(int));
		if(!v->b)return;
		v->c+=VVECLEN;
	}
}

void vec_push(Vec*v,int i)
{
	if(!v)return;
	if(!v->b||v->n+1>v->c)
		vec_grow(v);
	v->b[v->n]=i;
	++v->n;
}

void vec_print(Vec*v)
{
	if(!v)return;
	printf("v (%p) c:%lu n:%lu b: [",v,v->c,v->n);
	for(size_t i=0;i<v->n;++i)
		printf("%d, ",v->b[i]);
	printf("]\n");
}
