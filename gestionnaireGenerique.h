/********************************************
* Titre: Travail pratique #5 - gestionnaireGenerique.h
* Date: 4 novembre 2018
* Auteur: Ryan Hardie
*******************************************/
#pragma once

#include "foncteur.h"

template<typename T, typename C, typename D,typename FoncteurAjouter>
class GestionnaireGenerique {

public:
	C getConteneur() const {

		return conteneur_;
	}


	void ajouter(T t) {
		FoncteurAjouter ajout(conteneur_);
		conteneur_ = ajout(t);
	}

	int getNombreElements() const {

		return int(conteneur_.size());
		
	}

	D getElementParIndex(int i) const { // Test resolution external symbol (changer le type de getElementparIndex)
		pair<Utilisateur*, double> user;
		int counter = i;

		//vector<Utilisateur*>::iterator itVecteur;

		/*if (dynamic_cast<Depense*>(conteneur_[i]) != nullptr)
			return conteneur_[i];
		else {*/
			for (auto it = conteneur_.begin(); it != conteneur_.end() && counter != 1; it++) {
				counter--;
				
				if (counter == 1) {
					user = pair<Utilisateur*, double>(it->first, 0.0);
					break;
				}
			}
			return user;
	}
	

protected:
	C conteneur_;

};