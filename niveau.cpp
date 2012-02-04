#include<iostream>
#include<vector>

#include<irrlicht/irrlicht.h>

#include "niveau.hpp"
#include "case.hpp"

using namespace std;
using namespace irr;

Niveau::Niveau() :
	m_Init_Ligne(1), m_Init_Colone(2)
{
	cout << "Niveau  constructeur normal de la classe"; 
	m_Map.resize(3);
	cout << endl << '\t';
	
	// Initialisation d'une petite salle, porte d'entrée de la forteresse
	m_Map[0].push_back(Case(MUR));
	m_Map[0].push_back(Case(MUR));
	m_Map[0].push_back(Case(PORTE_NORD)); // Après, Case(PORTE)
	m_Map[0].push_back(Case(MUR));
	m_Map[0].push_back(Case(MUR));

	m_Map[1].push_back(Case(VIDE));
	m_Map[1].push_back(Case(MUR));
	m_Map[1].push_back(Case(SOL));
	m_Map[1].push_back(Case(MUR));

	m_Map[2].push_back(Case(VIDE));
	m_Map[2].push_back(Case(VIDE));
	m_Map[2].push_back(Case(MUR));

	cout << "OK" << endl;
}

Niveau::~Niveau()
{
}

void Niveau::afficheConsole(scene::ISceneManager *sceneManager)
{
	
//	cout << endl << endl << endl;
	// Affichage et chargement des niveaux 
	// On n'affiche que les changements
	const float DISTANCE_ECART = 0, // 0.1, 
		  largeurBox = 2,
		  longueurBox = 2;
	
	try
	{
		// Vide tout le scene manager
		// On récupère tous les mesh et on les drop
		//core::array<scene::ISceneNode*> meshsEnregistres;
		//sceneManager->getSceneNodesFromType(scene::ESNT_MESH, meshsEnregistres);

	for(unsigned int i = 0; i < m_Map.size(); i++)
	{
		for(unsigned int j = 0; j < m_Map[i].size(); j++)
		{
			scene::IMesh *meshCourant = NULL;
			scene::IMesh *meshObjet = NULL;
			core::vector3df rotationObjet(0, 0, 0);
			switch(m_Map[i][j].getTypeDeLaCase())
			{
				case MUR : 
					meshCourant = sceneManager->getMesh("data/mesh/mur_text.obj");
					if(!meshCourant) exit(1);
					break;
				case SOL : 
					meshCourant = sceneManager->getMesh("data/mesh/sol-plafond_text.obj");
					switch(m_Map[i][j].getTypeObjet())
					{
						case PORTE_NORD :
							rotationObjet = core::vector3df(0, 90, 0);
						case PORTE_EST :
							meshObjet = sceneManager->getMesh("data/mesh/objets/porte_test.3ds");
							if(!meshObjet) exit(1);
							break;
						default :
							break;
					}
					if(!meshCourant) exit(1);
					break;
				case VIDE :
				default : continue;
			}
			
			// addMeshSceneNode : mesh, parent, id, position, rotation, scale
				
			core::aabbox3df box = meshCourant->getBoundingBox();
			core::vector3df pointsBox[8];

			box.getEdges(pointsBox);
			/*
			 * 
			 * Les 8 points sont : 
			 *    3------7
			 *   /|     /|
			 *  / |    / |
			 * 1------5  |
			 * |  2- -| -6
			 * | /    | /
			 * |/     |/
			 * 0------4
			 *
			 * Affichage : 
			 *  Y
			 *  ^ 
			 *  | z
			 *  |/
			 *   ---> X>
			 **/
			scene::IMeshSceneNode *element = sceneManager->
				addMeshSceneNode(meshCourant,  // mesh
						 sceneManager->getRootSceneNode(), // parent
						 -1, // id par defaut
						 core::vector3df(j*(largeurBox + DISTANCE_ECART),
						 		 0,
								 i*(longueurBox + DISTANCE_ECART)),  // position : x, y, z
						 core::vector3df(0, 0, 0),   // rotation
						 core::vector3df(1.0f, 1.0f, 1.0f)  // scale
						);
			if(meshObjet != NULL)
			{
				scene::IMeshSceneNode *objet = sceneManager->
					addMeshSceneNode(meshObjet,  // mesh
							 sceneManager->getRootSceneNode(), // parent
							 -1, // id par defaut
							 core::vector3df(j*(largeurBox + DISTANCE_ECART),
							 		 0,
									 i*(longueurBox + DISTANCE_ECART)),  // position : x, y, z
							 rotationObjet,   // rotation
							 core::vector3df(1.0f, 1.0f, 1.0f)  // scale
							);
				objet->setMaterialFlag(video::EMF_LIGHTING, false);
				objet->setMaterialTexture(0, sceneManager->getVideoDriver()->getTexture("data/textures/objets/grande_porte.png"));
				// Trouver le moyen de mettre les deux
				//objet->setMaterialTexture(0, sceneManager->getVideoDriver()->getTexture("data/textures/objets/contour_test.png"));
			}
			element->setMaterialFlag(video::EMF_LIGHTING, false);
		}
		//cout << endl;
	}
	} catch (exception ex)
	{ cerr << ex.what() << endl; }
}

