/* MIHAILA Cosmin-Constantin - 315CB */

#include "page.h"
#include "TCoada.h"

// Functie pentru initalizarea unei paginii cu un URL dat
TPage* InitPage(char* URL)
{
	TPage* newPage = (TPage*)malloc(sizeof(TPage));
	if(!newPage){
		printf("ERROR");
		exit(1);
	}

	newPage->url = (char*)malloc(30 * sizeof(char));
	if(!newPage->url){
		free(newPage);
		printf("ERROR");
		exit(1);
	}

	strcpy(newPage->url,URL); // Copiem URL-ul la noua pagina
	newPage->resources = get_page_resources(URL,&newPage->num_res);

	return newPage;
}

// Functie pentru afisarea resurselor de pe o pagina
void list_dl(TPage* page,char* out_file)
{
	int i;
	FILE* out_dl;
	out_dl = fopen(out_file,"at");
	if(!out_dl){
		printf("ERROR");
		exit(1);
	}
	for(i = 0; i < page->num_res; i++)
	{
		fprintf(out_dl,"[%d - \"%s\" : %ld]\n",i,
			page->resources[i].name,page->resources[i].dimension);
	}
	fclose(out_dl);
}

// Functie pentru afisarea descarcarilor (in curs si cele compelte)
void downloads(AQ priority,char* fileName,TLG complete)
{	
	FILE* out_file_down;
	out_file_down = fopen(fileName,"at");
	if(!out_file_down){
		printf("ERROR");
		exit(1);
	}

	AQ auxQ = (AQ)malloc(sizeof(TCoada));
	if(!auxQ){
		printf("ERROR");
		exit(1);
	}

	auxQ->dime = sizeof(Resource);
	auxQ->ic = NULL;
	auxQ->sc = NULL;

	// Parcurgem coada de prioritati
	while(priority->ic != NULL){	
		Resource* auxResource = (Resource*)malloc(sizeof(Resource));
		if(!auxResource){
			printf("ERROR");
			exit(1);
		}
		ExtrQ(priority,auxResource); // Scoatem fiecare element
		long int total;
		long int remaining;
		total = auxResource->dimension;
		remaining = auxResource->dimension - auxResource->currently_downloaded;
		fprintf(out_file_down,"[\"%s\" : %ld/%ld]\n",auxResource->name,
				remaining,total);

		//Introducem in coada auxiliara elementul scos
		IntrQ(auxQ,auxResource);
	}

	// Reintroducem elementele in coada priority din coada auxiliara
	while(auxQ->ic != NULL){
		Resource* auxResource2 = (Resource*)malloc(sizeof(Resource));
		if(!auxResource2){
			printf("ERROR");
			exit(1);
		}
		ExtrQ(auxQ,auxResource2);
		IntrQ(priority,auxResource2);
	}

	// Parcurgem lista de descarcari complete si afisam fiecar element
	TLG complAux = complete;
	while(complAux != NULL){
		if(((Resource*)complAux->info)->name != NULL)
			fprintf(out_file_down,"[\"%s\" : completed]\n",
					((Resource*)complAux->info)->name);
		complAux = complAux->urm;
	}

	// Eliberam memoria din coada auxiliara si inchidem fisierul
	DistrQ(auxQ);
	free(auxQ);
	fclose(out_file_down);
}

// Functie pentru simularea trecerii timpului
void wait(AQ priority, int bandwith, TLG complete)
{	
	AQ auxQ = (AQ)malloc(sizeof(TCoada));
	if(!auxQ){
		printf("ERROR");
		exit(1);
	}

	auxQ->dime = sizeof(Resource);
	auxQ->ic = NULL;
	auxQ->sc = NULL;
	int check = 1;
	
	int toDownload;
	int rem = 0;

	// Parcurgem toata coada priority
	while(priority->ic != NULL){
		Resource* auxResource = (Resource*)malloc(sizeof(Resource));
		if(!auxResource){
			printf("ERROR");
			exit(1);
		}

		ExtrQ(priority,auxResource); // Extragem fiecare elemnt

		// Calculam dimensinea pe care o putem descarca in secunda respectiva
		toDownload = bandwith - rem;

		// Veriifcam daca dimensiunea disponibila pentru descarcat
		// este mai mica decat dimensiunea ramasa de descarcat
		if(auxResource->currently_downloaded + toDownload < 
			auxResource->dimension){

			// Verificam daca elementul extras este primul din coada
			if(check){

				// Daca este primul element, ii crestem dimensiunea
				// descarcata
				auxResource->currently_downloaded = 
					auxResource->currently_downloaded + toDownload;
				check = 0;
			}

			// Introducem elementul extras in coada auxQ 
			IntrQ(auxQ,auxResource);
			rem = 0;
		}

		// Cazul in care s-a descarcat complet
		else{

			// Calculam dimensiunea ramasa de la descarcarea resursei
			unsigned int remainingDownload = auxResource->currently_downloaded
			 							+ toDownload - auxResource->dimension;

			// Inseram resursa descarcata complet in lista complete
			InsLG(&complete,auxResource,sizeof(Resource));

			// Calculam cata dimensiune mai avem disponibila pe bandiwth
			rem = bandwith - remainingDownload;
		}
	}

	// Reintroducem resursele din coada auxiliara in priority
	while(auxQ->ic != NULL){
		Resource* auxResource2 = (Resource*)malloc(sizeof(Resource));
		if(!auxResource2){
			printf("ERROR");
			exit(1);
		}
		ExtrQ(auxQ,auxResource2);
		IntrQ(priority,auxResource2);
	}

	DistrQ(auxQ);
	free(auxQ);
}

