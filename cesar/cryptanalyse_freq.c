#include<stdio.h>
#include<stdlib.h>
#include"check_ram.h"
#include "analyse_freq.h"


// le message decrypté se trouve normalement dans le fichier "fichier_temporaire2.txt"

void cryptanalyse_freq_ram(char* text, char** dico, int** indices){
    	int cle = 0;
    	int boolean=0;
	int a[6];
	int i=0;
	analyse_freq(text,a);
	char text1[]="fichier_temporaire2.txt";
	while(boolean==0&&i<5){
		cle=4-a[i];
		chiffre(text,cle,text1,1);
    		boolean = check_ram(text1, dico, indices); 
		i++;
		printf("  Essai %d\n", i);
	}
    	if (boolean==0){
        	printf("Pas réussi à déchiffrer.\n");                
    	} else {
        	printf("Le message a été crypté avec la clé : %d\n",-cle);        
    	}
	remove(text1);
}
void cryptanalyse_freq_no_ram(char* text){
    	int cle = 0;
    	int boolean=0;
	int a[6];
	int i=0;
	analyse_freq(text,a);
	char text1[]="fichier_temporaire2.txt";
	while(boolean==0&&i<5){
		cle=4-a[i];
		chiffre(text,cle,text1,1);
    		boolean = check(text1); 
		i++;
		printf("  Essai %d\n", i);
	}
    	if (boolean==0){
        	printf("Pas réussi à déchiffrer.\n");                
    	} else {
        	printf("Le message a été crypté avec la clé : %d\n",-cle);        
    	}
	remove(text1);
}


