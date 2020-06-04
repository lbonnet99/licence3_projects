#ifndef _VANNE_PM_HH
#define _VANNE_PM_HH
#include "Vanne_RR.hh"
#include "Moteur.hh"


/* classe d'une vanne reliant une pompe à un moteur*/

class Vanne_PM: public Etat_BOOL {
	// etat = false si vanne fermée si vanne ouverte, etat = true
	private:
	Reservoir* t1 ; 
	Moteur* m1;
	Reservoir* t2 ; 
	Moteur* m2;
	
	public :
	Vanne_PM();	
	Vanne_PM(const bool e ,Reservoir&,Moteur&,Reservoir&,Moteur&);
	~Vanne_PM();
	friend ostream& operator << (ostream&, Vanne_PM&);
	friend class System;
	
	};


#endif
