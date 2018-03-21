#include<stdio.h>
#include "afficher_tableau.h"

#define TYPE "%d "


// cette fonction affiche au terminal un tableau de char. Il faut préciser la longueur en argument
// On peut préciser le type d'affichage ci-dessus (écrire "%d " pour affichage decimal et "%0x " pour affichage hexadecimal)

void afficher_tableau(int* tab, int longueur){
	int i;
	printf("( ");
	for (i=0;i<longueur;i++){
		printf(TYPE,tab[i]);
	}
	printf(")\n");	
}
