#include<irrlicht/irrlicht.h>

#include "TraitementEvennement.hpp"

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
		// Récupération du gestionnaire de collisions
		scene::ISceneCollisionManager *collisionManager = sceneManager->getSceneCollisionManager();
		scene::ISceneNode *mesh = collisionManager->getSceneNodeFromCameraBB(camera);
		// Récupération de la position du mesh ciblé
		core::vector3df positionMesh = mesh->getAbsolutePosition(),
				positionCamera = camera->getAbsolutePosition();

		// Calcul de la distance entre les deux points 
		f32 distance = /* core::vector3df(positionMesh.X - positionCamera.X, 
					       positionMesh.Y - positionCamera.Y,
					       positionMesh.Z - positionCamera.Z).getLength(),*/
				core::vector2df(positionMesh.X - positionCamera.X, positionMesh.Z - positionCamera.Z).getLength(),
		// calcul de l'angle du vecteur entre les deux points
		    angle = asinf( (positionMesh.X - positionCamera.X) / distance);

		// Déduction de la direction
		if(angle >= - core::PI/4.0f && angle < core::PI/4.0f)
			m_Niveau->creuse(m_Niveau->getLigneInit(), m_Niveau->getColoneInit(), NORD);
		else if(angle >= core::PI/4.0f && angle < 3.0f*core::PI/4.0f)
			m_Niveau->creuse(m_Niveau->getLigneInit(), m_Niveau->getColoneInit(), OUEST);
		else if(angle >= 3.0f*core::PI/4.0f && angle < -3.0f*core::PI/4.0f)
			m_Niveau->creuse(m_Niveau->getLigneInit(), m_Niveau->getColoneInit(), SUD);
		else
			m_Niveau->creuse(m_Niveau->getLigneInit(), m_Niveau->getColoneInit(), EST);
		changement = true;
		// Recalcul de Colone et de Ligne à partir des trois composantes de la caméra
		f32 colone = 0, 
		    ligne = 0;

	}
		/*
		if(m_IsShiftDown|| m_IsCtrlDown)
			m_Niveau->creuse(m_Niveau->getLigneInit(), m_Niveau->getColoneInit(), OUEST); 
		else
			m_Niveau->creuse(m_Niveau->getLigneInit(), m_Niveau->getColoneInit(), EST); 
		changement = true; 
	}
	if(MouseState.RightButtonDown)
	{ m_Niveau->creuse(m_Niveau->getLigneInit(), m_Niveau->getColoneInit(), NORD); changement = true; }
	*/

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
