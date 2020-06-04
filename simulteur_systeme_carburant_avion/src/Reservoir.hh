#ifndef _RESERVOIR_HH
#define _RESERVOIR_HH
#include "Etat_FLOAT.hh"
#include "Pompe.hh"
#include <iostream>
#include <string>

using namespace std;

class Reservoir: public Etat_FLOAT {
		private :
		Pompe pprimaire;
		Pompe psecondaire;
		string nom;

		public :
		Reservoir();
		Reservoir(const int e, const string);
		Reservoir(const int e, const Pompe& primaire,const Pompe& secondaire,const string);
		Reservoir(const Reservoir& r);
		Pompe& getPprimaire ();
		Pompe& getPsecondaire ();
		~Reservoir();	
		friend ostream& operator <<(ostream&, Reservoir&);	
		//Reservoir& operator = (const Reservoir&);
		friend class System;
		friend class tableau_bord;
	};


#endif
