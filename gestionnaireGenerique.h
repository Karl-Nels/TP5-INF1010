/********************************************
* Titre: Travail pratique #5 - gestionnaireGenerique.h
* Date: 4 novembre 2018
* Auteur: Ryan Hardie
*******************************************/
#include "foncteur.h"

template<typename T, typename C, typename D,typename FoncteurAjouter>
class GestionnaireGenerique {

public:
	C getConteneur() const {

		return C;
	}


	void ajouter(T t) {
		FoncteurAjouter ajout(conteneur_);
		conteneur_ = ajout(t);
	}

	int getNombreElements() const {

		return conteneur_.size();
	}

	D getElementParIndex(int i) const {
		iterator it;
		int counter = i;
		for (it = conteneur_.begin(); it != conteneur_.end() && counter ==0 ; it++) {
			it++;
			counter--;
		}
		
		D = *it;
		return D;
	}

protected:
	C conteneur_;

};