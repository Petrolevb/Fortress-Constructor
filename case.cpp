#include<iostream>

#include<irrlicht/irrlicht.h>

#include "case.hpp"
#include "objet.hpp"

using namespace irr;

Case::Case() :
	m_Objet(NULL), m_TypeDeLaCase(VIDE), m_EstFortifie(false), m_IsSmooth(false),
	m_Mesh(NULL)
{
}

Case::Case(TypeCase type, scene::ISceneManager *sceneManager) :
	m_Objet(NULL), m_TypeDeLaCase(type), m_EstFortifie(false), m_IsSmooth(false)
{
	switch(type)
	{
		case MUR_UN:
			m_Mesh = sceneManager->addAnimatedMeshSceneNode(sceneManager->getMesh("data/mesh/mur un.dae"));
			break;
		case MUR_DEUX_ADJACENTS:
			m_Mesh = sceneManager->addAnimatedMeshSceneNode(sceneManager->getMesh("data/mesh/mur deux adjacents.dae"));
			break;
		case MUR_DEUX_OPPOSES:
			m_Mesh = sceneManager->addAnimatedMeshSceneNode(sceneManager->getMesh("data/mesh/mur deux opposes.dae"));
			break;
		case MUR_TROIS:
			m_Mesh = sceneManager->addAnimatedMeshSceneNode(sceneManager->getMesh("data/mesh/mur trois.dae"));
			break;
		case SOL:
			m_Mesh = sceneManager->addAnimatedMeshSceneNode(sceneManager->getMesh("data/mesh/sol-plafond.dae"));
			break;
		default: m_Mesh = NULL; break;
	}
	if(m_Mesh != NULL)
	{
		m_Mesh->setMaterialFlag(video::EMF_LIGHTING, false);	
		// A mettre dans le switch, nécessitera le driver, IVideoDriver 
		//m_Mesh->setMaterialTexture(0, driver->getTexture("data/texture/ *.jpg|png");
	}
}

Case::~Case()
{
}


void Case::ajoutObjet(Objet *objet)
{
	m_Objet = objet;
}


void Case::retireObjet()
{
	if(m_Objet != NULL)
		m_Objet->~Objet();
}
