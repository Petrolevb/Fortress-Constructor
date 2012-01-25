#ifndef HPP_NIVEAU
#define HPP_NIVEAU

#include<vector>

#include<irrlicht/irrlicht.h>

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
		Niveau(irr::scene::ISceneManager *sceneManager);
		~Niveau();

		/* 
		 * Prend en parramêtre la position de la case de départ et traite automatiquement 
		 * la mise à jour des cases autour
		 */
		void creuse(int ligne, int colone, Direction direction);
	private :
		
		std::vector< std::vector<Case> > m_Map;
		irr::scene::ISceneManager *m_LINK_sceneManager;

};

#endif
