#include <stdlib.h>
#include <stdio.h>
#include "liste_token.h"
#include <string.h>

/* fonction qui affiche tous les éléments d'une liste de tokens */
void affiche_liste(liste_token l)
{
	int nb = 0;
	while(l!=NULL)
	{
		printf("element %d, valeur = %s\n",nb,l->valeur);
		
		l = l->suivant;
		nb++;
	}
}

/*fonction qui renvoie la même liste que celle donnée en paramètre*/
liste_token copier_liste(liste_token l)
{
	liste_token new,copie; //new = liste à renvoyer et copie juste pour la fonction
	if(l==NULL)
		new = NULL;
	else
	{
		new = malloc(sizeof(struct token));
		copie = new;
		while(l!=NULL)
		{
			*copie = *l;
			l = l->suivant;
			if(l!=NULL)
			{
				copie->suivant = malloc(sizeof(struct token));
				copie = copie->suivant;
			}
			
		}
		
	}
	return new;
	
}

/*fonction qui renvoie la liste de tous les tokens après la parenthèse*/
liste_token passer_parenthese(liste_token l){
	liste_token copie = l;
	int continuer = 1, cmp = 0;
	while(continuer){
		if(copie!=NULL)
		{
			if(!strcmp(copie->valeur,"("))
			{
				cmp++;
			}
			if(!strcmp(copie->valeur,")"))
			{
				cmp--;			
			}
			
			//printf("#####################\n");
			copie = copie->suivant;
			if(cmp==0)
				continuer = 0;
		}
		else
			continuer = 0;
	}
	return copie;
}

/* fonction pour ajouter un token à la fin d'une liste de tokens 
 * @ param	type_tok	type de token de l'élément à ajouter
 * 			valeur		le token de l'élément à ajouter
 * 			l 			liste de tokens à laquelle on ajoute l'élément
 * */
liste_token ajout_elem_fin(TYPE type_tok,char* valeur,liste_token l)
{
	liste_token new = malloc(sizeof(struct token));
	if(new == NULL){
		fprintf(stderr,"ERREUR : échec malloc\n");
		exit(EXIT_FAILURE);
		
	}
	new->valeur = valeur;
	new->type_tok = type_tok;
	new->suivant = NULL;
	if(l==NULL) //si l ne contient aucun élément
		return new;
	else
	{
		liste_token copie = l;
		while(copie->suivant!=NULL) //on parcourt tous les elements jusqu'à NULL
		{
			copie = copie->suivant;			
		}
		copie->suivant = new;//puis on ajoute
		return l;
	}
}

/* libérer la mémoire allouée d'une liste de tokens */
void free_liste_token(liste_token liste){
	while(liste){
		free(liste);
		liste = liste->suivant;
	}
}

/*fonction qui supprime le premier élément d'une liste de tokens*/
liste_token supprimer_deb(liste_token l)
{
	if(l != NULL)
	{
		liste_token aRenvoyer = l->suivant;
		free(l);
		return aRenvoyer;
	}
	else
	{
		fprintf(stderr, "ERREUR : suppression dans liste vide\n");
		exit(EXIT_FAILURE);
	}
}
/* fonction qui supprimer le dernier élément d'une liste de tokens
 * @return		l avec l'élément de fin supprimé*/
liste_token supprime_fin(liste_token l){
	if(l==NULL){
		fprintf(stderr, "ERREUR : suppression dans liste vide\n");
		exit(EXIT_FAILURE);
	}
	if(l->suivant == NULL) return supprimer_deb(l);
	l->suivant = supprime_fin(l->suivant);
	return l;
}

/*avoir le contenu d'une liste dans une parenthèse
 * @param	l	liste de tokens qui débute par minimum une parenthese ouvrante
 * @return	liste de token dans les parenthèses sans parenthèses de début et de fin*/
liste_token liste_ds_parenth(liste_token l)
{
	int cmp = 0; int continuer = 1;
	liste_token copie = l;
	liste_token new = NULL;
	while(copie!=NULL)
	{
		if(continuer)
		{
			if(!strcmp(copie->valeur,"("))
			{
				cmp++;
			}
			if(!strcmp(copie->valeur,")"))
			{
				cmp--;
			}		
			TYPE t = copie->type_tok;
			char* c = copie->valeur;
			new = ajout_elem_fin(t,c,new);
			if(cmp==0)
				continuer = 0;
		}
		copie = copie->suivant;
	}
	
	//supprimer les parenthèses de début et de fin 
	//pour avoir seulement le contenu donc supprimer le premier et le dernier élément de la liste
	new = supprimer_deb(new);
	new = supprime_fin(new); 
	
	
	return new;
	
}

/*convertir une chaîne de caractères en une liste de tokens 
 * @param	string		chaîne de caractères à convertir
 * */
liste_token string_to_token(char* string)
{
	int longueur = strlen(string);	
	int i;
	liste_token l = NULL;
	for(i=0;i<longueur;i++)//parcourir le tableau de la chaîne de caractères
	{
		if(string[i] == '(')
			l = ajout_elem_fin(parenthese,"(",l);
		if(string[i] == ')')
			l = ajout_elem_fin(parenthese,")",l);
		if(string[i] == '+')
			l = ajout_elem_fin(oper_bin,"+",l);
		if(string[i] == '.')
			l = ajout_elem_fin(oper_bin,".",l);
		if(string[i] == '<')
		{
			l = ajout_elem_fin(oper_bin,"<=>",l);
			i=i+3;
		}//pour sauter = et > de l'équivalence
		if(string[i] == '>')
			l = ajout_elem_fin(oper_bin,"=>",l);
		if(string[i] == 'O')
			l = ajout_elem_fin(oper_un,"NON",l);
			
			
		if(string[i] == '0')
			l = ajout_elem_fin(constante,"0",l);
		if(string[i] == '1')
			l = ajout_elem_fin(constante,"1",l);
		
	}
	
	return l;
}

/* fonction pour vérifier si une expression stockée dans la liste l est une expression booléenne
 * return	1	si oui
 * 			0	sinon
 * */
int verif_exp(liste_token l)
{
	int nb_par = 0; // compteur pour les parenthèses : +1 si par ouvrante -1 pour fermante
	int cst = 0; //vérifier qu'il y a constante puis op binaire puis constante
	int non = 0; //vérifier que l'opérateur non est suivie  d'une constante
	while(l!=NULL)
	{
		if(l->type_tok==parenthese)
		{
			if(!strcmp(l->valeur,"("))
				nb_par ++;
			else //parenthèse fermante
				nb_par --;
		}
		
		if(l->type_tok==oper_un)
		{
			non ++;
			if(l->suivant)
			{
				if(l->suivant->type_tok==constante)
					non --;
			}
		}
		if(l->type_tok==constante)
		{
			if(cst==0 || cst==1) //au départ ou après avoir compté les opérateurs binaires
			{
				cst ++;;
			}
			
			if(cst==3) //constante puis opérateur binaire puis constante
			{
				cst = 1;
			}
		}
		if(l->type_tok==oper_bin)
		{
			cst+=2;
		}
		l = l->suivant;
	}
	
	if(nb_par!=0 || non!=0 || cst!=1)
		return 0;
	return 1;
}
