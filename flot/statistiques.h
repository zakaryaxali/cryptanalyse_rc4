#ifndef _STATISTIQUES_H
#define _STATISTIQUES_H

void rand_key(unsigned char* key,int,int,int);
void add_tab_new_file(long int tab[32][256],char*);
void add_tab_double_new_file(double[32][256],char*);
void extract_tab_file(long int tab[32][256],char*);
void extract_tab_float_file(float tab[32][256], char* file);
void analyse_rand(long int tab[32][256],long int nb_cle, int thread,int);
void analyse_rand2(long int tab[256][256],long int nb_cle, int thread,int);
void gnuplot(char*);
void merge_tab_file(long int tab[32][256], char* file);
void graphes(char*);
void mpi_analyse_rand(long int nb_cle, int num_pc);
void mpi_analyse_rand2(long int nb_cle, int num_pc);
#endif
