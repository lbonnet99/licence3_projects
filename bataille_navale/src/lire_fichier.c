#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lire_fichier.h"

#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>



void lire_fichier (char *nom,map_t *mapType,coord_t *mapSize,int *nbShips,int *Cmax,int *Kmax,int *nbTours)
{
    struct stat sb;

    if (stat(nom, &sb) == -1)
    {
        printf("erreur stat fichier %s\n",nom);
        return;
    }


    int fd = open(nom,O_RDONLY);
    if (fd == -1)
    {
		fprintf(stderr,"Echec ouverture fichier");
		exit(EXIT_FAILURE);
	}
	
	int i=0;
	char type_carte[]="         "; //9 espaces pour allouer 9 caractères du mot rectangle
	char lettre;
	while(lettre!=';')
	{
		read(fd,&lettre,sizeof(char));
		if(lettre!=';')	type_carte[i] = lettre;
		i++;
	}
	char*r = "rectangle";
	if(strcmp(type_carte,r)==0)	*mapType = MAP_RECT;

	if(*mapType==MAP_RECT) printf("le type de carte navale est rectangle\n");


	i = 0;
	lettre = '.';
	char X[]="  ";
	while(lettre!=';')
	{
		read(fd,&lettre,sizeof(char));
		if(lettre!=';')	X[i] = lettre;
		i++;
	}
	mapSize->x = atoi(X);
	printf("la longueur de la carte est %d\n",mapSize->x);

	i = 0;
	lettre = '.';
	char Y[]="  ";
	while(lettre!='\n')
	{
		read(fd,&lettre,sizeof(char));
		if(lettre!='\n')	Y[i] = lettre;
		i++;
	}
	mapSize->y= atoi(Y);

	printf("la hauteur de la carte est %d\n",mapSize->y);


	i = 0;
	lettre = '.';
	char NB[]="  ";
	while(lettre!=';')
	{
		read(fd,&lettre,sizeof(char));
		if(lettre!=';')	NB[i] = lettre;
		i++;
	}
	*nbShips= atoi(NB);
	printf("Le nombre de joueurs est : %d\n",*nbShips);

	i = 0;
	lettre = '.';
	char C[]="   ";
	while(lettre!=';')
	{
		read(fd,&lettre,sizeof(char));
		if(lettre!=';')	C[i] = lettre;
		i++;
	}
	*Cmax = atoi(C);
	printf("La valeur de la coque initiale est : %d\n",*Cmax);

	i = 0;
	lettre = '.';
	char K[]="   ";
	while(lettre!=';')
	{
		read(fd,&lettre,sizeof(char));
		if(lettre!=';')	K[i] = lettre;
		i++;
	}
	*Kmax = atoi(K);
	printf("La valeur initiale du kerosene est : %d\n",*Kmax);
	
	i = 0;
	lettre = '.';
	char T[]="  ";
	while(lettre!='\n')
	{
		read(fd,&lettre,sizeof(char));
		if(lettre!=';')	T[i] = lettre;
		i++;
	}
	*nbTours = atoi(T);
	printf("Le nombre de tours est : %d\n",*nbTours);
	
	close(fd);
}
