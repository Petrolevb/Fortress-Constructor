#ifndef HPP_OBJET
#define HPP_OBJET

typedef enum {
	NULL_OBJET,

	CHAISE,
	TABLE,
	LIT,
	CONSTRUCTION,

	PORTE_NORD,
	PORTE_EST,
	PONT,

	ESCALIER_HAUT,
	ESCALIER_BAS,
	ESCALIER_HAUT_BAS

} TypeObjet;

class Objet
{
	public :
		Objet();
		Objet(TypeObjet type);
		Objet(const Objet& objetACopier);

		~Objet();

		Objet & operator=(const Objet &objetACopier);
		bool operator==(const Objet &a);

		TypeObjet getTypeObjet() { return m_TypeDeLObjet; }
		bool getActif() { return m_Actif; }
		void setActif(bool value) { m_Actif = value; }
		bool getActiviteEnCours() { return m_ActiviteEnCours; }
		void setActiviteEnCours(bool value) { m_ActiviteEnCours = value; }

	private :
		TypeObjet m_TypeDeLObjet;
		bool m_Actif;
		bool m_ActiviteEnCours;
};

#endif
