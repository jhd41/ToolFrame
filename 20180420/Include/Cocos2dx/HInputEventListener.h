#pragma once
#include "MacroCocos2dx.h"

#ifdef MACRO_LIB_COCOS2D

class HInputEventListener
{
public:
	virtual bool OnAcceleration(Acceleration* pAcceleration, Event* pEvent);//重力事件的回调
public:
	virtual bool OnKeyPressed(EventKeyboard::KeyCode eKeyCode, Event* pEvent);
	virtual bool OnKeyReleased(EventKeyboard::KeyCode eKeyCode, Event* pEvent);
public:
	virtual bool OnTouchBegan	(Touch* touch, Event *unusedEvent);
	virtual bool OnTouchMoved	(Touch* touch, Event *unusedEvent);
	virtual bool OnTouchEnded	(Touch* touch, Event *unusedEvent);
	virtual bool OnTouchCancelled(Touch* touch, Event *unusedEvent);
public:
	HInputEventListener(void);
	virtual ~HInputEventListener(void);
};

#endif //MACRO_LIB_COCOS2D
