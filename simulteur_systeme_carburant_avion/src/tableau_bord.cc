#include "tableau_bord.hh"
#include <iostream>

using namespace std;

tableau_bord::tableau_bord():QWidget(),s(),p(),pilote_actuel(0),creation_hist(0),bout_test(0),
    bout_exo1(0),bout_exo2(0),bout_exo3(0),bout_exo4(0),bout_exo5(0),bout_exo6(0),bout_fin(0),
    bout_p1(1),bout_p2(1),bout_p3(1)

{
    p1 = Pilote("Max","ciel");
    p2 = Pilote("Camille", "monde");
    p3 = Pilote("Marie", "info");
	VT12 = new QPushButton("VT12",this);
	VT23 = new QPushButton("VT23",this);
	P12_marche = new QPushButton("P12 marche",this);
    P22_marche = new QPushButton("P22 marche",this);
    P32_marche = new QPushButton("P32 marche",this);
    P12_arret = new QPushButton("P12 arret",this);
    P22_arret = new QPushButton("P22 arret",this);
    P32_arret = new QPushButton("P32 arret",this);
    V12 = new QPushButton("V12",this);
    V13 = new QPushButton("V13",this);
    V23 = new QPushButton("V23",this);
    pilote1 = new QPushButton("Max",this);
    pilote2 = new QPushButton("Camille",this);
    pilote3 = new QPushButton("Marie",this);
    quitter = new QPushButton("Quitter",this);
    deconnexion = NULL;
    affich_hist = NULL;
    consult_hist = NULL;
    test = NULL;
    exo1 = NULL;
    exo2 = NULL;
    exo3 = NULL;
    exo4 = NULL;
    exo5 = NULL;
    exo6 = NULL;
    fin = NULL;
  
    note = 0;
    layout = new QGridLayout;


    layout->addWidget(VT12, 0, 1);
    layout->addWidget(VT23, 0, 2);
    layout->addWidget(P12_marche, 1, 0);
    layout->addWidget(P22_marche, 1, 1);
    layout->addWidget(P32_marche, 1, 2);
    layout->addWidget(P12_arret, 2, 0);
    layout->addWidget(P22_arret, 2, 1);
    layout->addWidget(P32_arret, 2, 2);
    layout->addWidget(V12, 3, 0);
    layout->addWidget(V13, 3, 1);
    layout->addWidget(V23, 3, 2);
    layout->addWidget(pilote1,4,0);
    layout->addWidget(pilote2,4,1);
    layout->addWidget(pilote3,4,2);
    layout->addWidget(quitter, 6, 1);

    (*(this)).setLayout(layout);

    QObject::connect(quitter, SIGNAL(clicked()), qApp, SLOT(quit()));
    QObject::connect(pilote1, SIGNAL(clicked()), this, SLOT(action_pilote1()));
    QObject::connect(pilote2, SIGNAL(clicked()), this, SLOT(action_pilote2()));
    QObject::connect(pilote3, SIGNAL(clicked()), this, SLOT(action_pilote3()));

    QObject::connect(VT12, SIGNAL(clicked()), this ,SLOT(fermer_VT12()));
    QObject::connect(VT23, SIGNAL(clicked()), this, SLOT(fermer_VT23()));
    QObject::connect(V12, SIGNAL(clicked()), this, SLOT(fermer_V12()));
    QObject::connect(V13, SIGNAL(clicked()), this, SLOT(fermer_V13()));
    QObject::connect(V23, SIGNAL(clicked()), this, SLOT(fermer_V23()));

    QObject::connect(P12_marche, SIGNAL(clicked()), this, SLOT(action_P12_marche()));
    QObject::connect(P22_marche, SIGNAL(clicked()), this, SLOT(action_P22_marche()));
    QObject::connect(P32_marche, SIGNAL(clicked()), this, SLOT(action_P32_marche()));

    QObject::connect(P12_arret, SIGNAL(clicked()), this, SLOT(action_P12_arret()));
    QObject::connect(P22_arret, SIGNAL(clicked()), this, SLOT(action_P22_arret()));
    QObject::connect(P32_arret, SIGNAL(clicked()), this, SLOT(action_P32_arret()));

    
};

 

