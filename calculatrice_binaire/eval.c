#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arbre_token.h"

int main()
{
	char exp1[] = "(1.( (0 +1)=>NON10))<=> (1 => 0)";//nombre de parenthèses incorrectes et 2 constantes après NON
	liste_token l = string_to_token(exp1); 
	printf("%s\n",exp1);
	if(!verif_exp(l))
		printf("FAUX\n");
	else
		printf("VRAI\n");
	affiche_liste(l);
	free_liste_token(l);
	printf("##############################################\n");
	
	
	char exp2[] = "(1.( (0 1)=>NON1))<=> (1 => 0)";//faux nombre de parenthèses et 2 constantes à la suite
	liste_token m = string_to_token(exp2); 
	printf("%s\n",exp2);
	if(!verif_exp(m))
		printf("FAUX\n");
	else
		printf("VRAI\n");
	affiche_liste(m);
	free_liste_token(m);
	printf("##############################################\n");
	
	
	char exp3[] = "1.0 + 1    =>NON 0<=> 1 => 0";
	liste_token n = string_to_token(exp3); 
	printf("%s\n",exp3);
	if(!verif_exp(n))
		printf("FAUX\n");
	else
		printf("VRAI\n");
	affiche_liste(n);
	Arbre_token N = liste_to_arbre(n);
	affiche_arbre(N);
	printf("resultat : %d\n",arbre_to_int(N));
	free_arbre_token(N);
	free_liste_token(n);
	printf("##############################################\n");
	
		
	char exp4[] = " 1.NON1<=> 1 => 0";
	liste_token o = string_to_token(exp4); 
	printf("%s\n",exp4);
	if(!verif_exp(o))
		printf("FAUX\n");
	else
		printf("VRAI\n");
	affiche_liste(o);
	Arbre_token O = liste_to_arbre(o);
	affiche_arbre(O);
	printf("resultat : %d\n",arbre_to_int(O));
	free_arbre_token(O);
	free_liste_token(o);
	printf("##############################################\n");
	
	char exp5[] = "((NON0 + 1) <=> NON0) + 1";
	printf("%s\n",exp5);
	liste_token p = string_to_token(exp5); 
	if(!verif_exp(p))
		printf("FAUX\n");
	else
		printf("VRAI\n");
	affiche_liste(p);
	Arbre_token P = liste_to_arbre(p);
	affiche_arbre(P);
	printf("resultat : %d\n",arbre_to_int(P));
	free_arbre_token(P);
	free_liste_token(p);
	printf("##############################################\n");
	
	
	return 0;
}
