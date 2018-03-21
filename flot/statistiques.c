#include "statistiques.h"
#include "stream.h"
#include "chiffrement.h"
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <mpi.h>


#define LEN_KEY 16
#define CLE_INFO 250000000
#define LEN_NAME_MAX 30

#define SCRIPT_GNUPLOT "config.gp"






// cette fonction renvoie une clé de 16 octets aléatoirement. 
void rand_key(unsigned char* key, int longueur_key, int thread_id,int num_pc){
	int c;
	static int first = 0;
	   
	if (first == 0){
		//srand (time (NULL));
		//srand (thread_id + num_pc*100 + 2014 + FACT);
		srand (time (NULL)+thread_id + num_pc*100);
		first = 1;
	}
	for(c=0;c<longueur_key;c++){
		key[c]=rand();	
	}	
		
}
// cette fonction analyse les octets de clés générés par l'aglo RC4 en prenant des clés de générations au hasard
//int thread correspond à la thread utilisée par la fonction, ce qui permet de générer des combinaisons de nombres différentes
void analyse_rand(long int tab[32][256],long int nb_cle, int thread_id,int num_pc){
	printf("Processus %d lancé.\n",thread_id);
	int x;
	int y;
	for(x=0;x<32;x++){
	    for (y=0;y<256;y++){
	        tab[x][y]=0;    
	    }
	}
	unsigned char key[16] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 , 0, 0, 0, 0, 0, 0, 0 };
	unsigned char S[256];
	unsigned char keys[32];
	int compteur=0;
	int num_cle=0;
	int compteurInfo=0;
	int i;
	while (num_cle<nb_cle){
		//for(i=0;i<thread+1;i++)
		rand_key(key,16, thread_id,num_pc); 
		key_schedule(S,key,LEN_KEY);
		key_gen(keys,32,S);
	       
		for (compteur=0;compteur<32;compteur++){
			tab[compteur][keys[compteur]]++;   
		}
		compteurInfo++;
		if (compteurInfo==CLE_INFO){
			time_t t = time(NULL);
			char* date = ctime(&t);
			printf("Processus %d : %d clés ont été analysées. \n",thread_id,num_cle);
			compteurInfo=0;
			i++;
		}
		num_cle++;
	}
	printf("processus %d terminé. %ld clés ont été analysées.",thread_id,nb_cle);
	time_t t = time(NULL);
	char* date = ctime(&t);
}

void analyse_rand2(long int tab[256][256],long int nb_cle, int thread_id,int num_pc){
	printf("Processus %d lancé.\n",thread_id);
	int x;
	int y;
	for(x=0;x<256;x++){
	    for (y=0;y<256;y++){
	        tab[x][y]=0;    
	    }
	}
	unsigned char key[16] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 , 0, 0, 0, 0, 0, 0, 0 };
	unsigned char S[256];
	unsigned char keys[256];
	int compteur=0;
	int num_cle=0;
	int compteurInfo=0;
	int i;
	while (num_cle<nb_cle){
		//for(i=0;i<thread+1;i++)
		rand_key(key,16, thread_id,num_pc); 
		key_schedule(S,key,LEN_KEY);
		key_gen(keys,256,S);
	       
		for (compteur=0;compteur<256;compteur++){
			tab[compteur][keys[compteur]]++;   
		}
		compteurInfo++;
		if (compteurInfo==CLE_INFO){
			time_t t = time(NULL);
			char* date = ctime(&t);
			printf("Processus %d : %d clés ont été analysées. \n",thread_id,num_cle);
			compteurInfo=0;
			i++;
		}
		num_cle++;
	}
	printf("processus %d terminé. %ld clés ont été analysées.",thread_id,nb_cle);
	time_t t = time(NULL);
	char* date = ctime(&t);
}

