#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>

#define VVECLEN 32

typedef struct Vec
{
	size_t c;
	size_t n;
	int*b;
} Vec;

Vec*vec_new(void);
void vec_free(Vec*v);
void vec_grow(Vec*v);
void vec_push(Vec*v,int i);
void vec_print(Vec*v);
