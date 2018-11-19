/********************************************
* Titre: Travail pratique #5 - gestionnaireUtilisateurs.cpp
* Date: 4 novembre 2018
* Auteur: Ryan Hardie
*******************************************/

#include "gestionnaireUtilisateurs.h"
#include "utilisateurPremium.h"
#include "utilisateurRegulier.h"
using namespace std::placeholders;

bool  GestionnaireUtilisateurs::estExistant(Utilisateur* utilisateur) {
	bool testSurBooleen = false;

	for (auto positionIterateur = conteneur_.begin(); positionIterateur != conteneur_.end() && testSurBooleen == false; positionIterateur)
		if (positionIterateur->first == utilisateur)
			testSurBooleen = true;

	return testSurBooleen;
}

//Methodes possibles a appeler comme predicats:
//predicate estMax
/*bool estMax(pair<Utilisateur*,double>& userMax) {
	double max = 0.0;
	if (userMax.second > max)
		max = userMax.second;
	return userMax.second > max;
}*/

//predicate estMin
/*bool estMin(pair<Utilisateur*, double>& userMin) {

	double min = 0.0;
	if (userMin.second < min)
		min = userMin.second;
	return userMin.second < min;
}*/

pair<Utilisateur*, double>& GestionnaireUtilisateurs::getMax() const {
	double max = 0.0;
	pair <Utilisateur*, double> userMax, iterateurPredicate;
	for (auto it = conteneur_.begin(); it != conteneur_.end(); it++){

		if (it->second > max) {
			max = it->second;
			userMax = make_pair(it->first, max);
		} 
		// Ou utiliser des fonctions lambda ou predicats ( plus propre, avec un find_if)
		  //map<Utilisateur*, double>::iterator itUserMax;
		//auto itUserMax = find_if(conteneur_.begin(), conteneur_.end(), estMax(iterateurPredicate));
		//return make_pair(itUserMax->first,it->second);
	}
	return userMax;

}

pair<Utilisateur*, double>& GestionnaireUtilisateurs::getMin() const {
	double min = 0.0;
	pair<Utilisateur*, double> userMin;

	for (auto it = conteneur_.begin(); it != conteneur_.end(); it++) {

		if (min > it->second) {
			min = it->second;
			userMin = make_pair(it->first, min);
		}

	}

	return userMin;

}

Utilisateur* GestionnaireUtilisateurs::getUtilisateurSuivant(Utilisateur* utilisateur, double montant) const {

	auto it = find_if(conteneur_.begin(), conteneur_.end(), bind(equal_to<pair<Utilisateur*,double>>(),_1,make_pair(utilisateur,montant)));

	return it->first;
}

vector<pair<Utilisateur*, double>> GestionnaireUtilisateurs::getUtilisateursEntre(double borneInf, double borneSup) const {
	FoncteurIntervalle intervalle(borneInf,borneSup);
	vector<pair<Utilisateur*, double>> utilisateursInclus;

	copy_if(conteneur_.begin(), conteneur_.end(), back_inserter(utilisateursInclus), FoncteurIntervalle(borneInf,borneSup)); // cette ligne ne se fait pas : il faut definir un foncteur de type FoncteurIntervalle
//	auto it = copy_if(conteneur_.begin(), conteneur_.end(), back_inserter(utilisateursInclus), [intervalle](pair<Utilisateur*, double> t) { return intervalle(t.second)};
	/*for (auto it = conteneur_.begin(); it != conteneur_.end(); it++) {

		if (intervalle(it->second) == true) {
			utilisateursInclus.push_back(*it);
		}
	}*/

	return utilisateursInclus;
}

GestionnaireUtilisateurs& GestionnaireUtilisateurs::setCompte(pair<Utilisateur*, double> p) {
//	pair<Utilisateur*, double> test = make_pair(p.first,p.second);
	Utilisateur * userTmp = p.first;
	auto it = find_if(conteneur_.begin(), conteneur_.end(), [userTmp](pair<Utilisateur*, double> valeur) { return valeur.first->getNom() == userTmp->getNom(); });
//	auto it = find_if(conteneur_.begin(), conteneur_.end(), getUtilisateurSuivant(p.first,p.second));

	it->second += p.second;

	return *this;
}

void GestionnaireUtilisateurs::mettreAJourComptes(Utilisateur* payePar, double montant) {

	for (auto it = conteneur_.begin(); it != conteneur_.end(); it++) {
			
		if (it->first->getNom() == payePar->getNom())
			setCompte(make_pair(it->first, +montant));
		else
			setCompte(make_pair(it->first, -1*montant));
		
	}

}