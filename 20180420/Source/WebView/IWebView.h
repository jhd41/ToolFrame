#pragma once
#include "Macro.h"

NS_TOOL_FRAME_BEGIN

class IWebView
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
	IWebView(void);
	virtual ~IWebView(void);
};

NS_TOOL_FRAME_END
