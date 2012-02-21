#include<irrlicht/irrlicht.h>

#include "TraitementEvennement.hpp"
#include "definitions.hpp"

#include "niveau.hpp"

using namespace irr;

TraitementEvennement::TraitementEvennement(Niveau *niveau) :
	m_IsShiftDown(false), m_IsCtrlDown(false),
	m_ControleCamera(true),
	m_Niveau(niveau), m_Action(false), m_ActionEnCours(AUCUNE_ACTION)
{
	for(u32 i = 0; i < KEY_KEY_CODES_COUNT; i++)
	{ m_KeyIsDown[i] = false; m_KeyIsDownOld[i] = false; }
}

TraitementEvennement::~TraitementEvennement()
{
}

bool TraitementEvennement::OnEvent(const SEvent &event)
{
	switch(event.EventType)
	{
		case EET_GUI_EVENT :
			switch(event.GUIEvent.EventType)
			{
				case gui::EGET_BUTTON_CLICKED :
					MouseState.LeftButtonDown = false;
					MouseState.RightButtonDown = false;
					m_ControleCamera = true;
					switch(event.GUIEvent.Caller->getID())
					{
						case ID_GUI_Smooth : 
							m_Action = true; 
							m_ActionEnCours = SMOOTH; 
							break;
						case ID_GUI_Fortifie : 
							m_Action = true; 
							m_ActionEnCours = FORTIFIE; 
							break;
						case ID_GUI_Construit : 
							MouseState.RightButtonDown = true; // GUI réactivée
							m_ActionEnCours = CONSTRUIT; 
							break; // Pour le moment, pas d'action
						{ // GUI construction des batiments
							case ID_GUI_BATIMENT_ARCHERIE : 
								m_ActionEnCours = CONSTRUIT_ARCHERIE;
								m_Action = true; 
								break;
						}
						case ID_GUI_Annuler : 
							// Rien a faire, anulation déjà faites
						case ID_GUI_Default :
						default : break;
					}
					break;
				default : break;
			}
			break;
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
	if(IsKeyDown(KEY_KEY_A))
		m_Niveau->ouverturePorte();
	if(MouseState.LeftButtonDown)
	{ m_ActionEnCours = CREUSE; m_Action = true; MouseState.LeftButtonDown = false;}
	if (MouseState.RightButtonDown)
	{
		//cette fonction est appellée uniquement avec un controle caméra
		gui::IGUIEnvironment *guiEnvironnement = sceneManager->getGUIEnvironment();
		guiEnvironnement->clear();
		// Si le joueur a déjà les options d'affichées
		m_ControleCamera = false;
		// Button : border, parent, id, text, texte aide //
		int posButX = HAUTEUR_FENETRE/2,
		    posButY = LARGEUR_FENETRE/2;

		// Définition des quatres bouttons
		if(m_ActionEnCours == CONSTRUIT) // Si on construit
		{
			guiEnvironnement->addButton(core::rect<s32>(posButY, posButX, posButY + 35, posButX + 35),
				guiEnvironnement->getRootGUIElement(), ID_GUI_BATIMENT_ARCHERIE,
				L"Archerie", L"Construire une archerie ici");
			guiEnvironnement->addButton(core::rect<s32>(posButY + 40, posButX + 40, posButY +35 + 40, posButX + 35 + 40),
				guiEnvironnement->getRootGUIElement(), ID_GUI_Annuler, 
				L"Annuler", L"Annuler action");
		}
		else // Sinon c'est qu'on veut faire autre chose
		{
			guiEnvironnement->addButton(core::rect<s32>(posButY, posButX - 80, posButY + 100, posButX - 80 + 32), 
				guiEnvironnement->getRootGUIElement(), ID_GUI_Construit, 
				L"Construire", L"Construire ici");
			guiEnvironnement->addButton(core::rect<s32>(posButY, posButX - 40, posButY + 100, posButX - 40 + 32), 
				guiEnvironnement->getRootGUIElement(), ID_GUI_Smooth,
				L"Smoother", L"Smoother ce mur");
			guiEnvironnement->addButton(core::rect<s32>(posButY, posButX, posButY + 100, posButX + 32), 
				guiEnvironnement->getRootGUIElement(), ID_GUI_Fortifie, 
				L"Fortifier", L"Fortifier ce mur");
			guiEnvironnement->addButton(core::rect<s32>(posButY, posButX + 40, posButY + 100, posButX+40 + 32), 
				guiEnvironnement->getRootGUIElement(), ID_GUI_Annuler, 
				L"Annuler", L"Annuler action");
		}
		MouseState.RightButtonDown = false;
	}
	if(m_Action)
	{
		// Récupération d'un trait de la caméra vers sa direction à une distance de 2
		scene::ISceneCollisionManager *collisionManager = sceneManager->getSceneCollisionManager();
		core::position2di  screenCoordinate = collisionManager->getScreenCoordinatesFrom3DPosition(camera->getAbsolutePosition(), camera);
		core::line3df rayon = collisionManager->getRayFromScreenCoordinates(screenCoordinate, camera);
		
		scene::ISceneNode * tmp = collisionManager->getSceneNodeFromScreenCoordinatesBB(
			screenCoordinate,  ID_EstAtteignable, false, sceneManager->getRootSceneNode());
		if(tmp != NULL) 
			rayon.end = tmp->getPosition();

		// calcul de l'angle du vecteur entre les deux points
		f32 angle = asinf( (rayon.end.Z - rayon.start.Z) / rayon.getLength());
		// Transformation en degres
		angle *= 360/(2*core::PI);
		
				// Recalcul de Colone et de Ligne à partir des trois composantes de la caméra
		int colone = (int)(camera->getPosition().X/2 + 0.5), 
		    ligne = (int)(camera->getPosition().Z/2 + 0.5); // Largeur et longeur des box 
		if(ligne < 0 || colone < 0)
			return false;
		Direction directionAction;
		// Déduction de la direction
		if(angle >= -45  && angle < 45)
			directionAction = NORD;
		else if(angle >= 45 && angle < 135)
			directionAction = EST;
		else if(angle >=  135 && angle < -135)
			directionAction = SUD;
		else
			directionAction = OUEST;
		switch(m_ActionEnCours)
		{
			case CREUSE :
				m_Niveau->creuse(ligne, colone, directionAction);
				changement = true;
				break;
			case SMOOTH :
				m_Niveau->setSmooth(ligne, colone, directionAction);
				changement = true;
				break;
			case FORTIFIE :
				changement = m_Niveau->fortifie(ligne, colone, directionAction);
				break;
			case CONSTRUIT_ARCHERIE :
				changement = m_Niveau->construit(ligne, colone, Archerie);
				break;
			case AUCUNE_ACTION :
			default : break;
		}

		m_Action = false; // Action est effectuée 
		m_ActionEnCours = AUCUNE_ACTION;
		m_ControleCamera = true;
	}
	
	return changement;
}
