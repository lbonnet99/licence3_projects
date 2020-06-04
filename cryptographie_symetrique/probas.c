#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void affichage_tableau(int * T, int n)
{
	for (int i = 0; i < n; i++)
	{
		printf("%d",T[i]);
	}
	printf("\n");
}


void conversion_decimal_a_binaire(int a, int T2[],int n) 
//a entier décimal
//T2 tableau de bits à remplir
//n taille du tableau T2 à remplir

{

	int* T = malloc(n*sizeof(int));
	T[n-1] = 1;
	//placer les bits de poids faible à droite et bits de poids fort à gauche
	for(int i = n-2; i>=0;i--){
		T[i] = 2*T[i+1];

	}//remplir le tableau en T en puissance de 2

	for (int j=0;j<n;j++)
	{	
		if(a < T[j])
		{
			T2[j] = 0;
		}
		else 
		{
			T2[j] = 1;
			a = a - T[j];
		}
	}
	free(T);
}

float calcul_proba_F_donne(int F[], int x[]){
	//tableau F de la fonction filtrage
	//tableau X correspond à la sortie d'un LFSR

	int numerateur= 0;
	for(int i=0;i<8;i++)
	{

		if(F[i]==x[i])
			numerateur++;
	}

	return numerateur/(8.0);
}

void calcul_proba_ts_F(){
	int F[8]; //tableau de la fonction de filtrage
	int x0[8] = {0,1,0,1,0,1,0,1};
	int x1[8] = {0,0,1,1,0,0,1,1};
	int x2[8] = {0,0,0,0,1,1,1,1};
	for(int i=0;i<256;i++) //pour toutes les possibilités de fonction de filtrage
	{
		conversion_decimal_a_binaire(i,F,8);//transformer i sous forme binaire dans le tableau F
		affichage_tableau(F,8);
		float px0 = calcul_proba_F_donne(F,x0);
		printf("P(x0 = si) = %f \n", px0);
		printf("#####################################\n");		

		float px1 = calcul_proba_F_donne(F,x1);
		printf("P(x1 = si) = %f \n", px1);
		printf("#####################################\n");

		float px2 = calcul_proba_F_donne(F,x2);
		printf("P(x2 = si) = %f \n", px2);
		printf("#####################################\n");

	}

}




int main(){
	
	calcul_proba_ts_F();
	

}