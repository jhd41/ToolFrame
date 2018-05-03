#pragma once
#include "MacroCocos2dx.h"

#ifdef MACRO_LIB_COCOS2D

#include "HInputEventListener.h"

class CInputEventListener
{
public:
	virtual bool	SetHandler(HInputEventListener* hHandler);
	virtual bool	SetGraphPriorityNode(Node* pNode);		//����ͼ�����ȼ��ڵ�
public:
	virtual bool	SetKeyboardEnabled(bool bEnabled);					//�򿪼���
	virtual bool	SetAccelerometerEnabled(bool bEnabled);				//��������Ӧ
	virtual bool	SetTouchEnabled(bool bEnabled,bool bShare = false);	//�򿪴���
	virtual bool	IsKeyboardEnabled()const;
	virtual bool	IsAccelerometerEnabled()const;
	virtual bool	IsTouchEnabled()const;
public:
	virtual bool	SetEnabledAll(bool bEnabled);			//����/������������
public:
	CInputEventListener(void);
	virtual ~CInputEventListener(void);
private:
	virtual void OnAcceleration(Acceleration* pAcceleration, Event* pEvent);//�����¼��Ļص�
	virtual void OnKeyPressed(EventKeyboard::KeyCode eKeyCode, Event* pEvent);
	virtual void OnKeyReleased(EventKeyboard::KeyCode eKeyCode, Event* pEvent);
private:
	virtual bool OnTouchBegan	(Touch* touch, Event *unusedEvent);
	virtual void OnTouchMoved	(Touch* touch, Event *unusedEvent);
	virtual void OnTouchEnded	(Touch* touch, Event *unusedEvent);
	virtual void OnTouchCancelled(Touch* touch, Event *unusedEvent);
private:
	EventListenerKeyboard*		_pKeyBoard;		//���̼�����
	EventListenerAcceleration*	_pAcceleration;	//������Ӧ������
	EventListenerTouchOneByOne* _pTouchListener;//����������

	HInputEventListener*		_hHandler;
	Node*						_pNodeGraphPriority;//ͼ�����ȼ��ڵ�
};

#endif //MACRO_LIB_COCOS2D
