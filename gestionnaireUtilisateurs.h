/********************************************
* Titre: Travail pratique #5 - gestionnaireUtilisateurs.h
* Date: 4 novembre 2018
* Auteur: Ryan Hardie
*******************************************/

#pragma once

#include "utilisateur.h"

#include <vector>

class GestionnaireUtilisateurs {
public:
	Utilisateur* getUtilisateurParIndex(int i) const;
	vector<Utilisateur*> getUtilisateurs() const;
	int getNombreUtilisateurs() const;
	int getIndexDe(Utilisateur* utilisateur) const;

	
	GestionnaireUtilisateurs& ajouterUtilisateur(Utilisateur* utilisateur);

private:
	vector<Utilisateur*> utilisateurs_;
};