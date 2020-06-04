.PHONY: all lib debug

all : lib projet bateau lire

lire: lire_fichier.h lire_fichier.c 
	gcc -c lire_fichier.c lire_fichier.h -Wall

bateau : bateau.h bateau.c 
	gcc -c -lphread bateau.c bateau.h -Wall
	
projet: main.c bateau.o lire_fichier.o
	gcc -I. -o SoD $^ -L. -lnm -Wall

lib :
	gcc -g -c -fPIC nm_rect.c navalmap.c
	ar rcs libnm.a *.o

debug: 
	gcc -g -o SoD main.c  -L. -lnm

clean :
	rm *.gch
	rm SoD
	rm *.o
	rm libnm.a
