/********************************************
* Titre: Travail pratique #5 - groupe.cpp
* Date: 4 novembre 2018
* Auteur: Ryan Hardie
*******************************************/
#pragma once
#include "groupe.h"

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

// Methodes d'ajout
// TODO : À modifier :
Groupe& Groupe::ajouterDepense(double montant, Utilisateur* payePar, const string& nom, const string& lieu)
{
	// Trouver l'index de l'auteur de la depense
	bool indexPayePar = gestionnaireUtilisateurs_->estExistant(payePar); //point break majeur ligne_95
	map<Utilisateur*, double> conteneur = gestionnaireUtilisateurs_->getConteneur();
	
	if (indexPayePar == false) {
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
	/*for( it = gestionnaireUtilisateurs_->getConteneur().begin(); it == pos; it++)*/
	//		gestionnaireUtilisateurs_->setCompte(make_pair(payePar,))
	double currentAccount = depense->getMontant() - montantReparti;
	
	gestionnaireUtilisateurs_->mettreAJourComptes(payePar, currentAccount);
	//gestionnaireUtilisateurs_->
			//gestionnaireUtilisateurs_->getConteneur()[payePar] = pos->second;
	//comptes_[indexPayePar] += depense->getMontant() - montantReparti; // Similaire aux deux lignes precedentes(theoriquement)
	
	/*for (int i = 0; i < gestionnaireUtilisateurs_->getNombreElements(); i++) {
		if (i != indexPayePar) {
			comptes_[i] -= montantReparti;
		}
	}*/

			/*for (auto it = conteneur.begin(); it != conteneur.end(); it++) {	
				
				Utilisateur* userTmp = it->first;

				if (userTmp->getNom() != pos->first->getNom())
					it->second -= montantReparti;

			}*/

	return *this;
}

Groupe& Groupe::operator+=(Utilisateur* utilisateur)
{
	// Ajouté :
//	gestionnaireUtilisateurs_->ajouterUtilisateur(utilisateur);
	gestionnaireUtilisateurs_->ajouter(utilisateur);

	//gestionnaireUtilisateurs_->getConteneur().end()->second = 0.0; // mettre la valeur de la deuxieme operande pointee par l'iterateur a 0

	//comptes_.push_back(0); Le compte sera desormais associe a l'utilisateur, plus besoin d'utiliser le vecteur double

	return *this;
}

// TODO : À modifier :
void Groupe::equilibrerComptes() {

	bool calcul = true;
	int count = 0;
	while (calcul) {
		double max = 0;
		double min = 0;
		int posMin = 0, posMax = 0,posIterateur=0;
		map<Utilisateur*,double>::iterator indexMax;
		map<Utilisateur*,double>::iterator indexMin;

		// On cherche le compte le plus eleve et le moins eleve
//		for (int i = 0; i < gestionnaireUtilisateurs_->getNombreElements(); i++) {
		for (auto it = gestionnaireUtilisateurs_->getConteneur().begin(); it != gestionnaireUtilisateurs_->getConteneur().end(); it++) {

	
	/*  V2 ligne 161- 165
			
	map<Utilisateur*,double>::iterator iterateurTmp;
	for( iterateurTmp = gestionnaireUtilisateurs_->getConteneur().begin();
	iterateurTmp != gestionnaireUtilisateurs_->getConteneur().end(); iterateurTmp++){
			

		}
			
			*/
			posIterateur++;
			if (it->second > max) {  //comptes_[i] > max

				max = it->second;
				indexMax = it;
				posMax = posIterateur;
			}
			if (it->second < min) { //comptes_[i] < min
				min = it->second;
				indexMin = it;
				posMin = posIterateur;
			}
		}

		// On cherche lequel des deux a la dette la plus grande
		if (-min <= max && min != 0 && max != 0) {
			if (gestionnaireUtilisateurs_->getElementParIndex(posMin).first->getMethodePaiement() == Interac) {
				TransfertInterac* transfert = new TransfertInterac(-min, gestionnaireUtilisateurs_->getElementParIndex(posMin).first, gestionnaireUtilisateurs_->getElementParIndex(posMax).first);
				transferts_.push_back(transfert);
				transfert->effectuerTransfert();
			}
			else {
				TransfertPaypal* transfert = new TransfertPaypal(-min, gestionnaireUtilisateurs_->getElementParIndex(posMin).first, gestionnaireUtilisateurs_->getElementParIndex(posMax).first);
				transferts_.push_back(transfert);
				transfert->effectuerTransfert();
			}
			indexMax->second += min;
			indexMin->second = 0;

			/*comptes_[indexMax] += min;
			comptes_[indexMin] = 0;*/
		}
		else if (-min > max  && min != 0 && max != 0) {
			if (gestionnaireUtilisateurs_->getElementParIndex(posMin).first->getMethodePaiement() == Interac) {
				TransfertInterac* transfert = new TransfertInterac(max, gestionnaireUtilisateurs_->getElementParIndex(posMin).first, gestionnaireUtilisateurs_->getElementParIndex(posMax).first);
				transferts_.push_back(transfert);
				transfert->effectuerTransfert();
			}
			else {
				TransfertPaypal* transfert = new TransfertPaypal(max, gestionnaireUtilisateurs_->getElementParIndex(posMin).first, gestionnaireUtilisateurs_->getElementParIndex(posMax).first);
				transferts_.push_back(transfert);
				transfert->effectuerTransfert();
			}
			indexMax->second = 0;
			indexMin->second += max;
	
			/*comptes_[indexMax] = 0;
			comptes_[indexMin] += max;*/
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

/*ostream & operator<<(ostream& os, const Groupe& groupe)
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
		//for (int i = 0; i < groupe.comptes_.size(); i++) {
			//os << groupe.gestionnaireUtilisateurs_->getElementParIndex(i)->getNom() << " : " << groupe.comptes_[i] << endl;
		//}
	}

	os << endl;
	return os;
}
*/