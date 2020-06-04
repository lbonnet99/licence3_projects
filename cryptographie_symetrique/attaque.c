#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct element
{
    int cle ;
    struct element * suivant ;
};
typedef struct element element;

void initialiser_liste(element * liste){
	
	liste->suivant = NULL;
	liste->cle = -1;
	
}

void insertion(element* liste, int cle)
{
    /* Création du nouvel élément */
   
    element * nouveau = malloc(sizeof(element));
   
    if (liste == NULL || nouveau == NULL)
    {
		printf("erreur\n");
        exit(EXIT_FAILURE);
    }
    
    nouveau->cle = liste->cle;
	nouveau->suivant = liste->suivant;
   
    
    liste->suivant = nouveau;
    liste->cle = cle;
    
}

void affichage_tableau(int * T, int n)	
{
	for (int i = 0; i < n; i++)
	{
		printf("%d",T[i]);
	}
	printf("\n");
}

float correlation(int *Suite, int *L1,int taille){	//renvoie une probabilité de corrélation entre Suite et L1
	float compteur = 0.000 ;
	for(int i = 0 ; i < taille ; i++){
		if(L1[i] == Suite[i]) compteur += 1 ;
			
	}
	
	return compteur/taille ;
}

int comparer(float p1, float p2){		//compares deux probabilités et renvoie 1 si p1 est proche de p2
	float tmp = 0.05;
	if((p1 < p2 + tmp) && (p1 > p2 - tmp)) return 1;		//definir intervalle
	return 0;
}


