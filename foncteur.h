/********************************************
* Titre: Travail pratique #5 - foncteur.h
* Date: 4 novembre 2018
* Auteur: Ryan Hardie
*******************************************/
#include <map>
#include "utilisateurPremium.h"
#include "utilisateurRegulier.h"

#pragma once
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

		UtilisateurRegulier* utilisateurRegulier = dynamic_cast<UtilisateurRegulier*>(utilisateur);
		UtilisateurPremium* utilisateurPremium = dynamic_cast<UtilisateurPremium*>(utilisateur);

		if (utilisateurRegulier != nullptr) {
			
			if (!utilisateurRegulier->getPossedeGroupe()) {
				utilisateurRegulier->setPossedeGroupe(true);
			}
			else {
				cout << "Erreur: L'utilisateur " << utilisateurRegulier->getNom()
					<< " n'est pas un utilisateur premium et appartient deja a un groupe" << endl;
				return conteneur_;
			}
		}
		else {

			if (utilisateurPremium != nullptr && utilisateurPremium->getJoursRestants() <= 0) {
				cout << "Erreur: L'utilisateur " << utilisateur->getNom() << " doit renouveler son abonnement premium" << endl;
				return conteneur_;
			}
		}

		pair<Utilisateur*, double> newUser(utilisateur,0);

		conteneur_.insert(newUser);
		return conteneur_;
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