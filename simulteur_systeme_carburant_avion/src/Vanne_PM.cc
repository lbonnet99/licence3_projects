#include "Vanne_PM.hh"
#include <iostream>

using namespace std;


Vanne_PM :: Vanne_PM():Etat_BOOL (),t1(),m1(),t2(),m2(){} ;
	
	
Vanne_PM::Vanne_PM(const bool e ,Reservoir& T1 ,Moteur& M1,Reservoir& T2,Moteur& M2):Etat_BOOL (e) {
	t1 = &T1;
	m1 = &M1;
	t2 = &T2;
	m2 = &M2;
};
	
Vanne_PM::~Vanne_PM(){};

ostream& operator << (ostream& flux, Vanne_PM& v){
	if(v.getEtat()==true){
		flux << "Vanne ouverte";
	}
	else
		flux << "Vanne fermée";

	return flux;
};

