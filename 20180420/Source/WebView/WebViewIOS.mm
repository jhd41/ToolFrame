#include "WebViewIOS.h"

#include "ToolStd.h"
#include "ApiIOS.h"
#include "ToolPlat.h"
#include "ToolHttp.h"

#import "WebView_iOS.h"
#import "ApiObjC.h"

NS_TOOL_FRAME_BEGIN
//×ª»»
WebView_iOS* ConvertWevView(void* p){
	return (WebView_iOS*)p;
}

CWebViewIOS::CWebViewIOS(void)
{
	m_webViewiOS = nullptr;
}

CWebViewIOS::~CWebViewIOS(void)
{
	Remove();
}

bool CWebViewIOS::Init()
{
	if(m_webViewiOS)return false;
	m_webViewiOS = [[WebView_iOS alloc] init];
	return true;
}

bool CWebViewIOS::SetRect(float fX, float fY, float fWidth, float fHeight )
{
	WebView_iOS* pWebView = ConvertWevView(m_webViewiOS);
	if(!pWebView)return false;
	[pWebView showWebView_x:fX y:fY width:fWidth height:fHeight];
	return true;
}

bool CWebViewIOS::UpdateURL( const std::string& sUrl )
{
	if (ToolFrame::IsUrlNetAddress(sUrl)){
		std::string sUrlFull = ToolFrame::GetFullUrl(sUrl);

		WebView_iOS* pWebView = ConvertWevView(m_webViewiOS);
		if(!pWebView)return false;
		[pWebView updateURL:sUrlFull.c_str()];
		return true;
	}

	std::string sFullPath =	ToolFrame::GetAbsPath(sUrl);
	WebView_iOS* pWebView = ConvertWevView(m_webViewiOS);
	if(!pWebView)return false;
	[pWebView updateLocalURL:sFullPath.c_str()];
	return true;
}

bool CWebViewIOS::Remove()
{
	if(!m_webViewiOS)return false;

	WebView_iOS* pWebView = ConvertWevView(m_webViewiOS);
	if(!pWebView)return false;
	[pWebView removeWebView];

	if(m_webViewiOS){
		[m_webViewiOS release];
		m_webViewiOS = nullptr;
	}
	return true;
}

bool CWebViewIOS::ScreenShot( const std::string& sFileName )
{
    WebView_iOS* pWebView = ConvertWevView(m_webViewiOS);
	if(!pWebView)return false;
	return ApiObjC::ScreenShot([pWebView getView],sFileName);
}

bool CWebViewIOS::SetVisible( bool bVisible )
{
    WebView_iOS* pWebView = ConvertWevView(m_webViewiOS);
	if(!pWebView)return false;
    [[pWebView getView] setHidden: !bVisible];
    return true;
}

std::string CWebViewIOS::GetUrl() const
{
    WebView_iOS* pWebView = ConvertWevView(m_webViewiOS);
    NSString* pURL = [pWebView getURL];
    return [pURL UTF8String];
}

std::string CWebViewIOS::GetUrlTitle() const
{
    WebView_iOS* pWebView = ConvertWevView(m_webViewiOS);
    NSString* pURLTitle = [pWebView getURLTitle];
    return [pURLTitle UTF8String];
}

NS_TOOL_FRAME_END
