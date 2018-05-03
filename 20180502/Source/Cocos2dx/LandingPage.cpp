#include "LandingPage.h"

#ifdef MACRO_LIB_COCOS2D

#include "MLoger.h"
#include "ToolCPlus11.h"
#include "ApiCocos2dx.h"

CLandingPage::CLandingPage(void)
{
	_hHandler = nullptr;
	_pPageView = nullptr;
}

CLandingPage::~CLandingPage(void)
{
}

bool CLandingPage::AddPage( const std::string& sImgPath )
{
	return ApiCocos2dx::PageAddImage(_pPageView,sImgPath,-1,true);
}

bool CLandingPage::Init( Node* pNode,HLandingPage* hHandler )
{
	if (!pNode)return false;
	if (!hHandler)return false;

	_pPageView = PageView::create();
	ASSERT_LOG_ERROR(_pPageView);

	ApiCocos2dx::SetEnabled(_pPageView,true);
	ApiCocos2dx::AddTouchEvent(_pPageView,ToolFrame::Bind(&CLandingPage::CallBackTouch,this));

	if (!InitPageView())return false;

	pNode->addChild(_pPageView);

	_hHandler = hHandler;
	return true;
}

void CLandingPage::CallBackTouch( Ref* ref,Widget::TouchEventType eEvent )
{
	if (Widget::TouchEventType::ENDED == eEvent)
	{
		if (ApiCocos2dx::IsCurLastPage(_pPageView))
		{
			ASSERT_LOG_ERROR(_hHandler);
			_hHandler->OnLandingPageDone();
		}
	}
}

bool CLandingPage::Resize()
{
	if (!InitPageView())return false;
	return ApiCocos2dx::PageResetImage(_pPageView);
}

bool CLandingPage::InitPageView()
{
	if (!_pPageView)return false;

	_pPageView->setAnchorPoint(ccp(0.5f,0.5f));
	_pPageView->setPosition(ApiCocos2dx::GetVisibleCenter());
	return true;
}

#endif //MACRO_LIB_COCOS2D