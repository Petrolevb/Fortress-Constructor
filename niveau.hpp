#ifndef HPP_NIVEAU
#define HPP_NIVEAU

#include<vector>

#include"case.hpp"

typedef enum{
	HAUT,
	BAS,
	NORD,
	SUD,
	OUEST,
	EST
}Direction;

class Niveau
{
	public :
		Niveau();
		~Niveau();

		/* 
		 * Prend en parramêtre la position de la case de départ et traite automatiquement 
		 * la mise à jour des cases autour
		 */
		void creuse(int ligne, int colone, Direction direction);
		//std::vector< std::vector<TypeCase> > chaineNiveau();
		void afficheConsole();
	private :
		
		std::vector< std::vector<Case> > m_Map;
};

#endif
