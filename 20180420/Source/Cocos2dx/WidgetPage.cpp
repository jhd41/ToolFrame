#include "WidgetPage.h"
#include "MLoger.h"

#ifdef MACRO_LIB_COCOS2D

CWidgetPage::CWidgetPage(void)
{
	_pPage = nullptr;
}

CWidgetPage::~CWidgetPage(void)
{
	if (_pPage){
		_pPage->release();
		_pPage = nullptr;
	}
}

bool CWidgetPage::SetPage( IPage* pPage )
{
	if (_pPage)return false;
	_pPage = pPage;
	_pPage->retain();
	return true;
}

void CWidgetPage::onEnter()
{
	ASSERT_LOG_ERROR(_pPage);
	_pPage->FireEventEnter();
	
	Widget::onEnter();
}

void CWidgetPage::onExit()
{
	ASSERT_LOG_ERROR(_pPage);
	_pPage->FireEventExit();
	_pPage->Destory();
	_pPage->release();
	_pPage = nullptr;

	Widget::onExit();
}

void CWidgetPage::onEnterTransitionDidFinish()
{
	Widget::onEnterTransitionDidFinish();

	ASSERT_LOG_ERROR(_pPage);
	_pPage->FireEventEnterTransitionDidFinish();
}

#endif //MACRO_LIB_COCOS2D
