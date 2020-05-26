/* MIHAILA Cosmin-Constantin - 315CB */

#include "tab.h"
#include "TLista.h"
#include "TCoada.h"

// Functie pentru accesarea unei pagini
void GoTo(TTab* tab,char* URL,char* out,AQ coadaHistory)
{	

	TPage* newPage = InitPage(URL);

	if(tab->current_page){
		if(!Push((tab->back_stack),tab->current_page)){
			printf("ERROR1");
			exit(1);
		}
	}
	tab->current_page = newPage;

	char* urlsave = NULL;
	urlsave = (char*)malloc(25 * sizeof(char));
	if(!urlsave){
		printf("ERROR");
		exit(1);
	}
	strcpy(urlsave,URL);

	// Introducem in coada de history url-ul paginii accesate
	IntrQ(coadaHistory,urlsave);

}

// Functie pentru initalizarea unui tab
TTab* newTab()
{
	TTab* newTabs = (TTab*)malloc(sizeof(TTab));
	if(!newTabs){
		printf("ERROR1");
		exit(1);
	}

	newTabs->current_page = NULL;
	newTabs->back_stack = InitS(sizeof(TPage));
	newTabs->forward_stack = InitS(sizeof(TPage));

	return newTabs;
}

// Functie pentru creerea unei celule pentru lista de taburi
void newTabCell(TLG tabs)
{	
	TTab* newTabs = newTab();
	TLG p = tabs;
	if(!InsLG(&p,newTabs,sizeof(TTab))){
		printf("ERROR1");
		exit(1);
	}
}

// Functie pentru stergerea unui tab
TLG delTab(TLG tabs)
{
	TLG aux = tabs;
	TLG pre = aux;
	while(aux->urm != NULL)
	{	pre = aux;
		aux = aux->urm; // parcurgem taburile pana la ultimul
	}
	pre->urm = NULL;
	if(pre != aux){
	if(((TTab*)aux->info)->current_page != NULL){
			free(((TTab*)aux->info)->current_page->url);
			if(((TTab*)aux->info)->current_page->resources != NULL)
				free(((TTab*)aux->info)->current_page->resources);
			free(((TTab*)aux->info)->current_page);
	}}
	DistrS(((TTab*)aux->info)->back_stack);
	DistrS(((TTab*)aux->info)->forward_stack);
	free(((TTab*)aux->info)->forward_stack);
	free(((TTab*)aux->info)->back_stack);
	free(aux->info);
	free(aux);

	return pre;
}

void back(TCelulaG* current_tab)
{
	TPage* aux =(TPage*)malloc(sizeof(TPage));
	if(!aux){
		printf("ERROR");
		exit(1);
	}
	
	// Scoatem pagina din stiva back_stack
	if ( Pop(((TTab*)current_tab->info)->back_stack,aux) == 0){
		printf("can’t go back, no pages in stack");
	}

	// Introducem pagina curenta in stiva forward_stack
	if( Push(((TTab*)current_tab->info)->forward_stack,
		((TTab*)current_tab->info)->current_page) == 0){
		printf("ERROR");
	}
	
	// Punem pagina curenta ca fiind cea scoasa anterior din stiva
	((TTab*)current_tab->info)->current_page = aux;
	
}

void forward(TCelulaG* current_tab)
{
	TPage* aux = (TPage*)malloc(sizeof(TPage));
	if(!aux){
		printf("ERROR");
		exit(1);
	}
	
	// Scoatem pagian din stiva forward_stack
	if( Pop(((TTab*)current_tab->info)->forward_stack,aux) == 0){
		printf("can’t go forward, no pages in stack");
	}

	// Introducem pagina in stiva back_stack
	if( Push(((TTab*)current_tab->info)->back_stack,
		((TTab*)current_tab->info)->current_page) == 0){
		printf("ERROR");
	}
	
	// Punem pagina curenta ca fiind cea scoasa anterior din stiva
	((TTab*)current_tab->info)->current_page = aux;
}

// Functie pentru stergerea primelor nr url-uri din istoric
void delHistory(AQ coada, int nr)
{
	int i = 0;
	char* aux = (char*)malloc(25 * sizeof(char));
	if(!aux){
		printf("ERROR");
		exit(1);
	}
	while(i < nr && coada->ic != NULL){
		ExtrQ(coada,aux); // Extragem pe rand fiecare url
		i++;
	}
	if(!nr){ // In cazul in care nr este 0, stergem tot istoricul
		while(coada->ic != NULL){
			ExtrQ(coada,aux);
		}
	}
	free(aux);
}

