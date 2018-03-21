#include<stdio.h>
#include<stdlib.h>


void lecture(char* text){
//Fonction qui lit simplement le texte qui lui ait soumis.
	FILE* pFile = fopen (text, "r");
	
	char chaine_lue [100];
	if (!pFile){ 
	//Si le fichier présenté n'existe pas ou n'est pas bien orthographié on arrête la fonction.
		printf ("\aERROR: Unable to open file\n"); exit(EXIT_FAILURE); 
	}
   
	int j;
	while (1) {
	//Boucle qui renvoie chaque mot du fichier.
		j=fscanf(pFile,"%s", chaine_lue);
		if(j==EOF) {
		//Si on arrive à la fin du fichier, on sort de la boucle.
			printf("\nEnd of Lecture!\n");
			break;
		}
		printf ("%s ", chaine_lue);
	} 
	fclose(pFile);
	//Fermeture du fichier.
	printf("\n");
}
