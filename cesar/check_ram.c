#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"compare_ram.h"
//On utilise la fonction compare dans cette fonction.


int check_ram(char* text, char** dico, int** indices){
//Fonction qui vérifie pour un fichier texte donné, si tous les mots qu'il contient appartiennent au dictionnaire.
	FILE* pFile = fopen (text, "r");
	char chaine_lue [100];
	int i=0;
	if (!pFile){ 
	//Si le fichier présenté n'existe pas ou n'est pas bien orthographié on arrête la fonction.
		printf ("\aERROR: Unable to open file \n"); exit(EXIT_FAILURE); 
	}
   
	int j;
	while (1) {
		j=fscanf(pFile,"%s", chaine_lue);
		if(j==EOF||i==4) {
		//Si on arrive à la fin du fichier sans accroc, c'est que tous les mots font partis du dictionnaire.
			// printf("\nTous les mots sont dans le dictionnaires!\n");
			return 1;
			break;
		}
		if(strlen(chaine_lue)>3){
			i++;
		}
		if(strlen(chaine_lue)>3&&compare_ram(chaine_lue, dico, indices)!=1){
		//Si un seul des mots ne fait pas parti du dictionnaire, c'est que nous n'afvons pas affaire à la bonne clé (méthode très radicale).
			// printf("Mauvaise clé!\n");
			return 0;
			break;
		}
	} 
	fclose(pFile);
	//Fermeture du fichier.
	printf("\n");
}
