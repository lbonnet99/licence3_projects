#include "dessine_system.hh"



dessine_system::dessine_system():QGraphicsScene(){
	ligneT1T2 = new QLine(100, 50, 200, 50);
	ligneT2T3 = new QLine(300, 50, 400, 50);
	ligne1T1M1 = new QLine(70,100,70,230);
	ligne2T1M1 = new QLine(70,200,55,200);
	ligne3T1M1 = new QLine(55,200,55,300);
	ligne1T1M3 = new QLine(70,150,445,150);
	ligne2T1M3 = new QLine(445,150,445,300);
	ligne1T2M2 = new QLine(245,100,245,200);
	ligne2T2M2 = new QLine(245,200,255,200);
	ligne3T2M2 = new QLine(255,200,255,300);
	ligne1T1M2 = new QLine(70,230,255,230);
	ligne1T3M2 = new QLine(435,100,435,255);
	ligne2T3M2 = new QLine(435,255,255,255);
	ligne1T3M3 = new QLine(435,200,445,200);

	rectangleM1 = new QRect(20, 300, 50, 100);
	rectangleM2 = new QRect(220, 300, 50, 100);
	rectangleM3 = new QRect(420, 300, 50, 100);

	rectangleT1 = new QRect(0, 0, 100, 100);
	rectangleT2 = new QRect(200, 0, 100, 100);
	rectangleT3 = new QRect(400, 0, 100, 100);

	rectangleVT12_ouvert = new QRect(145,30,10,40);
	rectangleVT23_ouvert = new QRect(345,30,10,40);
	rectangleV12_ouvert = new QRect(145,210,10,40);
	rectangleV13_ouvert = new QRect(325,130,10,40);
	rectangleV23_ouvert = new QRect(345,235,10,40);

	rectangleVT12_ferme = new QRect(130,45,40,10);
	rectangleVT23_ferme = new QRect(330,45,40,10);
	rectangleV12_ferme = new QRect(130,225,40,10);
	rectangleV13_ferme = new QRect(310,145,40,10);
	rectangleV23_ferme = new QRect(330,250,40,10);



}


void dessine_system::ajout_lignes(){
	(*this).addLine(*ligneT1T2);
	(*this).addLine(*ligneT2T3);
	(*this).addLine(*ligne1T1M1);
	(*this).addLine(*ligne2T1M1);
	(*this).addLine(*ligne3T1M1);
	(*this).addLine(*ligne1T1M3);
	(*this).addLine(*ligne2T1M3);
	(*this).addLine(*ligne1T2M2);
	(*this).addLine(*ligne2T2M2);
	(*this).addLine(*ligne3T2M2);
	(*this).addLine(*ligne1T1M2);
	(*this).addLine(*ligne1T3M2);
	(*this).addLine(*ligne2T3M2);
	(*this).addLine(*ligne1T3M3);


}

void dessine_system::ajout_moteurs(){
	QPen penM(Qt::gray);
	QBrush brushM(Qt::gray);
	(*this).addRect(*rectangleM1, penM, brushM);
	(*this).addRect(*rectangleM2, penM, brushM);
	(*this).addRect(*rectangleM3, penM, brushM);

};

void dessine_system::ajout_T1_rempli(){
	QPen penT(Qt::black);
	QBrush brushT(Qt::blue);//bleu pour plein et blanc pour vide

	(*this).addRect(*rectangleT1, penT, brushT);
};

void dessine_system::ajout_T2_rempli(){
	QPen penT(Qt::black);
	QBrush brushT(Qt::blue);//bleu pour plein et blanc pour vide

	(*this).addRect(*rectangleT2, penT, brushT);
};

void dessine_system::ajout_T3_rempli(){
	QPen penT(Qt::black);
	QBrush brushT(Qt::blue);//bleu pour plein et blanc pour vide

	(*this).addRect(*rectangleT3, penT, brushT);
};

void dessine_system::ajout_T1_vide(){
	QPen penT(Qt::black);
	QBrush brushT(Qt::white);//bleu pour plein et blanc pour vide

	(*this).addRect(*rectangleT1, penT, brushT);
};

void dessine_system::ajout_T2_vide(){
	QPen penT(Qt::black);
	QBrush brushT(Qt::white);//bleu pour plein et blanc pour vide

	(*this).addRect(*rectangleT2, penT, brushT);
};

void dessine_system::ajout_T3_vide(){
	QPen penT(Qt::black);
	QBrush brushT(Qt::white);//bleu pour plein et blanc pour vide

	(*this).addRect(*rectangleT3, penT, brushT);
};

