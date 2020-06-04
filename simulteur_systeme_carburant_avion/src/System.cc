#include "System.hh"

#include <string.h>



System :: System ():Etat_BOOL(true),T1(30.0,"T1"),
	T2(9.0,"T2"),T3(30.0,"T3"),
	VT12(true,T1,T2),VT23(true,T2,T3),
	M1(true,T1.pprimaire,"M1"),
	M2(true,T2.pprimaire,"M2"),
	M3(true,T3.pprimaire,"M3"),
	V12(true,T1,M1,T2,M2),
	V13(true,T1,M1,T3,M3),
	V23(true,T2,M2,T3,M3){};


System:: System(const System& s):Etat_BOOL(s.etat),VT12(s.VT12),VT23(s.VT23),V12(s.V12),V13(s.V13),V23(s.V23),M1(s.M1),
		M2(s.M2),M3(s.M3),T1(s.T1),T2(s.T2),T3(s.T3){};
System::~System () {};

	
	
void System :: alimente_RR(Vanne_RR& V){
	if(V.getEtat()==false)
	{
		cerr << "vanne déjà actionnée" << endl;
		exit(1);
	}
	//si l'autre vanne déjà actionnée
	if(VT12.getEtat()==false || VT23.getEtat()==false)
	{
		// cap1= capacité 1 
		float cap1=T1.getEtat();
		// cap2= capacité 2 
		float cap2=T2.getEtat();
		float cap3=T3.getEtat();
	
		// équilbrer trois reservoirs
		float resultat = (cap1+cap2+cap3)/3 ;
		T1.setEtat(resultat);
		T2.setEtat(resultat);
		T3.setEtat(resultat);
		V.setEtat(false);
	}
	/* cap1= capacité 1 */
	float cap1=V.r1->getEtat();
	/* cap2= capacité 2 */
	float cap2=V.r2->getEtat();
	
	/* équilibrer deux réservoirs */
	float resultat = (cap1+cap2)/2 ;
	V.r1->setEtat(resultat);
	V.r2->setEtat(resultat);
	V.setEtat(false);
	};
	
void System :: alimente_RM(Vanne_PM& v){
	if(v.getEtat()==false)
	{
		cerr << "vanne déjà actionnée" << endl;
	}
	
	v.setEtat(false); //sinon modifier
	if((*(v.t1)).pprimaire.getEtat()==2.0 && (*(v.t1)).psecondaire.getEtat()==2.0 && (*(v.m1)).alim->getEtat()==2.0)
	{
		action_Pompe_secours(*(v.t2));
		(*(v.m1)).alim = &((*(v.t2)).psecondaire);

	}
	if((*(v.t2)).pprimaire.getEtat()==2.0 && (*(v.t2)).psecondaire.getEtat()==2.0 && (*(v.m2)).alim->getEtat()==2.0)
	{
		action_Pompe_secours(*(v.t1));
		(*(v.m2)).alim = &((*(v.t1)).psecondaire);
	}

	};
	
	
void System :: action_Pompe_secours(Reservoir& R){
	try
	{
		if (R.pprimaire.getEtat()==1.0
			&& R.psecondaire.getEtat()==1.0)
		{
			throw string ("action pompe de secours est impossible car les deux pompes sont en marche");
			exit (1);
		
		}
		else
		{
			if (R.psecondaire.getEtat()==2.0)
			{
				cout << "action pompe secours impossible car en panne" <<endl;
			}
			else
			R.getPsecondaire().setEtat(1.0);	
			// changer au moteur en question la pompe qui l'alimente en pompe secondaire
			if(M1.alim==(&R.pprimaire))
				M1.alim = &(R.psecondaire);
			if(M2.alim==(&R.pprimaire))
				M2.alim = &(R.psecondaire);
			if(M3.alim==(&R.pprimaire))
				M3.alim = &(R.psecondaire);


		}
		
	}
	catch (string const& chaine)
	{
		cerr << chaine << endl;
		exit(1);		
	}
	
};

void System::revenir_system_depart(){
	T1.setEtat(30);
	T2.setEtat(9);
	T3.setEtat(30);
	T1.pprimaire.setEtat(1.0);
	T1.psecondaire.setEtat(0.0);
	T2.pprimaire.setEtat(1.0);
	T2.psecondaire.setEtat(0.0);
	T3.pprimaire.setEtat(1.0);
	T3.psecondaire.setEtat(0.0);
	VT12.setEtat(true);
	VT23.setEtat(true);
	V12.setEtat(true);
	V13.setEtat(true);
	V23.setEtat(true);
	M1.alim = &T1.pprimaire;
	M2.alim = &T2.pprimaire;
	M3.alim = &T3.pprimaire;

};


ostream& operator << (ostream& flux, System& s){
	flux << "état du système : " << endl;
	flux << s.T1 << endl;
	flux << "état P11 : " << s.T1.getPprimaire() << endl;
	flux << "état P12 : " << s.T1.getPsecondaire() << endl << "\n";

	flux << s.T2 << endl;
	flux << "état P21 : " << s.T2.getPprimaire() << endl;
	flux << "état P22 : " << s.T2.getPsecondaire() << endl << "\n" ;

	flux << s.T3 << endl;
	flux << "état P31 : " << s.T3.getPprimaire() << endl;
	flux << "état P32 : " << s.T3.getPsecondaire() << endl << "\n";

	flux << s.M1 << endl;	
	flux << s.M2 << endl;
	flux << s.M3 << endl;
	
	flux << "état V12 : " << s.V12 << endl;
	flux << "état V13 : " << s.V13 << endl;
	flux << "état V23 : " << s.V23 << endl;


	flux << "état VT12 : " << s.VT12 << endl;
	flux << "état VT23 : " << s.VT23 << endl;
	



	return flux;
};
	
