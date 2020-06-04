#ifndef PILOTE_HH
#define PILOTE_HH

#include <string>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>


using namespace std;

struct elem_note
{
    int h_note;
    elem_note* suivant;
};

class Pilote
{
	private :
	string id;
	string mdp;
	elem_note* historique;

	public:
	Pilote();
	Pilote(string ID, string MDP);
	void ajouter_note_hist(int note);
	void afficher_historique();
	void ecrire_historique();
	int nb_elements_historique();
	int calculer_moyenne();
	~Pilote();

	friend class tableau_bord;
	
};




#endif