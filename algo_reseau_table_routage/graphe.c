#include "graphe.h"

GRAPHE init_GRAPHE(int n)
{
	GRAPHE G;
	
	G.nb_sommets = n;
	
	G.tab = malloc(n*sizeof(NOEUD));
	if(!G.tab)
	{
		fprintf(stderr,"échec allocation de mémoire pour le graphe");
		exit(EXIT_FAILURE);
		
	}
	
	for(int i=0;i<n;i++)
	{
		G.tab[i].type = 0;
		G.tab[i].voisins = init_LISTE();
	}
	
	return G;
}

/*
//exemple graphe à 5 sommets
GRAPHE init_GRAPHE()
{
	GRAPHE G;
	
	G.nb_sommets = 5;
	
	G.tab = malloc(5*sizeof(NOEUD));
	if(!G.tab)
	{
		fprintf(stderr,"échec allocation de mémoire pour le graphe");
		exit(EXIT_FAILURE);
		
	}
	
	for(int i=0;i<5;i++)
	{
		G.tab[i].type = 0;
		G.tab[i].voisins = init_LISTE();
	}
	
	return G;
}*/



//Initialiser les liens du backbone
GRAPHE backbone(GRAPHE G)
{
	int nb;
	
	for(int i=0;i<8;i++)
	{
		for(int j=0;j<8;j++)
		{
			G.tab[i].type = 1;
			
			if(i<j)
			{
				if((rand()%1001) <= (0.75*1000))
				{
					nb=rand()%6+5; // valeur aléatoire entre 5 et 10
					G.tab[i].voisins = add_LISTE(G.tab[i].voisins,j,nb);
//ajouter à la liste G.tab[i].voisins l'élément qui a pour noeud j et le lien nb 
					
					G.tab[j].voisins = add_LISTE(G.tab[j].voisins,i,nb);

				}
			}
		}
	}
	
	return G;
}
/*
GRAPHE exemple(GRAPHE G)
{
	
	G.tab[0].voisins = add_LISTE(G.tab[0].voisins,1,3);
	G.tab[0].voisins = add_LISTE(G.tab[0].voisins,3,5);
	
	G.tab[1].voisins = add_LISTE(G.tab[1].voisins,0,3);
	G.tab[1].voisins = add_LISTE(G.tab[1].voisins,2,3);
	G.tab[1].voisins = add_LISTE(G.tab[1].voisins,3,1);
	
	G.tab[2].voisins = add_LISTE(G.tab[2].voisins,1,3);
	G.tab[2].voisins = add_LISTE(G.tab[2].voisins,4,2);
	
	G.tab[3].voisins = add_LISTE(G.tab[3].voisins,0,5);
	G.tab[3].voisins = add_LISTE(G.tab[3].voisins,1,1);
	G.tab[3].voisins = add_LISTE(G.tab[3].voisins,4,7);
	
	G.tab[4].voisins = add_LISTE(G.tab[4].voisins,2,2);
	G.tab[4].voisins = add_LISTE(G.tab[4].voisins,3,7);
	
	return G;
}*/



//Savoir si un noeud est déjà voisin d'un autre
int est_voisin(GRAPHE G,int sommet,int voisin_possible)
{
	LISTE l = G.tab[sommet].voisins;	
	while(l != NULL)
	{
		if(l -> noeud == voisin_possible) return 1;
		l = l ->suivant;
	}	
	return 0;
}

//Compter le nombre de noeud de type 2
int nb_noeud_niv2(GRAPHE G,int sommet)
{
	LISTE l = G.tab[sommet].voisins;
	int n,nb_nn2=0;
	
	while(l != NULL)
	{
		n=l->noeud;
		if(G.tab[n].type == 2) nb_nn2+=1;
		l = l ->suivant;
	}
	
	return nb_nn2;
}

//Initialialiser les liens de noeuds de type 2 avec ceux du backbone
GRAPHE lien_niv1(GRAPHE G)
{
	int noeud1,num,num2,valeur;
	
	for(int i=8;i<28;i++)
	{
		G.tab[i].type = 2;

		noeud1 = rand()%2+1;
	
		if(noeud1 == 1)
		{
			num = rand()%8;
			valeur = rand()%11+10;
			G.tab[i].voisins = add_LISTE(G.tab[i].voisins,num,valeur);
			G.tab[num].voisins = add_LISTE(G.tab[num].voisins,i,valeur);
		}else if(noeud1==2)
		{
			num = rand()%8;
			valeur = rand()%11+10;
			G.tab[i].voisins = add_LISTE(G.tab[i].voisins,num,valeur);
			G.tab[num].voisins = add_LISTE(G.tab[num].voisins,i,valeur);
			num2 = rand()%8;
			while(num==num2){num2=rand()%8;}
			valeur = rand()%11+10;
			G.tab[i].voisins = add_LISTE(G.tab[i].voisins,num2,valeur);
			G.tab[num2].voisins = add_LISTE(G.tab[num2].voisins,i,valeur);
		}
		
	}
	
	return G;
}

