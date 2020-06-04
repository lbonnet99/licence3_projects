#include "Etat_BOOL.hh"

Etat_BOOL::Etat_BOOL():etat(true){};

Etat_BOOL::Etat_BOOL(const bool etat){
	this->etat = etat;
};

Etat_BOOL::Etat_BOOL(const Etat_BOOL& o){
	etat = o.etat;	
};

Etat_BOOL::~Etat_BOOL(){};

bool Etat_BOOL::getEtat(){
	
	return etat;
	
};

void Etat_BOOL :: setEtat(const bool E){
	etat=E;
	};
