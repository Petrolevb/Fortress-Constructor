#include<vector>

#include"salle.hpp"

using namespace std;

vector<vector<TypeConstruction> > Salle::getPlan(Batiment batiment)// Méthode statique
{
	vector<vector<TypeConstruction> > retour;
	vector<TypeConstruction> ligne1, ligne2, ligne3;
	switch(batiment)
	{
		case Bijouterie :
			ligne1.push_back(SALLE_VIDE); ligne1.push_back(SALLE_VIDE); ligne1.push_back(SALLE_ANGLE_NE);
			ligne2.push_back(SALLE_VIDE); ligne2.push_back(SALLE_VIDE); ligne2.push_back(SALLE_BORD_EST);
			ligne3.push_back(SALLE_VIDE); ligne3.push_back(SALLE_VIDE); ligne3.push_back(SALLE_ANGLE_SE);
			break;
		case Cendrerie :
			ligne1.push_back(SALLE_VIDE); ligne1.push_back(SALLE_VIDE); ligne1.push_back(SALLE_VIDE);
			ligne2.push_back(SALLE_VIDE); ligne2.push_back(SALLE_VIDE); ligne2.push_back(SALLE_VIDE);
			ligne3.push_back(SALLE_VIDE); ligne3.push_back(SALLE_VIDE); ligne3.push_back(SALLE_VIDE);
			break;
		case Ferme :
			ligne1.push_back(SALLE_ANGLE_NO); ligne1.push_back(SALLE_VIDE); ligne1.push_back(SALLE_VIDE);
			ligne2.push_back(SALLE_VIDE); ligne2.push_back(SALLE_VIDE); ligne2.push_back(SALLE_VIDE);
			ligne3.push_back(SALLE_ANGLE_SO); ligne3.push_back(SALLE_VIDE); ligne3.push_back(SALLE_VIDE);
			break;
		case Forge :
			ligne1.push_back(SALLE_VIDE); ligne1.push_back(SALLE_VIDE); ligne1.push_back(SALLE_VIDE);
			ligne2.push_back(SALLE_BORD_OUEST); ligne2.push_back(SALLE_VIDE); ligne2.push_back(SALLE_BORD_EST);
			ligne3.push_back(SALLE_VIDE); ligne3.push_back(SALLE_VIDE); ligne3.push_back(SALLE_VIDE);
			break;
		case Loom :
			ligne1.push_back(SALLE_VIDE); ligne1.push_back(SALLE_BORD_NORD); ligne1.push_back(SALLE_VIDE);
			ligne2.push_back(SALLE_VIDE); ligne2.push_back(SALLE_VIDE); ligne2.push_back(SALLE_VIDE);
			ligne3.push_back(SALLE_VIDE); ligne3.push_back(SALLE_VIDE); ligne3.push_back(SALLE_VIDE);
			break;
		case Poissonnerie :
			ligne1.push_back(SALLE_ANGLE_NO); ligne1.push_back(SALLE_BORD_NORD); ligne1.push_back(SALLE_VIDE);
			ligne2.push_back(SALLE_VIDE); ligne2.push_back(SALLE_VIDE); ligne2.push_back(SALLE_VIDE);
			ligne3.push_back(SALLE_VIDE); ligne3.push_back(SALLE_VIDE); ligne3.push_back(SALLE_VIDE);
			break;
		case Tannerie :
			ligne1.push_back(SALLE_ANGLE_NO); ligne1.push_back(SALLE_VIDE); ligne1.push_back(SALLE_VIDE);
			ligne2.push_back(SALLE_VIDE); ligne2.push_back(SALLE_VIDE); ligne2.push_back(SALLE_BORD_EST);
			ligne3.push_back(SALLE_ANGLE_SO); ligne3.push_back(SALLE_VIDE); ligne3.push_back(SALLE_VIDE);
			break;
		case Mechanic :
			ligne1.push_back(SALLE_VIDE); ligne1.push_back(SALLE_VIDE); ligne1.push_back(SALLE_VIDE);
			ligne2.push_back(SALLE_VIDE); ligne2.push_back(SALLE_CENTRE); ligne2.push_back(SALLE_VIDE);
			ligne3.push_back(SALLE_VIDE); ligne3.push_back(SALLE_VIDE); ligne3.push_back(SALLE_VIDE);
			break;
		case Menuiserie :
			ligne1.push_back(SALLE_VIDE); ligne1.push_back(SALLE_VIDE); ligne1.push_back(SALLE_VIDE);
			ligne2.push_back(SALLE_VIDE); ligne2.push_back(SALLE_VIDE); ligne2.push_back(SALLE_VIDE);
			ligne3.push_back(SALLE_VIDE); ligne3.push_back(SALLE_VIDE); ligne3.push_back(SALLE_VIDE);
			break;
		case Encrerie :
			ligne1.push_back(SALLE_VIDE); ligne1.push_back(SALLE_BORD_NORD); ligne1.push_back(SALLE_VIDE);
			ligne2.push_back(SALLE_VIDE); ligne2.push_back(SALLE_VIDE); ligne2.push_back(SALLE_VIDE);
			ligne3.push_back(SALLE_ANGLE_SO); ligne3.push_back(SALLE_VIDE); ligne3.push_back(SALLE_ANGLE_SE);
			break;
		case Couturier :
			ligne1.push_back(SALLE_ANGLE_NO); ligne1.push_back(SALLE_VIDE); ligne1.push_back(SALLE_VIDE);
			ligne2.push_back(SALLE_VIDE); ligne2.push_back(SALLE_VIDE); ligne2.push_back(SALLE_VIDE);
			ligne3.push_back(SALLE_VIDE); ligne3.push_back(SALLE_BORD_SUD); ligne3.push_back(SALLE_VIDE);
			break;
		case Atelier:
			ligne1.push_back(SALLE_VIDE); ligne1.push_back(SALLE_VIDE); ligne1.push_back(SALLE_ANGLE_NE);
			ligne2.push_back(SALLE_BORD_OUEST); ligne2.push_back(SALLE_VIDE); ligne2.push_back(SALLE_VIDE);
			ligne3.push_back(SALLE_ANGLE_SO); ligne3.push_back(SALLE_BORD_SUD); ligne3.push_back(SALLE_VIDE);
			break;
		case Atelier_Cuir :
			ligne1.push_back(SALLE_VIDE); ligne1.push_back(SALLE_VIDE); ligne1.push_back(SALLE_ANGLE_NE);
			ligne2.push_back(SALLE_BORD_OUEST); ligne2.push_back(SALLE_VIDE); ligne2.push_back(SALLE_VIDE);
			ligne3.push_back(SALLE_VIDE); ligne3.push_back(SALLE_VIDE); ligne3.push_back(SALLE_ANGLE_SE);
			break;
		case Archerie :
			ligne1.push_back(SALLE_ANGLE_NO); ligne1.push_back(SALLE_VIDE); ligne1.push_back(SALLE_VIDE);	
			ligne2.push_back(SALLE_BORD_OUEST); ligne2.push_back(SALLE_VIDE); ligne2.push_back(SALLE_VIDE);	
			ligne3.push_back(SALLE_VIDE); ligne3.push_back(SALLE_BORD_SUD); ligne3.push_back(SALLE_VIDE);
			break;
		case Massonnerie : // Les deux sont pour l'instant identiques
		case Boucherie:
			ligne1.push_back(SALLE_VIDE); ligne1.push_back(SALLE_VIDE); ligne1.push_back(SALLE_ANGLE_NE);	
			ligne2.push_back(SALLE_BORD_OUEST); ligne2.push_back(SALLE_VIDE); ligne2.push_back(SALLE_BORD_EST);	
			ligne3.push_back(SALLE_VIDE); ligne3.push_back(SALLE_VIDE); ligne3.push_back(SALLE_VIDE);
			break;
		case Brasserie :
			ligne1.push_back(SALLE_ANGLE_NO); ligne1.push_back(SALLE_VIDE); ligne1.push_back(SALLE_VIDE);	
			ligne2.push_back(SALLE_VIDE); ligne2.push_back(SALLE_VIDE); ligne2.push_back(SALLE_VIDE);	
			ligne3.push_back(SALLE_VIDE); ligne3.push_back(SALLE_VIDE); ligne3.push_back(SALLE_VIDE);
			break;
		case Cuisine :
			ligne1.push_back(SALLE_VIDE); ligne1.push_back(SALLE_BORD_NORD); ligne1.push_back(SALLE_ANGLE_NE);	
			ligne2.push_back(SALLE_VIDE); ligne2.push_back(SALLE_CENTRE); ligne2.push_back(SALLE_VIDE);	
			ligne3.push_back(SALLE_VIDE); ligne3.push_back(SALLE_VIDE); ligne3.push_back(SALLE_VIDE);
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
