#include "IWebView.h"

NS_TOOL_FRAME_BEGIN

IWebView::IWebView(void)
{
}

IWebView::~IWebView(void)
{
}

bool IWebView::Init()
{
	return true;
}

bool IWebView::SetRect(float fX, float fY, float fWidth, float fHeight )
{
	return true;
}

bool IWebView::UpdateURL( const std::string& sUrl )
{
	return true;
}

bool IWebView::Remove()
{
	return true;
}

bool IWebView::ScreenShot(const std::string& sFileName)
{
	return true;
}

bool IWebView::SetVisible( bool bVisible )
{
	return true;
}

std::string IWebView::GetUrl() const
{
	return "";
}

std::string IWebView::GetUrlTitle() const
{
    return "";
}

NS_TOOL_FRAME_END

