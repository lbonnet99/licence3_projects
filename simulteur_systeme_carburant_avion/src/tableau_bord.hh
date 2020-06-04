#ifndef TABLEAU_BORD_HH
#define TABLEAU_BORD_HH

#include <QtGui>
#include <QWidget>
#include <QPushButton>
#include "dessine_system.hh"
#include "Panne.hh"
#include "Pilote.hh"

/*contient un élément de type dessine_system et un pointeur vers un objet de type Panne*/


class tableau_bord : public QWidget
{
    Q_OBJECT
	private:
    QPushButton *VT12;
    QPushButton *VT23;
    QPushButton *P12_marche;
    QPushButton *P22_marche;
    QPushButton *P32_marche;
    QPushButton *P12_arret;
    QPushButton *P22_arret;
    QPushButton *P32_arret;
    QPushButton *V12;
    QPushButton *V13;
    QPushButton *V23;
    QPushButton *quitter;
    QPushButton *test;
    QPushButton *pilote1;
    QPushButton *pilote2;
    QPushButton *pilote3;
    QPushButton *deconnexion;
    QPushButton *affich_hist; 
    QGridLayout *layout;
    QPushButton *consult_hist;  
    QPushButton* fin;
    QPushButton* exo6;
    QPushButton* exo5;
    QPushButton* exo4;
    QPushButton* exo3;
    QPushButton* exo2;
    QPushButton* exo1;
    int bout_exo1;
    int bout_exo2;
    int bout_exo3;
    int bout_exo4;
    int bout_exo5;
    int bout_exo6;
    int bout_fin;
    int creation_hist;
    int bout_test;
    int bout_p1;
    int bout_p2;
    int bout_p3;



    dessine_system s;
    Pilote p1;
    Pilote p2;
    Pilote p3;
    Panne p;
    int note;
    int pilote_actuel;
    

	public:
	tableau_bord();
	~tableau_bord();
    dessine_system& get_system();
    void dessin_system();
    
    private slots:
    void fermer_VT12();
    void fermer_VT23();
    void fermer_V12();
    void fermer_V13();
    void fermer_V23();
    void action_P12_marche();
    void action_P22_marche();
    void action_P32_marche();
    void action_P12_arret();
    void action_P22_arret();
    void action_P32_arret();
    void action_test();
    void action_exo1();
    void action_exo2();
    void action_exo3();
    void action_exo4();
    void action_exo5();
    void action_exo6();
    void action_fin();
    void action_historique();
    void action_pilote1();
    void action_pilote2();
    void action_pilote3();
    void action_deconnexion();
    void action_cons_hist();

    
	
};




#endif