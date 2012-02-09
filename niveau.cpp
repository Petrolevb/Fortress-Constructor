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
	m_Map[0].push_back(Case(PORTE_NORD)); 
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
	// Affichage et chargement des niveaux 
	// On n'affiche que les changements
	const float DISTANCE_ECART = 0, // 0.1, 
		  largeurBox = 2,
		  longueurBox = 2;
	
	try
	{
		scene::IMetaTriangleSelector *metaSelector = sceneManager->createMetaTriangleSelector();
		for(unsigned int i = 0; i < m_Map.size(); i++)
		{
			for(unsigned int j = 0; j < m_Map[i].size(); j++)
			{
				scene::IAnimatedMesh *meshCourant = NULL, 
						     *meshObjet = NULL;
				core::vector3df rotationObjet(0, 0, 0),
						positionMesh(0, 0, 0);
	
				scene::ITriangleSelector *selector = NULL;
				switch(m_Map[i][j].getTypeDeLaCase())
				{
					case MUR :
						if(m_Map[i][j].getIsSmooth())
							meshCourant = sceneManager->getMesh("data/mesh/mur_poli.obj");
						else
							meshCourant = sceneManager->getMesh("data/mesh/mur_text.obj");

						if(!meshCourant) exit(1);
						selector = sceneManager->createOctreeTriangleSelector(meshCourant, 
												      sceneManager->getRootSceneNode());
						break;
					case SOL : 
						if(m_Map[i][j].getIsSmooth())
							//meshCourant = sceneManager->getMesh("data/mesh/sol-plafond_poli.obj");  N'EXISTE PAS
							meshCourant = sceneManager->getMesh("data/mesh/sol-plafond_text.obj");
						else
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
				scene::IMeshSceneNode *element = sceneManager->addOctreeSceneNode(meshCourant->getMesh(0));
				element->setPosition(core::vector3df(j*(largeurBox + DISTANCE_ECART), 0, i*(longueurBox + DISTANCE_ECART)));
				element->setParent(sceneManager->getRootSceneNode()); // parent
							 // Seul les murs sont creusable, et impassable
				element->setID((m_Map[i][j].getTypeDeLaCase() == MUR ? ID_EstAtteignable : ID_NEstPasAtteingable)); 
				// Pas de rotation, pas de mise à l'echelle
	
				if(meshObjet)
				{
					scene::IAnimatedMeshSceneNode *objet = sceneManager->addAnimatedMeshSceneNode(
						meshObjet, 
						sceneManager->getRootSceneNode(),
						((m_Map[i][j].getTypeObjet() == PORTE_NORD||PORTE_EST)?ID_Objet_Porte:ID_Objet),
						core::vector3df(j*(largeurBox + DISTANCE_ECART), 0, i*(longueurBox + DISTANCE_ECART)),
						rotationObjet); // scale par défaut, booléen suivant par défaut
					objet->setMaterialFlag(video::EMF_LIGHTING, false);
					if(m_Map[i][j].getObjetActivite()) // Si l'objet est actif (ouverture porte, etc...)
					{
						objet->setAnimationSpeed(50);
						objet->setLoopMode(true);
						// Animation finie
						m_Map[i][j].setObjetActivite(false);
					}
					// Trouver le moyen de mettre les deux textures
					objet->setMaterialTexture(1, sceneManager->getVideoDriver()->getTexture("data/textures/objets/contour_test.png"));
					objet->setMaterialTexture(0, sceneManager->getVideoDriver()->getTexture("data/textures/objets/grande_porte.png"));
				}
				element->setMaterialFlag(video::EMF_LIGHTING, false);
				
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
			

			} // Fin boucle de tous les mesh

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
	}	}	}	}	}
	// Fin générale jusqu'au try
	catch (exception ex)
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

void Niveau::setSmooth(int ligne, int colone, Direction direction)
{
	switch(direction)
	{
		case NORD  : m_Map[ligne+1][colone].setSmooth(); break;
		case SUD   : m_Map[ligne-1][colone].setSmooth(); break;
		case EST   : m_Map[ligne][colone+1].setSmooth(); break;
		case OUEST : m_Map[ligne][colone-1].setSmooth(); break;
		default : break;
	}
}

void Niveau::ouverturePorte()
{
	// On connait pour le moment la position de la seule et unique porte, après sera donné la position
	// position : Ligne 0, colone 2
	m_Map[0][2].setObjetActif(!m_Map[0][2].getObjetActif());
	// De toute faceon, l'objet change d'état
	m_Map[0][2].setObjetActivite(true);
}
