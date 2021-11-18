#include"blist.h"

BList*blist_new(BList*head)
{
	BList*bl=malloc(sizeof(BList));
	if(!bl)return NULL;
	bl->prev=head;
	bl->next=NULL;
	bl->b=NULL;
	return bl;
}

void blist_free(BList*bl)
{
	if(!bl)return;
	while(bl->next)
	{
		BList*t=bl;
		bl=bl->next;
		if(t->b)
			free(t->b);
		free(t);
	}
}

void blist_push(BList*bl,char*s,size_t n)
{
	BList*p=bl;
	if(!bl)return;
	while(p->next)p=p->next;
	p->next=blist_new(p);
	if(!p->next)return;
	{
		Buf*b=buf_new();
		if(!b)return;
		for(size_t i=0;i<n;i+=BBUFLEN)
			buf_push(b,s,n);
		p->next->b=b;
	}
	p->next->next=NULL;
}

size_t blist_len(BList*bl)
{
	size_t n=1;
	if(!bl)return 0;
	while(bl->next)
	{
		++n;
		bl=bl->next;
	}
	return n;
}

void blist_print(BList*bl)
{
	size_t i=0;
	printf("bl n: %lu\n",blist_len(bl));
	for(BList*p=bl;bl;bl=bl->next)
	{
		printf("[%lu: %p]{n:%p p:%p b:%p}\n",i,bl,bl->next,bl->prev,bl->b);
		buf_print(bl->b);
		printf("\n");
		++i;
	}
	puts("");
}

BList*blist_at(BList*head,size_t n)
{
	size_t i=0;
	for(BList*p=head;p->next;p=p->next)
	{
		if(i==n)
			return p;
		++i;
	}
	return NULL;
}

