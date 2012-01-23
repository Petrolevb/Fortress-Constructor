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

	sceneManager->addCameraSceneNode(0, core::vector3df(0, 0, 0), core::vector3df(5, 0, 0));


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
