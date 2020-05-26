/* MIHAILA Cosmin-Constantin - 315CB */

#include "TStiva.h"
#include "page.h"
void* InitS(size_t d)
{
	ASt s;
	s = (ASt)malloc(sizeof(TStiva));
	if(!s){
		printf("ERROR");
		exit(1);
	}

	s->dime = d;
	s->vf = NULL;
	return (void*)s;
}

// Functie pentru introducerea unui element in stiva
int Push(void* a, void* ae)
{
	ACelSt aux = (ACelSt)malloc(sizeof(TCelSt));
	if(!aux){
		printf("ERROR");
		exit(1);
	}

	aux->info = malloc(((TStiva*)a)->dime);
	if(!aux->info){
		free(aux);
		printf("ERROR");
		exit(1);
	}

	memcpy(aux->info,ae,((TStiva*)a)->dime);
	free(ae);
	aux->urm = ((TStiva*)a)->vf;
	((TStiva*)a)->vf = aux;

	return 1;
}

// Functie pentru scoaterea unui elemnt din stiva
int Pop(void* s,void* ae)
{
	if (((TStiva*)s)->vf == NULL){
		return 0;
	}
	memcpy(ae,((TStiva*)s)->vf->info, ((TStiva*)s)->dime);

	ACelSt aux = ((TStiva*)s)->vf;
	((TStiva*)s)->vf = aux->urm;
	free(aux->info);
	free(aux);
	return 1;
}

// Functie pentru eliberarea memoriei unei stive
void DistrS(void* a)
{
	ACelSt l = ((TStiva*)a)->vf;
	ACelSt aux = l;
	while(l != NULL){
		aux = l;
		l = l->urm;
		free(((TPage*)aux->info)->url);
		free(((TPage*)aux->info)->resources);
		free((TPage*)aux->info);
		free(aux);
	}
	((TStiva*)a)->vf = NULL;
}



