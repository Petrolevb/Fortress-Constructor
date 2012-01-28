#include<iostream>

#include "case.hpp"
#include "objet.hpp"

using namespace std;

Case::Case() :
	m_Objet(NULL), 
	m_TypeDeLaCase(VIDE), m_IsSmooth(false), 
	m_EstFortifie(false), m_EstVisible(false)
{
	cerr << "Case : constructeur par défaut" << endl;
}

Case::Case(TypeCase type) :
	m_Objet(NULL),
	m_TypeDeLaCase(type), m_IsSmooth(false), 
	m_EstFortifie(false), m_EstVisible(true)	
{
	cerr << "Case : constructeur normal de la classe ";
}

Case::Case(const Case &caseACopier) :
	m_TypeDeLaCase(caseACopier.m_TypeDeLaCase), m_IsSmooth(caseACopier.m_IsSmooth), 
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
	cerr << "Case : opérateur de copie ";
	m_TypeDeLaCase = caseACopier.m_TypeDeLaCase;
	
	if(m_Objet != NULL) delete m_Objet;

	if(caseACopier.m_Objet != NULL)
		m_Objet = new Objet(*(caseACopier.m_Objet));
	
	m_IsSmooth = caseACopier.m_IsSmooth;
	m_EstFortifie = caseACopier.m_EstFortifie;
	
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
