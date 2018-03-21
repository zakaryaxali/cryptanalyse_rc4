#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"lecture.h"
#include"chiffre.h"
#include"dico.h"
#include"compare.h"
#include"compare_ram.h"
#include"check.h"
#include"check_key.h"
#include"cryptanalyse_no_freq.h"
#include"cryptanalyse_freq.h"
#include"delAccent.h"
#include <time.h>
#include <sys/time.h>
#include<wchar.h>

#define NB_MOT 327014

 // Déclarer la fonction  computeTiming
 
void computeTiming( struct timeval start, struct timeval end, float* timeExp ) 
{
    *timeExp = (float)1000.0 * (end.tv_sec - start.tv_sec);
    if (end.tv_usec < start.tv_usec) {
    *timeExp -= 1000.0;
*timeExp += (double)(1000000.0 + end.tv_usec - start.tv_usec)/1000.0;
  } 
    else
*timeExp += (double)(end.tv_usec - start.tv_usec)/1000.0;
} 



int main (int argc, char *argv[]){

        ///// cette partie consiste à charger les dictionnaires dans la RAM 
/* 
                Le nombre de mots et le nombre de lettres max par mot ont été calculés une seule fois en 
        adaptant le programme ci-dessous. Nb de mots total : 327014. Nb de lettres max par mot : 25.
        
                La Ram contiendra deux tableaux à deux entrées.
        
                Le premier tableau est le tableau "dico". Il contient tous les mots. Le premier indice 
        permet d'accéder à chaque mot (il varie de 0 à 327014), le deuxième indice permet d'accéder aux lettres du mot.
        
                Le deuxième tableau est le tableau "indices". Il permet de se repérer dans le tableau dico afin de savoir
        où chercher. 
        Le premier indice correspond à la taille du mot (0 pour "4-6", 1 pour "7-10", 2 pour "10-").
        Le deuxième indice correspond à la première lettre du mot (0 pour "a", 1 pour "b", ....).
        Ainsi tous les mots de 7-9 lettres commençant par la lettre "c" sont à chercher entre les indices "indices[1][2]" (inclus)
        et "indices[1][3]" (exclus).

        
*/  
        /// PROGRAMME
        /*
        char **dico;
        dico = malloc(NB_MOT*sizeof(char*));
        int c1;
        for(c1=0;c1<NB_MOT;c1++){
                dico[c1]=malloc(26*sizeof(char));
        }
        int **indices;
        indices = malloc(3*sizeof(int*)); 
        int c2;
        for(c2=0;c2<23;c2++){
                indices[c2] = malloc(26*sizeof(int));
        }
        int i=0;
        int indice = 0;
        char fichier1[20];
        strcpy(fichier1,"dicos/");      
        for (i=0;i<3;i++){
                int j=0;
                char fichier3[20];
                if (i==0){
                        strcpy(fichier3,"4-6.txt\0");
                } else {
                        if (i==1) {
                                strcpy(fichier3,"7-10.txt\0");
                        } else {
                                strcpy(fichier3,"10-.txt\0");
                        }
                }                                   
                for (j=0;j<26;j++){
                        char fichier2[2];
                        fichier2[0]=j+97;                      
                        fichier2[1]='\0';                     
                        strcat(fichier2,fichier3);
                        strcat(fichier1,fichier2);                                                                                      
                        FILE *f;
                        f = fopen(fichier1,"r");
                        int k=0;                        
                        char boite[30];
                        indices[i][j] = indice;  
                        while (k!=EOF){
                                k = fscanf(f,"%s",boite);
                                strcpy(dico[indice],boite);                              
                                indice++;
                        }                                                                                    
                        fclose(f);                                                 
                        strcpy(fichier1,"dicos/");                                           
                }            
        }

        
*/
        /// FIN PROGRAMME RAM   
               

/*

	printf ("argc = %d\n", argc);
	int key = atoi(argv[1]);
	printf ("key = %d\n", key);
	char text[]="test.txt";
*/
        
	float resultat[26];	
		
	int a;
	for (a=0;a<26;a++){
		chiffre("fichiertexte.txt",a,"test1.txt",0);	
		float timeExp; 
		struct timeval start, end;
		gettimeofday (&start, NULL);
		//programme à calculer
		
		cryptanalyse_freq_no_ram("test1.txt");
		
		// fin calcul
		gettimeofday (&end, NULL);
		computeTiming(start, end, &timeExp );
		resultat[a] = timeExp;
	}
	int i;
	for (i=0;i<26;i++){
		printf("%f\n",resultat[i]);
	}
	

	//cryptanalyse_no_freq_ram("test-c.txt", dico, indices);
	//cryptanalyse_no_freq_no_ram("test-c.txt");


	

	
	 

	 


	 
	return 0;
	


}
