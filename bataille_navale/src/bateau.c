#include "bateau.h"
#include "navalmap.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <pthread.h>

#define equipe 2

bateau* init_bateau (
	const int							Cmax,
	const int							Kmax,
	const int							nbShips) 
{
	bateau *b=malloc (nbShips * sizeof (bateau ) );
	int i;
    for(i=0;i<nbShips;i++)
    {
		b[i].coque = Cmax;
		b[i].kero = Kmax;
		b[i].ID = i;
	}
	return b;
}

void free_bateau (
	bateau	* b) {

	free (b);
}

void aucune_action(navalmap_t* nmap,
	const int	shipID,bateau* b)
{
	b[shipID].kero = b[shipID].kero - 1;
	printf("   aucune_action: J%d utilise 1K. reste: %dK.\n",shipID,b[shipID].kero);
}

int deplacement_impossible(navalmap_t* nmap,
	const int	shipID,
	const coord_t	moveVec,bateau* b)
	
{
	//position où le navire souhaite se déplacer
	coord_t pos;
	pos.x = nmap->shipPosition[shipID].x + moveVec.x; pos.y = nmap->shipPosition[shipID].y +moveVec.y;
	
	
	//il faut que le vecteur de deplacement soit d'une distance comprise entre 1 et2
	if ((abs(moveVec.x)+abs(moveVec.y))<1 || (abs(moveVec.x)+abs(moveVec.y))>2)
    {
        printf("   deplacement: le vecteur de deplacement doit avoir une distance comprise entre 1 et 2.\n");
        aucune_action(nmap,shipID,b);
        return 1;
    }
	
	//si en dehors de la carte navale
	if(pos.x>nmap->size.x-1 || pos.x<0 || pos.y<0 || pos.y>nmap->size.y-1)
	{
		printf("   deplacement impossible : en dehors carte navale\n");
		aucune_action(nmap,shipID,b);
		return 1;
	}
	
	return 0;
}



void deplacement(navalmap_t* nmap,
	const int	shipID,
	const coord_t	moveVec,bateau* b)
{
	if(deplacement_impossible(nmap,shipID,moveVec,b))
		return;
		
	//position où le navire souhaite se déplacer
	coord_t pos;
	pos.x = nmap->shipPosition[shipID].x + moveVec.x; pos.y = nmap->shipPosition[shipID].y +moveVec.y;
	
	//s'il y a déjà un bateau sur la case
	if((nmap->map[pos.y][pos.x] ).type == ENT_SHIP)
	{
		int ID = nmap->map[nmap->shipPosition[shipID].y +moveVec.y][nmap->shipPosition[shipID].x + moveVec.x] .id;
		b[ID].coque = b[ID].coque - 5; //bateau présent sur la case
		b[shipID].coque = b[shipID].coque - 5;//bateau qui voulait se déplacer sur la case présente
		printf("    deplacement impossible : J%d et J%d ont perdu 5C. reste : %dC et %dC\n",ID,shipID,b[ID].coque,b[shipID].coque);
		return;
	}
		
	moveShip(nmap,shipID,moveVec);

	b[shipID].kero = b[shipID].kero-2;	
	printf("   J%d se deplace en (%d,%d) utilise 2K. reste: %dK.\n",shipID,pos.x,pos.y,b[shipID].kero);
}

