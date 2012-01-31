#ifndef HPP_CASE
#define HPP_CASE

#include "objet.hpp"

typedef enum {
	VIDE,
	MUR_UN_NORD,
	MUR_UN_SUD,
	MUR_UN_EST,
	MUR_UN_OUEST,

	MUR_DEUX_OPPOSES_NORD_SUD,
	MUR_DEUX_OPPOSES_EST_OUEST,
	
	// Indique le coin des murs
	MUR_DEUX_ADJACENTS_NORD_OUEST,
	MUR_DEUX_ADJACENTS_NORD_EST,
	MUR_DEUX_ADJACENTS_SUD_OUEST,
	MUR_DEUX_ADJACENTS_SUD_EST,

	// Indique le mur manquand
	MUR_TROIS_NORD,
	MUR_TROIS_SUD,
	MUR_TROIS_EST,
	MUR_TROIS_OUEST,

	SOL
} TypeCase;


class Case
{
	public :
		Case();
		Case(TypeCase type); 
		Case(const Case &caseACopier);
		~Case();
			
		Case & operator=(const Case &caseACopier);
		
		// Accesseur
		TypeCase getTypeDeLaCase() { return m_TypeDeLaCase; }

		void ajoutObjet(Objet objet);
		void retireObjet();
		
	private :
		Objet *m_Objet;
		TypeCase m_TypeDeLaCase;
		bool m_IsSmooth;
		bool m_EstFortifie;
};

#endif