void Niveau::creuse(int ligne, int colone, Direction direction)
{
	vector<Case> nouveauVector;
	switch(direction)
	{
		case HAUT :
			break;
		case BAS :
			break;
		case OUEST :
			if(colone-2 < 0) // Si on va creuser hors du tableau, il faut ajouter une colone complête
			{
				for(unsigned int i = 0; i < m_Map.size(); i++)
					m_Map[i].insert(m_Map[i].begin(), Case(VIDE));
				m_Init_Colone++; colone++;
			}
			switch(m_Map[ligne][colone-2].getTypeDeLaCase())
			{
				case VIDE :
					m_Map[ligne][colone-2] = Case(MUR);
				default : break;
			}
			switch(m_Map[ligne][colone-1].getTypeDeLaCase())
			{
				case VIDE :
				case MUR :
					m_Map[ligne][colone-1] = Case(SOL);
				default : break;
			}
			if(ligne-1 < 0)
			{
				m_Map.insert(m_Map.begin(), vector<Case>());
				m_Init_Ligne++;
				ligne++;
			}
			// Case en bas à gauche
			switch(m_Map[ligne-1][colone-1].getTypeDeLaCase())
			{
				case VIDE : m_Map[ligne-1][colone-1] = Case(MUR); break;
				default : break;
			}
			// Case en haut a gauche
			switch(m_Map[ligne+1][colone-1].getTypeDeLaCase())
			{
				case VIDE : m_Map[ligne+1][colone-1] = Case(MUR); break;
				default : break;
			}
			break;
		case EST :
			/* Ajoute un Sol à droite, un mur_un_sud diagonale haut droite, un mur_un_nord diagonale bas droite */
			if(m_Map.size() < (unsigned int)(ligne+1))
				m_Map.push_back(vector<Case>());
			
			// Ajout du SOL à droite et du MUR OUEST
				m_Map[ligne][colone+1] = Case(SOL);

				if(m_Map[ligne].size() <= (colone+2))
					m_Map[ligne].push_back(Case(MUR));
				else // cela signifie qu'il y a quelque chose en "colone+2"
				{
					switch(m_Map[ligne][colone+2].getTypeDeLaCase())
					{
						case VIDE : m_Map[ligne][colone+2] = Case(MUR); break;
						default : break;
					}
				}
			// Fin ajout du SOL a droite

			// Case en haut : 
				while(m_Map[ligne+1].size() <= (colone+1))
					m_Map[ligne+1].insert(m_Map[ligne+1].begin() + m_Map[ligne+1].size(), Case(VIDE));
				
				switch(m_Map[ligne+1][colone+1].getTypeDeLaCase())
				{
					case VIDE : 
						m_Map[ligne+1][colone+1] = Case(MUR);
						break;
					default : break;
				}
			// Case en bas : MUR NORD
				if(ligne-1 < 0)
				{
					m_Map.insert(m_Map.begin(), vector<Case>());
					m_Init_Ligne++;
					ligne++;
				}
				while(m_Map[ligne-1].size() <= (colone+1))
					m_Map[ligne-1].insert(m_Map[ligne-1].begin(), Case(VIDE));
				switch(m_Map[ligne-1][colone+1].getTypeDeLaCase())
				{
					case VIDE : m_Map[ligne-1][colone+1] = Case(MUR); break;
					default : break; // Si ce n'est pas une case que l'on vient d'ajouter
				}

			break;

		case NORD :
			if(m_Map[ligne+1][colone].getTypeDeLaCase() == SOL) break;

			if(m_Map.size() <= (unsigned int)(ligne+2)) //si m_Map.size() == ligne+2, alors m_Map[i] vas de 0 à (ligne+2) - 1
				m_Map.insert(m_Map.begin() + ligne+1, vector<Case>());
			
			// On ajoute dans la ligne+2 des cases VIDE jusqu'où il faut
			for(unsigned int i = m_Map[ligne+2].size(); i <= (unsigned int)(colone+1); i++)
					m_Map[ligne+2].insert(m_Map[ligne+2].begin()+ m_Map[ligne+2].size(), Case(VIDE));
			// De même, dans la ligne+1
			for(unsigned int i = m_Map[ligne+1].size(); i <= (unsigned int)(colone+1); i++)	
					m_Map[ligne+1].insert(m_Map[ligne+1].begin()+ m_Map[ligne+1].size(), Case(VIDE));

			// Case en haut a gauche
			switch(m_Map[ligne+1][colone-1].getTypeDeLaCase())
			{
				case VIDE : m_Map[ligne+1][colone-1] = Case(MUR); break;
				default : break;
			}

			// Case en haut
			switch(m_Map[ligne+1][colone].getTypeDeLaCase())
			{
				case VIDE : 
				case MUR : m_Map[ligne+1][colone] = Case(SOL); break;
				default : break;
			}

			// Case en haut a droite
			switch(m_Map[ligne+1][colone+1].getTypeDeLaCase())
			{
				case VIDE : m_Map[ligne+1][colone+1] = Case(MUR); break;
				default : break;
			}
			
			// Case tout en haut
			switch(m_Map[ligne+2][colone].getTypeDeLaCase())
			{
				case VIDE : m_Map[ligne+2][colone] = Case(MUR); break;
				default : break;
			};
			break;
		case SUD :
			break;
		default: break;
	}
}
