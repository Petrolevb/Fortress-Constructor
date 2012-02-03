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
	IrrlichtDevice *device = createDevice(video::EDT_OPENGL, core::dimension2d<u32>(800, 600), 32, false, true, false, 0);
	cerr << "Initialisation du device" << endl;
	video::IVideoDriver *driver = device->getVideoDriver();
	cerr << "Initialisation du driver video" << endl;
	scene::ISceneManager *sceneManager = device->getSceneManager();
	cerr << "Recuperation du scene manager" << endl;
	
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
	scene::ICameraSceneNode *camera = sceneManager->addCameraSceneNodeFPS(0, 100.0f, 0.01f, ID_NEstPasAtteingable,
									      keyMap, 5, true, 0.4);
	niveau1.afficheConsole(sceneManager);
	// affichage en haut a droite des m_InitColone et m_InitLigne
	core::stringw positionCase = L"Ligne ";
		positionCase += niveau1.getLigneInit();
		positionCase += ";";
		positionCase += camera->getPosition().Z;
		positionCase +=  " : Colone ";
		positionCase += niveau1.getColoneInit();
		positionCase += ";";
		positionCase += camera->getPosition().X;

	device->setWindowCaption(positionCase.c_str());
	while(device->run())
	{
		driver->beginScene(true, true, video::SColor(255, 100, 100, 255));
		if(receptionEvennement.majNiveau(sceneManager, camera))
		{
			// réinit de la scene
			core::array<scene::ISceneNode *> meshs;
			sceneManager->getSceneNodesFromType(scene::ESNT_MESH, meshs);
			for(unsigned int i = 0; i < meshs.size(); i++)
				meshs[i]->remove();

			// affichage
			niveau1.afficheConsole(sceneManager);

			// affichage en haut a droite des m_InitColone et m_InitLigne
			/*
			core::stringw positionCase = L"Ligne ";
			positionCase += + (niveau1.getLigneInit()+1);
			positionCase +=  " : Colone ";
			positionCase += (niveau1.getColoneInit()+1);
			*/

			device->setWindowCaption(positionCase.c_str());
		}
	core::stringw positionCase = L"Ligne ";
		positionCase += niveau1.getLigneInit();
		positionCase += ";";
		positionCase += (int)(camera->getPosition().Z / 2);
		positionCase +=  " : Colone ";
		positionCase += niveau1.getColoneInit();
		positionCase += ";";
		positionCase += (int)(camera->getPosition().X/2);
			device->setWindowCaption(positionCase.c_str());
		sceneManager->drawAll();
		driver->endScene();
	}


	device->drop();
	return 0;
}
