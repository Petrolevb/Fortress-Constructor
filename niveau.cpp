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

void Niveau::afficheConsole()
{
	cout << endl << endl << endl;
	// Affichage et chargement des niveaux 
	// On n'affiche que les changements
	for(int i = 0; i < m_Map.size(); i++)
	{
		for(int j = 0; j < m_Map[i].size(); j++)
		{
			switch(m_Map[i][j].getTypeDeLaCase())
			{
				case VIDE : cout << " "; break;
				case MUR_UN : cout << "|"; break;
				case MUR_DEUX_OPPOSES : cout << "H"; break;
				case MUR_DEUX_ADJACENTS : cout << "L"; break;
				case MUR_TROIS : cout << "U"; break;
				case SOL : cout << "#"; break;
				default : cout << " "; break;
			}
		}
		cout << endl;
	}
}

void Niveau::creuse(int ligne, int colone, Direction direction)
{
	Case nouvelleCase(SOL), 
	     nouveauMur(MUR_UN);

	vector<Case> nouveauVector;
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
			m_Map[ligne].insert((m_Map[ligne].begin() + colone+1), nouveauMur);
			m_Map.insert((m_Map.begin() + ligne), nouveauVector);
//			m_Map[ligne+1].insert((m_Map.begin() + colone), nouveauMur);
			//m_Map[ligne+1][colone+1] = nouveauMur;
			break;
		case NORD :
			break;
		case SUD :
			break;
		default: break;
	}
}
