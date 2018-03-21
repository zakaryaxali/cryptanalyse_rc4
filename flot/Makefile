%.o: %.c
	mpicc -c $*.c -o $*.o 

all : flot


flot : main.o stream.o afficher_tableau.o statistiques.o chiffrement.o
	gcc main.o stream.o afficher_tableau.o statistiques.o chiffrement.o -lm -o main	

stats : main.o stream.o afficher_tableau.o statistiques.o chiffrement.o
	mpicc main.o stream.o afficher_tableau.o statistiques.o chiffrement.o -lm -o main
	
clean:
	rm -rf *.o
	
mrproper:
	rm -rf main
	
 
