/* MIHAILA Cosmin-Constantin - 315CB */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include <stdarg.h>

#ifndef _COADA_
#define _COADA_

typedef struct cel
{
	struct cel* urm;
	void* info;
} TCel, *ACel;

typedef struct coada
{
	size_t dime;
	ACel ic,sc;
} TCoada, *AQ;

int ExtrQ(void* a, void* ae);
int IntrQ(void* a, void* ae);
int IntrQPriority(void* a, void* ae);
void DistrQ(void* a);

#endif