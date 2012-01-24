#include<iostream>

#include<irrlicht/irrlicht.h>

#include "niveau.hpp"
#include "case.hpp"
#include "objet.hpp"

using namespace std;
using namespace irr;

int main(int argc, char *argv[])
{
					     // api graphique : opengl, dimension fenetre : 800x600, bytes par pixel, 
					     // fullscreen, stencilbuffer, vsync, receiver
	IrrlichtDevice *device = createDevice(video::EDT_OPENGL, core::dimension2d<u32>(800, 600), 32, false, true, false, 0);
	video::IVideoDriver *driver = device->getVideoDriver();
	scene::ISceneManager *sceneManager = device->getSceneManager();

	scene::IAnimatedMesh *mesh = sceneManager->getMesh("data/mesh/mur trois.dae");
	scene::IAnimatedMeshSceneNode *mur_trois = sceneManager->addAnimatedMeshSceneNode(mesh);
	
	mur_trois->setMaterialFlag(video::EMF_LIGHTING, false);
//	mur_trois->setMaterialTexture(0, driver->getTexture("data/texture/plafond.jpg"));

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
	sceneManager->addCameraSceneNodeFPS(0, 100.0f, 0.01f, -1, keyMap, 5, true, 0.4);

	while(device->run())
	{
		driver->beginScene(true, true, video::SColor(255, 255, 255, 255));
		sceneManager->drawAll();
		driver->endScene();
	}

	// Creuser un mur
	// Ajouter un objet

	device->drop();
	return 0;
}
