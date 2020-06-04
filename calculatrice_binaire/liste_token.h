enum type{
	parenthese,
	oper_bin, //opérateur binaire
	oper_un, //opérateur unaire
	constante	
};
typedef enum type TYPE;

struct token{
	TYPE type_tok;//type de token 
	char* valeur; 
	struct token* suivant;	
};
typedef struct token* liste_token;

/* fonction qui affiche tous les éléments d'une liste de tokens */
void affiche_liste(liste_token l);

/*fonction qui renvoie la même liste que celle donnée en paramètre*/
liste_token copier_liste(liste_token l);

/* fonction qui renvoie la liste de tous les tokens après la parenthèse*/
liste_token passer_parenthese(liste_token l);

/* fonction pour ajouter un token à la fin d'une liste de tokens 
 * @ param	type_tok	type de token de l'élément à ajouter
 * 			valeur		le token de l'élément à ajouter
 * 			l 			liste de tokens à laquelle on ajoute l'élément*/
liste_token ajout_elem_fin(TYPE type_tok,char* valeur,liste_token l);

/* libérer la mémoire allouée d'une liste de tokens */
void free_liste_token(liste_token liste);

/*fonction qui supprime le premier élément d'une liste de tokens*/
liste_token supprimer_deb(liste_token l);

/* fonction qui supprimer le dernier élément d'une liste de tokens
 * @return		l avec l'élément de fin supprimé*/
liste_token supprime_fin(liste_token l);

/*avoir le contenu d'une liste dans une parenthèse
 * @param	l	liste de tokens qui débute par minimum une parenthese ouvrante
 * @return	liste de token dans les parenthèses sans parenthèses de début et de fin*/
liste_token liste_ds_parenth(liste_token l);

/*convertir une chaîne de caractères en une liste de tokens 
 * @param	string		chaîne de caractères à convertir */
liste_token string_to_token(char* string);

/* fonction pour vérifier si une expression stockée dans la liste l est une expression booléenne
 * return	1	si oui
 * 			0	sinon */
int verif_exp(liste_token l);
