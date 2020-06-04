#ifndef Etat_FLOAT_HH
#define Etat_FLOAT_HH

class Etat_FLOAT{
	protected :
		float etat;
		
	public : 
		Etat_FLOAT();
		Etat_FLOAT(const int e);
		Etat_FLOAT(const Etat_FLOAT& E);
		int getEtat();
		void setEtat(const int e);
		~Etat_FLOAT();


};
#endif
