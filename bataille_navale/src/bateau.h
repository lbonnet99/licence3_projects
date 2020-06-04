#ifndef _H_BATEAU_
#define _H_BATEAU_

#include "navalmap.h"
#include "nm_rect.h"

typedef struct
{
	int kero;
	int coque;
	int ID;
} bateau;

/*
typedef struct {
	int * i;
	//int * moy;
	//int * T;
	int id;
	pthread_mutex_t * m;
	pthread_mutex_t * m2;
	pthread_cond_t * c;
} arg_t; */


// Initialisation tableau de bateaux
// Création tableau de bateaux, les navires ne sont pas placés sur la carte
// \param								Cmax			    coque initiale
// \param								Kmax				kérosène initial
// \param								nbShips				Nombre de navires
// \return													tableau de bateaux
bateau* init_bateau (
	const int							Cmax,
	const int							Kmax,
	const int							nbShips);

//libérer mémoire tableau de bateaux
void free_bateau (bateau	* b);


void aucune_action(navalmap_t* nmap,
	const int	shipID,bateau* b);

//tester si le déplacement est possible
//return 1		si déplacement impossible
//       0		sinon
int deplacement_impossible(navalmap_t* nmap,
	const int	shipID,
	const coord_t	moveVec,bateau* b);


void deplacement(navalmap_t* nmap,
	const int	shipID,
	const coord_t	moveVec,bateau* b);

void attaque(navalmap_t* nmap,
	const int shipID,
	const coord_t	pos,bateau* b);


//return id du bateau le plus proche du joueur numéro shipID
int id_bateau_plus_proche(navalmap_t *nmap,
	int shipID,
	bateau*b);

//id_b_proche = id du bateau le plus proche
//récupére toutes les données du bateau le plus proche : 
//__ses coordonnées__sa coque__kérosène__son ID
coord_t radar_scn(navalmap_t* nmap,
	int shipID,
	bateau*b, int* coque, int* kero, int*ID_b_proche);

void charge(navalmap_t	*nmap,
	const int shipID,
	const coord_t pos,bateau *b);

void reparation(navalmap_t	*nmap,
	const int shipID,
	bateau *b);

//affiche la carte navale
void affiche (navalmap_t *nmap, bateau *b);

// teste si pos(position de l'adversaire) est à portée de charge de la position 
// du bateau ayant pour ID shipID
// return 1 si oui
//        0 sinon
int pos_portee_charge (navalmap_t* nmap, int shipID, 
	bateau* b, coord_t pos);

// teste si pos(position de l'adversaire) est à portée d'attaque de la position 
// du bateau ayant pour ID shipID
// return 1 si oui
//        0 sinon
int pos_portee_attaque(navalmap_t* nmap, 
	int shipID, 
	bateau* b,coord_t pos);

// Détermine déplacement en x par rapport à la position de l'adversaire 
// \param								moveVec				différence de position entre adversaire et le joueur
int pos_move_x(coord_t moveVec);

// Détermine déplacement en y par rapport à la position de l'adversaire 
// \param								moveVec				différence de position entre adversaire et le joueur
int pos_move_y(coord_t moveVec);

// Détermine coordonnées déplacement si la position n'est pas à portée d'attaque
coord_t pos_move(coord_t moveVec);

// Teste s'il reste qu'un bateau sur la carte navale
// \param								b			        tableau de bateaux
// \param								nmap				carte navale
// \return	1		s'il reste qu'un bateau
// \return	0		sinon
int reste_un_bateau(bateau* b, 
	navalmap_t* nmap);

//récupére l'id du bateau gagnant lorsqu'il reste que un bateau sur la map
int bateau_gagnant(bateau* b,
	navalmap_t* nmap);

// création de processus en utilisant l'algorithme "naïf"
// dans processus fils : détermination de la prochaine action à effectuer avec l'algo
// dans processus père : accomplissement de l'action
void creer_processus(navalmap_t* nmap, 
	bateau* b, int nb_tours);

#endif
