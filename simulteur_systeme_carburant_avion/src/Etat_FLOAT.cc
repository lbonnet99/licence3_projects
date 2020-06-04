#include "Etat_FLOAT.hh"

Etat_FLOAT::Etat_FLOAT():etat(0){};

Etat_FLOAT::Etat_FLOAT(const int e):etat(e){};

Etat_FLOAT::Etat_FLOAT(const Etat_FLOAT& E){
	etat = E.etat;
};

int Etat_FLOAT::getEtat(){
	return etat;
};

void Etat_FLOAT::setEtat(const int e){
	etat = e;
};

Etat_FLOAT::~Etat_FLOAT(){};
