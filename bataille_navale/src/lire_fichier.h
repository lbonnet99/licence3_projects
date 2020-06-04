
#ifndef __LIRE_FICHIER_H
#define __LIRE_FICHIER_H

#include "navalmap.h"
// Lecture d'un fichier pour lire:
//      1. la caracterisation de la carte avec son type, sa taille, en longueur et en hauteur
//      2. la caracterisation de la partie avec le nombre de joueurs, les valeurs initiales de coque et de kerosene et le nombre de tours maximum joues
void lire_fichier(char*nom,map_t *mapType,coord_t *mapSize, int *nbShips, int *Cmax, int *Kmax, int *nbTours);
#endif
