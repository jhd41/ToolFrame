#pragma once

#include "Macro.h"

#if MACRO_TARGET_OS == MACRO_OS_WINDOWS

#include <atlbase.h>
#include <atlwin.h>
#include <windows.h>

//extern HWND g_hWnd;

class WebView_ATL
{
public:
	WebView_ATL(void);
	virtual ~WebView_ATL(void);

	bool Init();
	/**
	*	@brief	显示WebView
	*
	*	@param 	url 	地址
	*	@param 	x 	x位置
	*	@param 	y 	y位置(左上的位置，坐标系为左上0)
	*	@param 	width 	宽度
	*	@param 	height 	高度
	*/
	bool		SetRect(float fX, float fY, float fWidth, float fHeight );
	
	bool		UpdateURL(const char* url);
	bool		RemoveWebView();
	HWND		GetHWnd();
	bool		SetVisible( bool bVisible );
	std::string GetUrl()const;
    std::string GetUrlTitle()const;
private:
	bool		Resize(float fX, float fY, float fWidth, float fHeight );
	bool		ShowWebView(float x, float y, float width, float height);
private:
	CAxWindow		_axWinContainer;
	IWebBrowser2*	_pWebBrowser;
	HWND			_hWnd;
};

#endif
