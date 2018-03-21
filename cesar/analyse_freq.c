#include<stdio.h>
#include<stdlib.h>
#include"analyse_freq.h"



// remarque : le message ne doit contenir que des minuscules et pas de poncutation 
// cette fonction renvoie les caractères dans l'ordre décroissant les plus fréquent dans un fichier texte

void analyse_freq(char *fichier, int* caractereHF){
        char mots[NB_MOTS_MAX][NB_LETTRES_MAX];
        FILE *f;
        f = fopen(fichier,"r");
        int i;
        int nb_mots = 0;
        // scanne le message (fichier texte) pour les mettres dans la RAM (via mots[][])(fonction à créer séparément ??)
        while (i!=EOF){
                i = fscanf(f,"%s",mots[nb_mots]);
                nb_mots++;
        }
        fclose(f);
        // tableau des occurences : indice 0 pour "a", 1 pour "b", ... 
        // initialisation du tableau 
        int occurences[26];
        for (i=0;i<26;i++){
                occurences[i]=0;       
        }
        // on parcourt le message et on note les occurences
        int c;
        for (c=0;c<nb_mots;c++){
                char *s = mots[c];
                while (*s != '\0'){
                        occurences[((*s)-97)]++;
                        s++;
                }
        }
        // permet d'afficher le tableau occurences (à utiliser pour checker ou debugger)
        /*
        int l;
        for(l=0;l<26;l++){
                printf("%c : %d\n",l+97,occurences[l]);
        }
        */
        // creation du tableau contenant les 5 caractères les plus présents (haute fréquence HF)
        for(i=0;i<5;i++){
                caractereHF[i]=-1;
        }
        //on parcourt 5 fois le tableau d'occurences pour en retirer les 5 lettres les plus récurrentes
        int p =0;
        int j;
        for(j=0;j<5;j++){
                int n;
                int max = 0;
                int indice_max = 0;
                for(n=0;n<26;n++){
                        if (occurences[n] > max){
                                // il faut penser à tester si la lettre n'a pas déjà été prise en compte dans caractereHF
                                int bool=1;
                                int c;
                                for (c=0;c<5;c++){
                                        if (n==caractereHF[c]){
                                                bool=0;
                                        } 
                                } 
                                if (bool==1){
                                        indice_max = n;
                                        max = occurences[n];
                                }                                
                        }
                } 
                caractereHF[j]=indice_max;       
        }
        caractereHF[j+1]="\0";
        /* 
        printf("Les lettres les plus récurrentes sont (dans l'ordre décroissant) : %c,%c,%c,%c,%c\n",caractereHF[0]+97,caractereHF[1]+97,caractereHF[2]+97,caractereHF[3]+97,caractereHF[4]+97);
	printf("Les clés possibles : %u\n",caractereHF[0] - 4);
	return caractereHF;
	*/
        // permet d'afficher le tableau caractereHF (à utiliser pour debugger ou checker)
        
        
        
                       
}

