#include <stdlib.h>
#include <stdio.h>
#include "arbre_token.h"
#include <string.h>

Arbre_token creer_arbre(TYPE type_tok,char* valeur,Arbre_token g, Arbre_token d){
  Arbre_token a;
  a = malloc(sizeof(struct Arbre));
  if(a == NULL){
    fprintf(stderr, "Erreur allocation memoire pour arbre\n");
    exit(EXIT_FAILURE);
  }
  a->type_tok = type_tok; a->valeur = valeur;
  a->g = g;a->d = d;
  return a;
}

void free_arbre_token(Arbre_token at){
	if(at){
		free_arbre_token(at->g);
		free_arbre_token(at->d);
		free(at);
	}
}

/* fonction qui affiche un arbre à partir d'une profondeur donnée
 * @ param	a	arbre de tokens
 * 			p	profondeur */
void affiche_arbre_prof(Arbre_token a, int p){
  int i;
  if(a != NULL){
    for(i=0; i<p; i++)//decalage selon la profondeur
      printf("     ");
    printf("%s\n", a->valeur);
    affiche_arbre_prof(a->d, p+1);
    affiche_arbre_prof(a->g, p+1);

  }
}

/* fonction qui affiche l'arbre donné en paramètre*/
void affiche_arbre(Arbre_token a){
 	affiche_arbre_prof(a, 0);
}

/* fonction qui calcule le résultat d'une opération binaire booléenne
 * @param	a	constante de gauche
 * 			b	constante de droite
 * 			c	opérateur binaire
 * @return	résultat opération binaire booléenne */
int calcul(int a, int b, char* c){
	if(!strcmp(c,"+"))//table de vérité du ou
		return (a+b)%2;
	if(!strcmp(c,"."))//table de vérité du et
		 return a*b;
	if(!strcmp(c,"=>"))//table de vérité de l'implication
	{
		if(a==0)
			return 1;
		else //a = 1
		{
			if(b==0)
				return 0;
			if(b==1)
				return 1;
		}		
	}		 
	if(!strcmp(c,"<=>"))//table de vérité de l'équivalence
	{
		if(a==b)
			return 1;
		else
			return 0;
	}		 
	return -1;
	
}

/* calculer la valeur de l'expression arithmétique contenue dans l'arbre a */
int arbre_to_int (Arbre_token a)
{
	if(a->type_tok==constante) return atoi(a->valeur);
	if(a->type_tok==oper_un) return (arbre_to_int(a->d)+1)%2;
	return calcul(arbre_to_int(a->g),arbre_to_int(a->d),a->valeur);	
}

/*fonction qui calcule renvoie le sous-arbre droit d'un opérateur unaire ou binaire*/
Arbre_token ss_arbre_droit(liste_token l)
{
	Arbre_token at = NULL;
	if(l!=NULL)
	{
		if(l->type_tok==constante)
		{
			at = creer_arbre(l->type_tok,l->valeur,NULL,NULL);
			
		}
		if(l->type_tok==oper_un)
		{
			at = creer_arbre(l->type_tok,l->valeur,NULL,ss_arbre_droit(l->suivant));
			
		}
		
	}
	return at;
	
}

/* convertir une liste de tokens en un arbre de tokens */
Arbre_token liste_to_arbre(liste_token l)
{
	liste_token copie = copier_liste(l);
	Arbre_token at = NULL;
	while(copie!=NULL)
	{
		if(copie->type_tok==parenthese) //1er token = parenthese ouvrante
		{
			at = liste_to_arbre(liste_ds_parenth(l));
			copie = passer_parenthese(copie);
		}
		if(copie->type_tok==oper_un)
		{
			at = creer_arbre(copie->type_tok,copie->valeur,NULL,ss_arbre_droit(copie->suivant));
			
			//l'opérateur non est forcément suivi de quelque chose
			if(copie->suivant->type_tok==constante) 
				copie = copie->suivant;
			if(copie->suivant!=NULL) 
			{
				if(copie->suivant->type_tok==oper_bin)
					copie = copie->suivant;
			}
		}
		if(copie->type_tok==constante)
		{
			at = creer_arbre(constante,copie->valeur,NULL,NULL);		
		}
		if(copie->type_tok==oper_bin)
		{
			Arbre_token at_prec = at;
			at = creer_arbre(oper_bin,copie->valeur,at_prec,ss_arbre_droit(copie->suivant));
			if(copie->suivant!=NULL)
			{	
				if(copie->suivant->type_tok==constante)			
					copie = copie->suivant;
			}
			if(copie->suivant!=NULL)
			{
				if(copie->suivant->type_tok==oper_un)
					copie = copie->suivant->suivant;
			}
		}
		if(copie!= NULL) 
			copie = copie->suivant;
	}
	return at;
}
