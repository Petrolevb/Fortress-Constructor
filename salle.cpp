#include<vector>

#include"salle.hpp"

using namespace std;

vector<vector<TypeConstruction> > Salle::getPlan(Batiment batiment)// Méthode statique
{
	vector<vector<TypeConstruction> > retour;
	vector<TypeConstruction> ligne1, ligne2, ligne3;
	switch(batiment)
	{
		case Archerie :
			ligne1.push_back(SALLE_ANGLE_NO); ligne1.push_back(SALLE_VIDE); ligne1.push_back(SALLE_VIDE);	
			ligne2.push_back(SALLE_BORD_OUEST); ligne2.push_back(SALLE_VIDE); ligne2.push_back(SALLE_VIDE);	
			ligne3.push_back(SALLE_VIDE); ligne3.push_back(SALLE_BORD_SUD); ligne3.push_back(SALLE_VIDE);
			break;
		default :
			throw "Batiment Inconnu";
	}
	// On doit mettre à l'envert ! sinon l'affichage est inversé
	retour.push_back(ligne3);
	retour.push_back(ligne2);
	retour.push_back(ligne1);
	return retour;
}
