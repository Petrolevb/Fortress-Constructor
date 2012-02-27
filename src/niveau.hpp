#ifndef HPP_NIVEAU
#define HPP_NIVEAU

#include<vector>

#include<irrlicht/irrlicht.h>

#include"case.hpp"
#include"salle.hpp"

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
		void activiteObjet(int ligne, int colone, Direction direction);
		void creuse(int ligne, int colone, Direction direction);
		void setSmooth(int ligne, int colone, Direction direction);
		// Retourne si la case a bien été fortifiée
		bool fortifie(int ligne, int colone, Direction direction);

		bool construit(int ligne, int colone, Batiment bat);

		void afficheConsole(irr::scene::ISceneManager *sceneManager);

	private :
		std::vector< std::vector<Case> > m_Map;
};

#endif
