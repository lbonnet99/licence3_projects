#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>
#include "SquareAndMultiply.h"


//Décompose n tel que n-1 = (2^s) * t avec t impair

void decomposition(mpz_t n, mpz_t s,mpz_t t){
	 mpz_t n2,mod;		
	
	 mpz_init(mod); 
	 mpz_init(s);							//puissance de 2
	 mpz_init(n2);							//Correspond à n - 1;
	 mpz_init_set_ui(t, 1);			//initialisation de la variable tmp à 1
	 mpz_sub_ui(n2,n,1);						// n2 = n-1
	
	while(mpz_cmp_ui(n2,1) > 0)			// n2 > 1
	{
		if(mpz_cmp_ui(mod,1) == 0)		// n2 mod 2 == 1
			{
				break;
			}
		mpz_add_ui(s,s,1);				//s++
		mpz_div_ui(n2,n2,2);			
		mpz_mod_ui(mod,n2,2);
	}
	mpz_set(t, n2);
	 
	mpz_clear(n2);
	mpz_clear(mod);
}


//Retourne 1 si n est premier et 0 si n est composé
int Test_Miller_Rabin(mpz_t n, mpz_t k){
	mpz_t s, t, a, i,y,s1,j,n2,deux;
	int res = 1 ;
	mpz_init_set_str(i, "1", 10);
	mpz_init(j);
	mpz_init(s);
	mpz_init(t);
	mpz_init(a);
	mpz_init(y);
	mpz_init(s1);
	mpz_init(n2);
	mpz_init_set_ui(deux, 2);
	mpz_sub_ui(n2,n,1);				//n2 = n - 1
	
	gmp_randstate_t  gmpRandState;
	gmp_randinit_mt (gmpRandState);		
	
	decomposition(n,s,t);			//On décompose n - 1 pour obtenir s et t tel que n - 1 = (2^s)*t
	mpz_sub_ui(s1,s,1);				//s - 1
	
	while (mpz_cmp(i,k) <= 0)			//while (i < k)
	{					
		mpz_set_ui(a,0);				//a = 0
		
		while(mpz_cmp_ui(a,0) == 0){		
			mpz_urandomm (a, gmpRandState, n);	// a = random
		}
			
		SquareAndMultiply(y, a, n, t);				// y = a^t mod n
				
		if (mpz_cmp_ui(y,1) != 0  && mpz_cmp(y,n2) != 0){		//si y != 1 et y != - 1
				mpz_set_ui(j,0);
				
				while((mpz_cmp(j,s1) <= 0) && (res == 1))		// Tant que j <= s - 1 ou res == 1 
				{	
					puissance(y, y, deux);			// y = y²
					mpz_mod(y,y,n);					// y = y  mod n		
					mpz_add_ui(j,j,1);					//j++
					
					if(mpz_cmp(y,n2) == 0) break;		// y = -1 

					if(mpz_cmp_ui(y,1) == 0) 				// y = 1 
					{
						res = 0;
						break;
					}		
				}
			if(mpz_cmp(y,n2) != 0) 			//y != -1
			{
					res = 0;
					break;
			}	
		}
		mpz_add_ui(i,i,1);			//i++
	}
	
	mpz_clear(s);
	mpz_clear(s1);
	mpz_clear(t); 
	mpz_clear(a); 
	mpz_clear(i);
	mpz_clear(j);
	mpz_clear(y);
	gmp_randclear (gmpRandState);
	
	return res;
}


int main(int argc, char **argv)
{
	if(argc != 3){
		printf("Nombre d'arguments insuffisants\n");
		exit(EXIT_FAILURE);
	}
	
	mpz_t n, mod,k;
	mpz_init_set_str(n,argv[1],10);
	mpz_init_set_str(k,argv[2],10);
	mpz_init(mod);
	mpz_mod_ui(mod, n, 2);
	
	if(mpz_cmp_ui(k,0) <= 0 || mpz_cmp_ui(n,0) <= 0) {				//si k <= 0 ou n <= 0
		printf("Valeur invalide \n");
		exit(EXIT_FAILURE);
	}
	
	if(Test_Miller_Rabin(n,k)==1)
		printf("Premier\n");
	else
		printf("Composé\n");

	mpz_clear(n);
	mpz_clear(mod);
	mpz_clear(k);
	return 0;
}

