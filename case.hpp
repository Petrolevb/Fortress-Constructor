#ifndef HPP_CASE
#define HPP_CASE

#include "objet.hpp"

typedef enum {
	VIDE,
	MUR_UN,
	MUR_DEUX_OPPOSES,
	MUR_DEUX_ADJACENTS,
	MUR_TROIS,
	SOL
} TypeCase;


class Case
{
	public :
		Case();
		~Case();

		void ajoutObjet(Objet *objet);
		void retireObjet();
	private :
		Objet *m_Objet;
		TypeCase m_TypeDeLaCase;
		bool m_IsSmooth;
		bool m_EstFortifie;
};

#endif
