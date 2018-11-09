/********************************************
* Titre: Travail pratique #5 - groupe.h
* Date: 4 novembre 2018
* Auteur: Ryan Hardie
*******************************************/

#ifndef GROUPE_H
#define GROUPE_H

#include <string>
#include <vector>

#include "depense.h"
#include "utilisateurPremium.h"
#include "utilisateurRegulier.h"
#include "transfertInterac.h"
#include "transfertPaypal.h"

#include "gestionnaireDepenses.h"
#include "gestionnaireUtilisateurs.h"

using namespace std;

class Groupe {
public:
	// Constructeurs
	Groupe();
	Groupe(const string& nom);

	// Destructeur
	~Groupe();

	// Methodes d'acces
	string getNom() const;
	vector<Transfert*> getTransferts() const;

	// TODO : À modifier :
	vector<double> getComptes() const;
	double getTotalDepenses() const;
	vector<Depense*> getDepenses() const;
	vector<Utilisateur*> getUtilisateurs() const;

	// Ajouté :
	GestionnaireUtilisateurs* getGestionnaireUtilisateurs();
	GestionnaireDepenses* getGestionnaireDepenses();

	// Methodes de modification
	void setNom(const string& nom);

	// Methodes d'ajout
	Groupe& ajouterDepense(double montant, Utilisateur* payePar, const string& nom = "", const string& lieu = "Montreal");
	Groupe& operator+=(Utilisateur* utilisateur);

	// Methodes de calcul
	void equilibrerComptes();

	// Methode d'affichage
	friend ostream& operator<<(ostream& os, const Groupe& groupe);

private:
	string nom_;
	vector<Transfert*> transferts_;

	// TODO : À modifier :
	vector<double> comptes_;

	// Retiré :
	// vector<Utilisateur*> utilisateurs_;
	// vector<Depense*> depenses_;

	// Ajouté :
	GestionnaireUtilisateurs* gestionnaireUtilisateurs_;
	GestionnaireDepenses* gestionnaireDepenses_;
};

#endif
