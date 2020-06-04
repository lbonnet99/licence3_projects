#ifndef _POMPE_HH
#define _POMPE_HH
//etat 0 = arrêt, etat 1 = marche, etat 2 = panne
#include "Etat_FLOAT.hh"
#include <iostream>
using namespace std;

class Pompe : public Etat_FLOAT{
	

	public :
	Pompe();
	Pompe(const int etat);
	Pompe(const Pompe&);
	~Pompe();
	friend ostream& operator << (ostream&, Pompe&);


};
#endif
