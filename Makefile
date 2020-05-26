
build:
	gcc -o tema2 -std=c11 -Wall -ggdb3 TLista.c TPage.c utils.c TTab.c TCoada.c TStiva.c main.c
clean:
	rm tema2
