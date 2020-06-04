#ifndef _MOTEUR_HH
#define _MOTEUR_HH
#include "Etat_BOOL.hh"
#include "Pompe.hh"
#include <iostream>
#include <string>

using namespace std;

class Moteur: public Etat_BOOL {
	
	// etat = false si moteur à l'arrêt et etat = true si moteur en marche
	
	private :
	Pompe* alim; // Pompe qui alimente le moteur
	string nom;
	
	public :
	Moteur();
	Moteur(const bool e,Pompe& p,const string); 
	~Moteur();
	friend ostream& operator <<(ostream&,Moteur&); 
	friend class System;
	friend class tableau_bord;

	};


#endif
