%.o: %.c
	gcc -o $@ -c $<

all: cesar

cesar: analyse_freq.o check.o check_key.o check_ram.o chiffre.o compare.o compare_ram.o cryptanalyse_freq.o cryptanalyse_no_freq.o delAccent.o dico.o lecture.o main.o
	gcc -o cesar analyse_freq.o check.o check_key.o check_ram.o chiffre.o compare.o compare_ram.o cryptanalyse_freq.o cryptanalyse_no_freq.o delAccent.o dico.o lecture.o main.o

lecture: lecture.o main.o
	gcc -o lecture lecture.o main.o

clean:
	rm -rf *.o

mrproper:
	rm -rf cesar
