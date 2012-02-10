#ifndef HPP_CASE
#define HPP_CASE

#include "objet.hpp"

typedef enum {
	VIDE,
	MUR,
	SOL
} TypeCase;


class Case
{
	public :
		Case();
		Case(TypeCase type);
		Case(TypeObjet typeObjet); // Constructeur automatique d'une case sol avec un objet chargé
		Case(const Case &caseACopier);
		~Case();
			
		Case & operator=(const Case &caseACopier);
		
		// Accesseur
		TypeCase getTypeDeLaCase() { return m_TypeDeLaCase; }
		TypeObjet getTypeObjet() { return (m_Objet ? m_Objet->getTypeObjet() : NULL_OBJET ); }
		bool getObjetActif() { return (m_Objet ? m_Objet->getActif() : false); }
		void setObjetActif(bool value) { if(m_Objet) { m_Objet->setActif(value); } }
		bool getObjetActivite() { return (m_Objet ? m_Objet->getActiviteEnCours() : false); }
		void setObjetActivite(bool value) { if(m_Objet) { m_Objet->setActiviteEnCours(value) ; } }

		void setSmooth() { m_IsSmooth = true; }
		bool getIsSmooth() { return m_IsSmooth; }

		void ajoutObjet(Objet objet);
		void retireObjet();
		
	private :
		Objet *m_Objet;
		TypeCase m_TypeDeLaCase;
		bool m_IsSmooth;
		bool m_EstFortifie;
};

#endif
