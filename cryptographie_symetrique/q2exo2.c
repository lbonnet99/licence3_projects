#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void affichage_tableau(int * T, int n)
{
	for (int i = 0; i < n; i++)
	{
		printf("%d",T[i]);
	}
	printf("\n");
}

//fonction pour appliquer <<<7 à un tableau t de 32 bits
void decalage_7(int* t){
	int tmp[7]; //tableau qui sauvegarde temporairement les 7 premiers bits 
	int i;
	for(i=0;i<7;i++){
		tmp[i] = t[i];//stocker temporairement les 7 premiers bits
	}

	for(i=0;i<25;i++){
		t[i] = t[i+7];//décaler les autres bits vers la gauche
	}
	for(i=25;i<32;i++){
		t[i] = tmp[i-25];//déplacer les 7 premiers bits à la fin du tableau
	}

}

void xor(int t1[32],int t2[32],int res[32]){
	for(int i=0;i<32;i++){
		res[i] = t1[i] ^ t2[i];

	}
}



void trouver_k0k1(int* x0_L, int* x0_R,int* x1_L, 
	int* x1_R,int* k0, int* k1){

	xor(x0_L,x0_R,k0);
	decalage_7(k0);
	xor(k0,x1_L,k0);

	xor(x1_L,x0_R,k1);
	decalage_7(k1);
	xor(k1,x1_R,k1);

}


int main(int argc, char const *argv[])//1er argument = texte_clair_L, 2eme argument = texte_clair_R
// 3eme argument = texte_chiffre_L, 4e argument = texte_chiffre_R
{
	if(argc < 5){
		printf("Nombre d'arguments insuffisants\n");
		exit(EXIT_FAILURE);
	}

	if(strlen(argv[1])<32 || strlen(argv[2])<32 || strlen(argv[3])<32 || strlen(argv[4])<32){
		printf("Erreur : taille des arguments < 32 bits\n");
		exit(EXIT_FAILURE);
	}

	int x0_L[32];
	int x0_R[32];
	int x1_L[32];
	int x1_R[32];

	//Conversion en tableau d'entiers
	
	//Pour x0_L, x0_R, x1_L et x1_R
	for (int i = 0; i < 32; i++)
	{
		if(argv[1][i] == '0') x0_L[i] = 0;
		else if(argv[1][i] == '1') x0_L[i] = 1;
		else
		{
			printf("ERREUR : caractère invalide\n");
			exit(EXIT_FAILURE);
		}
		
		if(argv[2][i] == '0') x0_R[i] = 0;
		else if(argv[2][i] == '1') x0_R[i] = 1;
		else
		{
			printf("ERREUR : caractère invalide\n");
			exit(EXIT_FAILURE);
		}
		
		if(argv[3][i] == '0') x1_L[i] = 0;
		else if(argv[3][i] == '1') x1_L[i] = 1;
		else
		{
			printf("ERREUR : caractère invalide\n");
			exit(EXIT_FAILURE);
		}

		if(argv[4][i] == '0') x1_R[i] = 0;
		else if(argv[4][i] == '1') x1_R[i] = 1;
		else
		{
			printf("ERREUR : caractère invalide\n");
			exit(EXIT_FAILURE);
		}
	}
	


	int* k0 = calloc(32,sizeof(int));
	int* k1 = calloc(32,sizeof(int));

	//afficher x0L
	printf("x0_L = \n");
	affichage_tableau(x0_L,32);

	//afficher x0R
	printf("x0_R = \n");
	affichage_tableau(x0_R,32);

	//afficher x1L
	printf("x1_L = \n");
	affichage_tableau(x1_L,32);

	//afficher x0R
	printf("x1_R = \n");
	affichage_tableau(x1_R,32);



	trouver_k0k1(x0_L,x0_R,x1_L,x1_R,k0,k1);



	//afficher k0
	printf("k0 = \n");
	affichage_tableau(k0,32);

	//afficher k1
	printf("k1 = \n");
	affichage_tableau(k1,32);

	free(k0);
	free(k1);
	return 0;
}