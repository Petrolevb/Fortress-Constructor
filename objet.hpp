#ifndef HPP_OBJET
#define HPP_OBJET

#include<irrlicht/irrlicht.h>

typedef enum {
	CHAISE,
	TABLE,
	LIT,
	CONSTRUCTION,

	PORTE,
	PONT,

	ESCALIER_HAUT,
	ESCALIER_BAS,
	ESCALIER_HAUT_BAS

} TypeObjet;

class Objet
{
	public :
		/* Prends en parramètre le type de l'objet (enum)
		 * le sceneManager
		 * le noeud parent, théoriquement le sol-plafond qui le contient
		 */
		Objet(TypeObjet type, irr::scene::ISceneManager *sceneManager, irr::scene::IAnimatedMeshSceneNode *parent);
		~Objet();

		Objet & operator=(const Objet &objetACopier);

	private :
		TypeObjet m_TypeDeLObjet;
		irr::scene::SMesh * m_Mesh;
};

#endif