void attaque(navalmap_t	* nmap,
	const int shipID,
	const coord_t	pos,bateau* b)
{
    if((shipID)>=(nmap->nbShips))
    {
        return;
    }

	b[shipID].kero = b[shipID].kero-5;
	printf("   J%d attaque en (%d,%d) utilise 5K. reste: %dK. -> ",shipID,pos.x,pos.y,b[shipID].kero);

	//il faut que la cible soit a une distance entre 2 et 4 de la position courante
	int x0 = nmap->shipPosition[shipID].x; int y0 = nmap->shipPosition[shipID].y;
	int x1 = pos.x; int y1 = pos.y;
	int dx = abs(x1 - x0);int dy = abs(y1 - y0);
	if ((dx+dy)<2 || (dx+dy) >4)
    {
        printf("   attaque: la position cible n'est pas a une distance entre 2 et 4 de la position courante.\n");
        return;
    }

    //navires presents sur la case cible
    int nbShips=0, iShip=0;
    int *list = rect_getTargets (nmap,pos,0,&nbShips);
    if(nbShips>0)
    {
        for (iShip=0; iShip<nbShips; iShip++)
        {
            int id = list[iShip];
            b[id].coque = b[id].coque - 40;
            printf("J%d subit 40C . reste: %dC.\n",id,b[id].coque);
        }
	}
	free(list);

	//navires presents sur une case adjacente en croix
	int nbShips2=0, iShip2=0;
	int *list2 = rect_getTargets (nmap,pos,1,&nbShips2);
	if (nbShips2>0)
	{
	    for (iShip2=0; iShip2<nbShips2; iShip2++)
        {
            int id = list2[iShip2];
            b[id].coque = b[id].coque - 20;
            printf("J%d subit 20C reste: %dC.\n",id,b[id].coque);
        }
	}
	free(list2);


	if (nbShips==0 && nbShips2==0)
    {
        printf("aucune cible touchee. \n");
    }

}

int id_bateau_plus_proche(navalmap_t *nmap, int shipID,bateau*b)
{
	int* liste = malloc ((nmap->nbShips)*sizeof(int));
	int ID = b[shipID].ID;
	coord_t pos_b; // récupérer position du bateau b
	pos_b = nmap->shipPosition[ID];
	int nb_ship = 0;

	int i = 1;
	int result = -1;

   while(1)
    {
        liste = rect_getTargets(nmap,pos_b,i,&nb_ship);
        if(nb_ship>0)
        {
            // meme s'il y a plusieurs bateaux a la distance d, on prend le 1er
            result = liste[0];
            free(liste);
            return result;
        }
        i++;
    }

	return -1; // en cas d'erreur (nombre de joueurs = 1)

}

coord_t radar_scn(navalmap_t *nmap,int shipID,bateau*b, int* coque, int* kero, int*ID_b_proche)
{

	b[shipID].kero = b[shipID].kero -3;

	// ID_b_proche = id du bateau le plus proche
	*ID_b_proche = id_bateau_plus_proche(nmap,shipID,b);
	

	*coque = b[*ID_b_proche].coque; // coque du bateau le plus proche
	*kero = b[*ID_b_proche].kero; // kérosène du bateau le plus proche


	coord_t pos_b_t; //position du navire trouvé
	pos_b_t = nmap->shipPosition[*ID_b_proche];
	printf("    J%d radar : bateau plus proche : %d en (%d,%d) avec kero = %d et coque = %d\n",shipID,*ID_b_proche,pos_b_t.x,pos_b_t.y,*kero,*coque);
	return pos_b_t;
}

void charge(navalmap_t	*nmap,
	const int shipID,
	const coord_t pos,bateau *b)
{
    if((shipID)>=(nmap->nbShips))
    {
        return;
    }

	b[shipID].kero = b[shipID].kero-3;
	b[shipID].coque = b[shipID].coque-5;
	printf("   J%d charge utilise 3K et subit 5C. reste: %dK et %dC.\n",shipID,b[shipID].kero,b[shipID].coque);
	
    //il faut que la nouvelle position soit a une distance entre 4 et 5 de la position courante
	int x0 = nmap->shipPosition[shipID].x; int y0 = nmap->shipPosition[shipID].y;
	int x1 = pos.x; int y1 = pos.y;
	int dx = abs(x1 - x0);int dy = abs(y1 - y0);
	if ((dx+dy)<4 || (dx+dy) >5)
    {
        printf("   charge: la nouvelle position n'est pas a une distance entre 4 et 5 de la position initiale.\n");
        return;
    }

    // il faut que la nouvelle case soit alignee verticalement ou horizontalement avec la case initiale
    if (x0!=x1 && y0!=y1)
    {
        printf("   charge: la nouvelle position n'est pas alignee verticalement ou horizontlement avec la position initiale.\n");
        return;
    }

    //navire present sur la case cible
    int nbShips=0;
    int *list = rect_getTargets (nmap,pos,0,&nbShips);
    if (nbShips>0)
    {
        int id = list[0];
        b[id].coque = b[id].coque - 50;
        printf("           J%d present sur la case cible subit 50C . reste: %dC.\n",id,b[id].coque);

        // comme la case est deja occupee, pas de deplacement, les 2 bateaux perdent 5C.
        b[shipID].coque = b[shipID].coque - 5;
        printf("           deplacement impossible pour charge: J%d subit 5C. reste: %dC.\n",shipID,b[shipID].coque);
        b[id].coque = b[id].coque - 5;
        printf("                                               J%d subit 5C . reste: %dC.\n",id,b[id].coque);
	}
	else
    {
        // move sur la nouvelle position
        nmap->map [nmap->shipPosition [shipID] .y][nmap->shipPosition [shipID] .x] .type = ENT_SEA;
        placeShip(nmap,shipID,pos);
    }
	free(list);
}