void conversion_decimal_a_binaire(int a, int T2[],int n) { //convertis un nombre entier en binaire sous forme de tableau d'entiers avec comme valeur des 0 et des 1
//n taille du tableau T2 à remplir


	int* T = malloc(n*sizeof(int));
	T[n-1] = 1;
	//placer les bits de poid faible à droite et bits de poid fort à gauche
	for(int i = n-2; i>=0;i--){
		T[i] = 2*T[i+1];

	}

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


int retroL0(int T[16]) 	//Cacule le dernier bit du premier LFSR en fonction des coefficients de rétro-action
{
	return T[15]^T[14]^T[11]^T[8];
}

int retroL1(int T[16]) //Cacule le dernier bit du deuxième LFSR en fonction des coefficients de rétro-action
{
	return T[15]^T[14]^T[8]^T[4];
}

int retroL2(int T[16]) //Cacule le dernier bit du troisième LFSR en fonction des coefficients de rétro-action
{
	return T[15]^T[13]^T[12]^T[10];
}


void decalage(int*L, int bit_calcule)	//Décale le LFSR représenté par L et ajoute bit_calcule à la dernière valeur
{		
	for(int i = 15;i>0; i--)
	{
		L[i] = L[i-1];
	}
	
	L[0] = bit_calcule;
}


int filtrage(int T[8] , int x, int y , int z)	//Sort une valeur en à l'aide de la fonction de filtraage représenté par F qui prend en entrée les 3 valeurs x,y et z
{	
	int w = -1; 
	
	if((x==0) && (y==0) && (z==0)) w = T[0];
	if((x==1) && (y==0) && (z==0)) w = T[1];
	if((x==0) && (y==1) && (z==0)) w = T[2];
	if((x==1) && (y==1) && (z==0)) w = T[3];
	if((x==0) && (y==0) && (z==1)) w = T[4];
	if((x==1) && (y==0) && (z==1)) w = T[5];
	if((x==0) && (y==1) && (z==1)) w = T[6];
	if((x==1) && (y==1) && (z==1)) w = T[7];
	
	if((w != 0) && (w!=1)) printf("ERREUR : Table de filtrage invalide\n") ;
	return w ;
}

int * generateur(int F[8], int k0[16], int k1[16], int k2[16], int n)	//Génére une suite chiffrante gràace à 3 tableaux représentant les LFSR et un tableau de taille 8 correspondant à la fonction de filtrage
{
	int * res = malloc(sizeof(int)*n);
	int bit_calcule_L0, bit_calcule_L1, bit_calcule_L2;
	
	for(int i = 0; i<n; i++)
	{
		res[i] = filtrage(F,k0[15],k1[15],k2[15]);
		bit_calcule_L0 = retroL0(k0);
		bit_calcule_L1 = retroL1(k1);
		bit_calcule_L2 = retroL2(k2);
		decalage(k0,bit_calcule_L0);
		decalage(k1,bit_calcule_L1);
		decalage(k2,bit_calcule_L2);
	}
	
	return res;
}

int main(int argc, char **argv)	//argv 1 = suite chiffrante 
{	
	if(argc < 2) {		//executable + suite chiffrante
		printf("Nombre d'arguments insuffisants\n");	
		exit(1);
	}

	int taille = strlen(argv[1]);	//taille de la suite
	if(taille < 16) { 				//pour que chaque LFSR soient remplis
		 printf("Taille insuffisante\n");
		 exit(1);
	 }
	int * suite = malloc(sizeof(int) * taille );	//tableau d'entiers qui va contenir la suite
	for(int i = 0 ; i < taille ; i++ ) 				
	{
		if(argv[1][i] == '0') suite[i] = 0;			//suite en string -> tableau d'entiers 
		else if(argv[1][i] == '1') suite[i] = 1;
		else
		{
			printf("ERREUR : Caractère invalide\n");	//si la suite n'est pas composée de 0 ou de 1
			exit(1);
		}
	}
	
	//Itérateurs
	int i = 0;
	int k = 0; 
	int l = 0;
	
	//Liste des potentiels clés pour chaque LFSR
	element * liste1 = malloc(sizeof(element));
	if(liste1 == NULL) exit(EXIT_FAILURE);
	initialiser_liste(liste1);
	element * liste2 = malloc(sizeof(element));
	if(liste1 == NULL) exit(EXIT_FAILURE);
	initialiser_liste(liste2);
	element * liste3 = malloc(sizeof(element));
	if(liste1 == NULL) exit(EXIT_FAILURE);
	initialiser_liste(liste3);
	
	
	int taille1 = 0;
	int taille2 = 0;
	int taille3 = 0;

	//Probabilités de corrélations
	float proba1 = 0.25 ;	//proba correlation du LFSR1
	float proba2 = 0.25 ;	//proba correlation du LFSR2
	float proba3 = 0.75 ;	//proba correlation du LFSR3
	
	//Variables temporaires
	int bit_calcule_L0 = 0; 
	int bit_calcule_L1 = 0; 
	int bit_calcule_L2 = 0; 

	//Tableaux représentant les LFSR
	int LFSR1[16];
	int LFSR2[16];
	int LFSR3[16];
	
	//Sortie de chaque LFSR
	int * sortieLFSR1 = malloc(sizeof(int) * taille);
	int * sortieLFSR2 = malloc(sizeof(int) * taille);
	int * sortieLFSR3 = malloc(sizeof(int) * taille);
	
	
	
	
	//LFSR1
	for (i = 0 ; i < 65536; i++)		//De 0 à (2 puissance 16) - 1  
	{	
		conversion_decimal_a_binaire(i , LFSR1 , 16);		//Passage entier -> binaire 
		for(int j = 0; j < taille ; j++){				//On génère autant de bits que dans la suite chiffrante 
			bit_calcule_L0 = retroL0(LFSR1);			//On calcule le dernier bit
			sortieLFSR1[j] = LFSR1[15];	//Probleme ?? On doit sortir le premier bit
			decalage(LFSR1,bit_calcule_L0);
		}
		float correl = correlation(suite,sortieLFSR1,taille);
		int comp = comparer(correl,proba1);	//On compare le coefficient de corrélation(proba1) avec la corrélation entre les 2 suites
		if(comp == 1)
		{ 
			taille1++;
			insertion(liste1,i);	//On insère dans la liste des potentiels clés
		}
	}	
	
		

	//LFSR2
	for (k = 0 ; k < 65536; k++)
	{	
		conversion_decimal_a_binaire(k , LFSR2 , 16);		
		
		for(int j = 0; j < taille ; j++){
			bit_calcule_L1 = retroL1(LFSR2);
			sortieLFSR2[j] = LFSR2[15];
			decalage(LFSR2,bit_calcule_L1);
		}
			float correl = correlation(suite,sortieLFSR2,taille);
			
			int comp = comparer(correl,proba2);
		if(comp == 1)
		{ 	
			taille2++;
			insertion(liste2,k);
			
		}
	}	


	//LFSR3
	for (l = 0 ; l < 65536; l++)
	{	
		conversion_decimal_a_binaire(l , LFSR3 , 16);		
		
		for(int j = 0; j < taille ; j++){
			bit_calcule_L2 = retroL2(LFSR3);
			sortieLFSR3[j] = LFSR3[15];
			decalage(LFSR3,bit_calcule_L2);
		}
			float correl = correlation(suite,sortieLFSR3,taille);
			int comp = comparer(correl,proba3);
		if(comp == 1)
		{ 	
			taille3++;
			insertion(liste3,l);
		}
	}	
	//On vérifie si il y a au moisn une clé potentielle pour chaque LFSR
	if((taille1 == 0) || (taille2 == 0) || (taille3 == 0)){
		printf("Pas assez de clé\n");
		exit(0);
	}
	
	
	printf("\n On a = %d clés possibles pour le premier LFSR\n", taille1);
	printf("On a = %d clés possibles pour le deuxième LFSR\n", taille2);
	printf("On a = %d clés possibles pour le troisième LFSR\n", taille3);
	
	
	
	int arret = 1;
	int F[8] = {1,0,0,0,1,1,1,0};
	int * TestSuite = malloc(sizeof(int) * taille);
	

	element * copieliste1 = liste1;
	element * copieliste2 = liste2;
	element * copieliste3 = liste3;
	
	
int count = 0;

    for(int i = 0 ; i < taille1 && arret == 1 ; i++){
		
		conversion_decimal_a_binaire(copieliste1->cle , LFSR1 , 16);
		for(int k = 0 ; k < taille2 && arret == 1 ; k++){
			
			conversion_decimal_a_binaire(copieliste2->cle , LFSR2 , 16);

			for(int l = 0 ; l < taille3 && arret == 1 ; l++){
				
				
				conversion_decimal_a_binaire(copieliste3->cle , LFSR3 , 16);
				TestSuite = generateur(F,LFSR1,LFSR2,LFSR3,taille);	
				float correl = correlation(suite,TestSuite,taille);
				float egal = 1.0;
				
				
				
				if(correl == egal){
					arret = 0;
					printf("k0 = ");
					affichage_tableau(LFSR1,16);
					printf("k1 = ");
					affichage_tableau(LFSR2,16);
					printf("k2 = ");
					affichage_tableau(LFSR3,16);
				}
				count++;
				
				copieliste3 = copieliste3->suivant;
			}
			copieliste3 = liste3;
			copieliste2 = liste2->suivant;
		}
		copieliste2 = liste2;
		copieliste1 = liste1->suivant;
	}
	
if(arret == 1) printf("On a pas trouvé d'initialisation clés");

	
	//Libération de la mémoire
	free(suite);
	free(TestSuite);
	free(sortieLFSR1);
	free(sortieLFSR2);
	free(sortieLFSR3);
	
	
	while(liste1 != NULL){
		element * tmp = liste1;
		liste1 = liste1->suivant ;
		free(tmp);
	}
	while(liste2 != NULL){
		element * tmp = liste2;
		liste2 = liste2->suivant ;
		free(tmp);
	}
	while(liste3 != NULL){
		element * tmp = liste3;
		liste3 = liste3->suivant ;
		free(tmp);
		
	}
	return 0;
}

