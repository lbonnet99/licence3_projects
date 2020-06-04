#include "Panne.hh"
#include <time.h>
using namespace std ; 
Panne::Panne(){
s=new System();

};


Panne::~Panne(){
	delete s;

}

System& Panne::get_system(){
	return *(this->s);
};

void Panne::panne_pompe_p11(){
	s->T1.getPprimaire().setEtat(2);
};

void Panne::panne_pompe_p12(){
		s->T1.getPsecondaire().setEtat(2);
	
};

void Panne::panne_pompe_p21(){
	s->T2.getPprimaire().setEtat(2);
};

void Panne::panne_pompe_p22(){
		s->T2.getPsecondaire().setEtat(2);
	
};

void Panne::panne_pompe_p31(){
	s->T3.getPprimaire().setEtat(2);
};

void Panne::panne_pompe_p32(){
		s->T3.getPsecondaire().setEtat(2);
	
};

void Panne::reservoir1_vide(){
	s->T1.setEtat(0);
};

void Panne::reservoir2_vide(){
	s->T2.setEtat(0);
};
	
void Panne::reservoir3_vide(){
	s->T3.setEtat(0);
};


void Panne::exo1(){
	panne_pompe_p11();
};

void Panne::exo2(){
	panne_pompe_p21();
};

void Panne::exo3(){
	panne_pompe_p31();
};

void Panne::exo4(){
	reservoir3_vide();
};

void Panne::exo5(){
	reservoir1_vide();
};

void Panne::exo6(){
	srand(time(NULL));
    int nbgen=rand()%4; 
    if (nbgen ==0){
    	reservoir2_vide();
    	reservoir1_vide();
    }
    if(nbgen==1){
    	panne_pompe_p11();
    	panne_pompe_p12();
    }
     if(nbgen==2){
    	panne_pompe_p21();
    	panne_pompe_p22();
    }
     if(nbgen==3){
    	panne_pompe_p31();
    	panne_pompe_p32();
    }
};
