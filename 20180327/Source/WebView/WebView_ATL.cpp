#include "WebView_ATL.h"

#pragma warning(disable:4244)

#if MACRO_TARGET_OS == MACRO_OS_WINDOWS

// #pragma comment(lib,"atl")
#pragma comment(lib,"User32.lib")
#pragma comment(lib,"urlmon.lib")

CComModule _Module;

WebView_ATL::WebView_ATL(void)
{
	_hWnd = nullptr;
	_pWebBrowser = nullptr;
}

WebView_ATL::~WebView_ATL(void)
{
	RemoveWebView();
}

bool WebView_ATL::Init()
{
	return true;
}

bool WebView_ATL::ShowWebView(float x, float y, float width, float height)
{
	if (_axWinContainer.IsWindow())
		RemoveWebView();

	char* s = "Mozilla/5.0 (compatible; AppleWebKit/537.36; Chrome/45.0.2454.101; Smartphone)";
	UrlMkSetSessionOption(URLMON_OPTION_USERAGENT, s, (DWORD)strlen(s), 0);

	HWND hWnd = ::GetActiveWindow();
	if (!hWnd)
		return false;

	LONG dwWindowStyle = ::GetWindowLong(hWnd, GWL_STYLE);
	::SetWindowLongW(hWnd, GWL_STYLE, dwWindowStyle & ~WS_POPUP);

	RECT rc = {(LONG)(x+0.5f), (LONG)(y+0.5f), (LONG)(width+0.5f), (LONG)(height+0.5f)};
	_hWnd = _axWinContainer.Create(hWnd, rc, _T("shell.Explorer.2"), WS_CHILD | WS_VISIBLE);
	_axWinContainer.QueryControl(__uuidof(IWebBrowser2), (void**)&_pWebBrowser);
	if (!_pWebBrowser)
		return false;

	_pWebBrowser->put_Silent(VARIANT_TRUE);

	return true;
}

bool WebView_ATL::UpdateURL(const char* url)
{
	if (!url)return false;
	if (!_pWebBrowser)return false;

	VARIANT varMyURL;
	VariantInit(&varMyURL);
	varMyURL.vt = VT_BSTR;
	USES_CONVERSION;
	varMyURL.bstrVal = SysAllocString(A2W(url));
	_pWebBrowser-> Navigate2(&varMyURL, 0, 0, 0, 0);
	VariantClear(&varMyURL);

	return true;
}

bool WebView_ATL::RemoveWebView()
{
	if (!_pWebBrowser)return false;
	_pWebBrowser->Release();
	_axWinContainer.DestroyWindow();

	_pWebBrowser = nullptr;
	return true;
}

HWND WebView_ATL::GetHWnd()
{
	return _hWnd;
}

bool WebView_ATL::SetVisible( bool bVisible )
{
	if (!_pWebBrowser)return false;
	if (!_hWnd)return false;
	return TRUE ==  ShowWindow(_hWnd,bVisible ? SW_SHOWNORMAL:SW_HIDE);
}

#include <comdef.h>
std::string ToString(BSTR str){
	_bstr_t bstr_t(str);
	std::string str1(bstr_t);
	return str1;
}

std::string WebView_ATL::GetUrl() const
{
	BSTR str;
	if (S_OK == _pWebBrowser->get_LocationURL(&str))
		return ToString(str);
	
	return "";
}

std::string WebView_ATL::GetUrlTitle() const
{
    BSTR str;
    if (S_OK == _pWebBrowser->get_LocationName(&str))
        return ToString(str);
    
    return "";
}

bool WebView_ATL::Resize( float fX, float fY, float fWidth, float fHeight )
{
	if (!_pWebBrowser)return false;

	//_pWebBrowser->put_Resizable(VARIANT_TRUE);
	_pWebBrowser->put_Left(fX);
	_pWebBrowser->put_Top(fY);
	_pWebBrowser->put_Width(fWidth);
	_pWebBrowser->put_Height(fHeight);
	return true;
}

bool WebView_ATL::SetRect( float fX, float fY, float fWidth, float fHeight )
{
	if (!_pWebBrowser)
	{
		ShowWebView(fX,fY,fWidth,fHeight);
		return true;
	}
	return Resize(fX,fY,fWidth,fHeight);
}

#endif
