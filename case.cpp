#include<iostream>

#include<irrlicht/irrlicht.h>

#include "case.hpp"
#include "objet.hpp"

using namespace irr;

Case::Case() :
	scene::ISceneNode(0, NULL),
	m_Objet(NULL), m_TypeDeLaCase(VIDE), m_IsSmooth(false), m_EstFortifie(false),
	m_Mesh(NULL)
{ }

Case::Case(scene::ISceneNode *parent, scene::ISceneManager *sceneManager) :
	scene::ISceneNode(parent, sceneManager),
	m_Objet(NULL), m_TypeDeLaCase(VIDE), m_IsSmooth(false), m_EstFortifie(false), 
	m_Mesh(NULL)
{ }

Case::Case(scene::ISceneNode *parent, scene::ISceneManager *sceneManager,
	TypeCase type, 
	s32 id/*=1*/, 
	const core::vector3df& position /*= core::vector3df(0, 0, 0)*/,
	const core::vector3df& rotation /*= core::vector3df(0, 0, 0)*/, 
	const core::vector3df& scale /*= core::vector3df(1.0f, 1.0f, 1.0f)*/)
		: scene::ISceneNode(parent, sceneManager, id, position, rotation, scale),
		  m_Objet(NULL), m_TypeDeLaCase(type), m_IsSmooth(false), m_EstFortifie(false) 
{
	std::cerr << "Recuperation du mesh type " << m_TypeDeLaCase << std::endl;
	switch(type)
	{
		case MUR_UN:
		m_Mesh = sceneManager->addAnimatedMeshSceneNode(sceneManager->getMesh("data/mesh/mur un.obj"));
		break;
		case MUR_DEUX_ADJACENTS:
			m_Mesh = sceneManager->addAnimatedMeshSceneNode(sceneManager->getMesh("data/mesh/mur deux adjacents.obj"));
			break;
		case MUR_DEUX_OPPOSES:
			m_Mesh = sceneManager->addAnimatedMeshSceneNode(sceneManager->getMesh("data/mesh/mur deux opposes.obj"));
			break;
		case MUR_TROIS:
			m_Mesh = sceneManager->addAnimatedMeshSceneNode(sceneManager->getMesh("data/mesh/mur trois.obj"));
			break;
		case SOL:
			m_Mesh = sceneManager->addAnimatedMeshSceneNode(sceneManager->getMesh("data/mesh/sol-plafond.obj"));
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
{ }

Case & Case::operator=(const Case &caseACopier)
{
	m_TypeDeLaCase = caseACopier.m_TypeDeLaCase;
	
	if(m_Objet != NULL) delete m_Objet;
	m_Objet = new Objet(*(caseACopier.m_Objet));
	
	m_IsSmooth = caseACopier.m_IsSmooth;
	m_EstFortifie = caseACopier.m_EstFortifie;
	return *this;
}
/*
void Case::render()
{
	// fonction abstraite pure dans la classe mère
	//scene::ISceneNode::render();
}

const core::aabbox3d<float>& Case::getBoundingBox() const
{
	// fonction abstraite pure dans la classe mère
	//return scene::ISceneNode::getBoundingBox();
}
*/
void Case::ajoutObjet(Objet *objet)
{
	m_Objet = objet;
}


void Case::retireObjet()
{
	if(m_Objet != NULL)
		m_Objet->~Objet();
}
