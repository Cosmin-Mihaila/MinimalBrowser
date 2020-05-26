/* MIHAILA Cosmin-Constantin - 315CB */

#include "TCoada.h"
#include "utils.h"

// Functie pentru introducerea unui element intr-o coada
int IntrQ(void* a, void* ae)
{
	ACel aux = (ACel)malloc(sizeof(TCel));
	if(!aux){
		printf("ERROR");
		exit(1);
	}

	aux->info = ae;
	aux->urm = NULL;
	if(((TCoada*)a)->ic == NULL && ((TCoada*)a)->sc == NULL){
		((TCoada*)a)->ic = aux;
		((TCoada*)a)->sc = aux;
	}
	else{
		((TCoada*)a)->sc->urm = aux;
		((TCoada*)a)->sc = aux;
	}
	return 1;
}

// Functie pentru extragerea unui element din coada
int ExtrQ(void* a, void* ae)
{	
	int check = 0;
	if(((TCoada*)a)->ic == ((TCoada*)a)->sc){
		check = 1;
	}
	ACel aux = ((TCoada*)a)->ic;
	((TCoada*)a)->ic = aux->urm;
	memcpy(ae,aux->info,((TCoada*)a)->dime);
	free(aux->info);
	free(aux);
	if(check){
		((TCoada*)a)->ic = NULL;
		((TCoada*)a)->sc = NULL;
	}
	return 1;
}

// Functie pentru adaugarea unui download in coada cu prioritati
int IntrQPriority(void* a, void* ae)
{
	ACel aux = (ACel)malloc(sizeof(TCel));
	if(!aux){
		printf("ERROR");
		exit(1);
	}

	Resource* newRes = (Resource*)malloc(sizeof(Resource));
	memcpy(newRes,ae,sizeof(Resource));

	aux->info = newRes;
	aux->urm = NULL;
	if(((TCoada*)a)->ic == NULL && ((TCoada*)a)->sc == NULL){
		((TCoada*)a)->ic = aux;
		((TCoada*)a)->sc = aux;
	}
	else{
		ACel p;
		p = ((TCoada*)a)->ic;
		int auxDimension;
		int qDimension;
		// Caculam dimensiunea de downloadat a resursei pe care o adaugam
		auxDimension = ((Resource*)aux->info)->dimension -
					((Resource*)aux->info)->currently_downloaded;
		// Calculam dimensiunea de downloadat a primei resurse din coada
		qDimension = ((Resource*)p->info)->dimension -
					((Resource*)p->info)->currently_downloaded;
		// Verificam daca trebuie sa adaugam noua resursa la inceputul cozii
		if( auxDimension < qDimension){
			aux->urm = p;
			((TCoada*)a)->ic = aux;
		}
		else{
			if(p->urm != NULL){
				qDimension = ((Resource*)p->urm->info)->dimension -
							((Resource*)p->urm->info)->currently_downloaded;
			}
			else{
				qDimension = 0;
			}

			// Parcurgem coada pana gasim unde trebuie introdusa noua resursa
			while(auxDimension > qDimension && p->urm!= NULL){
				p = p->urm;

				// Calculam dimensiunea de downloadat a resursei urmatoare
				if(p->urm != NULL){
					qDimension = ((Resource*)p->urm->info)->dimension -
							((Resource*)p->urm->info)->currently_downloaded;
				}
			}

			// Facem legaturile pentru a adauga noua resursa in coada
			aux->urm = p->urm;
			p->urm = aux;
		}

		if(aux->urm == NULL){
			((TCoada*)a)->sc = aux;
		}
	}
	return 1;
}

// Funcie pentru eliberarea memoriei unei cozi
void DistrQ(void* a)
{
	ACel l = ((TCoada*)a)->ic;
	ACel aux = l;
	while(l != NULL){
		aux = l;
		l = l->urm;
		free(aux->info);
		free(aux);
	}
	((TCoada*)a)->ic = NULL;
	((TCoada*)a)->sc = NULL;
}
