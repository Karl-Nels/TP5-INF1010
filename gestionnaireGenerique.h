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

		return conteneur_.size();
		
	}

	D getElementParIndex(int i) const {

		int counter = i;
		vector<Utilisateur*>::iterator itVecteur;
		Utilisateur* userTmp;

		/*if (dynamic_cast<Depense*>(conteneur_[i]) != nullptr)
			return conteneur_[i];
		else {*/
			for (auto it = conteneur_.begin(); it != conteneur_.end() && counter != 0; it++) {
				counter--;

				if (counter == 0)
					return it->first;
			}
		
			/*for (unsigned j = 0; j < conteneur_.size(); j++) {
			counter--;

			if (counter == 0)
				return conteneur_[j];
		
		}
	*/		
	}
	

protected:
	C conteneur_;

};