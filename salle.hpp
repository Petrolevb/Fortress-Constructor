#ifndef HPP_SALLE
#define HPP_SALLE


#include<vector>

typedef enum
{
	Archerie = 0,
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
	SALLE_VIDE
} TypeConstruction;

class Salle
{
	public :
		static std::vector<std::vector<TypeConstruction> > getPlan(Batiment batiment);
};


#endif
