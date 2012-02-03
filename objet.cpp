#include<iostream>

#include<irrlicht/irrlicht.h>

#include "case.hpp"

using namespace std;

Objet::Objet() :
	m_TypeDeLObjet(NULL_OBJET), m_Actif(false), m_ActiviteEnCours(false)
{ cerr << "Objet : constructeur par defaut OK" << endl; }

Objet::Objet(TypeObjet type) :
	m_TypeDeLObjet(type), m_Actif(false), m_ActiviteEnCours(false)
{ cerr << "Objet : constructeur normal de la classe OK" << endl; }

Objet::Objet(const Objet &objetACopier) :
	m_TypeDeLObjet(objetACopier.m_TypeDeLObjet), m_Actif(objetACopier.m_Actif), m_ActiviteEnCours(objetACopier.m_ActiviteEnCours)
{ cerr << "Objet : Constructeur de copie OK" << endl; }

Objet::~Objet()
{
}

Objet & Objet::operator=(const Objet &objetACopier)
{
	cerr << "Objet : opérateur de copie ";
	m_TypeDeLObjet = objetACopier.m_TypeDeLObjet;
	m_Actif = objetACopier.m_Actif;
	m_ActiviteEnCours = objetACopier.m_ActiviteEnCours;
	cerr << "OK" << endl;
	return *this;
}
