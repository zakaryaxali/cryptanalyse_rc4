#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void dico(char* text){
//Fonction qui "découpe" un dictionnnaire (format txt) en plusieurs sous-dictionnaires.
	char lettre[2]; 
	int a;
	char keytext[20];
	char keytext1[20];
	char keytext2[20];
	char voie[]="dicos/";
	FILE * pFile;
	FILE * wFile;
	FILE * wFile1;
	FILE * wFile2;
	//On crée 3 sous-dictionnaires pour chaque lettre de l'alphabet (décision arbitraire). 
	//Un sous-dictionnaire pour les mots entre 4 et 6 lettres.
	//Un sous-dictionnaire pour les mots entre 7 et 10 lettres. 
	//Un sous-dictionnaire pour les mots de plus de 10 lettres.
	char chaine_lue [100];
	if (!pFile){ 
	//Si le fichier présenté n'existe pas ou n'est pas bien orthographié on arrête la fonction.
		printf ("\aERROR: Unable to open file\n"); exit(EXIT_FAILURE); 
	}
   
	int j;
	for(a=97;a<123;a++){
	//Pour chaque lettre de l'alphabet on crée les sous-dictionnaires.
		pFile = fopen (text,"r");
		lettre[0]=a;
		lettre[1]='\0';
		strcpy(keytext, voie);
		strcpy(keytext1, voie);
		strcpy(keytext2, voie);
		strcat(keytext,lettre);
		strcat(keytext,"4-6.txt");
		strcat(keytext1,lettre);
		strcat(keytext1,"7-10.txt");
		strcat(keytext2,lettre);
		strcat(keytext2,"10-.txt");
		wFile = fopen (keytext,"w");
		wFile1 = fopen (keytext1,"w");
		wFile2 = fopen (keytext2,"w");
		while (1) {
		//
			j=fscanf(pFile,"%s", &chaine_lue[0]);
			if(j==EOF) {
			//On ferme tous les fichiers lorsqu'on arrive à la fin du dictionnaire.
				printf("\n%s %s et %s ont ete cree!\n", keytext, keytext1, keytext2);
				fclose(wFile);
				fclose(wFile1);
				fclose(wFile2);
				fclose(pFile);
				break;
			}
			if(3<strlen(chaine_lue)&&7>strlen(chaine_lue)&&chaine_lue[0]==a){
				fprintf(wFile, "%s\n", chaine_lue);
			}
			else if(6<strlen(chaine_lue)&&11>strlen(chaine_lue)&&chaine_lue[0]==a){
				fprintf(wFile1, "%s\n", chaine_lue);
			}
			else if(10<strlen(chaine_lue)&&chaine_lue[0]==a){
				fprintf(wFile2, "%s\n", chaine_lue);
			}
		} 
		//On réinitialise les keytext qui donnent le nom du fichier.
		*keytext=0;
		*keytext1=0;
		*keytext2=0;
	}
}