//Initialiser les liens des noeuds de type 2 avec ceux de type 2
GRAPHE lien_niv2(GRAPHE G)
{
	int noeud2,num,valeur;
	
	for(int i=8;i<28;i++)
	{	
		noeud2 = rand()%2+2;
		while(nb_noeud_niv2(G,i) < noeud2)
		{
			num = rand()%20+8;
			while((nb_noeud_niv2(G,num)==3) || (num==i) || (est_voisin(G,i,num))) num = rand()%20+8;
			
			valeur = rand()%11+10;
			G.tab[i].voisins = add_LISTE(G.tab[i].voisins,num,valeur);
			G.tab[num].voisins = add_LISTE(G.tab[num].voisins,i,valeur);
		}
		
	}
	
	return G;
}

//Initialiser les noeuds de type 2
GRAPHE op_transit(GRAPHE G)
{
	G = lien_niv1(G);
	G = lien_niv2(G);
	return G;
}

//Compter le nombre de noeud de type 3 pour un sommet donné
int nb_noeud_niv3(GRAPHE G,int sommet)
{
	LISTE l = G.tab[sommet].voisins;
	int n,nb_nn3=0;
	
	while(l != NULL)
	{
		n=l->noeud;
		if(G.tab[n].type == 3) nb_nn3+=1;
		l = l ->suivant;
	}
	
	return nb_nn3;
}

//Initialiser les noeuds de type 3
GRAPHE op_niv3(GRAPHE G)
{
	int num,num2,valeur;
	
	for(int i=28;i<100;i++)
	{
		G.tab[i].type = 3;
		
		num = rand()%20+8;
		num2 = rand()%20+8;
		while((num==num2) || (est_voisin(G,i,num)) || (est_voisin(G,i,num2))){num=rand()%20+8; num2=rand()%20+8;}
		
		valeur = rand()%36+15;
		G.tab[i].voisins = add_LISTE(G.tab[i].voisins,num,valeur);
		G.tab[num].voisins = add_LISTE(G.tab[num].voisins,i,valeur);
			
		valeur = rand()%36+15;
		G.tab[i].voisins = add_LISTE(G.tab[i].voisins,num2,valeur);
		G.tab[num2].voisins = add_LISTE(G.tab[num2].voisins,i,valeur);
	}
	
	for(int i=28;i<100;i++)
	{
		if(nb_noeud_niv3(G,i)==0)
		{
			num = rand()%72+28;
			while((num==i)||(nb_noeud_niv3(G,num)>=1)) num = rand()%72+28;
			G.tab[i].voisins = add_LISTE(G.tab[i].voisins,num,valeur);
			G.tab[num].voisins = add_LISTE(G.tab[num].voisins,i,valeur);
		}
	}
	return G;
}



TABLE ajout_element(TABLE b, int sommet, int distance, int pere)
{
	
	TABLE new;
	new = malloc(sizeof(struct table));
	new->sommet = sommet;
	new->distance = distance;
	new->pere = pere;
	new->suivant = b;

	return new;	
}

// retourne la distance d'un sommet à son père
int distance(GRAPHE G, int sommet, int pere)
{
	if(sommet==pere) return 0; // la distance d'un sommet à lui-même = 0
	LISTE l = G.tab[pere].voisins;
	while(l!=NULL )
	{
		if(l->noeud==sommet)
			return l->lien;
		l = l->suivant;
	}
	return 2500; // si sommet et père ne sont pas voisins donc père n'est pas le père de sommet
	
}



// initialisation algorithme de Dijsktra
TABLE initialisation_Dijkstra(GRAPHE G,int sommet)
{
	TABLE t = NULL;
	
	// distance minimale pour pouvoir déterminer le prochain sommet à traiter
	int minimum = distance(G,G.tab[sommet].voisins->noeud,sommet);
	
	
	int i;
	for(i=G.nb_sommets-1;i>=0;i--)
	{
		if(i!=sommet)//pour ne pas traiter le sommet à lui-même
		{
		
			if(est_voisin(G,sommet,i))
			{
				t = ajout_element(t,i,distance(G,i,sommet),sommet);	
				if(distance(G,i,sommet)<minimum)
				{
					minimum = distance(G,i,sommet);
				}
			}
			else
				t = ajout_element(t,i,distance(G,i,sommet),-1);
		}
		else //traiter le sommet à lui-même
		{
			t = ajout_element(t,i,distance(G,i,sommet),sommet);
		}		
	}	
	return t;
}



//donner le père d'un sommet 
int pere(TABLE t, int sommet)
{
	while(t!=NULL)
	{
		if(t->sommet==sommet)
			return t->pere;
		t = t->suivant;
	}
	
	return -5;//retourner une valeur impossible du pere pour montrer que le sommet passé en argument n'existe pas
	
}