void reparation(navalmap_t	*nmap,
	const int shipID, bateau *b)
{
    if((shipID)>=(nmap->nbShips))
    {
        return;
    }

	b[shipID].kero = b[shipID].kero-20;
	printf("   reparation: J%d utilise 20K. reste: %dK.\n",shipID,b[shipID].kero);
	b[shipID].coque = b[shipID].coque+25;
	printf("               J%d recupere 25C. reste: %dC.\n",shipID,b[shipID].coque);
}

void affiche (navalmap_t *nmap, bateau *b)
{
    int nbShips = nmap->nbShips;
    int i=0;
    for ( i=0 ; i<nbShips ;i++ )
    {
		if(b[i].kero >0 && b[i].coque>0)
			printf ("--- J%d a la position(%d,%d) possede %dC et %dK. \n",i,nmap->shipPosition[i].x, nmap->shipPosition[i].y, b[i].coque,b[i].kero);
	}

    int	j, k;

	//affichage de type log
	for (k = nmap->size.y-1; k >=0; --k)
    {

		
        for (j = 0; j < nmap->size.x; ++j) printf("----");
        printf ("\n");
		for (j = 0; j < nmap->size.x; ++j)
        {
			
            if (j==0) printf ("|");
            
			if (nmap->map [k][j] .type==ENT_SHIP)
            {
                 //printf ("nmap->map [%d][%d] .id=%d \n",k,j,nmap->map [k][j] .id);
                 printf (" %d |",nmap->map [k][j] .id);
            }
            else if (nmap->map [k][j] .type==ENT_SEA)
            {
                printf ("   |");
            }
		}
        printf ("\n");

    }
    for (j = 0; j < nmap->size.x; ++j) printf("----");
    printf ("\n\n");

}

int pos_portee_attaque(navalmap_t* nmap, int shipID, bateau* b, coord_t pos)
{
	int x0 = nmap->shipPosition[shipID].x; //abscisse bateau
	int y0 = nmap->shipPosition[shipID].y; //ordonnée bateau
	int x1 = pos.x; int y1 = pos.y;
	int dx = abs(x1 - x0);
	int dy = abs(y1 - y0);
	if ((dx+dy)<2 || (dx+dy)>4)
    {
        return 0;
    }

	return 1;
}

int pos_portee_charge	(navalmap_t* nmap, int shipID, 
			bateau* b, coord_t pos)

{	
	int x0 = nmap->shipPosition[shipID].x; int y0 = nmap->shipPosition[shipID].y;
	int x1 = pos.x; int y1 = pos.y;
	int dx = abs(x1 - x0);int dy = abs(y1 - y0);
	if ((dx+dy)<4 || (dx+dy) >5)
    {
        return 0;
    }
    if (x0!=x1 && y0!=y1)
    {
        return 0;
    }

    return 1;
}

int pos_move_x(coord_t moveVec)
{
	int dx = moveVec.x;
	if(abs(dx)>4)
	{
		if(dx >0) //il faudra se déplacer vers la droite
		{
			dx = 2;
		}
		else //moveVec négatif : il faudra se déplacer vers la gauche
		{
			dx = -2;
		}
		
		
	}
	else //égale à 0 ou 1
	{
		if(dx==0) //se déplacer vers la gauche ou la droite, au choix
		{
			dx = 2;
		}
		if(dx>0) //il faudra se déplacer vers la droite
		{
			dx = 1;
		}
		else //moveVec négatif : il faudra se déplacer vers la gauche
		{
			dx = -1;
		}
	}
	return dx;
}

