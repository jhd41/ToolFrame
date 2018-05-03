#pragma once
#include "MacroCocos2dx.h"
#include "IPage.h"

#ifdef MACRO_LIB_COCOS2D

class TOOLFRAME_DLL CWidgetPage
	:public Widget
{
	COCOS2DX_CREATE_INIT(CWidgetPage);
public:
	bool SetPage(IPage* pPage);
private:
	virtual void onEnter() override;
	virtual void onEnterTransitionDidFinish()override;
	virtual void onExit() override;
public:
	CWidgetPage(void);
	virtual ~CWidgetPage(void);
private:
	IPage* _pPage;
};

#endif //MACRO_LIB_COCOS2D

