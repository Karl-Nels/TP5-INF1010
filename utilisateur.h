/********************************************
* Titre: Travail pratique #4 - utilisateur.h
* Date: 19 octobre 2018
* Auteur: Wassim Khene & Ryan Hardie
*******************************************/

#ifndef UTILISATEUR_H
#define UTILISATEUR_H

#include <string>
#include <iostream>
#include <vector>
#include <iomanip>

#include "depense.h"

using namespace std;

enum MethodePaiement { Paypal, Interac };

class Utilisateur {
public:
	// Constructeurs
	Utilisateur();
	Utilisateur(const string& nom = "", MethodePaiement methodePaiement = Interac, const string& courriel = "", const string& idPaypal= "");

	// Methodes d'accès
	string getNom() const;
	vector<Depense*> getDepenses() const;
	string getCourriel() const;
	string getIdPaypal() const;
	MethodePaiement getMethodePaiement() const;
	double getTotalATransferer() const;
	double getBalance() const;

	// Methodes de modification
	void setNom(const string& nom);
	void setCourriel(const string& courriel);
	void setIdPaypal(const string idPaypal);
	void setMethodePaiement(MethodePaiement methodePaiement);

	void modifierBalanceTranferts(double montant);
	void modifierBalanceFrais(double montant);

	Utilisateur& operator+=(Depense* depense);
	virtual void print(ostream& os) const = 0;
	
	// Methode d'affichage
	friend ostream& operator<<(ostream& os, const Utilisateur& user);

protected:
	MethodePaiement methodePaiement_;
	string nom_;
	vector <Depense*> depenses_;
	string courriel_;
	string idPaypal_;
	double balanceFrais_;
	double balanceTransferts_;
};
#endif