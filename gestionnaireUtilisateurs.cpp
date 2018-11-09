/********************************************
* Titre: Travail pratique #5 - gestionnaireUtilisateurs.cpp
* Date: 4 novembre 2018
* Auteur: Ryan Hardie
*******************************************/

#include "gestionnaireUtilisateurs.h"
#include "utilisateurPremium.h"
#include "utilisateurRegulier.h"

Utilisateur* GestionnaireUtilisateurs::getUtilisateurParIndex(int i) const
{
	return utilisateurs_[i];
}

vector<Utilisateur*> GestionnaireUtilisateurs::getUtilisateurs() const
{
	return utilisateurs_;
}

int GestionnaireUtilisateurs::getNombreUtilisateurs() const
{
	return utilisateurs_.size();
}

int GestionnaireUtilisateurs::getIndexDe(Utilisateur * utilisateur) const
{
	int index = -1;
	for (int i = 0; i < utilisateurs_.size(); i++) {
		if (utilisateurs_[i] == utilisateur) {
			index = i;
			break;
		}
	}
	return index;
}

GestionnaireUtilisateurs& GestionnaireUtilisateurs::ajouterUtilisateur(Utilisateur * utilisateur)
{
	UtilisateurRegulier* utilisateurRegulier = dynamic_cast<UtilisateurRegulier*>(utilisateur);
	UtilisateurPremium* utilisateurPremium = dynamic_cast<UtilisateurPremium*>(utilisateur);

	if (utilisateurRegulier != nullptr) {
		if (!utilisateurRegulier->getPossedeGroupe()) {
			utilisateurRegulier->setPossedeGroupe(true);
		}
		else {
			cout << "Erreur : L'utilisateur " << utilisateur->getNom() << " n'est pas un utilisateur premium et est deja dans un groupe." << endl;
			return *this;
		}
	}
	else {
		if (utilisateurPremium != nullptr && utilisateurPremium->getJoursRestants() <= 0) {
			cout << "Erreur : L'utilisateur " << utilisateur->getNom() << " doit renouveler son abonnement premium" << endl;
			return *this;
		}
	}

	utilisateurs_.push_back(utilisateur);
	return *this;
}
