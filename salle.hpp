#ifndef HPP_SALLE
#define HPP_SALLE


#include<vector>

typedef enum
{
	Atelier = 0,
	Atelier_Cuir,
	Archerie,
	Bijouterie,
	Boucherie,
	Brasserie,
	Cendrerie,
	Couturier,
	Cuisine,
	Ferme,
	Forge,
	Loom,
	Massonnerie,
	Mechanic,
	Menuiserie,
	Poissonnerie,
	Tannerie,
	Teinturerie,
	NOMBRE_BATIMENT,
	SANS_BATIMENT
} Batiment;

typedef enum 
{
	SALLE_ANGLE_NO,
	SALLE_ANGLE_NE,
	SALLE_ANGLE_SO,
	SALLE_ANGLE_SE,

	SALLE_BORD_NORD,
	SALLE_BORD_OUEST,
	SALLE_BORD_SUD,
	SALLE_BORD_EST,

	SALLE_CENTRE,

	 // partie vide, mais avec objets : SALLE_VIDE_objet
		SALLE_VIDE,
		SALLE_VIDE_FORGE,
		SALLE_VIDE_TOURS
	
} TypeConstruction;

class Salle
{
	public :
		static std::vector<std::vector<TypeConstruction> > getPlan(Batiment batiment);
};


#endif