int pos_move_y(coord_t moveVec)
{
	
	int dy = moveVec.y;
	//la position cible n'est pas à portée d'attaque
	if(abs(dy)>4)
	{
		if(dy >0) //il faudra se déplacer vers la haut
		{
			dy = 2;
		}
		else //moveVec négatif : il faudra se déplacer vers la bas
		{
			dy = -2;
		}
		
		
	}
	else //égale à 0 ou 1
	{
		if(dy==0) //se déplacer vers la gauche ou la droite, au choix
		{
			dy = 2;
		}
		if(dy>0) //il faudra se déplacer vers la droite
		{
			dy = 1;
		}
		else //moveVec négatif : il faudra se déplacer vers la gauche
		{
			dy = -1;
		}
	}
	return dy;
}

coord_t pos_move(coord_t moveVec)
{
	coord_t Vec = moveVec;
	//x + y jamais égaux en même temps à 0 car deux navires ne doivent pas être au même endroit
	if((abs(Vec.x)+abs(Vec.y))==1) //situé à une distance de 1
	{
		if(Vec.x==0)//abscisse change pas
		{
			if(Vec.y==-1)
			{
				Vec.y = 1;
			}
			else //égal à 1
			{
				Vec.y = -1;
			}
		}
		if(Vec.y==0)//ordonnée change pas
		{
			if(Vec.x==-1)
			{
				Vec.x = 1;
			}
			else //égal à 1
			{
				Vec.x = -1;
			}
			
		}
		
	}
	if((abs(Vec.x)+abs(Vec.y))>4) //sinon
	{
		//on se déplace d'abord en ordonnée puis en abscisse
		if((Vec.y)!=0) // si l'ordonnée n'est pas la même
		{
			Vec.y = pos_move_y(Vec);
			Vec.x = 0;
			return Vec;
		}
		else //sinon
		{
			Vec.x = pos_move_x(Vec);
			return Vec;
		}
	}
	return Vec;
	
}


int reste_un_bateau(bateau* b, navalmap_t* nmap)
{
	int i;
	int cmp = 0;
	for(i=0;i<nmap->nbShips;i++)
	{
		if((b[i].coque>0) && (b[i].kero>0))
		{
			cmp ++;
		}
	}
	if(cmp==1) return 1;
	return 0;
	
}

int bateau_gagnant(bateau* b,navalmap_t* nmap)
{
	int i;
	for(i=0;i<nmap->nbShips;i++)
	{
		if(b[i].coque>0 && b[i].kero>0)
		{
			return i;
		}
	}
	
	return -1; //aucun bateau gagnant
}
/*
oid * ft (void * a) 
{
	
	//verrouillage du mutex
	pthread_mutex_lock(&m);
	
	
	//close(tub[0]); //fermer tube en lecture
	
	if(b[i].kero<=0 || b[i].coque<=0)
	{
		action = -1;
		//write(tub[1],&action,sizeof(int));
	}
	if(j%4==1)//radar trop vieux ou position inconnue
	{
		action = 0; //radar
		//write(tub[1],&action,sizeof(int)); 						
	}
	
	else //position connue
	{
		if(pos_portee_attaque(nmap,i,b,pos[i]))
		{
			action = 1;//attaque
			//write(tub[1],&action,sizeof(int));
			
		}
		else 
		{
			action = 2; //déplacement
			//write(tub[1],&action,sizeof(int));
			
		}
		
	}
	pthread_mutex_unlock;
	//close(tub[1]); //fermer le tube en écriture
	exit(0);

	
	
	int i;
	arg_t * A = (arg_t *) a;

	for (i = A->id * 2; i < (A->id + 1) * 2; ++i) 
	{
		pthread_mutex_lock (A->m);
		(*A->moy) += A->T[i];
		pthread_mutex_unlock (A->m);
	}

	
	if (! A->id)
		(*A->moy) /= 20;


	for (i = A->id * 2; i < (A->id + 1) * 2; ++i) 
	{
		A->T[i] = (*A->moy) - A->T[i];
		printf ("#%d -> %d\n", i, A->T[i]);
	}
}

}*/



