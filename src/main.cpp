// Include STL
#include<iostream>

// Include Librairies 
#include<irrlicht/irrlicht.h>

// Include Redéfinitions
#include"TraitementEvennement.hpp"
#include"definitions.hpp"

// Include Spécial programme
#include "niveau.hpp"
#include "case.hpp"
#include "objet.hpp"

using namespace std;
using namespace irr;

int main(int argc, char *argv[])
{
	// Initialisation du moteur
					     // api graphique : opengl, dimension fenetre : 800x600, bytes par pixel, 
					     // fullscreen, stencilbuffer, vsync, receiver
	IrrlichtDevice *device = createDevice(video::EDT_OPENGL, core::dimension2d<u32>(LARGEUR_FENETRE, HAUTEUR_FENETRE), 32, false, true, false, 0);
	cerr << "Initialisation du device" << endl;
	video::IVideoDriver *driver = device->getVideoDriver();
	cerr << "Initialisation du driver video" << endl;
	scene::ISceneManager *sceneManager = device->getSceneManager();
	cerr << "Recuperation du scene manager" << endl;
	device->getCursorControl()->setVisible(false);
	gui::IGUIEnvironment *guiEnvironnement = sceneManager->getGUIEnvironment();
	cerr << "Recuperation de l'environnement GUI" << endl;

	// Initialisation des composants du programme
	// après un tableau, pour le moment, un seul
	// ISceneNode *parent = 0, ISceneManager *
	Niveau niveau1;
	cerr << "Initialisation des niveaux" << endl;
	
	// Initialisation des redéfinitions
	TraitementEvennement receptionEvennement(&niveau1);
	cerr << "Initialisation du gestionnaire d'évennement" << endl;
	device->setEventReceiver(&receptionEvennement);
	
	SKeyMap keyMap[5];
	keyMap[0].Action = EKA_MOVE_FORWARD;
	keyMap[0].KeyCode = KEY_KEY_Z;
	keyMap[1].Action = EKA_MOVE_BACKWARD;
	keyMap[1].KeyCode = KEY_KEY_S;
	keyMap[2].Action = EKA_STRAFE_LEFT;
	keyMap[2].KeyCode = KEY_KEY_Q;
	keyMap[3].Action = EKA_STRAFE_RIGHT;
	keyMap[3].KeyCode = KEY_KEY_D;
	keyMap[4].Action = EKA_JUMP_UP;
	keyMap[4].KeyCode = KEY_SPACE;
	
	/* 
	 * ISceneNode parent,
	 * rotateSpeed, moveSpeed,
	 * id, 
	 * keyMapArray, keyMapSize
	 * noVerticalMovement (bool), jumpSpeed
	 */
	scene::ICameraSceneNode *camera = sceneManager->addCameraSceneNodeFPS(0, 100.0f, 0.005f, ID_NEstPasAtteingable,
									      keyMap, 5, true, 0.4);
	// Caméra en place, dans la bonne direction
	camera->setPosition(core::vector3df(4, 0.15, -1));
	camera->setTarget(core::vector3df(4, 0, 2));

	niveau1.afficheConsole(sceneManager);
	// affichage en haut a droite des m_InitColone et m_InitLigne
	core::stringw positionCase = L"Ligne ";
		positionCase += camera->getPosition().Z;
		positionCase +=  " : Colone ";
		positionCase += camera->getPosition().X;

	device->setWindowCaption(positionCase.c_str());

	// Ajout de la lumière : équivalent d'une torche
	scene::ILightSceneNode *torche = sceneManager->addLightSceneNode(
		camera, // Noeud parent est la caméra
		// On décalle un peu la torche par rapport à la caméra
		core::vector3df(camera->getAbsolutePosition().X+0.5f, camera->getAbsolutePosition().Y+0.5f, camera->getAbsolutePosition().Z),
		video::SColorf(127.f, 30.f, 0.f), // Couleur
		500.f, // Radius : atténuation des contours, par défaut 100
		ID_NEstPasAtteingable); //id
	
	torche->setLightType(video::ELT_SPOT);
	torche->getLightData().OuterCone = 50.f; // Angle cone lumière en degres
	torche->getLightData().SpecularColor = video::SColorf(0.8f, 0.2f, 0.f); // par défaut 1, 1, 1

	//torche->getLightData().Falloff = 100.f ;// 
	torche->getMaterial(0).Shininess = .03f; // Brillance, par défaut à 20

	// Ajout du brouillard pour ne pas avoir un champs de vue illimité
	
	driver->setFog(video::SColor(0, 175, 125, 0), video::EFT_FOG_EXP2, 
		       0.f, 0.f, // début et fin, inutile car en mode exponnentiel
		       0.35f, // densité
		       false, false); // pixel fog, range fog

	while(device->run())
	{
		driver->beginScene(true, true, video::SColor(255, 0, 0, 0));

		// Si le joueur n'a pas le controle de la caméra, on la désactive
		if(!receptionEvennement.getControleCamera())
		{
			device->getCursorControl()->setVisible(true);
			sceneManager->getActiveCamera()->setInputReceiverEnabled(false);
		}
		else 
		{
			sceneManager->getActiveCamera()->setInputReceiverEnabled(true);
			device->getCursorControl()->setVisible(false);
		}

		if(receptionEvennement.getControleCamera()) // Si le jeu n'est pas "freezé"
		{
			if(receptionEvennement.majNiveau(sceneManager, camera))
			{
				// réinit de la scene
				core::array<scene::ISceneNode *> meshs; // Octree mesh scene node
				sceneManager->getSceneNodesFromType(scene::ESNT_OCTREE, meshs);
				for(unsigned int i = 0; i < meshs.size(); i++)
					if(meshs[i] != NULL)
					{ meshs[i]->removeAll(); meshs[i]->remove(); }
/* BUG:#3 	
				sceneManager->getSceneNodesFromType(scene::ESNT_ANIMATED_MESH, meshs);
				for(unsigned int i = 0; i < meshs.size(); i++)
					if(meshs[i] != NULL)
						meshs[i]->remove();
* BUG:#32 */
				// affichage
				niveau1.afficheConsole(sceneManager);
	
	
				device->setWindowCaption(positionCase.c_str());
			}
		}
	
		core::vector3df positionCam = camera->getAbsolutePosition();	
		core::stringw positionCase = L"Ligne ";
			positionCase += (int)(positionCam.Z/2. +0.5);
			positionCase +=  " : Colone ";
			positionCase += (int)(positionCam.X/2. +0.5);
			positionCase += " : ";
			positionCase += (int)(positionCam.Y/2. +0.5);
		device->setWindowCaption(positionCase.c_str());


		sceneManager->drawAll();
		if(!receptionEvennement.getControleCamera()) // Si le joueur ne controle pas la caméra, il y a un gui a affiche
			guiEnvironnement->drawAll();
		
		driver->endScene();
	}
	camera->drop();
	guiEnvironnement->clear();
	sceneManager->clear();
	device->drop();
	return 0;
}
