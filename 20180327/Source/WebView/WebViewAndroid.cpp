#include "WebViewAndroid.h"

#if MACRO_TARGET_OS == MACRO_OS_ANDROID
#include "ApiJni.h"
#include "ToolStd.h"
#include "ToolHttp.h"

NS_TOOL_FRAME_BEGIN

CWebViewAndroid::CWebViewAndroid(void)
{
}

CWebViewAndroid::~CWebViewAndroid(void)
{
	Remove();
}

bool CWebViewAndroid::Init()
{
	return ApiJni::CallJniReturnBool("com/CloudCity/Lib/ApiAndroid","WebView_Init");
}

bool CWebViewAndroid::SetRect(float fX, float fY, float fWidth, float fHeight )
{
	return ApiJni::CallJniReturnBool("com/CloudCity/Lib/ApiAndroid","WebView_Display",(int)(fX+0.5f),(int)(fY+0.5),(int)(fWidth+0.5),(int)(fHeight+0.5));
}

bool CWebViewAndroid::UpdateURL( const std::string& sUrl )
{
	if (ToolFrame::IsFullUrl(sUrl))
		return ApiJni::CallJniReturnBool("com/CloudCity/Lib/ApiAndroid", "WebView_UpdateURL", sUrl);

	if (ToolFrame::IsUrlNetAddress(sUrl))
		return ApiJni::CallJniReturnBool("com/CloudCity/Lib/ApiAndroid","WebView_UpdateURL",ToolFrame::GetFullUrl(sUrl));

	return ApiJni::CallJniReturnBool("com/CloudCity/Lib/ApiAndroid","WebView_UpdateURL",MAKE_STRING("file:///android_asset/"<<sUrl));
}

bool CWebViewAndroid::Remove()
{
	return ApiJni::CallJniReturnBool("com/CloudCity/Lib/ApiAndroid","WebView_Remove");
}

bool CWebViewAndroid::ScreenShot( const std::string& sFileName )
{
	return ApiJni::CallJniReturnBool("com/CloudCity/Lib/ApiAndroid","WebView_ScreenShot",sFileName);
}

bool CWebViewAndroid::SetVisible( bool bVisible )
{
	return ApiJni::CallJniReturnBool("com/CloudCity/Lib/ApiAndroid","WebView_SetVisible",bVisible);
}

std::string CWebViewAndroid::GetUrl() const
{
	return ApiJni::CallJniReturnString("com/CloudCity/Lib/ApiAndroid","WebView_GetUrl");
}

std::string CWebViewAndroid::GetUrlTitle() const
{
    return ApiJni::CallJniReturnString("com/CloudCity/Lib/ApiAndroid","WebView_GetUrlTitle");
}

NS_TOOL_FRAME_END

#endif
