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
	HBITMAP CopyScreenToBitmap(LPRECT lpRect); //lpRect ����ѡ������ 
	int GetEncoderClsid(const WCHAR* format, CLSID* pClsid);//Ŀ������ѡ��

	//VC�°�HBITMAP����ΪbmpͼƬ 
	BOOL  SaveBmp(HBITMAP hBitmap,const std::string& sFileName) ;//����ΪBMP
	BOOL  ConvertToPng(const std::string& sFileNameBmp,const std::string& sFileNamePng);//����ΪPng
public:
	CApiWinScreenShot(void);
	virtual ~CApiWinScreenShot(void);
};

#endif
