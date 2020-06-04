#include "graphe.h"

#define N 100
int main()
{
	GRAPHE G;
	
	G = init_GRAPHE(N);
	G = backbone(G);
	G = op_transit(G);
	G = op_niv3(G);
	//G = exemple(G);
	for(int i=0;i<G.nb_sommets;i++)
	{
		printf("Noeud : %d Type: %d\n",i,G.tab[i].type);
		afficher_LISTE(G.tab[i].voisins);
		printf("###########################################\n");
	}
	
	
	
	TABLE* b;
	b = calcul_table_routage_all_noeuds(G);
	for(int i=0;i<G.nb_sommets;i++)
	{
		affiche_table(b[i]);
		printf("##########################################\n");
	}
    
    printf("saisir deux points du graphe pour connaitre le plus court chemin qui relie ces points\n");
    int c,d;
    printf("sélectionner le premier point qui est un nombre compris entre 1 et 100\n");
    scanf("%d",&c);
    printf("sélectionner le deuxième point qui est un nombre compris entre 1 et 100\n");
    scanf("%d",&d);
	chemin(b,c,d);
	
	
	
	free(b);
	return 0;

}
