#include<iostream>
#include<vector>

#include<irrlicht/irrlicht.h>

#include "definitions.hpp"

#include "niveau.hpp"
#include "case.hpp"
#include"salle.hpp"

using namespace std;
using namespace irr;

Niveau::Niveau()
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
	m_Map[2].push_back(Case(MUR));
	m_Map[2].push_back(Case(MUR));
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


				vector<scene::IAnimatedMesh *> meshsSalle;
				// Par défaut, les 9 sont à nul
				meshsSalle.push_back(NULL); meshsSalle.push_back(NULL); meshsSalle.push_back(NULL);
				meshsSalle.push_back(NULL); meshsSalle.push_back(NULL); meshsSalle.push_back(NULL);
				meshsSalle.push_back(NULL); meshsSalle.push_back(NULL); meshsSalle.push_back(NULL);

				vector<core::vector3df> rotationSalle(9, core::vector3df(0, 0, 0));
				bool construction = false; // Indique si on doit gérer une construction dans l'affichage

				core::vector3df rotationObjet(0, 0, 0),
						positionMesh(0, 0, 0);
	
				scene::ITriangleSelector *selector = NULL;
				switch(m_Map[i][j].getTypeDeLaCase())
				{
					case MUR :
						if(m_Map[i][j].getIsFortifie())
							meshCourant = sceneManager->getMesh("data/mesh/mur_fort.obj");
						else if(m_Map[i][j].getIsSmooth())
							meshCourant = sceneManager->getMesh("data/mesh/mur_poli.obj");
						else
							meshCourant = sceneManager->getMesh("data/mesh/mur_text.obj");

						if(!meshCourant) exit(1);
						selector = sceneManager->createOctreeTriangleSelector(meshCourant, 
												      sceneManager->getRootSceneNode());
						break;
					case EST_CONSTRUIT :
					case SOL : 
						if(m_Map[i][j].getIsSmooth())
							meshCourant = sceneManager->getMesh("data/mesh/sol-plafond_poli.obj");
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
						if(m_Map[i][j].getTypeDeLaCase() == EST_CONSTRUIT)
						{
							vector< vector<TypeConstruction> > planSalle;
							Batiment bat =  m_Map[i][j].getConstruction();
							if(bat != SANS_BATIMENT && bat != NOMBRE_BATIMENT) // Si il y a bien une vraie constructio
							{
								planSalle = Salle::getPlan(bat);
								construction = true;

								for(unsigned int a = 0; a < planSalle.size() ; a++)
								{
									for(unsigned int b = 0 ; b < planSalle[a].size(); b++)
									{
										switch(planSalle[a][b])
										{
										{ // Angles
											case SALLE_ANGLE_NO :
												rotationSalle[3*a +b] = core::vector3df(0, 90, 0);
												meshsSalle[3*a +b] = sceneManager->getMesh("data/mesh/salle/salle_angle.obj");
												break;
											case SALLE_ANGLE_NE :
												rotationSalle[3*a +b] = core::vector3df(0, 180, 0);
												meshsSalle[3*a +b] = sceneManager->getMesh("data/mesh/salle/salle_angle.obj");
												break;
											case SALLE_ANGLE_SO :
												rotationSalle[3*a +b] = core::vector3df(0, 0, 0);
												meshsSalle[3*a +b] = sceneManager->getMesh("data/mesh/salle/salle_angle.obj");
												break;
											case SALLE_ANGLE_SE :
												rotationSalle[3*a +b] = core::vector3df(0, -90, 0);
												meshsSalle[3*a +b] = sceneManager->getMesh("data/mesh/salle/salle_angle.obj");
												break;
										}
										{ // Bords
											case SALLE_BORD_NORD :
												rotationSalle[3*a +b] = core::vector3df(0, 90, 0);
												meshsSalle[3*a +b] = sceneManager->getMesh("data/mesh/salle/salle_cote.obj");
												break;
											case SALLE_BORD_SUD :
												rotationSalle[3*a +b] = core::vector3df(0, -90, 0);
												meshsSalle[3*a +b] = sceneManager->getMesh("data/mesh/salle/salle_cote.obj");
												break;
											case SALLE_BORD_EST :
												rotationSalle[3*a +b] = core::vector3df(0, 180, 0);
												meshsSalle[3*a +b] = sceneManager->getMesh("data/mesh/salle/salle_cote.obj");
												break;
											case SALLE_BORD_OUEST :
												rotationSalle[3*a +b] = core::vector3df(0, 0, 0);
												meshsSalle[3*a +b] = sceneManager->getMesh("data/mesh/salle/salle_cote.obj");
												break;
										}
											case SALLE_CENTRE :
												meshsSalle[3*a +b] = sceneManager->getMesh("data/mesh/salle/salle_centre.obj");
												break;
											default : break;
										}
									}
								} // Fin des for
							}
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
				if(construction)
				{
					for(unsigned int a = 0; a < meshsSalle.size(); a++)
					{
						if(meshsSalle[a] == NULL) // Si il n'y a pas de morceau de salle sur cette partie du plan
							continue; // recommence la boucle à a+1

						scene::IMeshSceneNode *morceauSalle = sceneManager->addOctreeSceneNode(meshsSalle[a]->getMesh(0));
						morceauSalle->setPosition(core::vector3df(
							(a%3-1 +j)*(largeurBox + DISTANCE_ECART), // Colone du centre, * position dans la salle
							0, 
							(a/3-1 +i)*(longueurBox + DISTANCE_ECART))); // ligne du centre * position dans la salle
						morceauSalle->setParent(sceneManager->getRootSceneNode()); // parent
									 // les morceaux de salle ne sont pas atteignables et compte comme des murs
						morceauSalle->setRotation(rotationSalle[a]);
						morceauSalle->setID(ID_EstAtteignable);
						morceauSalle->setMaterialFlag(video::EMF_LIGHTING, false); // WARN: Lumière à changer au merge
					}
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
						sceneManager->getActiveCamera()->addAnimator(anim);
						anim->drop();
			}	}	}
			metaSelector->drop();
	}	}
	// Fin générale jusqu'au try
	catch (exception ex)
	{ cerr << ex.what() << endl; }

}