int distance_sommet(TABLE t, int sommet) // récupérer la valeur distance du sommet
{
	
	while(t!=NULL)
	{
		if(t->sommet==sommet)
			return t->distance;
		t = t->suivant;
	}
	
	return -5;//retourner une valeur impossible d'une distance pour montrer que le sommet passé en argument n'existe pas
	
	
}

int tous_les_sommets_traites(int T[100]) // tester si tous les sommets sont traités
{
	for(int i=0;i<100;i++)
	{
		if(T[i]==0)
			return 0;
	}
	return 1;
	
}

int sommet_non_traite(int T[100], int sommet)
// tester si le sommet est traité
{
	
	if(T[sommet]==0)
		return 1;
	return 0;
}

int premier_sommet_a_traiter(int T[100])
{
	int i;
	for(i=0;i<100;i++)
	{
		if(sommet_non_traite(T,i))
			return i;
		
	}
	
	return -6; // tous les sommets sont déjà traités
}

int prochain_sommet_a_traiter(int T[100],TABLE t)
{
	int proch_sommet = premier_sommet_a_traiter(T);
	int dist_min;
	TABLE new = t;
	while(new!=NULL)
	{
		if(new->sommet==proch_sommet)
			dist_min = new->distance;
		new = new->suivant;
	}// parcourir la table jusqu'au premier sommet potentiel à traiter
	
	new = t;
	while(new!=NULL)
	{
		if((new->distance<dist_min)&&(T[new->sommet]==0))
		{
			proch_sommet = new->sommet;
			dist_min = new->distance;
		}
		new = new->suivant;
	}
	return proch_sommet;
	
}


// sommet source de départ
TABLE b_p_d(GRAPHE G, TABLE t, int source)
{
	TABLE new = t;
	int T[G.nb_sommets]; //tableau pour gérer les sommets traités
	int i;
	for(i=0;i<G.nb_sommets;i++)
	{
		if(i==source)
			T[i] = 1;//mettre comme étant sommet traité le sommet source
		else
			T[i] = 0;
	}
	int sommet_a_traiter = prochain_sommet_a_traiter(T,new); //sommet non traité précédemment et minimum

	while(tous_les_sommets_traites(T)==0)
	{
		T[sommet_a_traiter] = 1;
		while(new!=NULL)
		{
			if(est_voisin(G,sommet_a_traiter,new->sommet)
			&&(sommet_non_traite(T,new->sommet))) // si c'est le cas on compare la distance
			{
				if((distance(G,new->sommet,sommet_a_traiter) + distance_sommet(t,sommet_a_traiter))
				<distance_sommet(t,new->sommet)) // si la distance est plus petite on modifie sinon non
					{
					new->distance = distance(G,new->sommet,sommet_a_traiter) + distance_sommet(t,sommet_a_traiter);
					new->pere = sommet_a_traiter;
					}
			}
			new = new ->suivant;
		}
		new = t;
		sommet_a_traiter = prochain_sommet_a_traiter(T,t);
	}
	return t;	
}


void affiche_table(TABLE b)
{
	while(b!=NULL)
	{
		printf("sommet : %2d, distance : %d, père : %d\n",b->sommet,b->distance,b->pere);
		b = b->suivant;
	}
	
}



//algo de dijkstra à appliquer pour tous les noeuds du graphe
TABLE* calcul_table_routage_all_noeuds (GRAPHE G)
{
	TABLE * routage = malloc(100*sizeof(TABLE));

	int i ;
	for(i=0;i<G.nb_sommets;i++)
	{
		routage[i] = initialisation_Dijkstra(G,i);
	}
	
	for(i=0;i<G.nb_sommets;i++)
	{
		routage[i] = b_p_d(G,routage[i],i);
		
	}
	return routage;
	
}

void chemin(TABLE*T,int emetteur, int destinataire)
{
	
	if(emetteur>99 ||emetteur <0
	||destinataire>99 ||destinataire <0)
	{
		printf("Le destinataire et l'emetteur doivent être compris en 0 et 100");
		return;		
	}
	TABLE emet = T[emetteur];
	int dest = destinataire;
	
	printf("chemin entre %d et %d : ",emetteur,destinataire);
	while(pere(emet,dest)!=emetteur)
	{
		printf("%d <-- %d ",dest,pere(emet,dest));
		dest = pere(emet,dest);
	}
	
	printf("%d <-- %d\n",dest,emetteur);	
}


void explorer_sommet(GRAPHE G,int*couleur,int sommet)
{
	couleur[sommet] =1;
	LISTE l = G.tab[sommet].voisins;
	while(l!=NULL)
	{
		if(couleur[l->noeud]==0)
			explorer_sommet(G,couleur,l->noeud);
		l = l->suivant;
	}
}

int est_connexe(GRAPHE G)
{
	int* couleur = calloc(G.nb_sommets,sizeof(int));
	explorer_sommet(G,couleur,0);
	for(int i=0;i<G.nb_sommets;i++)
	{
		if(couleur[i]!=1)
			return 0;
	}
	
	return 1;
}
