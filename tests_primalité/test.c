#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>
#include "SquareAndMultiply.h"

int main(int argc, char **argv)
{
	//mpz_t m;
	mpz_t H,res,a,n;
	mpz_init(res);
	mpz_init_set_str(a,"2",10);
	mpz_init_set_str(n,"9",10);
	mpz_init_set_str(H,"1000",2);

	SquareAndMultiply(res,a,n,H);

	gmp_printf("resultat = %Zd\n",res);
	gmp_printf("H = %Zd\n",H);
	mpz_clear(H);
	mpz_clear(res);
	mpz_clear(a);
	mpz_clear(n);


	/*
	mpz_init(m);
	//mpz_set_ui(m,255);
	char * i = NULL,*j;
	j = malloc(sizeof(char));
	//j = mpz_get_str(i,2,m);
	//printf("%s\n",j);
	mpz_set_ui(m,255);
	printf("%lu\n",mpz_sizeinbase (m,2));
	mpz_clear(m);
	free(i);
	free(j);*/
	return 0;
}

