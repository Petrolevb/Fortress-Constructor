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
		Niveau();
		~Niveau();

		/* 
		 * Prend en parramêtre la position de la case de départ et traite automatiquement 
		 * la mise à jour des cases autour
		 */
		void creuse(int ligne, int colone, Direction direction);

		void afficheConsole(irr::scene::ISceneManager *sceneManager);

		int getLigneInit() { return m_Init_Ligne; }
		int getColoneInit() { return m_Init_Colone; } 

	private :
		std::vector< std::vector<Case> > m_Map;
		int m_Init_Ligne;
		int m_Init_Colone;
};

#endif
