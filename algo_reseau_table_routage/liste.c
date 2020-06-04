#include "liste.h"

LISTE init_LISTE()
{
	/*LISTE L = malloc(sizeof(LISTE));
	if(!L)
	{
		fprintf(stderr,"échec allocation mémoire pour la liste");
		exit(EXIT_FAILURE);
		
	}
	
	L->noeud = -1;
	L->lien = -1;
	L->suivant = NULL;*/
	LISTE L =  NULL;
	return L;
}

void afficher_LISTE(LISTE L)
{
	while(L!= NULL)
	{
		printf("Voisin : %d Lien : %d\n",L->noeud,L->lien);
		L = L->suivant;
	}
}

LISTE add_LISTE(LISTE L,int noeud,int lien)
{
	LISTE new = malloc(sizeof(LISTE));
	if(!new){}
	
	new->noeud = noeud;
	new->lien = lien;
	new->suivant = L;
	
	return new;
	
}

void sup_LISTE(LISTE L)
{
	while(L!=NULL)
	{
		free(L);
	}
}