void tableau_bord::fermer_VT12(){    
     p.s->alimente_RR(p.s->VT12);
     dessin_system();
     cout << p.get_system();
    
};

void tableau_bord::fermer_VT23(){
     p.s->alimente_RR(p.s->VT23);
     dessin_system();
     cout << p.get_system();
    
};

void tableau_bord::fermer_V12(){
    p.s->alimente_RM(p.s->V12);
    dessin_system();
    cout << p.get_system();
    
};

void tableau_bord::fermer_V13(){
    p.s->alimente_RM(p.s->V13);
    dessin_system();
    cout << p.get_system();
    
};

void tableau_bord::fermer_V23(){
    p.s->alimente_RM(p.s->V23);
    dessin_system();
    cout << p.get_system();
    
};

void tableau_bord::action_P12_arret(){
    p.s->T1.psecondaire.setEtat(0.0);
    dessin_system();
    cout << p.get_system();
};

void tableau_bord::action_P22_arret(){
    p.s->T2.psecondaire.setEtat(0.0);
    dessin_system();
    cout << p.get_system();
};

void tableau_bord::action_P32_arret(){
    p.s->T3.psecondaire.setEtat(0.0);
    dessin_system();
    cout << p.get_system();
};

void tableau_bord::action_P12_marche(){
    p.s->action_Pompe_secours(p.s->T1);
    dessin_system();
    cout << p.get_system();
    
};

void tableau_bord::action_P22_marche(){
    p.s->action_Pompe_secours(p.s->T2);
    dessin_system();
    cout << p.get_system();
    
};

void tableau_bord::action_P32_marche(){
    p.s->action_Pompe_secours(p.s->T3);
    dessin_system();
    cout << p.get_system();
    
};


void tableau_bord::dessin_system(){
    s.ajout_lignes();
    s.ajout_moteurs();

    s.ajout_cercles_noir_vannes();
    //réservoirs
    if(p.s->T1.getEtat())
        s.ajout_T1_rempli();
    else
        s.ajout_T1_vide();

    if(p.s->T2.getEtat())
        s.ajout_T2_rempli();
    else
        s.ajout_T2_vide();

    if(p.s->T3.getEtat())
        s.ajout_T3_rempli();
    else
        s.ajout_T3_vide();

    //pompes
    if(p.s->T1.pprimaire.getEtat()==0)
        s.ajout_P11_arret();
    if(p.s->T1.pprimaire.getEtat()==1.0)
        s.ajout_P11_marche();
    if(p.s->T1.pprimaire.getEtat()==2.0)
        s.ajout_P11_panne();

     if(p.s->T1.psecondaire.getEtat()==0)
        s.ajout_P12_arret();
    if(p.s->T1.psecondaire.getEtat()==1.0)
        s.ajout_P12_marche();
    if(p.s->T1.psecondaire.getEtat()==2.0)
        s.ajout_P12_panne();

     if(p.s->T2.pprimaire.getEtat()==0)
        s.ajout_P21_arret();
    if(p.s->T2.pprimaire.getEtat()==1.0)
        s.ajout_P21_marche();
    if(p.s->T2.pprimaire.getEtat()==2.0)
        s.ajout_P21_panne();

     if(p.s->T2.psecondaire.getEtat()==0)
        s.ajout_P22_arret();
    if(p.s->T2.psecondaire.getEtat()==1.0)
        s.ajout_P22_marche();
    if(p.s->T2.psecondaire.getEtat()==2.0)
        s.ajout_P22_panne();

     if(p.s->T3.pprimaire.getEtat()==0)
        s.ajout_P31_arret();
    if(p.s->T3.pprimaire.getEtat()==1.0)
        s.ajout_P31_marche();
    if(p.s->T3.pprimaire.getEtat()==2.0)
        s.ajout_P31_panne();

     if(p.s->T3.psecondaire.getEtat()==0)
        s.ajout_P32_arret();
    if(p.s->T3.psecondaire.getEtat()==1.0)
        s.ajout_P32_marche();
    if(p.s->T3.psecondaire.getEtat()==2.0)
        s.ajout_P32_panne();


    if(p.s->VT12.getEtat()==true)
        s.rect_VT12_ouverte();
    else
        s.rect_VT12_ferme();

    if(p.s->VT23.getEtat()==true)
        s.rect_VT23_ouverte();
    else
        s.rect_VT23_ferme();

    if(p.s->V13.getEtat()==true)
        s.rect_V13_ouverte();
    else
        s.rect_V13_ferme();

    if(p.s->V12.getEtat()==true)
        s.rect_V12_ouverte();
    else
        s.rect_V12_ferme();

    if(p.s->V23.getEtat()==true)
        s.rect_V23_ouverte();
    else
        s.rect_V23_ferme();

    cout << p.get_system();

};

