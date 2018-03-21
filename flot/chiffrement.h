#ifndef _CHIFFREMENT
#define _CHIFFREMENT
void chiffre(unsigned char* messageClair, unsigned char* messageChiffre, unsigned char key[16], int taille);
void get_virtual_crypt_msg(long int tab[32][256],unsigned char* messageClair,unsigned char*, int longueur, int nb_message, int thread,int);
void mpi_get_virtual_crypt( int nb_message, unsigned char* messageClair,unsigned char*, char* data_chiffrees,int longueur,int);
unsigned char* dechiffre(int longueur, char* data,char* data_chiffrees);
unsigned char* dechiffre2(int longueur, char* data,char* data_chiffrees2);
void compare(unsigned char* msgClair, unsigned char* msgChiffre, int longueur, int tab[32]);


#endif
