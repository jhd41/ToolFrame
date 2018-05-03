#include "WebView.h"
#include "ToolFrame.h"

#include "IWebView.h"
#include "WebViewAndroid.h"
#include "WebViewIOS.h"
#include "WebViewWin.h"

NS_TOOL_FRAME_BEGIN

CWebView::CWebView(void)
{
	_pWebView = Create();
}

CWebView::~CWebView(void)
{
	Destory();
}

IWebView* CWebView::Create()
{
#if MACRO_TARGET_OS == MACRO_OS_ANDROID
	return new CWebViewAndroid();
#endif
#if MACRO_TARGET_OS == MACRO_OS_WINDOWS
	return new CWebViewWin();
#endif
#if MACRO_TARGET_OS == MACRO_OS_IOS
	return new CWebViewIOS();
#endif

	return nullptr;
}

bool CWebView::Destory()
{
	ToolFrame::Delete(_pWebView);
	return true;
}

bool CWebView::Init()
{
	return _pWebView->Init();
}

bool CWebView::SetRect( float fX, float fY, float fWidth, float fHeight )
{
	return _pWebView->SetRect(fX,fY,fWidth,fHeight);
}

bool CWebView::UpdateURL( const std::string& sUrl )
{
	return _pWebView->UpdateURL(sUrl);
}

bool CWebView::Remove()
{
	return _pWebView->Remove();
}

bool CWebView::ScreenShot( const std::string& sFileName )
{
	return _pWebView->ScreenShot(sFileName);
}

bool CWebView::SetVisible( bool bVisible )
{
	return _pWebView->SetVisible(bVisible);
}

std::string CWebView::GetUrl() const
{
	return _pWebView->GetUrl();
}

std::string CWebView::GetUrlTitle() const
{
    return _pWebView->GetUrlTitle();
}

NS_TOOL_FRAME_END
