#pragma once

#include "MacroCocos2dx.h"
//Òýµ¼Ò³
#ifdef MACRO_LIB_COCOS2D

class TOOLFRAME_DLL HLandingPage{
public:
	virtual bool OnLandingPageDone(){return true;}
public:
	HLandingPage(){}
	virtual ~HLandingPage(){}
};

class TOOLFRAME_DLL CLandingPage
{
public:
	bool Init(Node* pNode,HLandingPage* hHandler);
	bool AddPage(const std::string& sImgPath);
	bool Resize();
private:
	void CallBackTouch(Ref* ref,Widget::TouchEventType eEvent);
	bool InitPageView();
public:
	CLandingPage(void);
	virtual ~CLandingPage(void);
private:
	PageView*			_pPageView;
	HLandingPage*	_hHandler;
};


#endif //MACRO_LIB_COCOS2D
