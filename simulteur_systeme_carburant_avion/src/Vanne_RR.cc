#include "Vanne_RR.hh"

#include <iostream>

using namespace std;

Vanne_RR :: Vanne_RR():Etat_BOOL (true),r1(),r2(){
} ;

Vanne_RR ::Vanne_RR(const Vanne_RR& v):Etat_BOOL(v.etat){
		r1= v.r1;
		r2= v.r2;
};
		
Vanne_RR::Vanne_RR(const bool e ,Reservoir& R1 ,Reservoir& R2):Etat_BOOL (e){
	r1 =  &R1;
	r2 =  &R2;
};

Reservoir& Vanne_RR::getR1(){
	return* r1;
	};
	
Reservoir& Vanne_RR::getR2(){
	return* r2;
	};

Vanne_RR::~Vanne_RR(){
};

Vanne_RR& Vanne_RR::operator=(const Vanne_RR& v){
	  if(this != &v)
    //On vérifie que l'objet n'est pas le même que celui reçu en argument
    {
        etat = v.etat;
		delete r1;
		delete r2;
        r1 = new Reservoir(*v.r1);
        r2 = new Reservoir(*v.r2);
    }
    return *this; //On renvoie l'objet lui-même
};
	
ostream& operator << (ostream& flux, Vanne_RR& v){
	if(v.getEtat()==true){
		flux << "Vanne ouverte";
	}
	else
		flux << "Vanne fermée";

	return flux;
};