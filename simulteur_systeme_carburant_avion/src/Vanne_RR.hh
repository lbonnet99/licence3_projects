#ifndef _VANNE_RR_HH
#define _VANNE_RR_HH
#include "Etat_BOOL.hh"
#include "Reservoir.hh"

/* classe d'une vanne reliant un réservoir à un autre
 * réservoir*/
 
class Vanne_RR: public Etat_BOOL {
	// etat = false si vanne fermée si vanne ouverte, etat = true
	private :
	Reservoir* r1;
	Reservoir* r2;
	
	public :
	Vanne_RR();	
	Vanne_RR(const Vanne_RR& v);
	Vanne_RR(const bool e ,Reservoir& R1 ,Reservoir& R2);
	~Vanne_RR();
	
	Reservoir& getR1();
	Reservoir& getR2();
	Vanne_RR& operator=(const Vanne_RR&);
	friend ostream& operator << (ostream&, Vanne_RR&);
	friend class System;

	};


#endif
