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
	m_Map[0].push_back(Case(MUR_UN_SUD));
	m_Map[0].push_back(Case(MUR_DEUX_ADJACENTS_SUD_EST));
	m_Map[0].push_back(Case(SOL)); // Après, Case(PORTE)
	m_Map[0].push_back(Case(MUR_DEUX_ADJACENTS_SUD_OUEST));
	m_Map[0].push_back(Case(MUR_UN_SUD));

	m_Map[1].push_back(Case(VIDE));
	m_Map[1].push_back(Case(MUR_UN_EST));
	m_Map[1].push_back(Case(SOL));
	m_Map[1].push_back(Case(MUR_UN_OUEST));

	m_Map[2].push_back(Case(VIDE));
	m_Map[2].push_back(Case(VIDE));
	m_Map[2].push_back(Case(MUR_UN_SUD));

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
	const float DISTANCE_ECART = 0.1, 
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
			core::vector3df rotation(0, 0, 0);

			switch(m_Map[i][j].getTypeDeLaCase())
			{
				case VIDE : continue;
				case MUR_UN_NORD : 
					rotation = core::vector3df(0, 0, 0);
					meshCourant = sceneManager->getMesh("data/mesh/mur_un.obj");
					break;
				case MUR_UN_SUD : 
					rotation = core::vector3df(0, 180, 0);
					meshCourant = sceneManager->getMesh("data/mesh/mur_un.obj");
					break;
				case MUR_UN_EST : 
					rotation = core::vector3df(0, 90, 0);
					meshCourant = sceneManager->getMesh("data/mesh/mur_un.obj");
					break;
				case MUR_UN_OUEST :
					rotation = core::vector3df(0, -90, 0);
					meshCourant = sceneManager->getMesh("data/mesh/mur_un.obj");
					break;

				case MUR_DEUX_OPPOSES_NORD_SUD :
					rotation = core::vector3df(0, 0, 0);
					meshCourant = sceneManager->getMesh("data/mesh/mur_deux_opposes.obj");
					break;
				case MUR_DEUX_OPPOSES_EST_OUEST :
					rotation = core::vector3df(0, 90, 0);
					meshCourant = sceneManager->getMesh("data/mesh/mur_deux_opposes.obj");
					break;

				case MUR_DEUX_ADJACENTS_NORD_OUEST :
					rotation = core::vector3df(0, 90, 0);
					meshCourant = sceneManager->getMesh("data/mesh/mur_deux_adjacents.obj");
					break;
				case MUR_DEUX_ADJACENTS_NORD_EST : 
					rotation = core::vector3df(0, 180, 0);
					meshCourant = sceneManager->getMesh("data/mesh/mur_deux_adjacents.obj");
					break;
				case MUR_DEUX_ADJACENTS_SUD_OUEST :
					rotation = core::vector3df(0, 0, 0);
					meshCourant = sceneManager->getMesh("data/mesh/mur_deux_adjacents.obj");
					break;
				case MUR_DEUX_ADJACENTS_SUD_EST :
					rotation = core::vector3df(0, -90, 0);
					meshCourant = sceneManager->getMesh("data/mesh/mur_deux_adjacents.obj");
					break;

				case MUR_TROIS_NORD : 
					rotation = core::vector3df(0, 0, 0);
					meshCourant = sceneManager->getMesh("data/mesh/mur_trois.obj");
					break;
				case MUR_TROIS_SUD :
					rotation = core::vector3df(0, 0, 0);
					meshCourant = sceneManager->getMesh("data/mesh/mur_trois.obj");
					break;
				case MUR_TROIS_EST :
					rotation = core::vector3df(0, 0, 0);
					meshCourant = sceneManager->getMesh("data/mesh/mur_trois.obj");
					break;
				case MUR_TROIS_OUEST :
					rotation = core::vector3df(0, 180, 0);
					meshCourant = sceneManager->getMesh("data/mesh/mur_trois.obj");
					break;
				case SOL : 
					meshCourant = sceneManager->getMesh("data/mesh/sol-plafond.obj");
					break;
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
						 rotation,   // rotation
						 core::vector3df(1.0f, 1.0f, 1.0f)  // scale
						);
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
					m_Map[ligne][colone-2] = Case(MUR_UN_EST);
				default : break;
			}
			switch(m_Map[ligne][colone-1].getTypeDeLaCase())
			{
				case VIDE :
				case MUR_UN_EST :
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
				case VIDE : m_Map[ligne-1][colone-1] = Case(MUR_UN_NORD); break;
				case MUR_UN_OUEST : m_Map[ligne-1][colone-1] = Case(MUR_DEUX_ADJACENTS_NORD_OUEST);break; 
				case MUR_UN_EST : m_Map[ligne-1][colone-1] = Case(MUR_DEUX_ADJACENTS_NORD_EST); break; 
				case MUR_UN_SUD : m_Map[ligne-1][colone-1] = Case(MUR_DEUX_OPPOSES_NORD_SUD); break;
				
				case MUR_DEUX_OPPOSES_EST_OUEST : m_Map[ligne-1][colone-1] = Case(MUR_TROIS_SUD); break;
				case MUR_DEUX_ADJACENTS_SUD_EST : m_Map[ligne-1][colone-1] = Case(MUR_TROIS_OUEST); break;
				case MUR_DEUX_ADJACENTS_SUD_OUEST : m_Map[ligne-1][colone-1] = Case(MUR_TROIS_EST); break;

				case MUR_DEUX_OPPOSES_NORD_SUD : 
				case MUR_DEUX_ADJACENTS_NORD_EST : 
				case MUR_DEUX_ADJACENTS_NORD_OUEST : 
				default : break;
			}
			// Case en haut a gauche
			switch(m_Map[ligne+1][colone-1].getTypeDeLaCase())
			{
				case VIDE : m_Map[ligne+1][colone-1] = Case(MUR_UN_SUD); break;
				case MUR_UN_OUEST : m_Map[ligne+1][colone-1] = Case(MUR_DEUX_ADJACENTS_NORD_OUEST);break; 
				case MUR_UN_EST : m_Map[ligne+1][colone-1] = Case(MUR_DEUX_ADJACENTS_NORD_EST); break; 
				case MUR_UN_NORD : m_Map[ligne+1][colone-1] = Case(MUR_DEUX_OPPOSES_NORD_SUD); break;
				
				case MUR_DEUX_OPPOSES_EST_OUEST : m_Map[ligne+1][colone-1] = Case(MUR_TROIS_NORD); break;
				case MUR_DEUX_ADJACENTS_SUD_OUEST : m_Map[ligne+1][colone-1] = Case(MUR_TROIS_EST); break;
				case MUR_DEUX_ADJACENTS_NORD_EST : m_Map[ligne+1][colone-1] = Case(MUR_TROIS_OUEST); break;

				case MUR_DEUX_OPPOSES_NORD_SUD : 
				case MUR_DEUX_ADJACENTS_SUD_EST :
				case MUR_DEUX_ADJACENTS_NORD_OUEST : 
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
					m_Map[ligne].push_back(Case(MUR_UN_OUEST));
				else // cela signifie qu'il y a quelque chose en "colone+2"
				{
					switch(m_Map[ligne][colone+2].getTypeDeLaCase())
					{
						case VIDE : m_Map[ligne][colone+2] = Case(MUR_UN_OUEST); break;
						default : break;
					}
				}
			// Fin ajout du SOL a droite

			// Ajout des MUR_SUD et MUR_NORD de chaque coté du SOL
			// Case en haut : MUR SUD
				while(m_Map[ligne+1].size() <= (colone+1))
					m_Map[ligne+1].insert(m_Map[ligne+1].begin(), Case(VIDE));
				
				switch(m_Map[ligne+1][colone+1].getTypeDeLaCase())
				{
					case VIDE : 
						m_Map[ligne+1][colone+1] = Case(MUR_UN_SUD);
						break;
					case MUR_UN_OUEST : m_Map[ligne+1][colone+1] = Case(MUR_DEUX_ADJACENTS_SUD_OUEST); break;
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
					case VIDE : m_Map[ligne-1][colone+1] = Case(MUR_UN_NORD); break;
					case MUR_UN_OUEST : m_Map[ligne-1][colone+1] = Case(MUR_DEUX_ADJACENTS_NORD_OUEST); break;
					case MUR_DEUX_ADJACENTS_SUD_OUEST : m_Map[ligne-1][colone+1] = Case(MUR_TROIS_EST); break;
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
				case VIDE : m_Map[ligne+1][colone-1] = Case(MUR_UN_EST); break;
				default : break;
			}

			// Case en haut
			switch(m_Map[ligne+1][colone].getTypeDeLaCase())
			{
				case VIDE : 
				case MUR_UN_SUD : m_Map[ligne+1][colone] = Case(SOL); break;
				default : break;
			}

			// Case en haut a droite
			switch(m_Map[ligne+1][colone+1].getTypeDeLaCase())
			{
				case VIDE : m_Map[ligne+1][colone+1] = Case(MUR_UN_OUEST); break;
				default : break;
			}
			
			// Case tout en haut
			switch(m_Map[ligne+2][colone].getTypeDeLaCase())
			{
				case VIDE : m_Map[ligne+2][colone] = Case(MUR_UN_SUD); break;
				default : break;
			};
			break;
		case SUD :
			break;
		default: break;
	}
}
