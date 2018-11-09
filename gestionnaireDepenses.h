#pragma once

#include "depense.h"
#include "utilisateur.h"
#include "gestionnaireGenerique.h"

#include <algorithm>
#include <vector>

class GestionnaireDepenses {
public:
	vector<Depense*> getDepenses() const;
	int getNombreDepenses() const;
	int getIndexDe(Depense * depense) const;
	Depense* getDepenseParIndex(int i) const;
	double getTotalDepenses() const;

	GestionnaireDepenses& ajouterDepense(Depense* depense);

private:
	vector<Depense*> depenses_;
};
