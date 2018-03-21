#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"compare.h"
//On utilise la fonction compare dans cette fonction.


int check(char* text){
//Fonction qui vérifie pour un fichier texte donné, si les 5 premiers mots du texte de plus de 3 lettres appartiennent au dictionnaire.
	int i=0;
	FILE* pFile = fopen (text, "r");
	char chaine_lue [100];
	
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
			fclose(pFile);
			return 1;
		}
		if(strlen(chaine_lue)>3&&compare(chaine_lue)!=1){
		//Si un seul des mots ne fait pas parti du dictionnaire, c'est que nous n'avons pas affaire à la bonne clé (méthode très radicale).
			// printf("Mauvaise clé!\n");
			fclose(pFile);
			return 0;
		}
		i++;
	} 
}
