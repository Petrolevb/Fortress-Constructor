#ifndef HPP_CASE
#define HPP_CASE

#include"objet.hpp"
#include"salle.hpp"
typedef enum {
	VIDE,
	MUR,
	SOL,
	EST_CONSTRUIT
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
		bool operator==(const Case & a);
		
		// Accesseur
		TypeCase getTypeDeLaCase() { return m_TypeDeLaCase; }
		TypeObjet getTypeObjet() { return (m_Objet ? m_Objet->getTypeObjet() : NULL_OBJET ); }
		bool getObjetActif() { return (m_Objet ? m_Objet->getActif() : false); }
		void setObjetActif(bool value) { if(m_Objet) { m_Objet->setActif(value); } }
		bool getObjetActivite() { return (m_Objet ? m_Objet->getActiviteEnCours() : false); }
		void setObjetActivite(bool value) { if(m_Objet) { m_Objet->setActiviteEnCours(value) ; } }

		void setSmooth() { m_IsSmooth = true; }
		bool getIsSmooth() { return m_IsSmooth; }
		void fortifie() { m_EstFortifie = true; }
		bool getIsFortifie() { return m_EstFortifie; }
		
		// La case doit être marquée comme construit pour pouvoir mettre un batiment
		void setConstruit() 
		{ if(m_TypeDeLaCase == SOL) m_TypeDeLaCase = EST_CONSTRUIT; else throw "Vous ne pouvez pas construire cette case"; }
		void setConstruit(Batiment bat) { if(m_TypeDeLaCase == EST_CONSTRUIT) m_Batiment = bat; }
		Batiment getConstruction() { return m_Batiment; }

		void ajoutObjet(Objet objet);
		void retireObjet();
		
	private :
		Objet *m_Objet;
		TypeCase m_TypeDeLaCase;
		Batiment m_Batiment;
		bool m_IsSmooth;
		bool m_EstFortifie;
};

#endif