void tableau_bord::action_pilote1(){
    cout << "Id : " << p1.id << endl;
    cout << "Entrer le mot de passe : ";
    string mdp;
    cin >> mdp;
    if(mdp.compare(p1.mdp) == 0){
        affich_hist = NULL;
        delete consult_hist;
        delete pilote1; // enlever le bouton
        delete pilote2;
        delete pilote3;
        bout_p1 = 0;
        bout_p2 = 0;
        bout_p3 = 0;
        deconnexion = new QPushButton("Deconnexion",this);
        layout->addWidget(deconnexion, 4, 0);

        (*(this)).setLayout(layout);
        QObject::connect(deconnexion, SIGNAL(clicked()), this ,SLOT(action_deconnexion()));


        pilote_actuel = 1;
        p.s->revenir_system_depart();
        dessin_system();
        test = new QPushButton("Lancer Test",this);
        bout_test = 1;
        layout->addWidget(test, 4, 1);

        (*(this)).setLayout(layout);
        QObject::connect(test, SIGNAL(clicked()), this ,SLOT(action_test()));
    }
    else {
        cout << "Mot de passe incorrect" << endl;
    }

}

void tableau_bord::action_pilote2(){
    cout << "Id : " << p2.id << endl;
    cout << "Entrer le mot de passe : ";
    string mdp;
    cin >> mdp;
    if(mdp.compare(p2.mdp) == 0){
        affich_hist = NULL;
        delete consult_hist;
        delete pilote1;
        delete pilote2; // enlever le bouton
        delete pilote3;
        bout_p1 = 0;
        bout_p2 = 0;
        bout_p3 = 0;
        deconnexion = new QPushButton("Deconnexion",this);
        layout->addWidget(deconnexion, 4, 0);

        (*(this)).setLayout(layout);
        QObject::connect(deconnexion, SIGNAL(clicked()), this ,SLOT(action_deconnexion()));


        pilote_actuel = 2;
        p.s->revenir_system_depart();
        dessin_system();
        test = new QPushButton("Lancer Test",this);
        bout_test = 1;
        layout->addWidget(test, 4, 1);

        (*(this)).setLayout(layout);
        QObject::connect(test, SIGNAL(clicked()), this ,SLOT(action_test()));
    }
    else {
        cout << "Mot de passe incorrect" << endl;
    }

}

void tableau_bord::action_pilote3(){
    cout << "Id : " << p3.id << endl;
    cout << "Entrer le mot de passe : ";
    string mdp;
    cin >> mdp;
    if(mdp.compare(p3.mdp) == 0){
        affich_hist = NULL;
        delete consult_hist;
        delete pilote1; // enlever le bouton
        delete pilote2;
        delete pilote3;
        bout_p1 = 0;
        bout_p2 = 0;
        bout_p3 = 0;
        deconnexion = new QPushButton("Deconnexion",this);
        layout->addWidget(deconnexion, 4, 0);

        (*(this)).setLayout(layout);
        QObject::connect(deconnexion, SIGNAL(clicked()), this ,SLOT(action_deconnexion()));


        pilote_actuel = 3;
        p.s->revenir_system_depart();
        dessin_system();
        test = new QPushButton("Lancer Test",this);
        bout_test = 1;
        layout->addWidget(test, 4, 1);

        (*(this)).setLayout(layout);
        QObject::connect(test, SIGNAL(clicked()), this ,SLOT(action_test()));
    }
    else {
        cout << "Mot de passe incorrect" << endl;
    }

}


