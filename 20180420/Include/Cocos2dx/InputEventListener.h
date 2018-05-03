#pragma once
#include "MacroCocos2dx.h"

#ifdef MACRO_LIB_COCOS2D

#include "HInputEventListener.h"

class CInputEventListener
{
public:
	virtual bool	SetHandler(HInputEventListener* hHandler);
	virtual bool	SetGraphPriorityNode(Node* pNode);		//设置图形优先级节点
public:
	virtual bool	SetKeyboardEnabled(bool bEnabled);					//打开键盘
	virtual bool	SetAccelerometerEnabled(bool bEnabled);				//打开重力感应
	virtual bool	SetTouchEnabled(bool bEnabled,bool bShare = false);	//打开触摸
	virtual bool	IsKeyboardEnabled()const;
	virtual bool	IsAccelerometerEnabled()const;
	virtual bool	IsTouchEnabled()const;
public:
	virtual bool	SetEnabledAll(bool bEnabled);			//开启/禁用所有输入
public:
	CInputEventListener(void);
	virtual ~CInputEventListener(void);
private:
	virtual void OnAcceleration(Acceleration* pAcceleration, Event* pEvent);//重力事件的回调
	virtual void OnKeyPressed(EventKeyboard::KeyCode eKeyCode, Event* pEvent);
	virtual void OnKeyReleased(EventKeyboard::KeyCode eKeyCode, Event* pEvent);
private:
	virtual bool OnTouchBegan	(Touch* touch, Event *unusedEvent);
	virtual void OnTouchMoved	(Touch* touch, Event *unusedEvent);
	virtual void OnTouchEnded	(Touch* touch, Event *unusedEvent);
	virtual void OnTouchCancelled(Touch* touch, Event *unusedEvent);
private:
	EventListenerKeyboard*		_pKeyBoard;		//键盘监听器
	EventListenerAcceleration*	_pAcceleration;	//重力感应监听器
	EventListenerTouchOneByOne* _pTouchListener;//触摸监听器

	HInputEventListener*		_hHandler;
	Node*						_pNodeGraphPriority;//图形优先级节点
};

#endif //MACRO_LIB_COCOS2D
