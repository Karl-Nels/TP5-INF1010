/********************************************
* Titre: Travail pratique #5 - groupe.cpp
* Date: 4 novembre 2018
* Auteur: Ryan Hardie
*******************************************/

#include "groupe.h"
#pragma once
// Constructeurs
Groupe::Groupe() {
	nom_ = "";
	gestionnaireDepenses_ = new GestionnaireDepenses();
	gestionnaireUtilisateurs_ = new GestionnaireUtilisateurs();
}

Groupe::Groupe(const string& nom) : nom_(nom) {
	gestionnaireDepenses_ = new GestionnaireDepenses();
	gestionnaireUtilisateurs_ = new GestionnaireUtilisateurs();
}

Groupe::~Groupe() {
	vector<Depense*> depenses = gestionnaireDepenses_->getConteneur();
	for (int i = 0; i < depenses.size(); i++) {
		delete depenses[i];
	}
	for (int i = 0; i < transferts_.size(); i++) {
		delete transferts_[i];
	}

	delete gestionnaireDepenses_;
	delete gestionnaireUtilisateurs_;
}

// Methodes d'acces
string Groupe::getNom() const {
	return nom_;
}

// TODO : À modifier :
vector<Depense*> Groupe::getDepenses() const
{
	return gestionnaireDepenses_->getConteneur();
}

// TODO : À modifier :
map<Utilisateur*,double> Groupe::getUtilisateurs() const // Resolu
{
	return gestionnaireUtilisateurs_->getConteneur();
}

vector<Transfert*> Groupe::getTransferts() const
{
	return transferts_;
}

// TODO : À modifier :
vector<double> Groupe::getComptes() const { // Declaration variable necessaire?
		
	vector<double> elements;
	map<Utilisateur*, double> conteneur = gestionnaireUtilisateurs_->getConteneur();

	for (auto it = conteneur.begin(); it != conteneur.end(); it++) {

		elements.push_back(it->second);
	}

	return elements;
}

double Groupe::getTotalDepenses() const { 
	
return gestionnaireDepenses_->getTotalDepenses();
}

GestionnaireUtilisateurs * Groupe::getGestionnaireUtilisateurs()
{
	return gestionnaireUtilisateurs_;
}

GestionnaireDepenses * Groupe::getGestionnaireDepenses()
{
	return gestionnaireDepenses_;
}

// Methodes de modifications
void Groupe::setNom(const string& nom) {
	nom_ = nom;
}

//Methodes ajoutees(retour de pointeur sur les Gestionnaires depenses et  utilisateurs
GestionnaireUtilisateurs* Groupe::getGestionnaireUtilisateurs() {

	return gestionnaireUtilisateurs_;
}

GestionnaireDepenses* Groupe::getGestionnaireDepenses() {

	return gestionnaireDepenses_;
}

// Methodes d'ajout
// TODO : À modifier :
Groupe& Groupe::ajouterDepense(double montant, Utilisateur* payePar, const string& nom, const string& lieu)
{
	// Trouver l'index de l'auteur de la depense
	int indexPayePar = gestionnaireUtilisateurs_->estExistant(payePar);

	if (indexPayePar == -1) {
		return *this;
	}

	Depense* depense = new Depense(nom, montant, lieu);

	// Modifié :
	// depenses_.push_back(depense);

	// Ajouté :
//	gestionnaireDepenses_->ajouterDepense(depense); // modifie sur la ligne du bas
	gestionnaireDepenses_->ajouter(depense);
	*payePar += depense;

	// Mise a jour des comptes
	double montantReparti = depense->getMontant() / gestionnaireUtilisateurs_->getNombreElements();
	comptes_[indexPayePar] += depense->getMontant() - montantReparti;
	for (int i = 0; i < gestionnaireUtilisateurs_->getNombreElements(); i++) {
		if (i != indexPayePar) {
			comptes_[i] -= montantReparti;
		}
	}
	return *this;
}

