#ifndef HPP_EVENT
#define HPP_EVENT

#include<irrlicht/irrlicht.h>

#include "niveau.hpp"

class TraitementEvennement : public irr::IEventReceiver
{
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

		bool majNiveau(irr::scene::ICameraSceneNode *camera);

		const SMouseState & GetMouseState() const
		{ return MouseState; }
	private :
		bool m_KeyIsDown[irr::KEY_KEY_CODES_COUNT];
		bool m_KeyIsDownOld[irr::KEY_KEY_CODES_COUNT];
		bool m_IsShiftDown;
		bool m_IsCtrlDown;

		Niveau *m_Niveau;
};


#endif
