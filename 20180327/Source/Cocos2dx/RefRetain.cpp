#include "RefRetain.h"

#ifdef MACRO_LIB_COCOS2D

CRefRetain::CRefRetain( Ref* pObj )
{
	_pObj = pObj;

	_pObj->retain();
}


CRefRetain::~CRefRetain(void)
{
	_pObj->release();
}

#endif //MACRO_LIB_COCOS2D
