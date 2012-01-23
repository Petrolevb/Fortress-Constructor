#ifndef HPP_OBJET
#define HPP_OBJET


typedef enum {
	CHAISE,
	TABLE,
	LIT,
	CONSTRUCTION,

	PORTE,
	PONT,

	ESCALIER_HAUT,
	ESCALIER_BAS,
	ESCALIER_HAUT_BAS

} TypeObjet;

class Objet
{
	public :
		Objet(TypeObjet type);
		~Objet();
	private :
		TypeObjet m_TypeDeLObjet;
};

#endif
