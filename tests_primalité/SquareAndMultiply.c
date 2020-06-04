#include "SquareAndMultiply.h"


void puissance(mpz_t res, mpz_t a, mpz_t pow){
			
			mpz_t j,t, tmp1, tmp2; 
			
			mpz_init(tmp1);
			mpz_init(tmp2);
			
			mpz_init(t);
			mpz_init_set_str(j,"1",10);			//itérateur j à 1
			
			mpz_set(tmp1,a);					//tmp1 = a
			mpz_set(tmp2,pow);					//tmp2 = pow
			mpz_set(t,tmp1);					//t = a
			
			if(mpz_cmp_ui(pow,0)==0) mpz_set_ui (res, 1);		//si l'exposant vaut 0
			else{
				
					while(mpz_cmp(j,tmp2) < 0){				
						mpz_mul(tmp1, tmp1, t);				// tmp1 = tmp * a
						mpz_add_ui(j,j,1);					// j = j + 1
					}	
				
					mpz_set(res, tmp1);				//res = tmp1
			}
			mpz_clear(j);
			mpz_clear(t);
			mpz_clear(tmp1);
			mpz_clear(tmp2);
}

void SquareAndMultiply(mpz_t res, mpz_t a, mpz_t n, mpz_t H){
	//res = a^H mod n
	mpz_t r, deux;
	long unsigned int t = mpz_sizeinbase (H,2); // t = nombre de bits de H
	long int i;
	mpz_init_set(r,a);	//r = a
	mpz_init_set_ui(deux,2);
	

	for(i = t-2 ; i >= 0 ; i--){
		
		puissance(r,r,deux);	//r = r²
		mpz_mod(r,r,n);			//r = r mod n
		if(mpz_tstbit(H,i))		//si h(i) = 1 alors
		{
			mpz_mul(r,r,a);		//r = r*a
			mpz_mod(r,r,n);		//r = r mod n
		}	
			
	}
	if(mpz_cmp_ui(H,0) == 0) //si H = 0
		mpz_set_ui(res,1);	 //renvoyer 1
	else mpz_set(res,r);	 //sinon res = r
	
	mpz_clear(r);
	mpz_clear(deux);
}

