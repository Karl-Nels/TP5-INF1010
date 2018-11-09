/********************************************
* Titre: Travail pratique #5 - foncteur.h
* Date: 4 novembre 2018
* Auteur: Ryan Hardie
*******************************************/
#include <map>

class AjouterDepense{
public:
AjouterDepense(vector<Depense*> conteneur): conteneur_(conteneur){

};
vector<Depense*>& operator()(Depense* depense) {

	conteneur_.push_back(depense);

	return conteneur_;
};

private:
vector<Depense*> conteneur_;
};




class AjouterUtilisateur {

public:
	AjouterUtilisateur(map<Utilisateur*, double>conteneur):conteneur_(conteneur){
	}

	map<Utilisateur*, double>& operator()(Utilisateur* utilisateur) {

		pair<Utilisateur*, double> newUser(utilisateur,0);

		conteneur_.insert(newUser);
	}

private:
	map<Utilisateur*, double> conteneur_;
};




class FoncteurIntervalle {

public:
	FoncteurIntervalle(double borneInf, double borneSup): borneInf_(borneInf), borneSup_(borneSup) {

	}
	bool operator()(double valeur) {

		return ((valeur <= borneSup_) && (valeur >= borneInf_));
		}

private:
	double borneInf_, borneSup_;
};