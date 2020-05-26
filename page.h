/* MIHAILA Cosmin-Constantin - 315CB */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include "utils.h"
#include "TCoada.h"
#include "TLista.h"
#ifndef _PAGE_
#define _PAGE_
typedef struct{
	char* url;
	unsigned int num_res;
	Resource* resources;
} TPage;


void list_dl(TPage* page,char* out_file);
TPage* InitPage(char* URL);
void downloads(AQ priority,char* fileName,TLG complete);
void wait(AQ priority, int bandwith, TLG complete);
#endif