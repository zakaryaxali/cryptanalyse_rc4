#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <mpi.h>
#include <math.h>
#include "stream.h"
#include "afficher_tableau.h"
#include "statistiques.h"
#include "chiffrement.h"
#define NB_CLE 1000000000
#define DONNEES "resultatsLabo.txt"
#define NB_MSG 1100000000
#define NB_DECHIFFRE 10
#define PROBA "graphes/probabilitees.txt"
#define COMPARE_1 "resultatsCompare1.txt"
#define COMPARE_2 "resultatsCompare2.txt"



int main( int argc, char** argv) {
	
	

	//graphes(DONNEES);
	
// calcul du nombre de clés analysés
	
/*
	long int tab[32][256];
	extract_tab_file(tab,DONNEES);
	int i;
	long int total = 0;
	for(i=0;i<256;i++){
		total = total + tab[0][i];
	}
	printf("Nombre total de clés analysés : %ld\n",total);
*/
	
//Accumulation de clés et enregistrement dans un fichier à part
/*
	
	MPI_Init(&argc, &argv);	
	int myid;
	int num_pc = atoi(argv[1]);
	
	MPI_Comm_rank(MPI_COMM_WORLD, &myid); 
	
	mpi_analyse_rand(NB_CLE, num_pc);

	MPI_Finalize ();
	
*/


	
//Fusion des différents fichiers

/*
	int i = 0; 
	char fusion[10];
	long int tab[32][256];
	char numero[2];

	for(i=1; i<13; i++){
		
		int x;
		int y;
		for(x=0;x<32;x++){
		    for (y=0;y<256;y++){
			tab[x][y]=0;    
		    }
		}
		sprintf(numero, "%d", i);
		strcpy(fusion, numero);
		strcat(fusion,".txt");

		extract_tab_file(tab,fusion);
		merge_tab_file(tab, DONNEES);
		
		*fusion=0;
	}

*/


//Déchiffrement message
///*
	
	MPI_Init(&argc, &argv);	
	int num_pc = atoi(argv[1]);
	int myid, nProcs;
	MPI_Comm_rank( MPI_COMM_WORLD, &myid); 
	MPI_Comm_size( MPI_COMM_WORLD, &nProcs);
	int i;
	int posDechiffre[32];
	int posDechiffre2[32];
	unsigned char msg[33];
	unsigned char msg_final[33];
	if (myid == 0){				
		for (i=0;i<32;i++){
			posDechiffre[i] = 0;
			posDechiffre2[i] = 0;
		}
	}

	

	for(i=0;i<NB_DECHIFFRE;i++){
		unsigned char msgC[33]; 
		unsigned char *res;
		unsigned char *res2;
		int c;
		for(c=0;c<32;c++){
			msg[c] = 0;
			msg_final[c] = 0;	
		}
		if (myid==0){
			rand_key(msg,32,myid,num_pc);		
		}
		MPI_Allreduce(&msg, &msg_final, 8, MPI_INT, MPI_SUM, MPI_COMM_WORLD);

		
		long int tab[32][256];
		long int tab_final[32][256];

	
		MPI_Barrier(MPI_COMM_WORLD);
		get_virtual_crypt_msg( tab, msg_final, msgC, 33, NB_MSG/nProcs, myid, num_pc);

		MPI_Reduce(&tab, &tab_final, 16384, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

		if (myid == 0){ 
			add_tab_new_file(tab_final,"resultatsDonneesChiffrees.txt"); 
		
			res = dechiffre(32,DONNEES,"resultatsDonneesChiffrees.txt");
			//printf("Dechiffre : %s \n",res);
			compare(msg_final, res, 32, posDechiffre);

			res2 = dechiffre2(32,DONNEES,"resultatsDonneesChiffrees.txt");
			//printf("Dechiffre2 : %s \n",res2); 		
			compare(msg_final, res2, 32, posDechiffre2);		

			printf("Déchiffrement n°%d/%d terminé\n", i+1, NB_DECHIFFRE);
		}
	
		MPI_Barrier(MPI_COMM_WORLD);					
	}



	// ajout des résultats de déchiffrement dans des fichiers

	
	if (myid == 0){
		
		FILE* f_new;
		FILE* f_new2;
		char fusion[10];
		char fusion2[10];
		char numero[2];
		sprintf(numero, "%d", num_pc);
		strcpy(fusion, numero);
		strcat(fusion,"-compare.txt");
		strcpy(fusion2, numero);
		strcat(fusion2,"-compare2.txt");
		f_new = fopen(fusion,"w");
		f_new2 = fopen(fusion2,"w");
	
		int j;
		fprintf(f_new,"n %d ",NB_DECHIFFRE);
		fprintf(f_new2,"n %d ",NB_DECHIFFRE);
		// indique dans le fichier la position concernée	 
		for (j=0;j<32;j++){
			fprintf(f_new,"P%d %d ",j+1,posDechiffre[j]);  
			fprintf(f_new2,"P%d %d ",j+1,posDechiffre2[j]);    
		}
	
		fclose(f_new);
		fclose(f_new2);
		
	}
	MPI_Finalize ();
//*/


	
//Fusion des différents fichiers
/*
	int i = 0; 
	char fusion1[10];
	char fusion2[10];
	int tab1[32];
	int tab2[32];
	char numero[2];
	int x;
	int dechiffre1=0;
	int dechiffre2=0;
	for(x=0;x<32;x++){
		tab1[x]=0;  
		tab2[x]=0;
	}

	for(i=1; i<12; i++){
		
		sprintf(numero, "%d", i);
		strcpy(fusion1, numero);
		strcpy(fusion2, numero);
		strcat(fusion1,"-compare.txt");
		strcat(fusion2,"-compare2.txt");

		//EXTRACT
		FILE* f1;
		f1 = fopen(fusion1,"r");
		FILE* f2;
		f2 = fopen(fusion2,"r");	
		if (f1==NULL||f2==NULL){
			printf("Le fichier %s  et/ou  %s est (sont) introuvable(s).\n",fusion1,fusion2);
		} else {
			char saut[30];
			int k;
			int j;
			int n;
			int m;
			fscanf(f1,"%s ",saut);
			fscanf(f1,"%d ",&k);
			dechiffre1 += k;
			fscanf(f2,"%s ",saut);
			fscanf(f2,"%d ",&k);
			dechiffre2 += k;
			for (j=0;j<32;j++){
				fscanf(f1,"%s ",saut);
				fscanf(f1,"%d ",&n);
				tab1[j] += n;
				fscanf(f2,"%s ",saut);
				fscanf(f2,"%d ",&m);
				tab2[j] += m;
			}
			fclose(f1);
			fclose(f2);
		}
		
		*fusion1=0;
		*fusion2=0;
	}
	FILE* f_new;
	FILE* f_new2;
	f_new = fopen(COMPARE_1,"w");
	f_new2 = fopen(COMPARE_2,"w");
	
	int j;
	// indique dans le fichier la position concernée
	fprintf(f_new,"n %d ",dechiffre1);  
	fprintf(f_new2,"n %d ",dechiffre2);  	 
	for (j=0;j<32;j++){
		fprintf(f_new,"P%d %d ",j+1,tab1[j]);  
		fprintf(f_new2,"P%d %d ",j+1,tab2[j]);    
	}
	
	fclose(f_new);
	fclose(f_new2);
*/
}