Groupe& Groupe::operator+=(Utilisateur* utilisateur)
{
	// Ajouté :
//	gestionnaireUtilisateurs_->ajouterUtilisateur(utilisateur);
	gestionnaireUtilisateurs_->ajouter(utilisateur);

	comptes_.push_back(0);
	return *this;
}

// TODO : À modifier :
void Groupe::equilibrerComptes() {

	bool calcul = true;
	int count = 0;
	while (calcul) {
		double max = 0;
		double min = 0;
		int indexMax = 0;
		int indexMin = 0;

		// On cherche le compte le plus eleve et le moins eleve
		for (int i = 0; i < gestionnaireUtilisateurs_->getNombreElements(); i++) {
			if (comptes_[i] > max) {
				max = comptes_[i];
				indexMax = i;
			}
			if (comptes_[i] < min) {
				min = comptes_[i];
				indexMin = i;
			}
		}

		// On cherche lequel des deux a la dette la plus grande
		if (-min <= max && min != 0 && max != 0) {
			if (gestionnaireUtilisateurs_->getElementParIndex(indexMin)->getMethodePaiement() == Interac) {
				TransfertInterac* transfert = new TransfertInterac(-min, gestionnaireUtilisateurs_->getElementParIndex(indexMin), gestionnaireUtilisateurs_->getElementParIndex(indexMax));
				transferts_.push_back(transfert);
				transfert->effectuerTransfert();
			}
			else {
				TransfertPaypal* transfert = new TransfertPaypal(-min, gestionnaireUtilisateurs_->getElementParIndex(indexMin), gestionnaireUtilisateurs_->getElementParIndex(indexMax));
				transferts_.push_back(transfert);
				transfert->effectuerTransfert();
			}
			comptes_[indexMax] += min;
			comptes_[indexMin] = 0;
		}
		else if (-min > max  && min != 0 && max != 0) {
			if (gestionnaireUtilisateurs_->getElementParIndex(indexMin)->getMethodePaiement() == Interac) {
				TransfertInterac* transfert = new TransfertInterac(max, gestionnaireUtilisateurs_->getElementParIndex(indexMin), gestionnaireUtilisateurs_->getElementParIndex(indexMax));
				transferts_.push_back(transfert);
				transfert->effectuerTransfert();
			}
			else {
				TransfertPaypal* transfert = new TransfertPaypal(max, gestionnaireUtilisateurs_->getElementParIndex(indexMin), gestionnaireUtilisateurs_->getElementParIndex(indexMax));
				transferts_.push_back(transfert);
				transfert->effectuerTransfert();
			}
			comptes_[indexMax] = 0;
			comptes_[indexMin] += max;
		}

		// On incremente le nombre de comptes mis a 0
		count++;
		if (-min == max) {
			count++;
		}
		if (count >= gestionnaireUtilisateurs_->getNombreElements() - 1) {
			calcul = false;
		}
	}

}

// Methode d'affichage
// TODO : À modifier :
ostream & operator<<(ostream& os, const Groupe& groupe)
{
	os << "\nGroupe " << groupe.nom_ << ".\nCout total: " << groupe.getTotalDepenses() << "$ \nUtilisateurs:    \n\n";
	for (int i = 0; i < groupe.gestionnaireUtilisateurs_->getNombreElements(); i++) {
		os << "\t- " << *groupe.gestionnaireUtilisateurs_->getElementParIndex(i);
	}
	os << endl;

	if (groupe.transferts_.size() != 0) {
		os << "Transferts :" << endl;
		for (int i = 0; i < groupe.transferts_.size(); i++)
			os << "\t" << *(groupe.transferts_[i]);
	}
	else {
		os << "Les comptes ne sont pas equilibres" << endl << endl;
		for (int i = 0; i < groupe.comptes_.size(); i++) {
			os << groupe.gestionnaireUtilisateurs_->getElementParIndex(i)->getNom() << " : " << groupe.comptes_[i] << endl;
		}
	}

	os << endl;
	return os;
}
