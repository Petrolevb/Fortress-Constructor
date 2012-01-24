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

Case::Case(TypeCase type) :
	m_Objet(NULL), m_TypeDeLaCase(type), m_EstFortifie(false), m_IsSmooth(false)
{
	switch(type)
	{
		case MUR_UN:
		//	m_Mesh = scene::ISceneManager::getMesh("");
			break;
		case MUR_DEUX_ADJACENTS:
		//	m_Mesh = scene::ISceneManager::getMesh("");
			break;
		case MUR_DEUX_OPPOSES:
		//	m_Mesh = scene::ISceneManager::getMesh("");
			break;
		case MUR_TROIS:
		//	m_Mesh = scene::ISceneManager::getMesh("");
			break;
		case SOL:
		//	m_Mesh = scene::ISceneManager::getMesh("");
			break;
		default: m_Mesh = NULL; break;
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
