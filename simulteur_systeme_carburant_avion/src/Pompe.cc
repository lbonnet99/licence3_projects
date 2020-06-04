#include "Pompe.hh"
using namespace std;

Pompe::Pompe():Etat_FLOAT(){};

Pompe::Pompe(const int etat):Etat_FLOAT(etat){};

Pompe::Pompe(const Pompe& p):Etat_FLOAT(p.etat){};

Pompe::~Pompe(){};


ostream& operator << (ostream& flux, Pompe& p){
	if(p.getEtat()==0.0)
	flux << "Pompe à l'arrêt";
	if(p.getEtat()==1.0)
	flux << "Pompe en marche";
	if(p.getEtat()==2.0)
	flux << "Pompe en panne";

	return flux;
};