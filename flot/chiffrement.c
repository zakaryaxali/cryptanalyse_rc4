#include "statistiques.h"
#include "stream.h"
#include "chiffrement.h"
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <mpi.h>
#include <math.h>


#define DONNEES "resultatsLabo.txt"
#define IND_MSG 50000000



//Chiffre un message donné à l'aide d'une clé de 16 octets 
// taille est la longueur du messageClair (et du donc du messageChiffre
void chiffre(unsigned char* messageClair,unsigned char* messageChiffre,unsigned char key[16], int taille){
	unsigned char S[256];
	key_schedule(S,key,16);
	unsigned char keys[taille];
	key_gen(keys,taille,S);
	int i;
	for (i=0;i<taille;i++){
		messageChiffre[i] = messageClair[i] ^ keys[i];
	}
}

//Chiffre nb_message fois le messageClair avec des clés différentes. Puis on en analyses les stats pour en sortir un tableau d'entiers [32][256] à la manière de l'analyse de clés purs 
// longueur est la longueur du messageClair

void get_virtual_crypt_msg(long int tab[32][256], unsigned char* messageClair, unsigned char* msgChiffre, int longueur, int nb_message, int thread,int num_pc){
	int i,j,k;	
	for(i=0;i<32;i++){
	    for (j=0;j<256;j++){
	        tab[i][j]=0;    
	    }
	}
	int indice = 0;
	unsigned char key[16];
	printf("Processus %d : commencement de l'analyse.\n",thread);
	for(i=0;i<nb_message;i++){

		rand_key(key,16,thread,num_pc);
		
		chiffre(messageClair,msgChiffre, key, longueur);		
		for (j=0;j<32 && j<longueur-1;j++){
			tab[j][msgChiffre[j]]++;
		}
		if (indice == IND_MSG){
			// printf("Processus %d : %d messages ont été analysées.\n",thread,i+1);
			indice = 0;
		}
		indice = indice + 1;
	}
	printf("Processus %d terminé. %d messages ont été analysés. \n",thread,nb_message);
}

//fonction reprenant get_virtual_crypt en multithread et qui ajoute directment les resultats dans un fichier
void mpi_get_virtual_crypt(int nb_message,unsigned char* messageClair,unsigned char* msgChiffre,char* data,int longueur,int num_pc){ 
	int myid, nProcs;
	long int tab[32][256];
	long int tab_final[32][256];
	MPI_Comm_size(MPI_COMM_WORLD, &nProcs);
	MPI_Comm_rank(MPI_COMM_WORLD, &myid);

	
	MPI_Barrier(MPI_COMM_WORLD);
	get_virtual_crypt_msg(tab, messageClair,msgChiffre,longueur, nb_message/nProcs, myid,num_pc);

	MPI_Reduce(&tab, &tab_final, 8192, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

	if (myid == 0){ 
		add_tab_new_file(tab_final,data);
	}

}

// Utilise les stats pour déchiffrer le message. Pour cela il faudra rentrer manuellement la règle de déchiffrement (pour la position 1 prendre le "min" des valeurs, pour les autres prendre le max, et effectuer un Xor. Il faut référencier le fichier de statistiques.
// longueur est la longueur du message clair et data le fichier de statistique de RC4.
//nb_message et le nombre de chiffrés que l'on souhaite générée via la fonction get_virtual_crypt_msg.

// char* data_chiffrees est le fichier où l'on récupère les résultats des messages chiffrés analysés
unsigned char* dechiffre(int longueur, char* data,char* data_chiffrees){
	// définit les octets correspondant aux Max (au min pour la position 1) et, parallèlement, obtient des stats des differents chiffrés
	long int donnees[32][256];
	long int donnees_chiffrees[32][256];
	extract_tab_file(donnees,DONNEES);
	extract_tab_file(donnees_chiffrees, data_chiffrees);
	unsigned char minMax[32];
	unsigned char minMaxChiffre[32];
	int i,j;
	long int max;
	long int max_chiffre;
	int indice_max;
	int indice_max_chiffre;
	max = donnees[0][0];
	max_chiffre = donnees_chiffrees[0][0];
	indice_max = 0;
	indice_max_chiffre = 0;
	for (j=1;j<256;j++){
		if (donnees[0][j] < max){
			max = donnees[0][j];
			indice_max = j;
		}
		if (donnees_chiffrees[0][j] < max_chiffre){
			max_chiffre = donnees_chiffrees[0][j];
			indice_max_chiffre = j;
		}	
	}
	minMax[0] = indice_max;
	minMaxChiffre[0] = indice_max_chiffre;
	for (i=1;i<32;i++){
		indice_max = 0;
		indice_max_chiffre = 0;
		max = 0;
		max_chiffre = 0;
		for (j=0;j<256;j++){
			if (donnees[i][j] > max){
				max = donnees[i][j];
				indice_max = j;
			}
			if (donnees_chiffrees[i][j] > max_chiffre){
				max_chiffre = donnees_chiffrees[i][j];
				indice_max_chiffre = j;
			}
		}
		minMax[i] = indice_max;
		minMaxChiffre[i] = indice_max_chiffre;
	}
	// effectue les Xor
	unsigned char *msgDechiffre;
	msgDechiffre = malloc(longueur*sizeof(unsigned char));
	for (i=0;i<longueur;i++){
		msgDechiffre[i] = minMax[i]^minMaxChiffre[i];	
	}
	msgDechiffre[longueur] = '\0';
	return msgDechiffre;
	
}


// char* data_chiffrees2 est le fichier où l'on récupère les résultats des messages chiffrés analysés
unsigned char* dechiffre2(int longueur, char* data, char* data_chiffrees2){
	int r;
	unsigned char* msgDechiffre;
	msgDechiffre = malloc(longueur*sizeof(unsigned char));
	// calcul les probabilités à partir des données enregistrés sur les clés
	long int stats[32][256];
	extract_tab_file(stats,data);
	double result[32][256];
	int i,j;
	double total;
	for (i=0;i<32;i++){
		total = 0;
		for (j=0;j<256;j++){
			total = total + stats[i][j];
		}
		for (j=0;j<256;j++){
			result[i][j] = stats[i][j]/total;
		}
	}
	// prends les données sur les messages chiffrés
	long int donnees_chiffrees[32][256];
	extract_tab_file(donnees_chiffrees, data_chiffrees2);
	
	for (r=0;r<32 && r<longueur;r++){
		// pour chaque position "r" on applique l'algorithme 4 du document
		double lambda[256];
		int u,k;
		long int tab[256];
		double somme;
		for (u=0;u<256;u++){
			for (k=0;k<256;k++){
				tab[k] = donnees_chiffrees[r][k^u];		
			}
			somme = 0;
			for (k=0;k<256;k++){
				somme = somme + tab[k]*log(result[r][k]);
			}
			lambda[u] = somme;
		}
		double lambda_max = lambda[0];
		unsigned char u_max;
		u_max = 0;
		for (u=1;u<256;u++){
			if (lambda[u] > lambda_max){
				
				lambda_max = lambda[u];
				u_max = u;
			}
		}
		msgDechiffre[r] = u_max;
	}
	return msgDechiffre;	
}

void compare(unsigned char* msgClair, unsigned char* msgChiffre, int longueur, int tab[32]){
	int i;
	for( i=0; i<longueur; i++){
		if(msgClair[i]==msgChiffre[i]){
			tab[i]++;
		}
	}
}









