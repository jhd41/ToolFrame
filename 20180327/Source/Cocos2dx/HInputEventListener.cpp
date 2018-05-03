#include "HInputEventListener.h"

#ifdef MACRO_LIB_COCOS2D

HInputEventListener::HInputEventListener(void)
{
}


HInputEventListener::~HInputEventListener(void)
{
}

bool HInputEventListener::OnAcceleration( Acceleration* pAcceleration, Event* pEvent )
{
	return false;
}

bool HInputEventListener::OnKeyPressed( EventKeyboard::KeyCode eKeyCode, Event* pEvent )
{
	return false;
}

bool HInputEventListener::OnKeyReleased( EventKeyboard::KeyCode eKeyCode, Event* pEvent )
{
	return false;
}

bool HInputEventListener::OnTouchBegan( Touch* touch, Event *unusedEvent )
{
	return false;
}

bool HInputEventListener::OnTouchMoved( Touch* touch, Event *unusedEvent )
{
	return false;
}

bool HInputEventListener::OnTouchEnded( Touch* touch, Event *unusedEvent )
{
	return false;
}

bool HInputEventListener::OnTouchCancelled( Touch* touch, Event *unusedEvent )
{
	return false;
}

#endif //MACRO_LIB_COCOS2D
