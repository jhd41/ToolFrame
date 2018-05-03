#include "WebViewWin.h"
#include "WebView_ATL.h"
#include "ToolFrame.h"

#if MACRO_TARGET_OS == MACRO_OS_WINDOWS

NS_TOOL_FRAME_BEGIN

CWebViewWin::CWebViewWin(void)
{
	_pWebView = nullptr;
}

CWebViewWin::~CWebViewWin(void)
{
	Remove();
	ToolFrame::Delete(_pWebView);
}

bool CWebViewWin::Init()
{
	if (_pWebView)return false;
	_pWebView = new WebView_ATL();
	return true;
}

bool CWebViewWin::SetRect( float fX, float fY, float fWidth, float fHeight )
{
	if (!_pWebView)return false;
	_pWebView->SetRect(fX, fY, fWidth, fHeight);
	return true;
}

bool CWebViewWin::UpdateURL( const std::string& sUrl )
{
	if (!_pWebView)return false;
	_pWebView->UpdateURL(sUrl.c_str());
	return true;
}

bool CWebViewWin::Remove()
{
	if (!_pWebView)return false;
	return _pWebView->RemoveWebView();
}

bool CWebViewWin::ScreenShot( const std::string& sFileName )
{
	if (!_pWebView)return false;
	return _pWebView->RemoveWebView();
}

bool CWebViewWin::SetVisible( bool bVisible )
{
	if (!_pWebView)return false;
	return _pWebView->SetVisible(bVisible);
}

std::string CWebViewWin::GetUrl() const
{
	if (!_pWebView)return "";
	return _pWebView->GetUrl(); 
}

std::string CWebViewWin::GetUrlTitle() const
{
    if (!_pWebView)return "";
    return _pWebView->GetUrlTitle();
}

NS_TOOL_FRAME_END

#endif
