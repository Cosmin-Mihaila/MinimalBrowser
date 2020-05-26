/* MIHAILA Cosmin-Constantin - 315CB */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include <stdarg.h>

#ifndef _LISTA_
#define _LISTA_
typedef struct celulag
{
	void* info;
	struct celulag* urm;
	struct celulag* pre;
} TCelulaG, *TLG;

int InsLG(TLG* aL, void* ae, size_t d);
TCelulaG* change_tab(TLG tabs, int tab_index);
void print_open_tabs(TLG tabs,char* url);
void DistrugeLG(TLG* aL);
void DistrugeLGTabs(TLG* aL);

#endif