void dessine_system::ajout_cercles_noir_vannes(){
	QBrush blackBrush(Qt::black);
    QPen blackPen(Qt::black);

    (*this).addEllipse(130, 30, 40, 40, blackPen, blackBrush);//VT12
	(*this).addEllipse(330, 30, 40, 40, blackPen, blackBrush);//VT23

	(*this).addEllipse(130, 210, 40, 40, blackPen, blackBrush);//V12
	(*this).addEllipse(310, 130, 40, 40, blackPen, blackBrush);//V13
	(*this).addEllipse(330, 235, 40, 40, blackPen, blackBrush);//V23

};


void dessine_system::ajout_P11_arret(){
	QBrush blackBrush(Qt::black);
    QPen blackPen(Qt::black);
    (*this).addEllipse(5,50,40,40, blackPen,blackBrush);//P11

};

void dessine_system::ajout_P11_marche(){
	QBrush greenBrush(Qt::green);
    QPen blackPen(Qt::black);
    (*this).addEllipse(5,50,40,40, blackPen,greenBrush);//P11
};

void dessine_system::ajout_P11_panne(){
	QBrush redBrush(Qt::red);
    QPen blackPen(Qt::black);
    (*this).addEllipse(5,50,40,40, blackPen,redBrush);//P11
};	

void dessine_system::ajout_P12_arret(){
	QBrush blackBrush(Qt::black);
    QPen blackPen(Qt::black);
    (*this).addEllipse(55,50,40,40, blackPen,blackBrush);//P12
};

void dessine_system::ajout_P12_marche(){
	QBrush greenBrush(Qt::green);
    QPen blackPen(Qt::black);
    (*this).addEllipse(55,50,40,40, blackPen,greenBrush);//P12
};

void dessine_system::ajout_P12_panne(){
	QBrush redBrush(Qt::red);
    QPen blackPen(Qt::black);
    (*this).addEllipse(55,50,40,40, blackPen,redBrush);//P12
};
	
void dessine_system::ajout_P21_arret(){
	QBrush blackBrush(Qt::black);
    QPen blackPen(Qt::black);
    (*this).addEllipse(205,50,40,40,blackPen,blackBrush);//P21	
};

void dessine_system::ajout_P21_marche(){
	QBrush greenBrush(Qt::green);
    QPen blackPen(Qt::black);
    (*this).addEllipse(205,50,40,40,blackPen,greenBrush);//P21	
};

void dessine_system::ajout_P21_panne(){
	QBrush redBrush(Qt::red);
    QPen blackPen(Qt::black);
    (*this).addEllipse(205,50,40,40,blackPen,redBrush);//P21	
};

void dessine_system::ajout_P22_arret(){
	QBrush blackBrush(Qt::black);
    QPen blackPen(Qt::black);
    (*this).addEllipse(255,50,40,40,blackPen,blackBrush);//P22
};

void dessine_system::ajout_P22_marche(){
	QBrush greenBrush(Qt::green);
    QPen blackPen(Qt::black);
    (*this).addEllipse(255,50,40,40,blackPen,greenBrush);//P22
};

void dessine_system::ajout_P22_panne(){
	QBrush redBrush(Qt::red);
    QPen blackPen(Qt::black);
    (*this).addEllipse(255,50,40,40,blackPen,redBrush);//P22
};

void dessine_system::ajout_P31_arret(){
	QBrush blackBrush(Qt::black);
    QPen blackPen(Qt::black);
    (*this).addEllipse(405,50,40,40,blackPen,blackBrush);//P31	
};

void dessine_system::ajout_P31_marche(){
	QBrush greenBrush(Qt::green);
    QPen blackPen(Qt::black);
    (*this).addEllipse(405,50,40,40,blackPen,greenBrush);//P31	
};

void dessine_system::ajout_P31_panne(){
	QBrush redBrush(Qt::red);
    QPen blackPen(Qt::black);
    (*this).addEllipse(405,50,40,40,blackPen,redBrush);//P31	
};

void dessine_system::ajout_P32_arret(){
	QBrush blackBrush(Qt::black);
    QPen blackPen(Qt::black);
    (*this).addEllipse(455,50,40,40,blackPen,blackBrush);//P32
};

void dessine_system::ajout_P32_marche(){
	QBrush greenBrush(Qt::green);
    QPen blackPen(Qt::black);
    (*this).addEllipse(455,50,40,40,blackPen,greenBrush);//P32
};

void dessine_system::ajout_P32_panne(){
	QBrush redBrush(Qt::red);
    QPen blackPen(Qt::black);
    (*this).addEllipse(455,50,40,40,blackPen,redBrush);//P32
};

