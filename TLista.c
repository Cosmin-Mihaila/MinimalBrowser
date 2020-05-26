/* MIHAILA Cosmin-Constantin - 315CB */

#include "TLista.h"
#include "tab.h"
#include "TStiva.h"

// Functie pentru inserarea unui element intr-o lista generica
int InsLG(TLG* aL, void* ae, size_t d)
{
	TLG aux = (TLG)malloc(sizeof(TCelulaG));
	if(!aux){
		return 0;
	}

	aux->info = malloc(d);
	if(!aux->info){
		free(aux);
		return 0;
	}

	TLG p = *aL;
	memcpy(aux->info,ae,d);
	free(ae);

	// Parcurgem lista pentru a adauga elementul la sfarsitul acesteia
	while(p->urm != NULL){
		p=p->urm;
	}

	// Cazul in care lista nu este goala
	if(p->info != NULL && p != NULL){
		p->urm = aux;
		aux->pre = p;
		aux->urm = NULL;
	}
	else{
		p->info = aux->info;
		p->urm = NULL;
		free(aux);
	}

	return 1;
}

// Functie pentru schimbarea tabului curent
TCelulaG* change_tab(TLG tabs, int tab_index)
{
	int i;
	TLG p = tabs;
	for(i = 0; i < tab_index; i++){
		p = p->urm;
	}
	return p;
}

// Functie pentru afisarea taburilor deschise intr-un moment
void print_open_tabs(TLG tabs,char* url)
{
	TLG aux = tabs;
	int i = 0;
	FILE* print_out;
	print_out = fopen(url,"at");
	if(!print_out){
		printf("ERROR");
		exit(1);
	}
	// Parcurgem toata lista de taburi
	while(aux != NULL){

		// Verificam daca tabul are o pagina deschisa
		if(((TTab*)aux->info)->current_page != NULL){
			fprintf(print_out,"(%d: %s)\n",i,
					((TTab*)aux->info)->current_page->url);
		}
		else{
			fprintf(print_out,"(%d: empty)\n",i);
		}
		i++;
		aux = aux->urm;
	}
	fclose(print_out);
}

// Functie pentru eliberarea memoriei listei de taburi
void DistrugeLGTabs(TLG* aL)
{
	TLG aux;
	while(*aL){
		aux = *aL;
		*aL = aux->urm;
		if(((TTab*)aux->info)->current_page != NULL){
			free(((TTab*)aux->info)->current_page->url);
			free(((TTab*)aux->info)->current_page->resources);
			free(((TTab*)aux->info)->current_page);
		}
		DistrS(((TTab*)aux->info)->back_stack);
		DistrS(((TTab*)aux->info)->forward_stack);
		free(((TTab*)aux->info)->forward_stack);
		free(((TTab*)aux->info)->back_stack);
		free((TTab*)aux->info);
		free(aux);
	}
}

// Functie pentru eliberarea memoriei unei liste
void DistrugeLG(TLG* aL)
{
	TLG aux;
	while(*aL){
		aux = *aL;
		*aL = aux->urm;
		free(aux->info);
		free(aux);
	}
	free(*aL);
}