void tableau_bord::action_deconnexion(){
         if(pilote_actuel==1)
            p1.ecrire_historique();
        if(pilote_actuel==2)
            p2.ecrire_historique();
        if(pilote_actuel==3)
            p3.ecrire_historique();
        delete affich_hist;
        delete deconnexion; 
        if(bout_test){
            delete test;
            bout_test = 0;
        }
        if(bout_exo1){
            delete exo1;
            bout_exo1 = 0;
        }
            
         if(bout_exo2){
            delete exo2;
            bout_exo2 = 0;
         }
         if(bout_exo3){
            delete exo3;
            bout_exo3 = 0;
         }
            
         if(bout_exo4){
            delete exo4;
            bout_exo4 = 0;
         }
         if(bout_exo5){
            delete exo5;
            bout_exo5 =0;
         }
         if(bout_exo6){
            delete exo6;
            bout_exo6 = 0;
         }
         if(bout_fin){
            delete fin;
            bout_fin = 0;
         }
        pilote1 = new QPushButton("Max",this);
        layout->addWidget(pilote1, 4, 0);
        bout_p1 = 1;
        pilote2 = new QPushButton("Camille",this);
        layout->addWidget(pilote2, 4, 1);
        bout_p2 = 1;
        pilote3 = new QPushButton("Marie",this);
        layout->addWidget(pilote3, 4, 2);
        bout_p3 = 1;

        consult_hist = new QPushButton("Consultation historique",this);
        layout->addWidget(consult_hist, 5, 1);


        (*(this)).setLayout(layout);
        QObject::connect(pilote1, SIGNAL(clicked()), this ,SLOT(action_pilote1()));
        QObject::connect(pilote2, SIGNAL(clicked()), this ,SLOT(action_pilote2()));
        QObject::connect(pilote3, SIGNAL(clicked()), this ,SLOT(action_pilote3()));
        QObject::connect(consult_hist, SIGNAL(clicked()), this ,SLOT(action_cons_hist()));

};

void tableau_bord::action_cons_hist(){
    p1.afficher_historique();
    p2.afficher_historique();
    p3.afficher_historique();

}

void tableau_bord::action_test(){
    delete test;
    bout_test = 0;
    p.s->revenir_system_depart();
    dessin_system();
    note = 0;
    exo1 = new QPushButton("Exercice 1",this);
    bout_exo1 = 1;
    layout->addWidget(exo1, 4, 1);

    (*(this)).setLayout(layout);
    QObject::connect(exo1, SIGNAL(clicked()), this ,SLOT(action_exo1()));

};

void tableau_bord::action_exo1(){
    delete exo1;
    bout_exo1 = 0;
    p.s->revenir_system_depart();
    p.exo1();
    dessin_system();
    bout_exo2 = 1;
    exo2 = new QPushButton("Exercice 2",this);
    layout->addWidget(exo2, 4, 1);

    (*(this)).setLayout(layout);
    QObject::connect(exo2, SIGNAL(clicked()), this ,SLOT(action_exo2()));
};
   
void tableau_bord::action_exo2(){
    delete exo2;
    bout_exo2 = 0;
    if(p.s->T1.psecondaire.getEtat()==1.0)
        note ++;
    p.s->revenir_system_depart();
    p.exo2();
    dessin_system();

    bout_exo3 = 1;
    exo3 = new QPushButton("Exercice 3",this);
    layout->addWidget(exo3, 4, 1);

    (*(this)).setLayout(layout);
    QObject::connect(exo3, SIGNAL(clicked()), this ,SLOT(action_exo3()));
};

void tableau_bord::action_exo3(){
    delete exo3;
    bout_exo3 = 0;
    if(p.s->T2.psecondaire.getEtat()==1.0)
        note ++;
    p.s->revenir_system_depart();
    p.exo3();
    dessin_system();

    bout_exo4 = 1;
    exo4 = new QPushButton("Exercice 4",this);
    layout->addWidget(exo4, 4, 1);

    (*(this)).setLayout(layout);
    QObject::connect(exo4, SIGNAL(clicked()), this ,SLOT(action_exo4()));

};

