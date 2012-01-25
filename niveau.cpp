#include<vector>

#include<irrlicht/irrlicht.h>

#include "niveau.hpp"
#include "case.hpp"

using namespace irr;

Niveau::Niveau(scene::ISceneManager *sceneManager) :
	m_LINK_sceneManager(sceneManager)
{
	m_Map.resize(0);
}

Niveau::~Niveau()
{
}

void Niveau::creuse(int ligne, int colone, Direction direction)
{
	Case //nouvelleCase(SOL, m_LINK_sceneManager), 
	     nouveauMur(MUR_UN, m_LINK_sceneManager);
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
			if(m_Map.size() <= ligne+1)
				m_Map.resize(m_Map.size()+1);
			// Ajoute les colones
			if(m_Map[ligne].size() <= colone+2)
				m_Map[ligne].resize(m_Map[ligne].size()+2);

			//m_Map[ligne][colone+1] = nouvelleCase;
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
