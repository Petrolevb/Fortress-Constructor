#include<iostream>

#include<irrlicht/irrlicht.h>

#include "case.hpp"

using namespace irr;

Objet::Objet(TypeObjet type, scene::ISceneManager *sceneManager, scene::IAnimatedMeshSceneNode *parent) :
	m_TypeDeLObjet(type)
{
	switch(m_TypeDeLObjet)
	{
		/*
		case : 
			m_Mesh = sceneManager->addAnimatedMeshSceneNode(sceneManager->getMesh("data/mesh/objet/"));
			break;
		*/
		default : m_Mesh = NULL;
	}
	if(m_Mesh != NULL)
	{
		m_Mesh->setMaterialFlag(video::EMF_LIGHTING, false);
		/*
		m_Mesh->setMaterialTexture(0, driver->getTexture("data/textures/objets/");
		*/
	}
}

Objet::~Objet()
{
}
