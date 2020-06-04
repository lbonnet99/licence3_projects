#include "Moteur.hh"

Moteur::Moteur(): Etat_BOOL(true),alim(),nom("vide"){};

Moteur::Moteur(const bool e, Pompe& p,const string Nom):Etat_BOOL(e),nom(Nom),
	alim(&p){};


Moteur::~Moteur(){};


ostream& operator <<(ostream& flux,Moteur& m){
	flux << "état " << m.nom << " : " ;
	if(m.etat==true){
		flux << "Moteur en marche";
	}
	else
		flux << "Moteur en arrêt";
	return flux;
};
