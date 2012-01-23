#include<iostream>

#include "case.hpp"
#include "objet.hpp"

Case::Case() :
	m_Objet(NULL), m_TypeDeLaCase(VIDE), m_EstFortifie(false), m_IsSmooth(false)
{
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
