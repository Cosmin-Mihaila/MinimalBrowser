/* MIHAILA Cosmin-Constantin - 315CB */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include <stdarg.h>

#ifndef _STIVA_
#define _STIVA_

typedef struct celst{
	struct celst* urm;
	void* info;
} TCelSt, *ACelSt;

typedef struct stiva{
	size_t dime;
	ACelSt vf;
} TStiva, *ASt;

#define VF(a) (((ASt)(a))->vf)
#define DIME(a) (((ASt)(a))->dime)

void* InitS(size_t d);
int Push(void* a, void* ae);
int Pop(void* s,void* ae);
void DistrS(void* a);

#endif