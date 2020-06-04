#include <stdio.h>
#include <stdlib.h>

#include "navalmap.h"
#include "bateau.h"
#include "lire_fichier.h"

#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

//#define equipe 2

int main(int argc, char** argv)
{
    // Initialisation de la bibliothèque
    printf("initNavalMapLib \n");
    initNavalMapLib();

    // Initialisation d'une carte navale
    // Les informations sont lues dans un fichier en entree (type de la carte navale, taille da la carte, nombre de joueurs)
    map_t mapType;
    coord_t mapSize;
    int nbShips;

    // Le fichier en entree donne aussi les valeurs d'initialisation de C(coque) et K(kerosene) et le nombre max de tours
    int Cmax;
    int Kmax;
    int nbTours;

    //lecture du fichier
    printf("lecture du fichier\n");
    if(argc==2)
    {
		lire_fichier(argv[1],&mapType,&mapSize,&nbShips,&Cmax,&Kmax,&nbTours);
		//nbShips = equipe * nbShips;

	}
	else
	{
		fprintf(stderr,"Erreur ouverture fichier\n");
		exit(EXIT_FAILURE);
	}
	
	
    printf("init navalmap \n");
    navalmap_t *nmap = init_navalmap (mapType,mapSize,nbShips);


    // initialisation des bateaux
    bateau *b=init_bateau(Cmax,Kmax,nbShips);
	printf("init bateaux \n");


    // placer aléatoirement
    placeRemainingShipsAtRandom (nmap);
	printf("bateaux places aleatoirement\n");
	
    affiche (nmap,b);

    creer_processus(nmap,b,nbTours);

  
    // desallocation
    printf("free_bateaux \n");
    free_bateau (b);

    printf("free_navalmap \n");
    free_navalmap(nmap);

    return 0;
}
