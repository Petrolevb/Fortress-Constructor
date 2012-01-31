#include<iostream>
#include<vector>

#include<irrlicht/irrlicht.h>

#include "niveau.hpp"
#include "case.hpp"

using namespace std;
using namespace irr;

Niveau::Niveau() :
	m_Init_Ligne(0), m_Init_Colone(0)
{
	cout << "Niveau  constructeur normal de la classe"; 
	m_Map.resize(1);
	cout << endl << '\t';

	m_Map[0].push_back(Case(MUR_UN_EST));
	m_Map[0].push_back(Case(SOL));
		m_Init_Colone++;
	m_Map[0].push_back(Case(MUR_DEUX_ADJACENTS_NORD_OUEST));

	m_Map.push_back(vector<Case>());
	m_Map[1].push_back(Case(VIDE));
	m_Map[1].push_back(Case(SOL));
	m_Map[1].push_back(Case(SOL));
	m_Map[1].push_back(Case(MUR_UN_OUEST));
	
	m_Map.push_back(vector<Case>());
	m_Map[2].push_back(Case(VIDE));
	m_Map[2].push_back(Case(MUR_UN_SUD));
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
	const int DISTANCE_ECART = 1, 
		  largeurBox = 2,
		  longueurBox = 2;
	try
	{
	for(int i = 0; i < m_Map.size(); i++)
	{
		for(int j = 0; j < m_Map[i].size(); j++)
		{
			scene::IMesh *meshCourant = NULL;
			core::vector3df rotation(0, 0, 0);

			switch(m_Map[i][j].getTypeDeLaCase())
			{
				case VIDE : continue;
//					break;
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
					rotation = core::vector3df(0, 0, 0);
					meshCourant = sceneManager->getMesh("data/mesh/mur_deux_adjacents.obj");
					break;
				case MUR_DEUX_ADJACENTS_NORD_EST : 
					rotation = core::vector3df(0, 90, 0);
					meshCourant = sceneManager->getMesh("data/mesh/mur_deux_adjacents.obj");
					break;
				case MUR_DEUX_ADJACENTS_SUD_OUEST :
					rotation = core::vector3df(0, -90, 0);
					meshCourant = sceneManager->getMesh("data/mesh/mur_deux_adjacents.obj");
					break;
				case MUR_DEUX_ADJACENTS_SUD_EST :
					rotation = core::vector3df(0, 180, 0);
					meshCourant = sceneManager->getMesh("data/mesh/mur_deux_adjacents.obj");
					break;

				case MUR_TROIS_NORD : 
				case MUR_TROIS_SUD :
				case MUR_TROIS_EST :
				case MUR_TROIS_OUEST :
					meshCourant = sceneManager->getMesh("data/mesh/mur_trois.obj");
					break;
				case SOL : 
					meshCourant = sceneManager->getMesh("data/mesh/sol-plafond.obj");
					break;
				default : continue;
//					break;
			}
			
			// addMeshSceneNode : mesh, parent, id, position, rotation, scale
			
			core::aabbox3df box = meshCourant->getBoundingBox();
			core::vector3df pointsBox[8];

			box.getEdges(pointsBox);
			/*
			 * 
			 * Les 8 points sont : 
			 *    3---_--7
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
			break;
		case EST :
			/* Ajoute un Sol à droite, un mur_un_sud diagonale haut droite, un mur_un_nord diagonale bas droite */
			m_Map[ligne].insert(m_Map[ligne].begin() + colone, Case(SOL));
			break;
		case NORD :
			//if(m_Map.size() < ligne+1)
			m_Map.insert(m_Map.begin() + ligne+1, nouveauVector);

			while(m_Map[ligne+1].size() < colone) // Tant qu'on n'est pas à la bonne colone
				m_Map[ligne+1].insert(m_Map[ligne+1].begin(), Case(VIDE));
			m_Map[ligne+1].insert(m_Map[ligne+1].begin() + colone-1, Case(MUR_UN_EST));
			m_Map[ligne+1].insert(m_Map[ligne+1].begin() + colone, Case(SOL));
			m_Map[ligne+1].insert(m_Map[ligne+1].begin() + colone+1, Case(MUR_UN_OUEST));
			break;
		case SUD :
			break;
		default: break;
	}
}
