#include "liste.h"

typedef struct{
	int type; //backbone, type 2 ou 3
	LISTE voisins;
}NOEUD;

typedef struct {
	
	int nb_sommets; // nombre de sommets (100 dans le sujet)
	NOEUD *tab; // tableau de noeuds 
	
}GRAPHE;

struct table
{
	int sommet;
	int distance;
	int pere;
	struct table* suivant;	
};

typedef struct table* TABLE;





GRAPHE init_GRAPHE(int n); //tous les noeud.type = 0 et voisins = init_liste
//GRAPHE init_GRAPHE(); pour l'exemple
//GRAPHE exemple(GRAPHE G);
GRAPHE backbone(GRAPHE G); //initialiser les liens du backbone
GRAPHE op_transit(GRAPHE G);
GRAPHE lien_niv1(GRAPHE G);
GRAPHE lien_niv2(GRAPHE G);
GRAPHE op_niv3(GRAPHE G);
int nb_noeud_niv2(GRAPHE G,int sommet);
int nb_noeud_niv3(GRAPHE G,int sommet);

//Savoir si un noeud est déjà voisin d'un autre
int est_voisin(GRAPHE G,int sommet,int voisin_possible);


//calculer le minimum entre deux nombres pour l'algo de Dikstra
int minimum(int a, int b);

TABLE ajout_element(TABLE b, int sommet, int distance, int pere);

int nb_elements_table(TABLE t);

int distance(GRAPHE G, int sommet, int pere);

//algo de dijkstra
TABLE initialisation_Dijkstra(GRAPHE G,int sommet);

int distance(GRAPHE G, int sommet, int pere);
int distance_sommet(TABLE t, int sommet);
int pere(TABLE t, int sommet);
int tous_les_sommets_traites(int T[100]);


int sommet_non_traite(int T[100], int sommet);
int premier_sommet_a_traiter(int T[100]);
int prochain_sommet_a_traiter(int T[100],TABLE t);
TABLE b_p_d(GRAPHE G, TABLE t, int source);


void affiche_table(TABLE b);
// algo de dijkstra à appliquer pour tous les noeuds du graphe
TABLE* calcul_table_routage_all_noeuds (GRAPHE G);

// faire une fonction pour faire un free de table
void explorer_sommet(GRAPHE G,int*couleur,int sommet);
int est_connexe(GRAPHE G);
void chemin(TABLE*T,int emetteur, int destinataire);
