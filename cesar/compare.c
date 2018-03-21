#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int compare(char* text){
//Fonction qui prend un mot et recherche son existence dans le dictionnaire.
	if(strlen(text)>3){
	//Le mot doit contenir plius de 3 mots.
		int a;
		a=text[0];
		char lettre[30];
		FILE * pFile;
		char chaine_lue [100];
		int bon;
   		int i;
		int j;
		
		char voie[]="dicos/";
		char keytext[2];
		keytext[0]=a;
		keytext[1]='\0';
		strcpy(lettre,voie);
		strcat(lettre,keytext);
		//On cheche le mot par rapport à sa première lettre...
		
		//... et au nombre de lettres qu'il contient.
		if(3<strlen(text)&&7>strlen(text)){
			strcat(lettre,"4-6.txt");
		}
		else if(6<strlen(text)&&11>strlen(text)){
			strcat(lettre,"7-10.txt");
		}
		else if(10<strlen(text)){
			strcat(lettre,"10-.txt");
		}
		
		
		pFile = fopen (lettre,"r");
		//On ouvre le bon fichier où chercher.
		
		
		if (!pFile){ 
		//Si le fichier présenté n'existe pas ou n'est pas bien orthographié on arrête la fonction.
			printf ("\aERROR: Unable to open file\n"); exit(EXIT_FAILURE); 
		}
		
		while (1) {
			bon=1;
			j=fscanf(pFile,"%s", &chaine_lue[0]);
			if(j==EOF) {
			//Si on arrive à la fin du fichier, on sort de la boucle.
				// printf("Le mot %s a ete cherche dans le fichier %s mais n'a pas ete trouvé.\n", text, lettre);
				return 0;
				break;
			}
			if(strlen(chaine_lue)==strlen(text)){
			//On cherche les mots qui nt exactement la même longueur.
				for(i=0;i<strlen(text);i++){
				//Puis on compare les lettres une par une.
					if(chaine_lue[i]!=text[i]){
					//Si le mot n'est pas dans le dico.
						bon=0;
						break;
					}
				}
				if(bon==1){
				//Si le mot est bien dans le dico.
					// printf("Le mot \"%s\" a été cherché dans le fichier %s et il existe bien!\n", text, lettre);
					return 1;
					break;
				}
			}
		} 
		fclose(pFile);
		//Fermeture du fichier.
		*lettre=0;
	}
	else{
		// printf("\n%s est un mot trop court. Seuls les mots de plus de 3 lettres (strictement) peuvent etre comparés.\n", text);
	}
}