void Niveau::creuse(int ligne, int colone, Direction direction)
{
	vector<Case> nouveauVector;
	int decallageLigne = 0, decallageColone = 0;
	switch(direction)
	{
		case NORD : 
			decallageLigne++;
			if(m_Map.size() <= (unsigned int) (ligne + 2*decallageLigne)) // S'il est égal, ce n'est pas bon non plus
				m_Map.insert(m_Map.begin() + ligne+2, vector<Case>());
			
			// On ajoute dans la ligne+2 des cases VIDE jusqu'où il faut
			for(unsigned int i = m_Map[ligne+2].size(); i <= (unsigned int)(colone+1); i++)
					m_Map[ligne+2].insert(m_Map[ligne+2].begin()+ m_Map[ligne+2].size(), Case(VIDE));
			
			// De même, dans la ligne+1
			for(unsigned int i = m_Map[ligne+1].size(); i <= (unsigned int)(colone+1); i++)	
					m_Map[ligne+1].insert(m_Map[ligne+1].begin()+ m_Map[ligne+1].size(), Case(VIDE));
			break;
		case SUD : 
			decallageLigne--;
			if(ligne == 1) // ne peut pas être égal à 0 à priori
			{
				m_Map.insert(m_Map.begin(), vector<Case>());
				ligne++;
			}
			for(unsigned int i = m_Map[ligne-1].size(); i <=(unsigned int)(colone+1); i++)
				m_Map[ligne-1].insert(m_Map[ligne-1].begin() + m_Map[ligne-1].size(), Case(VIDE));

			for(unsigned int i = m_Map[ligne-2].size(); i <=(unsigned int)(colone+1); i++)
				m_Map[ligne-2].insert(m_Map[ligne-2].begin() + m_Map[ligne-2].size(), Case(VIDE));
			break;
		case EST : 
			decallageColone++;
			if(m_Map[ligne].size() <= (unsigned int)(colone+2))
				m_Map[ligne].push_back(Case(VIDE));
			if(m_Map[ligne-1].size() <= (unsigned int)(colone+2))
				m_Map[ligne-1].push_back(Case(VIDE));
			if(m_Map[ligne+1].size() <= (unsigned int)(colone+2))
				m_Map[ligne+1].push_back(Case(VIDE));
			break;
		case OUEST : 
			decallageColone--;
			if(colone == 1) // Ne peut être 0, 0 est un mur
				for(unsigned int i = 0; i < m_Map.size(); i++)
					m_Map[i].insert(m_Map[i].begin(), Case(VIDE));
			break;
		case HAUT :
		case BAS : 
		default : break;
	}
	// Modification d'une case, et ajout de trois
	
	if(m_Map[ligne+decallageLigne][colone+decallageColone].getTypeDeLaCase() == SOL) return;
	if(direction == NORD || direction == SUD)
	{
		switch(m_Map[ligne+decallageLigne][colone].getTypeDeLaCase())
		{
			case MUR : m_Map[ligne+decallageLigne][colone] = Case(SOL); break;
			default : break;
		}
	
		switch(	m_Map[ligne+2*decallageLigne][colone].getTypeDeLaCase()) 
		{
			case VIDE :
				m_Map[ligne+2*decallageLigne][colone] = Case(MUR);
				break;
			case MUR :
			default : break;
		}
	
		switch(	m_Map[ligne+decallageLigne][colone+1].getTypeDeLaCase()) 
		{
			case VIDE :
				m_Map[ligne+decallageLigne][colone+1] = Case(MUR);
				break;
			case MUR :
			default : break;
		}

		switch(	m_Map[ligne+decallageLigne][colone-1].getTypeDeLaCase()) 
		{
			case VIDE :
				m_Map[ligne+decallageLigne][colone-1] = Case(MUR);
				break;
			case MUR :
			default : break;
		}
	}
	else // Donc EST ou OUEST
	{
		switch(m_Map[ligne][colone+decallageColone].getTypeDeLaCase())
		{
			case MUR : m_Map[ligne][colone+decallageColone] = Case(SOL); break;
			default : break;
		}
	
		switch(	m_Map[ligne][colone+2*decallageColone].getTypeDeLaCase()) 
		{
			case VIDE :
				m_Map[ligne][colone+2*decallageColone] = Case(MUR);
				break;
			case MUR :
			default : break;
		}
	
		switch(	m_Map[ligne+1][colone+decallageColone].getTypeDeLaCase()) 
		{
			case VIDE :
				m_Map[ligne+1][colone+decallageColone] = Case(MUR);
				break;
			case MUR :
			default : break;
		}

		switch(	m_Map[ligne-1][colone+decallageColone].getTypeDeLaCase()) 
		{
			case VIDE :
				m_Map[ligne-1][colone+decallageColone] = Case(MUR);
				break;
			case MUR :
			default : break;
		}
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

bool Niveau::fortifie(int ligne, int colone, Direction direction)
{
	int decallageLigne = 0, decallageColonne = 0;
	switch(direction)
	{
		case NORD  : decallageLigne++; break;
		case SUD   : decallageLigne--; break;
		case EST   : decallageColonne++; break;
		case OUEST : decallageColonne--; break;
		default : break;
	}
	switch(m_Map[ligne+decallageLigne][colone+decallageColonne].getTypeDeLaCase())
	{
		// Seul un mur Smooth peut être fortifié dans le jeu
		case MUR : 
			if(m_Map[ligne+decallageLigne][colone+decallageColonne].getIsSmooth())
			{ 
				m_Map[ligne+decallageLigne][colone+decallageColonne].fortifie(); 
				return true; 
			}
			return false; // Sinon pas de changement
		default : return false; // pas de changement
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

bool Niveau::construit(int ligne, int colone, Batiment bat)
{
	// Est ce que les cases sont définies
	if(m_Map.size() < (unsigned int)ligne+2) 		return false;
	if(m_Map[ligne-1].size() < (unsigned int)colone+2) 	return false;
	if(m_Map[ligne].size() < (unsigned int)colone+2) 	return false;
	if(m_Map[ligne+1].size() < (unsigned int)colone+2) 	return false;

	// Test si les 9 cases autours sont des SOL et libres
	if(m_Map[ligne-1][colone-1].getTypeDeLaCase() != SOL) 	return false;
	if(m_Map[ligne-1][colone].getTypeDeLaCase() != SOL) 	return false;
	if(m_Map[ligne-1][colone+1].getTypeDeLaCase() != SOL) 	return false;
	if(m_Map[ligne][colone-1].getTypeDeLaCase() != SOL) 	return false;
	if(m_Map[ligne][colone].getTypeDeLaCase() != SOL) 	return false;
	if(m_Map[ligne][colone+1].getTypeDeLaCase() != SOL) 	return false;
	if(m_Map[ligne+1][colone-1].getTypeDeLaCase() != SOL) 	return false;
	if(m_Map[ligne+1][colone].getTypeDeLaCase() != SOL) 	return false;
	if(m_Map[ligne+1][colone+1].getTypeDeLaCase() != SOL) 	return false;

	// On peut donc construire
	m_Map[ligne-1][colone-1].setConstruit();
	m_Map[ligne-1][colone].setConstruit();
	m_Map[ligne-1][colone+1].setConstruit();
	m_Map[ligne][colone-1].setConstruit();
	m_Map[ligne][colone].setConstruit(); m_Map[ligne][colone].setConstruit(bat);
	m_Map[ligne][colone+1].setConstruit();
	m_Map[ligne+1][colone-1].setConstruit();
	m_Map[ligne+1][colone].setConstruit();
	m_Map[ligne+1][colone+1].setConstruit();
	return true;
}