/*

void dessine_system::ajout_cercles(){
	QBrush blackBrush(Qt::black);
    QPen blackPen(Qt::black);

	(*this).addEllipse(130, 30, 40, 40, blackPen, blackBrush);//VT12
	(*this).addEllipse(330, 30, 40, 40, blackPen, blackBrush);//VT23

	(*this).addEllipse(130, 210, 40, 40, blackPen, blackBrush);//V12
	(*this).addEllipse(310, 130, 40, 40, blackPen, blackBrush);//V13
	(*this).addEllipse(330, 235, 40, 40, blackPen, blackBrush);//V23

	QBrush bpmarche(Qt::green);
    QPen ppmarche(Qt::black);

	QBrush bppanne(Qt::red);
    QPen pppanne(Qt::black);


	(*this).addEllipse(5,50,40,40, ppmarche,bpmarche);//P11
	(*this).addEllipse(55,50,40,40, blackPen,blackBrush);//P12

	(*this).addEllipse(205,50,40,40,ppmarche,bpmarche);//P21	
	(*this).addEllipse(255,50,40,40,blackPen,blackBrush);//P22

	(*this).addEllipse(405,50,40,40,ppmarche,bpmarche);//P31	
	(*this).addEllipse(455,50,40,40,blackPen,blackBrush);//P32
}*/

dessine_system::~dessine_system(){
	delete ligneT1T2;
	delete ligneT2T3;
	delete ligne1T1M1;
	delete ligne2T1M1;
	delete ligne3T1M1;
	delete ligne1T1M3;
	delete ligne2T1M3;
	delete ligne1T2M2;
	delete ligne2T2M2;
	delete ligne3T2M2;
	delete ligne1T1M2;
	delete ligne1T3M2;
	delete ligne2T3M2;
	delete ligne1T3M3;

	delete rectangleM1;
	delete rectangleM2;
	delete rectangleM3;

	delete rectangleT1;
	delete rectangleT2;
	delete rectangleT3;

	delete rectangleVT12_ouvert;
	delete rectangleVT23_ouvert;
	delete rectangleV12_ouvert;
	delete rectangleV13_ouvert;
	delete rectangleV23_ouvert;

	delete rectangleVT12_ferme;
	delete rectangleVT23_ferme;
	delete rectangleV12_ferme;
	delete rectangleV13_ferme;
	delete rectangleV23_ferme;
}

void dessine_system::rect_VT12_ferme(){	
	QPen pvanne(Qt::black);
	QBrush bvanne(Qt::white);	

	(*this).addRect(*rectangleVT12_ferme, pvanne, bvanne);
};


void dessine_system::rect_VT12_ouverte(){	
	QPen pvanne(Qt::black);
	QBrush bvanne(Qt::white);	
	(*this).addRect(*rectangleVT12_ouvert, pvanne, bvanne);
};

void dessine_system::rect_VT23_ferme(){
	QPen pvanne(Qt::black);
	QBrush bvanne(Qt::white);	
	(*this).addRect(*rectangleVT23_ferme, pvanne, bvanne);

};

void dessine_system::rect_VT23_ouverte(){
	QPen pvanne(Qt::black);
	QBrush bvanne(Qt::white);
	(*this).addRect(*rectangleVT23_ouvert, pvanne, bvanne);
	

};

void dessine_system::rect_V12_ferme(){
	QPen pvanne(Qt::black);
	QBrush bvanne(Qt::white);;
	(*this).addRect(*rectangleV12_ferme, pvanne, bvanne);

};

void dessine_system::rect_V12_ouverte(){
	QPen pvanne(Qt::black);
	QBrush bvanne(Qt::white);
	(*this).addRect(*rectangleV12_ouvert, pvanne, bvanne);
	
};

void dessine_system::rect_V13_ferme(){
	QPen pvanne(Qt::black);
	QBrush bvanne(Qt::white);
	(*this).addRect(*rectangleV13_ferme, pvanne, bvanne);
	
};

void dessine_system::rect_V13_ouverte(){
	QPen pvanne(Qt::black);
	QBrush bvanne(Qt::white);
	(*this).addRect(*rectangleV13_ouvert, pvanne, bvanne);
	
};

void dessine_system::rect_V23_ferme(){
	QPen pvanne(Qt::black);
	QBrush bvanne(Qt::white);
	(*this).addRect(*rectangleV23_ferme, pvanne, bvanne);

};

void dessine_system::rect_V23_ouverte(){
	QPen pvanne(Qt::black);
	QBrush bvanne(Qt::white);
	(*this).addRect(*rectangleV23_ouvert, pvanne, bvanne);
};
