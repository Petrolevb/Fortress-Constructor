#include<iostream>
#include<vector>

#include<irrlicht/irrlicht.h>

#include "definitions.hpp"

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
	const float DISTANCE_ECART = 0.1, 
		  largeurBox = 2,
		  longueurBox = 2;
	
	try
	{
	
	scene::IMetaTriangleSelector *metaSelector = sceneManager->createMetaTriangleSelector();
	for(unsigned int i = 0; i < m_Map.size(); i++)
	{
		for(unsigned int j = 0; j < m_Map[i].size(); j++)
		{
			scene::IMesh *meshCourant = NULL;
			scene::IMesh *meshObjet = NULL;
			core::vector3df rotationObjet(0, 0, 0);
			scene::ITriangleSelector *selector = NULL;
			switch(m_Map[i][j].getTypeDeLaCase())
			{
				case MUR : 
					meshCourant = sceneManager->getMesh("data/mesh/murs.obj");
					selector = sceneManager->createOctreeTriangleSelector(meshCourant, 
											      sceneManager->getRootSceneNode());
					break;
				case SOL : 
					meshCourant = sceneManager->getMesh("data/mesh/sol-plafond.obj");
					switch(m_Map[i][j].getTypeObjet())
					{
						case PORTE_NORD :
							rotationObjet = core::vector3df(0, 90, 0);
						case PORTE_EST :
							meshObjet = sceneManager->getMesh("data/mesh/objets/porte.obj");
							break;
						default :
							break;
					}
					break;
				case VIDE :
				default : continue;
			}
			
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
						 // Seul les murs sont creusable, et impassable
						 (m_Map[i][j].getTypeDeLaCase() == MUR ? ID_EstAtteignable : ID_NEstPasAtteingable), 
						 core::vector3df(j*(largeurBox + DISTANCE_ECART),
						 		 0,
								 i*(longueurBox + DISTANCE_ECART)),  // position : x, y, z
						 core::vector3df(0, 0, 0),   // rotation
						 core::vector3df(1.0f, 1.0f, 1.0f)  // scale
						);
			if(selector)
			{
				metaSelector->addTriangleSelector(selector);
				/* 
				 * Marche très bien uniquement pour le premier scene node, mais pas pour les suivants

				element->setTriangleSelector(selector);
				scene::ISceneNodeAnimator *anim = sceneManager->createCollisionResponseAnimator(
									selector, 
									sceneManager->getActiveCamera(), // SceneNode affecté
									(meshCourant->getBoundingBox().MaxEdge - meshCourant->getBoundingBox().getCenter()), // Radius, code donné dans la librairie
									core::vector3df(0, 0, 0)); // Gravité desactivée
									// Les deux autres paramêtres par défaut
				sceneManager->getActiveCamera()->addAnimator(anim);
				
				**/
				selector->drop();
				//anim->drop();
			}
			

			if(meshObjet != NULL)
			{
				scene::IMeshSceneNode *objet = sceneManager->
					addMeshSceneNode(meshObjet,  // mesh
							 sceneManager->getRootSceneNode(), // parent
							 ID_EstAtteignable, 
							 core::vector3df(j*(largeurBox + DISTANCE_ECART),
							 		 ((m_Map[i][j].getTypeObjet() == PORTE) ? ID_Objet_Porte:ID_Objet),
									 i*(longueurBox + DISTANCE_ECART)),  // position : x, y, z
							 rotationObjet,   // rotation
							 core::vector3df(1.0f, 1.0f, 1.0f)  // scale
							);
				objet->setMaterialFlag(video::EMF_LIGHTING, false);
			}
			element->setMaterialFlag(video::EMF_LIGHTING, false);
		}
		//cout << endl;
		if(metaSelector)
		{
			core::array<scene::ISceneNode*> sceneNodes;
			sceneManager->getSceneNodesFromType(scene::ESNT_ANY, sceneNodes);
			for(u32 i = 0; i < sceneNodes.size(); i++)
			{
				if(sceneNodes[i]->getID() == ID_EstAtteignable)
				{
					// La bounding box du mesh
					core::aabbox3df boundingBoxBase = sceneNodes[i]->getBoundingBox();
					scene::ISceneNodeAnimatorCollisionResponse *anim = sceneManager->createCollisionResponseAnimator
								(
									metaSelector,
									sceneManager->getActiveCamera(),
									(boundingBoxBase.MaxEdge - boundingBoxBase.getCenter()),
									core::vector3df(0, 0, 0) // Gravitée nulle 
								);
					metaSelector->drop();
					sceneManager->getActiveCamera()->addAnimator(anim);
					anim->drop();
				}
			}
		}
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
