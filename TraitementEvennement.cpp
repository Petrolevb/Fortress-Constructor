#include<irrlicht/irrlicht.h>

#include "TraitementEvennement.hpp"
#include "definitions.hpp"

#include "niveau.hpp"

using namespace irr;

TraitementEvennement::TraitementEvennement(Niveau *niveau) :
	m_Niveau(niveau)
{
	for(u32 i = 0; i < KEY_KEY_CODES_COUNT; i++)
	{ m_KeyIsDown[i] = false; m_KeyIsDownOld[i] = false; }

	m_IsShiftDown = false;
	m_IsCtrlDown = false;

}

TraitementEvennement::~TraitementEvennement()
{
}

bool TraitementEvennement::OnEvent(const SEvent &event)
{
	switch(event.EventType)
	{
		case EET_KEY_INPUT_EVENT :
			// Ancienne valeur dans la nouvelle
			m_KeyIsDownOld[event.KeyInput.Key] = m_KeyIsDown[event.KeyInput.Key];
			// Nouvelle valeur
			m_KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;
			m_IsCtrlDown = event.KeyInput.Control;
			m_IsShiftDown = event.KeyInput.Shift;
			break;
		case EET_MOUSE_INPUT_EVENT :
			switch(event.MouseInput.Event)
			{
				case EMIE_LMOUSE_PRESSED_DOWN :
					MouseState.LeftButtonDown = true;
					break;
				case EMIE_LMOUSE_LEFT_UP:
					MouseState.LeftButtonDown = false;
					break;
				case EMIE_RMOUSE_PRESSED_DOWN : 
					MouseState.RightButtonDown = true;
					break;
				case EMIE_RMOUSE_LEFT_UP : 
					MouseState.RightButtonDown = false;
					break;
				case EMIE_MOUSE_MOVED :
					MouseState.Position.X = event.MouseInput.X;
					MouseState.Position.Y = event.MouseInput.Y;
					break;
				default :
					/*
					 * Clic milieu,
					 * Pour les trois : 
					 *  * double clics
					 *  * triple clics
					 * mouvement molette
					 *
					 */
					break;
			}
			break; // Fin du MOUSE_INPUT_EVENT
		default : break;
	}
		
		
	return false;
}

bool TraitementEvennement::IsKeyDown(EKEY_CODE keyCode) const
{ return m_KeyIsDown[keyCode] && !m_KeyIsDownOld[keyCode]; }

bool TraitementEvennement::majNiveau(scene::ISceneManager *sceneManager, scene::ICameraSceneNode *camera)
{
	bool changement = false;
	if(MouseState.LeftButtonDown || MouseState.RightButtonDown)
	{
		// Récupération d'un trait de la caméra vers sa direction à une distance de 2
		/*core::line3df rayon;
		rayon.start = camera->getPosition();
		rayon.end = rayon.start + (camera->getTarget() - rayon.start).normalize()*1000.0f;*/
		scene::ISceneCollisionManager *collisionManager = sceneManager->getSceneCollisionManager();

		core::position2di  screenCoordinate = collisionManager->getScreenCoordinatesFrom3DPosition(camera->getPosition(), camera);
		core::line3df rayon = collisionManager->getRayFromScreenCoordinates(screenCoordinate, camera);
		
		// calcul de l'angle du vecteur entre les deux points
		f32 angle = asinf( (rayon.end.Z - rayon.start.Z) / rayon.getLength());
		// Transformation en degres
		angle *= 360/(2*core::PI);
		

		// Recalcul de Colone et de Ligne à partir des trois composantes de la caméra
		int colone = (int)(rayon.start.X/2.0f), 
		    ligne = (int)(rayon.start.Z/2.0f); // Largeur et longeur des box 
		if(ligne < 0 || colone < 0)
			return false;

		// Déduction de la direction
		if(angle >= -45  && angle < 45)
			m_Niveau->creuse(ligne, colone, NORD);
		else if(angle >= 45 && angle < 135)
			m_Niveau->creuse(ligne, colone, EST);
		else if(angle >=  135 && angle < -135)
			m_Niveau->creuse(ligne, colone, SUD);
		else
			m_Niveau->creuse(ligne, colone, OUEST);
		changement = true;
		

	}
/*	
	if(IsKeyDown(KEY_UP))
	{ changement = true; m_Niveau->setLigneInit(m_Niveau->getLigneInit()+1); }
	if(IsKeyDown(KEY_DOWN))
	{ changement = true; m_Niveau->setLigneInit(m_Niveau->getLigneInit()-1); }
	if(IsKeyDown(KEY_RIGHT))
	{ changement = true; m_Niveau->setColoneInit(m_Niveau->getColoneInit()+1); }
	if(IsKeyDown(KEY_LEFT))
	{ changement = true; m_Niveau->setColoneInit(m_Niveau->getColoneInit()-1); }
*/	
	if(IsKeyDown(KEY_F1))
	{
		if(m_IsCtrlDown)
		{ changement = true; m_Niveau->setColoneInit(0); }
		else if(m_IsShiftDown)
		{ changement = true; m_Niveau->setLigneInit(0); }
	}
	if(IsKeyDown(KEY_F2))
	{
		if(m_IsCtrlDown)
		{ changement = true; m_Niveau->setColoneInit(1); }
		else if(m_IsShiftDown)
		{ changement = true; m_Niveau->setLigneInit(1); }
	}
	if(IsKeyDown(KEY_F3))
	{
		if(m_IsCtrlDown)
		{ changement = true; m_Niveau->setColoneInit(2); }
		else if(m_IsShiftDown)
		{ changement = true; m_Niveau->setLigneInit(2); }
	}
	if(IsKeyDown(KEY_F4))
	{
		if(m_IsCtrlDown)
		{ changement = true; m_Niveau->setColoneInit(3); }
		else if(m_IsShiftDown)
		{ changement = true; m_Niveau->setLigneInit(3); }
	}
	if(IsKeyDown(KEY_F5))
	{
		if(m_IsCtrlDown)
		{ changement = true; m_Niveau->setColoneInit(4); }
		else if(m_IsShiftDown)
		{ changement = true; m_Niveau->setLigneInit(4); }
	}
	if(IsKeyDown(KEY_F6))
	{
		if(m_IsCtrlDown)
		{ changement = true; m_Niveau->setColoneInit(5); }
		else if(m_IsShiftDown)
		{ changement = true; m_Niveau->setLigneInit(5); }
	}
	if(IsKeyDown(KEY_F7))
	{
		if(m_IsCtrlDown)
		{ changement = true; m_Niveau->setColoneInit(6); }
		else if(m_IsShiftDown)
		{ changement = true; m_Niveau->setLigneInit(6); }
	}
	if(IsKeyDown(KEY_F8))
	{
		if(m_IsCtrlDown)
		{ changement = true; m_Niveau->setColoneInit(7); }
		else if(m_IsShiftDown)
		{ changement = true; m_Niveau->setLigneInit(7); }
	}
	if(IsKeyDown(KEY_F9))
	{
		if(m_IsCtrlDown)
		{ changement = true; m_Niveau->setColoneInit(8); }
		else if(m_IsShiftDown)
		{ changement = true; m_Niveau->setLigneInit(8); }
	}
	if(IsKeyDown(KEY_F10))
	{
		if(m_IsCtrlDown)
		{ changement = true; m_Niveau->setColoneInit(9); }
		else if(m_IsShiftDown)
		{ changement = true; m_Niveau->setLigneInit(9); }
	}

	return changement;
}
