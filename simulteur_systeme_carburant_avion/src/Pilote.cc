#include "Pilote.hh"



Pilote::Pilote():id(),mdp(){
	historique = NULL;
};

Pilote::Pilote(string ID, string MDP):id(ID),mdp(MDP){
	historique = NULL;
};

void Pilote::ajouter_note_hist(int note){
    elem_note* new_element = new elem_note;
    new_element->h_note = note;
    new_element->suivant = NULL;
    if(historique==NULL){historique = new_element;}
    else {
        elem_note* tmp = historique;
        while(tmp->suivant != NULL)
            tmp = tmp->suivant;
        tmp->suivant = new_element;
    }
};

void Pilote::afficher_historique(){
	cout << "L'historique du pilote " << id << " est : " << endl;
    elem_note* tmp = historique;
    if(tmp==NULL) cout << "vous n'avez pas de note" << endl;
    while(tmp!=NULL){
        cout << tmp->h_note << " sur 10." << endl;
        tmp = tmp->suivant;
    }   
};

void Pilote::ecrire_historique(){
	string nomfic = "historique_pilote" + id + ".txt"; 
	ofstream fout(nomfic,ios::app);
    fout << "L'historique du pilote " << id << " est : " << endl;
    elem_note* tmp = historique;
    if(tmp==NULL) fout << "vous n'avez pas de note" << endl;
    while(tmp!=NULL){
        fout << tmp->h_note << " sur 10." << endl;
        tmp = tmp->suivant;
    }   
    fout << "La moyenne est " << calculer_moyenne() << " sur 10." << endl;
    fout.close();
    
};

int Pilote::nb_elements_historique(){
	elem_note* tmp = historique;
	int nb_elem = 0;
	 if(tmp==NULL) nb_elem = 0;
    while(tmp!=NULL){
        nb_elem ++;
        tmp = tmp->suivant;
    }   
	return nb_elem;
};

int Pilote::calculer_moyenne(){
	int denom = 0;
	elem_note* tmp = historique;
	 if(tmp==NULL) return -1;
    while(tmp!=NULL){
        denom += tmp->h_note;
        tmp = tmp->suivant;
    }   
	return denom/nb_elements_historique();

};


Pilote::~Pilote(){
	 if (historique!=NULL){
        while(historique->suivant!=NULL){
            elem_note* tmp = historique;
            historique = historique->suivant;
            delete tmp;
        }
        delete historique;
        historique = NULL;
    }
        
};