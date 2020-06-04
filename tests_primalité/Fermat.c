#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>
#include "SquareAndMultiply.h"




//retourne 1 si n est premier et 0 si n est composé
int algorithme_Fermat(mpz_t n, mpz_t k){
	
	 int res = 1;
	 gmp_randstate_t  gmpRandState;		//seed
	 mpz_t i,n2,a;
	
	 mpz_init(i);							//itérateur i à 0
	 mpz_init(a);							//initialisation de la variable aléatoire à 0
	 mpz_init(n2);							//initialisation de la variable à 0
	 
	 mpz_sub_ui(n2,n,1);					//n2 = n - 1
	 gmp_randinit_mt (gmpRandState);		//initialisation de la seed
	
	 while(mpz_cmp(i,k)<0){
		mpz_urandomm (a, gmpRandState, n);	// a = random
	
		while(mpz_cmp_ui(a,0) == 0){		//si a = 0 choisir un autre nombre aléatoire
			mpz_urandomm (a, gmpRandState, n);	// a = random
		}
			
		SquareAndMultiply(a,a,n,n2);	//a = a^n2 mod n
		
		if(mpz_cmp_ui(a,1) != 0){
			res = 0 ;					//renvoyer composé
			break;
		}
		mpz_add_ui(i,i,1);				//i = i + 1 
	 }
	 gmp_printf("Itérations = %Zd\n",i);
	 mpz_clear(a);
	 mpz_clear(i);
	 mpz_clear(n2);
	 
	 gmp_randclear (gmpRandState);
	return res;
}




int main(int argc, char*argv[]) {
	//fournir un entier n (entier à tester) et un entier k (nombre d'itérations)
		if(argc<3){
		printf("Erreur: nombre d'arguments insuffisant\n");
		exit(EXIT_FAILURE);
	}

	 mpz_t k,n;	

	 mpz_init_set_str(n, argv[1],10);
	 mpz_init_set_str(k, argv[2],10);
	
	if(mpz_cmp_ui(k,0) <= 0 || mpz_cmp_ui(n,0) <=0) {				//si k <= 0
		printf("Valeur invalide \n");
		exit(EXIT_FAILURE);
	}
	
	if(algorithme_Fermat(n,k) == 1)
	printf("Premier\n");
	else
	printf("Composé\n ");
	 

	 /* free used memory */
	 mpz_clear(k);
	 mpz_clear(n);

 return 0;
}
