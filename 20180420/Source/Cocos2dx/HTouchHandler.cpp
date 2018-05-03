#include "HTouchHandler.h"

#ifdef MACRO_LIB_COCOS2D

bool HTouchListener::OnTouchDrag( Node* pNode,bool bActive,const Vec2& ptOffset,const Vec2& ptBegin,Touch* touch, Event *unusedEvent )
{
	return true;
}

bool HTouchListener::OnTouchScaleView( Node* pNode,bool bActive,float fRate,Touch* touch, Event *unusedEvent )
{
	return true;
}

bool HTouchListener::OnTouchManual( Node* pNode,bool bActive )
{
	return true;
}

bool HTouchListener::OnTouchSingle( Node* pNode,const Vec2& ptPostion )
{
	return true;
}

bool HTouchListener::OnTouchIdle( Node* pNode )
{
	return true;
}

bool HTouchListener::OnTouchSlip(Node* pNode, const Vec2& ptDirect)
{
	return true;
}

bool HTouchListener::OnTouchDelay(Node* pNode, bool bActive)
{
	return true;
}

//////////////////////////////////////////////////////////////////////////
bool HTouchListener::OnTouchGroupBegan( Touch* touch, Event *unusedEvent )
{
	return true;
}

bool HTouchListener::OnTouchGroupMoved( Touch* touch, Event *unusedEvent )
{
	return true;
}

bool HTouchListener::OnTouchGroupEnded( Touch* touch, Event *unusedEvent )
{
	return true;
}

bool HTouchListener::OnTouchGroupCancelled( Touch* touch, Event *unusedEvent )
{
	return true;
}

#endif //MACRO_LIB_COCOS2D
