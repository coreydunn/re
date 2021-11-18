#pragma once
#include"buf.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct BList
{
	struct BList*next;
	struct BList*prev;
	Buf*b;
} BList;

BList*blist_at(BList*head,size_t n);
BList*blist_new(BList*head);
size_t blist_len(BList*bl);
void blist_free(BList*bl);
void blist_print(BList*bl);
void blist_push(BList*bl,char*s,size_t n);
