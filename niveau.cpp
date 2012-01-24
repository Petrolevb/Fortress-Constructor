#include<vector>

#include "niveau.hpp"

Niveau::Niveau()
{
	m_Map.resize(0);
}

Niveau::~Niveau()
{
}

void Niveau::creuse(int ligne, int colone, Direction direction)
{
/*
	switch(direction)
	{
		case HAUT :
			break;
		case BAS :
			break;
		case OUEST :
			break;
		case EST :
			m_Map[ligne].resize(m_Map[ligne].size()+1);
			Case nouvelleCase(SOL);
			m_Map[ligne][colone+1] = nouvelleCase;
			break;
		case NORD :
			break;
		case SUD :
			break;
		default: break;
	}
	*/
}
