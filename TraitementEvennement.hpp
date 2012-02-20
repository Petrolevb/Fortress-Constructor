#ifndef HPP_EVENT
#define HPP_EVENT

#include<irrlicht/irrlicht.h>

#include"definitions.hpp"
#include "niveau.hpp"

class TraitementEvennement : public irr::IEventReceiver
{
	enum 
	{
		ID_GUI_Smooth = 101,
		ID_GUI_Fortifie,
		ID_GUI_Annuler,
		ID_GUI_Default
	};
	public :
		struct SMouseState
		{
			irr::core::position2di Position;
			bool LeftButtonDown;
			bool RightButtonDown;
			SMouseState() : LeftButtonDown(false), RightButtonDown(false) { }
		} MouseState;
		
		TraitementEvennement(Niveau *niveau);
		~TraitementEvennement();

		virtual bool OnEvent(const irr::SEvent &event);
		virtual bool IsKeyDown(irr::EKEY_CODE keyCode) const;
		
		bool getControleCamera() { return m_ControleCamera; }

		bool majNiveau(irr::scene::ISceneManager *sceneManager, irr::scene::ICameraSceneNode *camera);

		const SMouseState & GetMouseState() const
		{ return MouseState; }
	private :
		bool m_KeyIsDown[irr::KEY_KEY_CODES_COUNT];
		bool m_KeyIsDownOld[irr::KEY_KEY_CODES_COUNT];
		bool m_IsShiftDown;
		bool m_IsCtrlDown;
		
		bool m_ControleCamera; // Si le joueur clique, il perd le controle de la caméra pour sélectionner son option
		Niveau *m_Niveau;
		bool m_Action; // Action en cours
		Action m_ActionEnCours;
};


#endif
