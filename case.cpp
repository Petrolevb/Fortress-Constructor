#include<iostream>

#include "case.hpp"
#include "objet.hpp"

using namespace std;

Case::Case() :
	m_Objet(NULL), 
	m_TypeDeLaCase(VIDE), m_IsSmooth(false), 
	m_EstFortifie(false)
{
	cerr << "Case : constructeur par défaut ";
	m_Objet = new Objet(NULL_OBJET);
	cerr << "OK" << endl;
}

Case::Case(TypeCase type) :
	m_Objet(NULL),
	m_TypeDeLaCase(type), m_IsSmooth(false), 
	m_EstFortifie(false)
{
	cerr << "Case : constructeur normal de la classe ";
	m_Objet = new Objet(NULL_OBJET);
	cerr << "OK" << endl;
}

Case::Case(const Case &caseACopier) :
	m_TypeDeLaCase(caseACopier.m_TypeDeLaCase), 
	m_IsSmooth(caseACopier.m_IsSmooth), 
	m_EstFortifie(caseACopier.m_EstFortifie)
{
	cerr << "Case : constructeur de copie ";
	
	if(caseACopier.m_Objet != NULL)
		m_Objet = new Objet(*(caseACopier.m_Objet));
		
	cerr << "OK" << endl;
}

Case::~Case()
{ }

Case & Case::operator=(const Case &caseACopier)
{
	cerr << "Case : opérateur de copie : ";
	m_TypeDeLaCase = caseACopier.m_TypeDeLaCase;
	cerr << "Type, ";

	if(m_Objet != NULL) delete m_Objet;
	cerr << "Suppression Objet, ";
	if(caseACopier.m_Objet != NULL)
		m_Objet = new Objet(*(caseACopier.m_Objet));
	cerr << "Objet, ";

	m_IsSmooth = caseACopier.m_IsSmooth;
	m_EstFortifie = caseACopier.m_EstFortifie;
	cerr << "Smooth, Fortification, ";
	cerr << "OK" << endl;
	return *this;
}

// Fonctions personnelles

void Case::ajoutObjet(Objet objet)
{
	if(m_Objet != NULL) delete m_Objet;

	m_Objet = new Objet(objet); 
}


void Case::retireObjet()
{ if(m_Objet != NULL) delete m_Objet; }
