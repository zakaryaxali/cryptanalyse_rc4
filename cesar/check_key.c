#include<stdio.h>
#include<stdlib.h>
#include"check.h"
#include"check_ram.h"

int check_key(char* text, int key){
//Fonction qui applique à un texte donnée la clé key
	//int i=0;
	char* temp = "fichier_temporaire.txt";
	chiffre(text,26-key,temp,1);
	int bonne_cle =check(temp);
	remove(temp);
	return bonne_cle;
}
int check_key_ram(char* text, int key, char** dico, int** indices){
//Fonction qui applique à un texte donnée la clé key
	//int i=0;
	char* temp = "fichier_temporaire.txt";
	chiffre(text,26-key,temp,1);
	int bonne_cle =check_ram(temp, dico, indices);
	remove(temp);
	return bonne_cle;
}
