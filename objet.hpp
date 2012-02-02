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

		TypeObjet getTypeObjet() { return m_TypeDeLObjet; }

	private :
		TypeObjet m_TypeDeLObjet;
};

#endif
