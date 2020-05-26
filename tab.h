/* MIHAILA Cosmin-Constantin - 315CB */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include "page.h"
#include "TStiva.h"
#include "TLista.h"
#include "TCoada.h"
#ifndef _TAB_
#define _TAB_

typedef struct{
	TPage* current_page;
	ASt back_stack;
	ASt forward_stack;
} TTab;

void GoTo(TTab* tab,char* URL,char* out,AQ coadaHistory);
TTab* newTab();
void newTabCell(TLG tabs);
TLG delTab(TLG tabs);
void back(TCelulaG* current_tab);
void forward(TCelulaG* current_tab);
void delHistory(AQ coada, int nr);

#endif