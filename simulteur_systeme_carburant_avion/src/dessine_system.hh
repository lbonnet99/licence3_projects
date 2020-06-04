#ifndef DESSINE_SYSTEM_HH
#define DESSINE_SYSTEM_HH
#include <QtGui>
#include <QWidget>
#include <QPushButton>


class dessine_system : public QGraphicsScene
{

	private :
	QLine *ligneT1T2;
	QLine *ligneT2T3;
	QLine *ligne1T1M1;
	QLine *ligne2T1M1;
	QLine *ligne3T1M1;
	QLine *ligne1T1M3;
	QLine *ligne2T1M3;
	QLine *ligne1T2M2;
	QLine *ligne2T2M2;
	QLine *ligne3T2M2;
	QLine *ligne1T1M2;
	QLine *ligne1T3M2;
	QLine *ligne2T3M2;
	QLine *ligne1T3M3;

	QRect *rectangleM1;
	QRect *rectangleM2;
	QRect *rectangleM3;

	QRect *rectangleT1;
	QRect *rectangleT2;
	QRect *rectangleT3;

	QRect *rectangleVT12_ouvert;
	QRect *rectangleVT23_ouvert;
	QRect *rectangleV12_ouvert;
	QRect *rectangleV13_ouvert;
	QRect *rectangleV23_ouvert;

	QRect *rectangleVT12_ferme;
	QRect *rectangleVT23_ferme;
	QRect *rectangleV12_ferme;
	QRect *rectangleV13_ferme;
	QRect *rectangleV23_ferme;

	public:
	dessine_system();
	~dessine_system();
	void ajout_lignes();

	void ajout_moteurs();

	void ajout_T1_rempli();
	void ajout_T2_rempli();
	void ajout_T3_rempli();
	void ajout_T1_vide();
	void ajout_T2_vide();
	void ajout_T3_vide();

	void ajout_cercles_noir_vannes();

	void ajout_P11_arret();
	void ajout_P11_marche();
	void ajout_P11_panne();	

	void ajout_P12_arret();
	void ajout_P12_marche();
	void ajout_P12_panne();
	
	void ajout_P21_arret();
	void ajout_P21_marche();
	void ajout_P21_panne();

	void ajout_P22_arret();
	void ajout_P22_marche();
	void ajout_P22_panne();

	void ajout_P31_arret();
	void ajout_P31_marche();
	void ajout_P31_panne();

	void ajout_P32_arret();
	void ajout_P32_marche();
	void ajout_P32_panne();


	void rect_VT12_ferme();
	void rect_VT12_ouverte();
	void rect_VT23_ferme();
	void rect_VT23_ouverte();
	void rect_V12_ferme();
	void rect_V12_ouverte();
	void rect_V13_ferme();
	void rect_V13_ouverte();
	void rect_V23_ferme();
	void rect_V23_ouverte();
	

};


#endif