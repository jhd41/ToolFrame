#include "Macro.h"

#ifdef MACRO_LIB_COCOS2D

#include "Cocos2dxEx.h"

//ÊÇ·ñ¿É¼ûAction
//////////////////////////////////////////////////////////////////////////
CVisibleAction::CVisibleAction( void )
{
	SetVisible(false);
}

CVisibleAction::~CVisibleAction( void )
{

}

CVisibleAction* CVisibleAction::Create( bool bVisible )
{
	CVisibleAction* pAction = new CVisibleAction();
	pAction->autorelease();
	pAction->setDuration(0);
	
	pAction->SetVisible(bVisible);
	return pAction;
}

void CVisibleAction::update( float time )
{
	getOriginalTarget()->setVisible(IsVisible());
}

FiniteTimeAction* CVisibleAction::reverse() const
{
	return Create(!IsVisible());
}

FiniteTimeAction* CVisibleAction::clone() const
{
	return Create(IsVisible());
}

#endif //MACRO_LIB_COCOS2D
