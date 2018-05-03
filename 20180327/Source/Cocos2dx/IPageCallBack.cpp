#include "IPageCallBack.h"
#include "SceneFrameMgr.h"

#ifdef MACRO_LIB_COCOS2D
IPageCallBack::IPageCallBack( IPage* pPage )
{
	_pPage = pPage;
	_pPage->retain();
}

IPageCallBack::~IPageCallBack(void)
{
	_pPage->GetSceneMgr()->TryInitPage();
	_pPage->release();
}
#endif //MACRO_LIB_COCOS2D