void creer_processus(navalmap_t* nmap,bateau* b, int nb_tours)
{
	//pthread_t tid[equipe];
	int nb_joueurs = nmap->nbShips;
	int i,j;
	int tub[2];
	coord_t pos[nb_joueurs];//stocke les coordonées bateau le plus proche
	int action;// entier qui détermine l'action à effectuer
	//-1=aucune action(navire écroulé), 0=radar, 1=attaque, 2=déplacement, 3=reparation, 4=charge
	
	for(j=1;j<=nb_tours;j++)
	{
		printf("Tour %d : \n",j);
		for(i=0;i<nb_joueurs;i++)
		{
			
			if(pipe(tub)!=0)
			{
				fprintf(stderr,"Erreur de creation du tube\n");
				exit(EXIT_FAILURE);
			}	
			
			pid_t pid = fork();
			
			if(pid==-1)
			{
				fprintf(stderr,"échec creation processus");
				exit(EXIT_FAILURE);
			}
			else //s'il n'y a pas d'erreurs
			{
				if(pid==0) // le fils = joueur déterminer l'action suivante
				{
					
					close(tub[0]); //fermer tube en lecture
					if(b[i].kero<=0 || b[i].coque<=0) //bateau écroulé = sans action
					{
						action = -1; //action pas possible
						write(tub[1],&action,sizeof(int));
					}
					if(b[i].coque>0 && b[i].coque<=40)
					{
						action = 3;//reparation
						write(tub[1],&action,sizeof(int));						
					}
					if(j%4==1)//radar trop vieux ou position inconnue
					{
						action = 0; //radar
						write(tub[1],&action,sizeof(int)); 						
					}
					
					else //position connue
					{
						if(pos_portee_attaque(nmap,i,b,pos[i]))
						{
							action = 1;//attaque
							write(tub[1],&action,sizeof(int));
							
						}
						else 
						{
							if(pos_portee_charge(nmap,i,b,pos[i]))
							{
								action = 4; //charge
								write(tub[1],&action,sizeof(int));
							}
							else
							{
								action = 2; //déplacement
								write(tub[1],&action,sizeof(int));
							}						
						}
						
					}
					close(tub[1]); //fermer le tube en écriture
					exit(0);
				}
				else //le père = le serveur
				{
					wait(NULL);
					close(tub[1]);//fermer le tube en écriture
					int action_lire;
					read(tub[0],&action_lire,sizeof(int));
					close(tub[0]);
					
					if(action_lire==0)
					{
						int kero,coque,id_b_proche;
						pos[i] = radar_scn(nmap,i,b,&coque,&kero,&id_b_proche);					
					}					
					
					if(action_lire==1)
					{
						attaque(nmap,i,pos[i],b);
						
					}
					if(action_lire==2)
					{
						coord_t moveVec;
						moveVec.x = pos[i].x - nmap->shipPosition[i].x;
						moveVec.y = pos[i].y - nmap->shipPosition[i].y;
						moveVec = pos_move(moveVec);
						deplacement(nmap,i,moveVec,b);
					}
					
					if(action_lire==3)
					{
						reparation(nmap,i,b);
					}
					
					if(action_lire==4)
					{
						charge(nmap,i,pos[i],b);						
					}
					if((action_lire==-1)&&(nmap->shipPosition[i].y != -1)) 
					//si le joueur écroule
					{
						nmap->map[nmap->shipPosition[i].y][nmap->shipPosition[i].x].type = ENT_SEA;
						nmap->shipPosition[i].y = -1; nmap->shipPosition[i].x = -1;
						
					}
					
				}	
				
			}
			
		}
		printf("\n");
		
		if(reste_un_bateau(b,nmap))
		{
			printf("partie terminee : J%d a gagne\n",bateau_gagnant(b,nmap));
			return;
		}
		
		affiche(nmap,b);
	}

}
/*
void creer_thread(int nb_joueurs)
{
	pthread_t tid[nb_joueurs]; //faire un tableau du nobre de joueurs
	pthread_mutex_t m;
	
	
	*/
	
	
	
	
	
	 
