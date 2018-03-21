#include "stream.h"



// cette fonction echange les elements d'indice i et j du tableau 'tab'

void swap(int i, int j, char* tab){
	int aux = tab[i];
	tab[i]=tab[j];
	tab[j]=aux;
}

// en argument : la clé et la longueur de la clé et le tableau S à remplir de taille 256 octets (tableau S de l'algo key schedule RC4)
// cette fonction modifie S selon l'algo key schedule RC4

void key_schedule(unsigned char* S, unsigned char* key,int longueur){
	int i;
	for (i=0;i<256;i++){
		S[i]=i;
	}
	unsigned char j = 0;
	for (i=0;i<256;i++){
		j = j + S[i] + key[i%longueur];
		swap(i,j,S);
	}		
}

// en entree : tableau du flot de clé 'keys', longueur de ce tableau et enfin le tableau S de l'aglo key schedule RC4
// cette fonction entre dans 'keys' les clés générés à partir de S et selon l'aglo de cryptographie à flots type RC4

void key_gen(unsigned char* keys,int longueur_keys,unsigned char* S){
	unsigned char i = 0;
	unsigned char j = 0;
	int c;
	unsigned char boite;
	for(c=0;c<longueur_keys;c++){
		i++;
		j = j + S[i];
		swap(i,j,S);
		boite = S[i] + S[j];
		keys[c] = S[boite];
	}
}
