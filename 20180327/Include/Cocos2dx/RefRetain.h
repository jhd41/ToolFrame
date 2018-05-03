#pragma once
#include "MacroCocos2dx.h"

#ifdef MACRO_LIB_COCOS2D

class TOOLFRAME_DLL CRefRetain
{
public:
	CRefRetain(Ref* pObj);
	virtual ~CRefRetain(void);
private:
	Ref*	_pObj;
};

#endif //MACRO_LIB_COCOS2D
