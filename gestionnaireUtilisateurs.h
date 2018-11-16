/********************************************
* Titre: Travail pratique #5 - gestionnaireUtilisateurs.h
* Date: 4 novembre 2018
* Auteur: Ryan Hardie
*******************************************/

#pragma once

#include "utilisateur.h"
#include "gestionnaireGenerique.h"
#include <vector>
#include <map>
#include<iterator>
#include<algorithm>
#include"utilisateur.h"

class GestionnaireUtilisateurs: public GestionnaireGenerique<Utilisateur*,map<Utilisateur*,double>,Utilisateur*,AjouterUtilisateur> {
public:
	int estExistant(Utilisateur* utilisateur);
};