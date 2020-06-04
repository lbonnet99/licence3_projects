#ifndef _SYSTEM_HH
#define _SYSTEM_HH

#include "Vanne_PM.hh"


using namespace std;

class System : public Etat_BOOL {
	
    private :
    Reservoir T1,T2,T3;
    Vanne_RR VT12 ,VT23;
    Moteur M1,M2,M3;	
	Vanne_PM V12 ,V13,V23;
	
	
	
	public :
	System ();
	System(const System& s);
	~System ();

     /* le pilote appuie sur une vanne de type RR */
	void alimente_RR(Vanne_RR&);
	
	void alimente_RM(Vanne_PM&);
	void action_Pompe_secours(Reservoir&);
	void revenir_system_depart();
	friend ostream& operator << (ostream& flux, System& s);
	friend class Panne;
	friend class tableau_bord;
		
	
	};

#endif 
