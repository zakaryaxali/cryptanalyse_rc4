#include<stdio.h>
#include<stdlib.h>
#include"check_key.h"


// le message decrypté se trouve normalement dans le fichier "fichier_temporaire.txt"

void cryptanalyse_no_freq_no_ram(char* text){
        int cle = 0;
        int bool=0;
        while (bool==0 && cle<26) {
                cle++;
                bool = check_key(text,cle);
		// printf("Dechiffrage avec la cle : %d  \n", cle);
        }
        if (bool==0){
                printf("Pas réussi à déchiffrer.\n");                
        } else {
                printf("Le message a été crypté avec la clé : %d\n",cle);        
        }
}

void cryptanalyse_no_freq_ram(char* text, char** dico, int** indices){
        int cle = 0;
        int bool=0;
        while (bool==0 && cle<26) {
                cle++;
                bool = check_key(text,cle);
		// printf("Dechiffrage avec la cle : %d  \n", cle);
        }
        if (bool==0){
                printf("Pas réussi à déchiffrer.\n");                
        } else {
                printf("Le message a été crypté avec la clé : %d\n",cle);        
        }
}
