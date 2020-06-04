#include "liste_token.h"

struct Arbre {
	TYPE type_tok;//type de token 
	char* valeur; 
	struct Arbre* g;
	struct Arbre* d;
};
typedef struct Arbre* Arbre_token;

Arbre_token creer_arbre(TYPE type_tok,char* valeur,Arbre_token g, Arbre_token d);

void free_arbre_token(Arbre_token at);

/* fonction qui affiche un arbre à partir d'une profondeur donnée
 * @ param	a	arbre de tokens
 * 			p	profondeur */
void affiche_arbre_prof(Arbre_token a, int p);

/* fonction qui affiche l'arbre donné en paramètre*/
void affiche_arbre(Arbre_token a);

/* fonction qui calcule le résultat d'une opération binaire booléenne
 * @param	a	constante de gauche
 * 			b	constante de droite
 * 			c	opérateur binaire
 * @return	résultat opération binaire booléenne */
int calcul(int a, int b, char* c);

/* calculer la valeur de l'expression arithmétique contenue dans l'arbre a */
int arbre_to_int (Arbre_token a);

/*fonction qui calcule renvoie le sous-arbre droit d'un opérateur unaire ou binaire*/
Arbre_token ss_arbre_droit(liste_token l);

/* convertir une liste de tokens en un arbre de tokens */
Arbre_token liste_to_arbre(liste_token l);
