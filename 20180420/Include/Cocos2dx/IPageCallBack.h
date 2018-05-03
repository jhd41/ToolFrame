#pragma once
#include "Macro.h"
#include "IPage.h"

#ifdef MACRO_LIB_COCOS2D

class TOOLFRAME_DLL IPageCallBack
{
public:
	IPageCallBack(IPage* pPage);
	virtual ~IPageCallBack(void);
private:
	IPage* _pPage;
};

#endif //MACRO_LIB_COCOS2D