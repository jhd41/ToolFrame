#pragma once
#include "IWebView.h"

#if MACRO_TARGET_OS == MACRO_OS_IOS

NS_TOOL_FRAME_BEGIN

class CWebViewIOS
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
	CWebViewIOS(void);
	virtual ~CWebViewIOS(void);
private:
	void* m_webViewiOS;
};

NS_TOOL_FRAME_END

#endif
	