void tableau_bord::action_exo4(){
    delete exo4;
    bout_exo4 = 0;
    if(p.s->T3.psecondaire.getEtat()==1.0)
        note ++;
    p.s->revenir_system_depart();
    p.exo4();
    dessin_system();

    bout_exo5 = 1;
    exo5 = new QPushButton("Exercice 5",this);
    layout->addWidget(exo5, 4, 1);

    (*(this)).setLayout(layout);
    QObject::connect(exo5, SIGNAL(clicked()), this ,SLOT(action_exo5()));
};
void tableau_bord::action_exo5(){
    delete exo5;
    bout_exo5 = 0;
    if(p.s->T3.getEtat()>0)
        note += 2;
    p.s->revenir_system_depart();
    p.exo5();
    dessin_system();

    exo6 = new QPushButton("Exercice 6",this);
    bout_exo6 = 1;
    layout->addWidget(exo6, 4, 1);

    (*(this)).setLayout(layout);
    QObject::connect(exo6, SIGNAL(clicked()), this ,SLOT(action_exo6()));
};
void tableau_bord::action_exo6(){
    delete exo6;
    bout_exo6 = 0;
    if(p.s->T1.getEtat()>0)
        note += 2;
    p.s->revenir_system_depart();
    p.exo6();
    dessin_system();
    
    bout_fin = 1;
    fin = new QPushButton("Fin du Test",this);
    layout->addWidget(fin, 4, 1);

    (*(this)).setLayout(layout);
    QObject::connect(fin, SIGNAL(clicked()), this ,SLOT(action_fin()));

};

void tableau_bord::action_fin(){
    delete fin;
    bout_fin = 0;
    if(p.s->T1.getEtat()>0 && p.s->T2.getEtat()>0 && p.s->M1.alim->getEtat()==1.0 && p.s->M2.alim->getEtat()==1.0
        &&p.s->M3.alim->getEtat()==1.0)
        note += 3;
    cout << "Votre note est de " << note << " sur 10." << endl;
    if(pilote_actuel==1)
        p1.ajouter_note_hist(this->note);
    if(pilote_actuel==2)
        p2.ajouter_note_hist(this->note);
    if(pilote_actuel==3)
        p3.ajouter_note_hist(this->note);

   

    p.s->revenir_system_depart();
    dessin_system();
     
     bout_test = 1;
     test = new QPushButton("Lancer Test",this);

    
    layout->addWidget(test, 4, 1);
    if(creation_hist==1)
    {
      delete affich_hist;
      affich_hist = new QPushButton("Afficher historique",this);
    } 

    else
    {        
      affich_hist = new QPushButton("Afficher historique",this);
      creation_hist=1;
    }
    layout->addWidget(affich_hist, 4, 2);

    (*(this)).setLayout(layout);
    QObject::connect(test, SIGNAL(clicked()), this ,SLOT(action_test()));
    QObject::connect(affich_hist, SIGNAL(clicked()), this ,SLOT(action_historique()));

}

void tableau_bord::action_historique(){
    
    if(pilote_actuel==1)
        p1.afficher_historique();
    if(pilote_actuel==2)
        p2.afficher_historique();
     if(pilote_actuel==3)
        p3.afficher_historique();
    
}

tableau_bord::~tableau_bord(){
	delete VT12;
	delete VT23;
	delete P12_marche;
	delete P22_marche;
	delete P32_marche;
    delete P12_arret;
    delete P22_arret;
    delete P32_arret;
	delete V12;
	delete V13;
	delete V23;
	delete quitter;

     if(bout_p1)
        delete pilote1;
    if(bout_p2)
        delete pilote2;
    if(bout_p3)
        delete pilote3;
    if(bout_exo1)
        delete exo1;
    if(bout_exo2)
        delete exo2;
    if(bout_exo3)
        delete exo3;
    if(bout_exo4)
        delete exo4;
    if(bout_exo5)
        delete exo5;
    if(bout_exo6)
        delete exo6;
    if(bout_test)
        delete test;
	delete layout;
}

   
   
dessine_system& tableau_bord::get_system()
{
    return s;
}