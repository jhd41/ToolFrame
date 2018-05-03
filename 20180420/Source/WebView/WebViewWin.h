#pragma once
#include "IWebView.h"

#if MACRO_TARGET_OS == MACRO_OS_WINDOWS

class WebView_ATL;

NS_TOOL_FRAME_BEGIN

class CWebViewWin
	:public IWebView
{
public:
	virtual bool		Init();
	virtual bool		SetRect(float fX, float fY, float fWidth, float fHeight );
	virtual bool		UpdateURL(const std::string& sUrl);
	virtual bool		Remove();
	virtual bool		ScreenShot(const std::string& sFileName);
	virtual bool		SetVisible(bool bVisible);
	virtual std::string GetUrl()const;
    virtual std::string GetUrlTitle()const;
public:
	CWebViewWin(void);
	virtual ~CWebViewWin(void);
private:
	WebView_ATL* _pWebView;
};

NS_TOOL_FRAME_END

#endif
	