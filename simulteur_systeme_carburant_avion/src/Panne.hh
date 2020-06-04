#ifndef _PANNE_HH
#define _PANNE_HH


#include "System.hh"


class Panne {

	private:
	System* s;



	public :
	Panne();
	System& get_system();
	void panne_pompe_p11();
	void panne_pompe_p12();
	void panne_pompe_p21();
	void panne_pompe_p22();
	void panne_pompe_p31();
	void panne_pompe_p32();
	void reservoir1_vide();
	void reservoir2_vide();
	void reservoir3_vide();
	~Panne();

	void exo1();//niveau1
	void exo2();//niveau1
	void exo3();//niveau1
	void exo4();//niveau2
	void exo5();//niveau2
	void exo6();//niveau3

	friend class tableau_bord;
	
};




#endif