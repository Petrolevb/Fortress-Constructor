#include<iostream>
#include<vector>

#include "niveau.hpp"
#include "case.hpp"

using namespace std;

Niveau::Niveau()
{
	cout << "Niveau  constructeur normal de la classe" << endl;
	m_Map.resize(1);
	m_Map[0].push_back(Case(MUR_UN));
}

Niveau::~Niveau()
{
}

void Niveau::creuse(int ligne, int colone, Direction direction)
{
	Case nouvelleCase(SOL), 
	     nouveauMur(MUR_UN);
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
				m_Map.push_back(vector<Case>(0));
			// Ajoute les colones
			m_Map[ligne].insert((m_Map[ligne].begin() + colone), nouvelleCase);
			m_Map[ligne][colone+2] = nouveauMur;
			//m_Map[ligne+1][colone+1] = nouveauMur;
			break;
		case NORD :
			break;
		case SUD :
			break;
		default: break;
	}
}
