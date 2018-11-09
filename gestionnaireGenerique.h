/********************************************
* Titre: Travail pratique #5 - gestionnaireGenerique.h
* Date: 4 novembre 2018
* Auteur: Ryan Hardie
*******************************************/

template<typename T, typename C, typename D>
class GestionnaireGenerique {

public:
	C getConteneur() const {

		return C;
	}

	void ajouter(T t) {

	
	}

	int getNombreElements() const {

	}

	D getElementParIndex(int i) const {

	}

private:
	C conteneur_;

};