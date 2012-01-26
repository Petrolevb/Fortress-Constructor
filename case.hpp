#ifndef HPP_CASE
#define HPP_CASE

#include<irrlicht/irrlicht.h>

#include "objet.hpp"

typedef enum {
	VIDE,
	MUR_UN,
	MUR_DEUX_OPPOSES,
	MUR_DEUX_ADJACENTS,
	MUR_TROIS,
	SOL
} TypeCase;


class Case : irr::scene::ISceneNode
{
	public :
		Case();

		Case(irr::scene::ISceneNode *parent, irr::scene::ISceneManager *sceneManager);
		// Héritage impose :
		// ISceneNode parent, SceneManager, id, position, rotation, scale
		Case(irr::scene::ISceneNode *parent, irr::scene::ISceneManager *sceneManager, 
		     TypeCase type, irr::s32 id=-1,
		     const irr::core::vector3df& position = irr::core::vector3df(0, 0, 0),
		     const irr::core::vector3df& rotation = irr::core::vector3df(0, 0, 0),
		     const irr::core::vector3df& scale = irr::core::vector3df(1.0f, 1.0f, 1.0f)); 
		~Case();
		
		Case & operator=(const Case &caseACopier);
		virtual void render() = 0;
		virtual const irr::core::aabbox3d<float>& getBoundingBox() const = 0;

		void ajoutObjet(Objet *objet);
		void retireObjet();
	private :
		Objet *m_Objet;
		TypeCase m_TypeDeLaCase;
		bool m_IsSmooth;
		bool m_EstFortifie;

		irr::scene::IAnimatedMeshSceneNode *m_Mesh;
};

#endif
