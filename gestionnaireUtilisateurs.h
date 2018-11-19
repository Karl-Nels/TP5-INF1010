/********************************************
* Titre: Travail pratique #5 - gestionnaireUtilisateurs.h
* Date: 4 novembre 2018
* Auteur: Ryan Hardie
*******************************************/

#pragma once

#include "utilisateur.h"
#include "gestionnaireGenerique.h"
#include"foncteur.h"
#include <vector>
#include <map>
#include<iterator>
#include<algorithm>
#include<functional>

class GestionnaireUtilisateurs: public GestionnaireGenerique<Utilisateur*,map<Utilisateur*,double>,pair<Utilisateur*,double>,AjouterUtilisateur> {
public:
	bool estExistant(Utilisateur* utilisateur);
	pair<Utilisateur*, double>& getMax() const; // Fait
	pair<Utilisateur*, double>& getMin() const; // Fait
	Utilisateur* getUtilisateurSuivant(Utilisateur* utilisateur, double montant) const; // Fait
	vector<pair<Utilisateur*, double>> getUtilisateursEntre(double borneInf, double borneSup) const; // Fait
	GestionnaireUtilisateurs& setCompte(pair<Utilisateur*, double> p); // Fait
	void mettreAJourComptes(Utilisateur* payePar, double montant);
};