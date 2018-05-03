#pragma once
#include "MacroCocos2dx.h"

#ifdef MACRO_LIB_COCOS2D

class HTouchListener{
public:
	virtual bool OnTouchDrag(Node* pNode,bool bActive,const Vec2& ptOffset,const Vec2& ptBegin,Touch* touch, Event *unusedEvent);//�϶�
	virtual bool OnTouchScaleView(Node* pNode,bool bActive,float fRate,Touch* touch, Event *unusedEvent);	//�Ŵ���С
	virtual bool OnTouchManual(Node* pNode,bool bActive);													//������
	virtual bool OnTouchSingle(Node* pNode,const Vec2& ptPostion);											//����
	virtual bool OnTouchDelay(Node* pNode,bool bActive);													//������ʱ״̬
	virtual bool OnTouchIdle(Node* pNode);																	//����
	virtual bool OnTouchSlip(Node* pNode,const Vec2& ptDirect);																	//����
public:
	virtual bool OnTouchGroupBegan	(Touch* touch, Event *unusedEvent);
	virtual bool OnTouchGroupMoved	(Touch* touch, Event *unusedEvent);
	virtual bool OnTouchGroupEnded	(Touch* touch, Event *unusedEvent);
	virtual bool OnTouchGroupCancelled(Touch* touch, Event *unusedEvent);
public:
	HTouchListener(){}
	virtual ~HTouchListener(){}
};

#endif //MACRO_LIB_COCOS2D
