#pragma once

#include "Macro.h"

#if MACRO_TARGET_OS == MACRO_OS_WINDOWS

#include <windows.h>

class CApiWinScreenShot
{
public:
	bool SavePng(HWND hwnd,const std::string& sFileName);
	bool SaveBmp(HWND hwnd,const std::string& sFileName);
private:
	RECT GetWindowsRect(HWND hwnd);
	HBITMAP CopyScreenToBitmap(LPRECT lpRect); //lpRect 代表选定区域 
	int GetEncoderClsid(const WCHAR* format, CLSID* pClsid);//目标编码的选择

	//VC下把HBITMAP保存为bmp图片 
	BOOL  SaveBmp(HBITMAP hBitmap,const std::string& sFileName) ;//保存为BMP
	BOOL  ConvertToPng(const std::string& sFileNameBmp,const std::string& sFileNamePng);//保存为Png
public:
	CApiWinScreenShot(void);
	virtual ~CApiWinScreenShot(void);
};

#endif
