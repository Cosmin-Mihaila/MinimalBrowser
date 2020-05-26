/* MIHAILA Cosmin-Constantin - 315CB */

#include "TStiva.h"
#include "tab.h"
#include "TLista.h"
#include "utils.h"
#include "page.h"
#include "TCoada.h"
#define MAX_CMD 30

int main(int n, char* argv[])
{	
	// Deschidem cele 2 fisiere, de citire si scriere
	FILE* in_file;
	in_file = fopen(argv[1], "rt");
	if(!in_file){
		printf("ERROR");
		exit(1);
	}

	FILE* out_file;
	out_file = fopen(argv[2], "at");
	if(!out_file){
		printf("ERROR");
		exit(1);
	}
	int bandwith = 1024;
	char* command = (char*)malloc(MAX_CMD * sizeof(char));
	if(!command){
		printf("ERROR");
		exit(1);
	}

	// Lista generica de taburi
	TLG tabs = (TLG)malloc(sizeof(TCelulaG));
	if(!tabs){
		printf("ERROR");
		exit(1);
	}
	tabs->urm = NULL;
	tabs->pre = NULL;
	tabs->info = NULL;

	// Lista generica de resurse complet descarcate
	TLG complete = (TLG)malloc(sizeof(TCelulaG));
	if(!complete){
		printf("ERROR");
		exit(1);
	}

	complete->urm = NULL;
	complete->pre = NULL;
	complete->info = NULL;

	// Creem primul tab gol
	TTab* newTabs = newTab();
	tabs->info = newTabs;
	TCelulaG* current_tab = tabs;

	// Coada istoricului paginilor parcurse
	AQ coadaHistory = (AQ)malloc(sizeof(TCoada));
	if(!coadaHistory){
		printf("ERROR");
		exit(1);
	}
	coadaHistory->dime = 25;
	coadaHistory->ic = NULL;
	coadaHistory->sc = NULL;

	// Coada de prioritati pentru descarcare
	AQ priority = (AQ)malloc(sizeof(TCoada));
	if(!priority){
		printf("ERROR");
		exit(1);
	}
	priority->dime = sizeof(Resource);
	priority->ic = NULL;
	priority->sc = NULL;

	while(!feof(in_file)) // Citim pana la terminarea fisierului
	{
		fscanf(in_file,"%s",command);
		if(strcmp(command,"set_band") == 0){
			fscanf(in_file,"%d",&bandwith); // Setam bandwith-ul
		}
		else if(strcmp(command,"newtab") == 0){
			newTabCell(tabs); // Creem noul tab
			while(current_tab->urm != NULL){ // Punem nou tab ca fiind curent
				current_tab = current_tab->urm; 
			}
		}
		else if(strcmp(command,"goto") == 0){
			wait(priority,bandwith,complete); 
			char* url = NULL;
			url = (char*)malloc(MAX_CMD);
			if(!url){
				printf("ERROR");
				exit(1);
			}
			fscanf(in_file,"%s",url);
			GoTo((TTab*)current_tab->info,url,argv[2],coadaHistory);
			free(url);
		}
		else if(strcmp(command,"history") == 0){
				
				AQ auxQ = (AQ)malloc(sizeof(TCoada));
				if(!auxQ){
					printf("ERROR");
					exit(1);
				}
				auxQ->dime = 25;
				auxQ->ic = NULL;
				auxQ->sc = NULL;
				while(coadaHistory->ic != NULL){	
					char* auxString = (char*)malloc(25 * sizeof(char));
					if(!auxString){
						printf("ERROR");
						exit(1);
					}
					ExtrQ(coadaHistory,auxString);
					fprintf(out_file,"%s\n",auxString);
					IntrQ(auxQ,auxString);
				}

				while(auxQ->ic != NULL){
					char* auxString2 = (char*)malloc(25 * sizeof(char));
					if(!auxString2){
						printf("ERROR");
						exit(1);
					}
					ExtrQ(auxQ,auxString2);
					IntrQ(coadaHistory,auxString2);
				}
				free(auxQ);
			
		}
		else if(strcmp(command,"change_tab") == 0){
			int tab_index;
			fscanf(in_file,"%d",&tab_index);
			current_tab = change_tab(tabs,tab_index);
		}
		else if(strcmp(command,"print_open_tabs") == 0){
			fclose(out_file);
			print_open_tabs(tabs,argv[2]);
			out_file = fopen(argv[2],"at");
		}
		else if(strcmp(command,"back") == 0){
			back(current_tab);
		}
		else if(strcmp(command,"forward") == 0){
			forward(current_tab);
		}
		else if(strcmp(command,"deltab") == 0){
			if(current_tab->urm == NULL){
				current_tab = delTab(tabs);
			}
			else{
				delTab(tabs);
			}
		}
		else if(strcmp(command,"del_history") == 0){
			int ax;
			fscanf(in_file,"%d",&ax);
			delHistory(coadaHistory,ax);
		}
		else if(strcmp(command,"list_dl") == 0){
			fclose(out_file);
			if(((TTab*)current_tab->info)->current_page != NULL)
				list_dl(((TTab*)current_tab->info)->current_page,argv[2]);
			out_file = fopen(argv[2],"at");
		}
		else if(strcmp(command,"download") == 0){
			int dI;
			fscanf(in_file,"%d",&dI);
			if(((TTab*)current_tab->info)->current_page != NULL)
				IntrQPriority(priority,
					&((TTab*)current_tab->info)->current_page->resources[dI]);
		}
		else if(strcmp(command,"downloads") == 0){
			fclose(out_file);
			downloads(priority,argv[2],complete);
			out_file = fopen(argv[2],"at");
		}
		else if(strcmp(command,"wait") == 0){
			int additionalSeconds;
			fscanf(in_file,"%d",&additionalSeconds);
			int waitIndex;
			for(waitIndex = 0; waitIndex < additionalSeconds; waitIndex++){
				wait(priority,bandwith,complete);
			}
		}

		strcpy(command,"");
		
	}
	fclose(in_file);
	fclose(out_file);
	DistrugeLGTabs(&tabs);
	DistrQ(coadaHistory);
	DistrQ(priority);
	DistrugeLG(&complete);
	free(command);
	free(coadaHistory);
	free(priority);

}