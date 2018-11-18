/********************************************
* Titre: Travail pratique #5 - gestionnaireUtilisateurs.cpp
* Date: 4 novembre 2018
* Auteur: Ryan Hardie
*******************************************/

#include "gestionnaireUtilisateurs.h"
#include "utilisateurPremium.h"
#include "utilisateurRegulier.h"

bool  GestionnaireUtilisateurs::estExistant(Utilisateur* utilisateur) {

	//map<Utilisateur*, double>::iterator it, it1;

	/*auto existe = [utilisateur](map<Utilisateur*, double>::iterator iterateur) -> bool {

		return iterateur->first == utilisateur;
	};*/  //Test sur lamda a effecteuer plus tard

	/*	it = find_if(conteneur_.begin(), conteneur_.end(), existe(it1));

	if (it != conteneur_.end())
	return 1;
	else
	return 0;
	}*/

	map<Utilisateur*, double>::iterator  test;
	test = conteneur_.begin();
	bool testSurBooleen = false;

	for (test = conteneur_.begin(); test != conteneur_.end() && testSurBooleen == false; test++)
		if (test->first == utilisateur) 
			testSurBooleen = true;

	return testSurBooleen;
}
