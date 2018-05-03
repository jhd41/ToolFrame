#pragma once
#include "Macro.h"
//�������Ƕ�COCOS2d���༶��Ĳ���

#ifdef MACRO_LIB_COCOS2D

#include "MacroCocos2dx.h"

//�ɼ�
//////////////////////////////////////////////////////////////////////////
class TOOLFRAME_DLL CVisibleAction
	:public CCFiniteTimeAction
{
public:
	static CVisibleAction*	Create(bool bVisible);
public:
	virtual void update(float time);
	virtual FiniteTimeAction* reverse() const;
	virtual FiniteTimeAction* clone() const;
private:
	CVisibleAction(void);
	virtual ~CVisibleAction(void);
private:
	CFIELD_BOOL(Visible);
};



#endif //MACRO_LIB_COCOS2D
