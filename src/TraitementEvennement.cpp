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
					m_Action = true; // Quasiment dans tousles cas
					switch(event.GUIEvent.Caller->getID())
					{
						case ID_GUI_Smooth : 
							m_ActionEnCours = SMOOTH; 
							break;
						case ID_GUI_Fortifie : 
							m_ActionEnCours = FORTIFIE; 
							break;
						case ID_GUI_Construit : 
							MouseState.RightButtonDown = true; // GUI réactivée
							m_ActionEnCours = CONSTRUIT;
							m_Action = false;
							break; // Pour le moment, pas d'action
						{ // GUI construction des batiments
							case ID_GUI_BATIMENT_ATELIER :
								m_ActionEnCours = CONSTRUIT_ATELIER;
								break;
							case ID_GUI_BATIMENT_ATELIER_CUIR :
								m_ActionEnCours = CONSTRUIT_ATELIER_CUIR;
								break;
							case ID_GUI_BATIMENT_ARCHERIE : 
								m_ActionEnCours = CONSTRUIT_ARCHERIE;
								break;
							case ID_GUI_BATIMENT_BIJOUTERIE :
								m_ActionEnCours = CONSTRUIT_BIJOUTERIE;
								break;
							case ID_GUI_BATIMENT_BOUCHERIE : 
								m_ActionEnCours = CONSTRUIT_BOUCHERIE;
								break;
							case ID_GUI_BATIMENT_BRASSERIE : 
								m_ActionEnCours = CONSTRUIT_BRASSERIE;
								break;
							case ID_GUI_BATIMENT_CENDRERIE :
								m_ActionEnCours = CONSTRUIT_CENDRERIE;
								break;
							case ID_GUI_BATIMENT_MENUISERIE : 
								m_ActionEnCours = CONSTRUIT_MENUISERIE;
								break;
							case ID_GUI_BATIMENT_COUTURIER :
								m_ActionEnCours = CONSTRUIT_COUTURIER;
								break;
							case ID_GUI_BATIMENT_CUISINE : 
								m_ActionEnCours = CONSTRUIT_CUISINE;
								break;
							case ID_GUI_BATIMENT_FERME :
								m_ActionEnCours = CONSTRUIT_FERME;
								break;
							case ID_GUI_BATIMENT_FORGE :
								m_ActionEnCours = CONSTRUIT_FORGE;
								break;
							case ID_GUI_BATIMENT_LOOM :
								m_ActionEnCours = CONSTRUIT_LOOM;
								break;
							case ID_GUI_BATIMENT_MASSONNERIE : 
								m_ActionEnCours = CONSTRUIT_MASSONNERIE;
								break;
							case ID_GUI_BATIMENT_MECHANIC :
								m_ActionEnCours = CONSTRUIT_MECHANIC;
								break;
							case ID_GUI_BATIMENT_POISSONNERIE :
								m_ActionEnCours = CONSTRUIT_POISSONNERIE;
								break;
							case ID_GUI_BATIMENT_TANNERIE :
								m_ActionEnCours = CONSTRUIT_TANNERIE;
								break;
						}
						case ID_GUI_Annuler : 
							// Rien a faire, anulation déjà faites
						case ID_GUI_Default :
						default :  m_Action = false;break;
					}
					break;
				default : m_Action = false; break;
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
		int posButX = HAUTEUR_FENETRE/4,
		    posButY = LARGEUR_FENETRE/2;
		// Définition des boutons
		if(m_ActionEnCours == CONSTRUIT) // Si on construit
		{
			int dek = 50, // dek pour decallage
			    tailleX = posButX+45,
			    tailleY = posButY+45;

			{ // Première ligne Menuiserie Maconnerie
				guiEnvironnement->addButton(
					core::rect<s32>(posButY, posButX, tailleY, tailleX),
					guiEnvironnement->getRootGUIElement(), ID_GUI_BATIMENT_MASSONNERIE,
					#ifdef _LANG_FR
					L"Maconnerie", L"Construire une maconnerie ici");
					#else
					#ifdef _LANG_EN
					L"Mason", L"Create Mason's workshop");
					#endif
					#endif
				guiEnvironnement->addButton(
					core::rect<s32>(posButY + 1*dek, posButX, tailleY + 1*dek, tailleX),
					guiEnvironnement->getRootGUIElement(), ID_GUI_BATIMENT_MENUISERIE,
					#ifdef _LANG_FR
					L"Menuiserie", L"Construire une menuiserie ici");
					#else
					#ifdef _LANG_EN
					L"Carpenter", L"Create Carpenter's workshop");
					#endif
					#endif
			}
			{ // Seconde ligne Atelier, Archerie, Forge, Mechanic
				guiEnvironnement->addButton(
					core::rect<s32>(posButY, posButX + dek, tailleY, tailleX + dek),
					guiEnvironnement->getRootGUIElement(), ID_GUI_BATIMENT_ATELIER,
					#ifdef _LANG_FR
					L"Atelier", L"Construire un atelier ici");
					#else
					#ifdef _LANG_EN
					L"Craftsdwarf", L"Create Carftsdwarf's workshop");
					#endif
					#endif
				guiEnvironnement->addButton(
					core::rect<s32>(posButY + dek, posButX + dek, tailleY + dek, tailleX + dek),
					guiEnvironnement->getRootGUIElement(), ID_GUI_BATIMENT_ARCHERIE,
					#ifdef _LANG_FR
					L"Archerie", L"Construire une archerie ici");
					#else
					#ifdef _LANG_EN
					L"Bowyer", L"Create Bowyer's workshop");
					#endif
					#endif
				guiEnvironnement->addButton(
					core::rect<s32>(posButY + 2*dek, posButX + dek, tailleY + 2*dek, tailleX + dek),
					guiEnvironnement->getRootGUIElement(), ID_GUI_BATIMENT_FORGE,
					#ifdef _LANG_FR
					L"Forge", L"Construire une forge ici");
					#else
					#ifdef _LANG_EN
					L"Forge", L"Create Forge");
					#endif
					#endif
				guiEnvironnement->addButton(
					core::rect<s32>(posButY + 3*dek, posButX + dek, tailleY + 3*dek, tailleX + dek),
					guiEnvironnement->getRootGUIElement(), ID_GUI_BATIMENT_MECHANIC,
					#ifdef _LANG_FR
					L"Mechanic", L"Construire une mechanic ici");
					#else
					#ifdef _LANG_EN
					L"Mechanics", L"Create Mechanics workshop");
					#endif
					#endif
			}
			{ // Troisième ligne Boucherie, Poissonnerie, Brasserie, Cuisine
				guiEnvironnement->addButton(
					core::rect<s32>(posButY, posButX + 2*dek, tailleY, tailleX + 2*dek),
					guiEnvironnement->getRootGUIElement(), ID_GUI_BATIMENT_BOUCHERIE,
					#ifdef _LANG_FR
					L"Boucherie", L"Construire une boucherie ici");
					#else
					#ifdef _LANG_EN
					L"Butcher", L"Create butcher's shop");
					#endif
					#endif
				guiEnvironnement->addButton(
					core::rect<s32>(posButY + dek, posButX + 2*dek, tailleY + dek, tailleX + 2*dek),
					guiEnvironnement->getRootGUIElement(), ID_GUI_BATIMENT_POISSONNERIE,
					#ifdef _LANG_FR
					L"Poissonnerie", L"Construire une poissonnerie ici");
					#else
					#ifdef _LANG_EN
					L"Fichery", L"Create Fisher's shop");
					#endif
					#endif
				guiEnvironnement->addButton(
					core::rect<s32>(posButY + 2*dek, posButX + 2*dek, tailleY + 2*dek, tailleX + 2*dek),
					guiEnvironnement->getRootGUIElement(), ID_GUI_BATIMENT_BRASSERIE,
					#ifdef _LANG_FR
					L"Brasserie", L"Construire une brasserie ici");
					#else
					#ifdef _LANG_EN
					L"Still", L"Create still");
					#endif
					#endif
				guiEnvironnement->addButton(
					core::rect<s32>(posButY + 3*dek, posButX + 2*dek, tailleY + 3*dek, tailleX + 2*dek),
					guiEnvironnement->getRootGUIElement(), ID_GUI_BATIMENT_CUISINE,
					#ifdef _LANG_FR
					L"Cuisine", L"Construire une cuisine ici");
					#else
					#ifdef _LANG_EN
					L"Kitchen", L"Create kitchen");
					#endif
					#endif
			}
			{ // Quatrième ligne Atelier Cuir, Tannerie
				guiEnvironnement->addButton(
					core::rect<s32>(posButY,  posButX + 3*dek, tailleY, tailleX + 3*dek),
					guiEnvironnement->getRootGUIElement(), ID_GUI_BATIMENT_ATELIER_CUIR,
					#ifdef _LANG_FR
					L"Atelier Cuir", L"Construire un atelier de cuir ici");
					#else
					#ifdef _LANG_EN
					L"Leather Works", L"Create leather works");
					#endif
					#endif
				guiEnvironnement->addButton(
					core::rect<s32>(posButY + dek, posButX + 3*dek, tailleY + dek, tailleX + 3*dek),
					guiEnvironnement->getRootGUIElement(), ID_GUI_BATIMENT_TANNERIE,
					#ifdef _LANG_FR
					L"Tannerie", L"Construire une tannerie ici");
					#else
					#ifdef _LANG_EN
					L"Tanner's shop", L"Create tanner's shop");
					#endif
					#endif
			}
			{ // Cinquième ligne Teinturerie, Cendrerie, Ferme
				guiEnvironnement->addButton(
					core::rect<s32>(posButY, posButX + 4*dek, tailleY, tailleX + 4*dek),
					guiEnvironnement->getRootGUIElement(), ID_GUI_BATIMENT_TEINTURERIE,
					#ifdef _LANG_FR
					L"Teinturerie", L"Construire une teinturerie ici");
					#else
					#ifdef _LANG_EN
					L"Dyer", L"Create Dyer's workshop");
					#endif
					#endif
				guiEnvironnement->addButton(
					core::rect<s32>(posButY + dek, posButX + 4*dek, tailleY + dek, tailleX + 4*dek),
					guiEnvironnement->getRootGUIElement(), ID_GUI_BATIMENT_CENDRERIE,
					#ifdef _LANG_FR
					L"Cendrerie", L"Construire une cendrerie ici");
					#else
					#ifdef _LANG_EN
					L"Ashery", L"Create ashery");
					#endif
					#endif
				guiEnvironnement->addButton(
					core::rect<s32>(posButY + 2*dek, posButX + 4*dek, tailleY + 2*dek, tailleX + 4*dek),
					guiEnvironnement->getRootGUIElement(), ID_GUI_BATIMENT_FERME,
					#ifdef _LANG_FR
					L"Ferme", L"Construire une ferme ici");
					#else
					#ifdef _LANG_EN
					L"Farm", L"Create farm");
					#endif
					#endif
			}
			{ // Sixième ligne Couturier, Loom
				guiEnvironnement->addButton(
					core::rect<s32>(posButY, posButX + 5*dek, tailleY, tailleX + 5*dek),
					guiEnvironnement->getRootGUIElement(), ID_GUI_BATIMENT_COUTURIER,
					#ifdef _LANG_FR
					L"Couturier", L"Construire un couturier ici");
					#else
					#ifdef _LANG_EN
					L"Clothier", L"Create clothier workshop");
					#endif
					#endif
				guiEnvironnement->addButton(
					core::rect<s32>(posButY + dek, posButX + 5*dek, tailleY + dek, tailleX + 5*dek),
					guiEnvironnement->getRootGUIElement(), ID_GUI_BATIMENT_LOOM,
					#ifdef _LANG_FR
					L"Loom", L"Construire une loom ici");
					#else
					#ifdef _LANG_EN
					L"Loom", L"Create loom");
					#endif
					#endif
			}
			{ // Septième ligne Bijouterie
				guiEnvironnement->addButton(
					core::rect<s32>(posButY, posButX + 6*dek, tailleY, tailleX + 6*dek),
					guiEnvironnement->getRootGUIElement(), ID_GUI_BATIMENT_BIJOUTERIE,
					#ifdef _LANG_FR
					L"Bijouterie", L"Construire une bijouterie ici");
					#else
					#ifdef _LANG_EN
					L"Jeweler's workshop", L"Create jeweler's workshop");
					#endif
					#endif
			}

			guiEnvironnement->addButton(core::rect<s32>(posButY - dek, posButX - dek, tailleY -dek, tailleX - dek),
				guiEnvironnement->getRootGUIElement(), ID_GUI_Annuler, 
				#ifdef _LANG_FR
				L"Annuler", L"Annuler action");
				#else
				#ifdef _LANG_EN
				L"Cancel", L"Cancel action");
				#endif
				#endif
		}
		else // Sinon c'est qu'on veut faire autre chose
		{
			guiEnvironnement->addButton(core::rect<s32>(posButY, posButX - 80, posButY + 100, posButX - 80 + 32), 
				guiEnvironnement->getRootGUIElement(), ID_GUI_Construit,
			#ifdef _LANG_FR
				L"Construire", L"Construire ici");
			#else
			#ifdef _LANG_EN
				L"Build", L"Build around here");
			#endif
			#endif
			guiEnvironnement->addButton(core::rect<s32>(posButY, posButX - 40, posButY + 100, posButX - 40 + 32), 
				guiEnvironnement->getRootGUIElement(), ID_GUI_Smooth,
			#ifdef _LANG_FR
				L"Smoother", L"Smoother ce mur");
			#else
			#ifdef _LANG_EN
				L"Smooth", L"Smooth this wall");
			#endif
			#endif
			guiEnvironnement->addButton(core::rect<s32>(posButY, posButX, posButY + 100, posButX + 32), 
				guiEnvironnement->getRootGUIElement(), ID_GUI_Fortifie, 
			#ifdef _LANG_FR
				L"Fortifier", L"Fortifier ce mur");
			#else
			#ifdef _LANG_EN
				L"Fortificate", L"Carve fortifications here");
			#endif
			#endif
			guiEnvironnement->addButton(core::rect<s32>(posButY, posButX + 40, posButY + 100, posButX+40 + 32), 
				guiEnvironnement->getRootGUIElement(), ID_GUI_Annuler, 
			#ifdef _LANG_FR
				L"Annuler", L"Annuler action");
			#else
			#ifdef _LANG_EN
				L"Cancel", L"Cancel action");
			#endif
			#endif
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
			{ // Constructions
				case CONSTRUIT_ATELIER : 	changement = m_Niveau->construit(ligne, colone, Atelier); break;
				case CONSTRUIT_ATELIER_CUIR : 	changement = m_Niveau->construit(ligne, colone, Atelier_Cuir); break;
				case CONSTRUIT_ARCHERIE : 	changement = m_Niveau->construit(ligne, colone, Archerie); break;
				case CONSTRUIT_BIJOUTERIE : 	changement = m_Niveau->construit(ligne, colone, Bijouterie); break;
				case CONSTRUIT_BOUCHERIE : 	changement = m_Niveau->construit(ligne, colone, Boucherie); break;
				case CONSTRUIT_BRASSERIE: 	changement = m_Niveau->construit(ligne, colone, Brasserie); break;
				case CONSTRUIT_CENDRERIE : 	changement = m_Niveau->construit(ligne, colone, Cendrerie); break;
				case CONSTRUIT_COUTURIER : 	changement = m_Niveau->construit(ligne, colone, Couturier); break;
				case CONSTRUIT_CUISINE : 	changement = m_Niveau->construit(ligne, colone, Cuisine); break;
				case CONSTRUIT_FERME : 		changement = m_Niveau->construit(ligne, colone, Ferme); break;
				case CONSTRUIT_FORGE : 		changement = m_Niveau->construit(ligne, colone, Forge); break;
				case CONSTRUIT_LOOM : 		changement = m_Niveau->construit(ligne, colone, Loom); break;
				case CONSTRUIT_MASSONNERIE : 	changement = m_Niveau->construit(ligne, colone, Massonnerie); break;
				case CONSTRUIT_MECHANIC : 	changement = m_Niveau->construit(ligne, colone, Mechanic); break;
				case CONSTRUIT_MENUISERIE : 	changement = m_Niveau->construit(ligne, colone, Menuiserie); break;
				case CONSTRUIT_POISSONNERIE : 	changement = m_Niveau->construit(ligne, colone, Poissonnerie); break;
				case CONSTRUIT_TANNERIE : 	changement = m_Niveau->construit(ligne, colone, Tannerie); break;
				case CONSTRUIT_TEINTURERIE : 	changement = m_Niveau->construit(ligne, colone, Teinturerie); break;
			}
			case AUCUNE_ACTION :
			default : break;
		}

		m_Action = false; // Action est effectuée 
		m_ActionEnCours = AUCUNE_ACTION;
		m_ControleCamera = true;
	}
	
	return changement;
}
