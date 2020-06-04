#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>
#include "SquareAndMultiply.h"



//retourne 1 si n est premier et 0 si n est composé
int algorithme_Fermat(mpz_t n, mpz_t k){
	
	 int res = 1;
	 gmp_randstate_t  gmpRandState;		//seed
	 mpz_t un,zero,i,j, n2,pow,h,resultat;
	 
	 mpz_init_set_str(un, "1", 10);			//initialisation de la variable un à 1
	 mpz_init(zero);
	 mpz_init(i);							//itérateur i à 0
	 mpz_init(h);							//h = exposant en binaire pour SquareAndMultiply
	 mpz_init(pow);
	 mpz_t a;								//nombre aléatoire
	 mpz_init(a);							//initialisation de la variable à 0
	 mpz_init(n2);							//initialisation de la variable à 0
	 //mpz_sub(n2,n,un);						// n2 = n-1
	 
	 gmp_randinit_mt (gmpRandState);		//initialisation de la seed
	
	 while(mpz_cmp(i,k)<0){
		mpz_init(a); 
		mpz_init_set_str(j, "2", 10);						//itérateur j à 0
		
		mpz_urandomm (a, gmpRandState, n);	// a = random
	
		while(mpz_cmp(a,zero) == 0){
			mpz_urandomm (a, gmpRandState, n);	// a = random
		}
		
		gmp_printf("urandom  = %Zd\n",a);
		mpz_add(pow,a,zero);
		
		gmp_printf("a = %Zd\n",a);
		
		mpz_sub(n2,n,un);						// n2 = n-1	 
		char * m = NULL;
		char * n2_b2 = malloc(sizeof(char));		//n2 en base 2
		n2_b2 = mpz_get_str(m,2,n2);				//n2_b2 = (n2) en base 2
		mpz_set_str(h,n2_b2,2);	
		mpz_init(resultat);

		SquareAndMultiply(resultat,a,n,h);


		/*while(mpz_cmp(j,n) < 0){		//a puissance n-1
			
			mpz_mul(a, a, pow);			// a = a*a
			mpz_add(j,j,un);
			
			
		}*/
	gmp_printf("j = %Zd\n",j);
				
		gmp_printf("n = %Zd\n",n);
		gmp_printf("a puissance %Zd mod n= %Zd\n",h,resultat);
		if(mpz_cmp(a,un) == 0){
			
		}
		else{
			res = 0 ;
			break;
		}
		
		
		
		
		mpz_add(i,i,un);
		free(m);
		free(n);
	 }
	 gmp_printf("Itérations = %Zd\n",i);
	 mpz_clear(a);
	 mpz_clear(un);
	 mpz_clear(i);
	 mpz_clear(n2);
	 mpz_clear(h);
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

	if(algorithme_Fermat(n,k) == 1)
	printf("Premier\n");
	else
	printf("Composé\n ");	
	

	 /* free used memory */
	 mpz_clear(k);
	 mpz_clear(n);

 return 0;
}
