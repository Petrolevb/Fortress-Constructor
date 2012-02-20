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
			ligne2.push_back(SALLE_BORD_OUEST); ligne1.push_back(SALLE_VIDE); ligne1.push_back(SALLE_VIDE);	
			ligne3.push_back(SALLE_ANGLE_SO); ligne1.push_back(SALLE_VIDE); ligne1.push_back(SALLE_VIDE);
			break;
		default :
			throw "Batiment Inconnu";
	}
	retour.push_back(ligne1);
	retour.push_back(ligne2);
	retour.push_back(ligne3);
	return retour;
}
