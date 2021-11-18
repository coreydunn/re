#pragma once
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>

#define BBUFLEN 512

typedef struct Buf
{
	size_t c;
	size_t n;
	char*b;
} Buf;

Buf*buf_new(void);
void buf_free(Buf*b);
void buf_grow(Buf*b);
void buf_print(Buf*b);
void buf_push(Buf*b,char*c,size_t n);
