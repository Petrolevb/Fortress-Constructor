#include<vector>

#include<irrlicht/irrlicht.h>

#include "niveau.hpp"
#include "case.hpp"

using namespace irr;

Niveau::Niveau(scene::ISceneNode *parent, scene::ISceneManager *sceneManager) :
	m_LINK_sceneManager(sceneManager)
{
	m_Map.resize(1);
	m_Map[0].push_back( /*new*/ Case(parent, sceneManager, MUR_UN));
}

Niveau::~Niveau()
{
/*
	for(int i = 0; i < m_Map.size(); i++)
		for(int j = 0; j < m_Map[i].size(); j++)
			delete m_Map[i][j];
			*/
}

void Niveau::creuse(int ligne, int colone, Direction direction)
{
	Case nouvelleCase(0, m_LINK_sceneManager, SOL), 
	     nouveauMur(0, m_LINK_sceneManager, MUR_UN);
	     // parent = 0, scene manager, type mur
	switch(direction)
	{
		case HAUT :
			break;
		case BAS :
			break;
		case OUEST :
			break;
		case EST :
			/* Ajoute un Sol à gauche, un mur deux a gauche, un mur diagonale haut gauche, un mur diagonale bas gauche */

			// Ajoute une ligne si nécessaire
			if(m_Map.size() <= (unsigned int)ligne+1)
				m_Map.push_back(std::vector<Case>(0));
			// Ajoute les colones
			m_Map[ligne].insert((m_Map[ligne].begin() + colone), nouvelleCase);
			m_Map[ligne][colone+2] = nouveauMur;
			m_Map[ligne+1][colone+1] = nouveauMur;
			break;
		case NORD :
			break;
		case SUD :
			break;
		default: break;
	}
}
