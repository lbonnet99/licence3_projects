#include "Reservoir.hh"
#include <iostream>
using namespace std;

Reservoir::Reservoir() : Etat_FLOAT(),pprimaire(1.0),psecondaire(),nom("vide"){};

Reservoir::Reservoir(const int e,const string Nom) : Etat_FLOAT(e),pprimaire(1.0),psecondaire(),nom(Nom){};

Reservoir::Reservoir(const int e, const Pompe& primaire,
		const Pompe& secondaire,const string Nom): Etat_FLOAT(e),pprimaire(primaire),
		psecondaire(secondaire),nom(Nom){};

Reservoir::Reservoir(const Reservoir& r):Etat_FLOAT(r.etat),
pprimaire(r.pprimaire),psecondaire(r.psecondaire),nom(r.nom){};

Pompe& Reservoir ::getPprimaire (){
	return pprimaire ;
	};
	
Pompe& Reservoir ::getPsecondaire (){
	return psecondaire ;
	};	

Reservoir::~Reservoir(){};

ostream& operator <<(ostream& flux, Reservoir& r){
	flux << "état " << r.nom << " : " << r.etat;
	return flux;
};
/*
Reservoir& Reservoir::operator = (const Reservoir& r){
	if(this!=&r)
	{
		etat = r.etat;
		pprimaire = r.pprimaire;
		psecondaire = r.psecondaire;
		nom = r.nom;
	}
	
	return *this;

};*/