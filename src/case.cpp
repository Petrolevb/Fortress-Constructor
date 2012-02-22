#include<iostream>

#include "case.hpp"
#include "objet.hpp"

using namespace std;

Case::Case() :
	m_Objet(NULL), 
	m_TypeDeLaCase(VIDE), m_IsSmooth(false), 
	m_EstFortifie(false)
{
	cerr << "Case : constructeur par défaut " << '\t';
	m_Objet = new Objet(NULL_OBJET);
	cerr << "OK" << endl;
}

Case::Case(TypeCase type) :
	m_Objet(NULL),
	m_TypeDeLaCase(type), m_IsSmooth(false), 
	m_EstFortifie(false)
{
	cerr << "Case : constructeur normal de la classe "  << '\t';
	m_Objet = new Objet(NULL_OBJET);
	cerr << "OK" << endl;
}

Case::Case(TypeObjet typeObjet):
	m_TypeDeLaCase(SOL), m_IsSmooth(false),
	m_EstFortifie(false)
{
	cerr << "Case : constructeur SOL + Objet de la classe " << '\t';
	m_Objet = new Objet(typeObjet);
	cerr << "OK" << endl;
}

Case::Case(const Case &caseACopier) :
	m_TypeDeLaCase(caseACopier.m_TypeDeLaCase), 
	m_IsSmooth(caseACopier.m_IsSmooth), 
	m_EstFortifie(caseACopier.m_EstFortifie)
{
	cerr << "Case : constructeur de copie " << endl << '\t';
	
	if(caseACopier.m_Objet != NULL)
		m_Objet = new Objet(*(caseACopier.m_Objet));
		
	cerr << "OK" << endl;
}

Case::~Case()
{ if(m_Objet) delete m_Objet; }

Case & Case::operator=(const Case &caseACopier)
{
	cerr << "Case : opérateur de copie : ";
	m_TypeDeLaCase = caseACopier.m_TypeDeLaCase;

	if(m_Objet != NULL) delete m_Objet;
	cerr << endl << '\t';
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