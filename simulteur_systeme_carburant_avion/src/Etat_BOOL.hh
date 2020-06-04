#ifndef _ETAT_BOOL_HH
#define _ETAT_BOOL_HH

class Etat_BOOL{
	
	protected:
	bool etat;
	
	public :
	
	Etat_BOOL();
	Etat_BOOL(const Etat_BOOL& o);
	Etat_BOOL(const bool etat);
	~Etat_BOOL();
	bool getEtat();
	void setEtat(const bool E);


};


#endif