//fonction reprenant analyse_rand en multithread et qui ajoute directment les resultats dans un fichier et met a jour les graphes
void mpi_analyse_rand(long int nb_cle, int num_pc){
	long int tab[32][256];
	long int tab_final[32][256];
	int x;
	int y;
	for(x=0;x<32;x++){
	    for (y=0;y<256;y++){
	        tab_final[x][y]=0;    
	    }
	}

	int myid, nProcs;
	MPI_Comm_size(MPI_COMM_WORLD, &nProcs);
	
	MPI_Comm_rank(MPI_COMM_WORLD, &myid);
	MPI_Barrier(MPI_COMM_WORLD);
	analyse_rand(tab, nb_cle/nProcs, myid,num_pc); 
	
	MPI_Reduce(&tab, &tab_final, 16384, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
	
	if (myid == 0){ 
		//merge_tab_file(tab_final,"resultatsClesAleatoires.txt");
		char fusion[10];
		char numero[2];
		sprintf(numero, "%d", num_pc);
		strcpy(fusion, numero);
		strcat(fusion,".txt");
		merge_tab_file(tab_final,fusion);
		//graphes("resultatsClesAleatoires.txt");
	}
}

void mpi_analyse_rand2(long int nb_cle, int num_pc){
	long int tab[256][256];
	long int tab_final[256][256];
	int x;
	int y;
	for(x=0;x<256;x++){
	    for (y=0;y<256;y++){
	        tab_final[x][y]=0;    
	    }
	}

	int myid, nProcs;
	MPI_Comm_size(MPI_COMM_WORLD, &nProcs);
	
	MPI_Comm_rank(MPI_COMM_WORLD, &myid);
	MPI_Barrier(MPI_COMM_WORLD);
	analyse_rand2(tab, nb_cle/nProcs, myid,num_pc); 
	MPI_Barrier(MPI_COMM_WORLD);
	// MPI_Reduce(&tab, &tab_final, 16384, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
	/*
	if (myid == 0){ 
		//merge_tab_file(tab_final,"resultatsClesAleatoires.txt");
		char fusion[10];
		char numero[2];
		sprintf(numero, "%d", num_pc);
		strcpy(fusion, numero);
		strcat(fusion,".txt");
		merge_tab_file(tab_final,fusion);
		//graphes("resultatsClesAleatoires.txt");
	}
	*/
}


// cette fonction copie le tableau 'tab' d'entiers dans le fichier cible (le précédent est écrasé)

void add_tab_new_file(long int tab[32][256], char* fichier_new){
	FILE* f_new;
	f_new = fopen(fichier_new,"w");	
	int n;
	int i,j;
	fprintf(f_new,"n ");
	// indique dans le fichier les clés concernées	 
	for (j=1;j<33;j++){
		fprintf(f_new,"P%d ",j);    
	}
	// on y écrit les entiers de tab[32][256]
	for (i=0;i<256;i++){
		fprintf(f_new,"\n");
		fprintf(f_new,"%d ",i);
		for (j=0;j<32;j++){
			fprintf(f_new,"%ld ",tab[j][i]);
		}
		
	}
	fclose(f_new);
}

// cette fonction copie le tableau 'tab' de float dans le fichier cible (le précédent est écrasé)

void add_tab_double_new_file(double tab[32][256], char* fichier_new){
	FILE* f_new;
	f_new = fopen(fichier_new,"w");	
	int n;
	int i,j;
	fprintf(f_new,"n ");
	// indique dans le fichier les clés concernées	 
	for (j=1;j<33;j++){
		fprintf(f_new,"P%d ",j);    
	}
	// on y écrit les entiers de tab[32][256]
	for (i=0;i<256;i++){
		fprintf(f_new,"\n");
		fprintf(f_new,"%d ",i);
		for (j=0;j<32;j++){
			fprintf(f_new,"%.15lf ",tab[j][i]);
		}
		
	}
	fclose(f_new);
}

// cette fonction extrait les données du fichier file et les place dans le tableau tab

void extract_tab_file(long int tab[32][256], char* file){	
	FILE* f;
	f = fopen(file,"r");	
	if (f==NULL){
		printf("Le fichier %s est introuvable.\n",file);
	} else {
		char saut[30];
		int i,j;
		int n;
		// saut d'une ligne 
		for (i=0;i<33;i++){
			fscanf(f,"%s ",saut);
		}
		// lecture et enregistrement des données dans tab
		for (i=0;i<256;i++){
			fscanf(f,"%d ",&n);
			for (j=1;j<33;j++){
				fscanf(f,"%d ",&n);
				tab[j-1][i] = n;
			}
		}		
		fclose(f);
	}
}

// même que précédemment mais pour un tableau de float

void extract_tab_float_file(float tab[32][256], char* file){	
	FILE* f;
	f = fopen(file,"r");	
	if (f==NULL){
		printf("Le fichier %s est introuvable.\n",file);
	} else {
		char saut[30];
		int i,j;
		float n;
		// saut d'une ligne 
		for (i=0;i<33;i++){
			fscanf(f,"%s ",saut);
		}
		// lecture et enregistrement des données dans tab
		for (i=0;i<256;i++){
			fscanf(f,"%f ",&n);
			for (j=1;j<33;j++){
				fscanf(f,"%f ",&n);
				tab[j-1][i] = n;
			}
		}		
		fclose(f);
	}
}


// cette fonctionne somme les entiers du tableau int[32][256] avec les entiers du fichie file et enregistre le temps dans file

void merge_tab_file(long int tab[32][256], char* file){
	// récupération des données du fichier
	long int tab_file[32][256];
	extract_tab_file(tab_file,file);
	// sommation des données dans tab
	int i,j;
	for (i=0;i<32;i++){
		for (j=0;j<256;j++){
			tab[i][j] = tab[i][j] + tab_file[i][j];
		}
	}
	// enregistrement des données dans file
	add_tab_new_file(tab,file);
}

// cette fonction prend les données du fichier data et en trace les graphes statistiques dans le dossier "graphes"

void graphes(char* data){
	long int tab[32][256];
	extract_tab_file(tab,data);
	// normalise les données pour avoir des probabilités
	double result[32][256];
	int i,j;
	double total;
	for (i=0;i<32;i++){
		total = 0;
		for (j=0;j<256;j++){
			total = total + tab[i][j];
		}
		for (j=0;j<256;j++){
			result[i][j] = tab[i][j]/total;
		}
	}
	// enregistrement des données dans un fichier  puis exécution du script gnuplot
	add_tab_double_new_file(result,"graphes/probabilitees.txt");
	gnuplot(SCRIPT_GNUPLOT);
}




// cette fonction permet d'exécuter un script gnuplot

void gnuplot(char* script_file){	
	FILE *gp;
	gp = popen("/usr/bin/gnuplot", "w");
	fprintf(gp, "load \"%s\"",script_file);
	fflush(gp);
	pclose(gp);

	// exit();
}













