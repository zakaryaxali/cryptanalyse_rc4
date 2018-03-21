#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define NB_MOT 327014

//Fonction qui prend un mot et recherche son existence dans le dictionnaire (le mot doit contenir au moins 4 lettres).
// retourne 1 si le mot appartient au dico, 0 sinon.

// ATTENTION : traitez le cas "premierLettre"==z

int compare_ram(char* mot,char** dico,int** indices){
	int longueur_mot = strlen(mot);   
	int indiceNbLettre[30] = {-1,-1,-1,-1,0,0,0,1,1,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2};
	int indiceNb = indiceNbLettre[longueur_mot];
	int premiereLettre = mot[0] - 97; 
	int resultat = 0;	
	if(indiceNb != -1){		
		int compteur = indices[indiceNb][premiereLettre];
		int compteurFIN;
		// conditions permettant de traiter le cas particulier où premiereLettre == z (le cran est suivant est plus compliqué à obtenir)
		if (premiereLettre==25){
				if (indiceNb==2){
					compteurFIN = NB_MOT;
				} else {
					compteurFIN=indices[indiceNb+1][0];
				}			
		} else {
			compteurFIN = indices[indiceNb][premiereLettre+1];
		}		
		while ((resultat==0) && (compteur < compteurFIN)) {		
			if(strcmp(dico[compteur],mot)==0) {
				resultat=1;			
			} else {
				compteur++;
			}
		}		 		
	}
	return resultat;
	
}
