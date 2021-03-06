#ifndef HPP_DEFINITIONS
#define HPP_DEFINITIONS

const int LARGEUR_FENETRE = 800;
const int HAUTEUR_FENETRE = 600;

enum
{
	ID_NEstPasAtteingable = 0, // N'est pas touchable par la caméra
	ID_EstAtteignable = 1,
	ID_Objet = 1 << 0, // objet atteignable, de base
	ID_Objet_Porte = 1 << 1 // objet porte, id spécifique
};

typedef enum
{
	CREUSE = 0,
	ACTION_OBJET,
	SMOOTH,
	FORTIFIE,
	CONSTRUIT,
	CONSTRUIT_ATELIER,
	CONSTRUIT_ATELIER_CUIR,
	CONSTRUIT_ARCHERIE,
	CONSTRUIT_BIJOUTERIE,
	CONSTRUIT_BOUCHERIE,
	CONSTRUIT_BRASSERIE,
	CONSTRUIT_CENDRERIE,
	CONSTRUIT_COUTURIER,
	CONSTRUIT_CUISINE,
	CONSTRUIT_FERME,
	CONSTRUIT_FORGE,
	CONSTRUIT_LOOM,
	CONSTRUIT_MASSONNERIE,
	CONSTRUIT_MECHANIC,
	CONSTRUIT_MENUISERIE,
	CONSTRUIT_POISSONNERIE,
	CONSTRUIT_TANNERIE,
	CONSTRUIT_TEINTURERIE,
	AUCUNE_ACTION
} Action;

#endif
