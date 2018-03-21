#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"chiffre.h"


void chiffre(char* text, int key, char* new_file, int court){
	key=key%26;
	//Il n'y a que 26 clés possibles.
	
	//Création du nouveau fichier dans le sous-dossier textes_crees.
	FILE * pFile;
	FILE * wFile;
	pFile = fopen (text,"r");
	wFile = fopen (new_file,"w");
	//On ouvre le fichier à chiffrer et on crée le nouveau fichier.
   
	char chaine_lue [100];
	if (!pFile){ 
	//Si le fichier présenté n'existe pas ou n'est pas bien orthographié on arrête la fonction.
		printf ("\aERROR: Unable to open file\n"); exit(EXIT_FAILURE); 
	}
	
	int j;
	int ja=0;
	int a;
	int i = 0;
	while (1) {
	//Boucle s'occupant du chiffrement.
		j=fscanf(pFile,"%s", &chaine_lue[0]);
		if(j==EOF||(court==1&&i==10)) {
		//Si le mode court est activé (court = 1) alors on ne chiffre que les 10 premiers mot du texte
		//On sort de la boucle si on arrive à la fin du fichier à chiffrer.
			// printf("--Chiffrement de chiffre terminé!--\n");
			break;
		}
		while(ja<strlen(chaine_lue)){
		//Le chiffrement se fait lettre par lettre. On remplace la lettre par son code ascii et à ce code, on lui ajoute +key.
			a=chaine_lue[ja];
			if(a+key<123&&a+key>96){
				a+=key;
			}
			else if(a+key<97){
				a=123-(97-(a+key));	
			}
			else {
				a=a+key-123;
				a=97+a;
			}
			chaine_lue[ja]=a;
			ja++;
		}
		fprintf(wFile, "%s ", chaine_lue);
		//Le mot est enregistré das le fichier crée.
		ja=0;
		i++;
	} 
	fclose(pFile);
	fclose(wFile);
	//On ferme les deux fichiers.
}
