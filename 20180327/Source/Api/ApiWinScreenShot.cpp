#include "ApiWinScreenShot.h"

#if MACRO_TARGET_OS == MACRO_OS_WINDOWS

#include <math.h>
#include <vector>
#include <TCHAR.H>
#include <stdio.h>

#include <windows.h>
#include <TCHAR.H>
#include <stdio.h>
#include <iostream>
#include <gdiplus.h>
#include <string>
#include <atltrace.h>

#include "ApiWin.h"

#pragma comment(lib,"gdiplus")

using namespace std;
using namespace Gdiplus;

CApiWinScreenShot::CApiWinScreenShot(void)
{
}

CApiWinScreenShot::~CApiWinScreenShot(void)
{
}

bool CApiWinScreenShot::SaveBmp( HWND hwnd,const std::string& sFileName )
{
	RECT rect=GetWindowsRect(hwnd);
	tagRECT trect;
	trect.left=rect.left;
	trect.top=rect.top;
	trect.bottom=rect.bottom;
	trect.right=rect.right;
	HBITMAP hBitMap=CopyScreenToBitmap(&trect);
	return TRUE == SaveBmp(hBitMap,sFileName);
}

bool CApiWinScreenShot::SavePng( HWND hwnd,const std::string& sFileName )
{
	std::string sFileNameTemp  = "temp.bmp";
	if (!SaveBmp(hwnd,sFileNameTemp))return false;
	return TRUE == ConvertToPng(sFileNameTemp,sFileName);
}

BOOL CApiWinScreenShot::SaveBmp( HBITMAP hBitmap,const std::string& sFileName )
{
	HDC     hDC;       
	//��ǰ�ֱ�����ÿ������ռ�ֽ���       
	int     iBits;       
	//λͼ��ÿ������ռ�ֽ���       
	WORD     wBitCount;       
	//�����ɫ���С��     λͼ�������ֽڴ�С     ��λͼ�ļ���С     ��     д���ļ��ֽ���           
	DWORD     dwPaletteSize=0,   dwBmBitsSize=0,   dwDIBSize=0,   dwWritten=0;           
	//λͼ���Խṹ           
	BITMAP     Bitmap;               
	//λͼ�ļ�ͷ�ṹ       
	BITMAPFILEHEADER     bmfHdr;               
	//λͼ��Ϣͷ�ṹ           
	BITMAPINFOHEADER     bi;               
	//ָ��λͼ��Ϣͷ�ṹ               
	LPBITMAPINFOHEADER     lpbi;               
	//�����ļ��������ڴ�������ɫ����           
	HANDLE     fh,   hDib,   hPal,hOldPal=NULL;           

	//����λͼ�ļ�ÿ��������ռ�ֽ���           
	hDC  = CreateDC(_T("DISPLAY"),   NULL,   NULL,   NULL);       
	iBits  = GetDeviceCaps(hDC,   BITSPIXEL)     *     GetDeviceCaps(hDC,   PLANES);           
	DeleteDC(hDC);           
	if(iBits <=  1)                                                 
		wBitCount = 1;           
	else  if(iBits <=  4)                             
		wBitCount  = 4;           
	else if(iBits <=  8)                             
		wBitCount  = 8;           
	else                                                                                                                             
		wBitCount  = 24;           

	GetObject(hBitmap,   sizeof(Bitmap),   (LPSTR)&Bitmap);       
	bi.biSize= sizeof(BITMAPINFOHEADER);       
	bi.biWidth = Bitmap.bmWidth;       
	bi.biHeight =  Bitmap.bmHeight;       
	bi.biPlanes =  1;       
	bi.biBitCount = wBitCount;       
	bi.biCompression= BI_RGB;       
	bi.biSizeImage=0;       
	bi.biXPelsPerMeter = 0;       
	bi.biYPelsPerMeter = 0;       
	bi.biClrImportant = 0;       
	bi.biClrUsed =  0;       

	dwBmBitsSize  = ((Bitmap.bmWidth *wBitCount+31) / 32)*4* Bitmap.bmHeight;       

	//Ϊλͼ���ݷ����ڴ�           
	hDib  = GlobalAlloc(GHND,dwBmBitsSize+dwPaletteSize+sizeof(BITMAPINFOHEADER));           
	lpbi  = (LPBITMAPINFOHEADER)GlobalLock(hDib);           
	*lpbi  = bi;           

	//     �����ɫ��               
	hPal  = GetStockObject(DEFAULT_PALETTE);           
	if (hPal)           
	{           
		hDC  = ::GetDC(NULL);           
		hOldPal = ::SelectPalette(hDC,(HPALETTE)hPal, FALSE);           
		RealizePalette(hDC);           
	}       

	//     ��ȡ�õ�ɫ�����µ�����ֵ           
	GetDIBits(hDC,hBitmap, 0,(UINT)Bitmap.bmHeight,
		(LPSTR)lpbi+ sizeof(BITMAPINFOHEADER)+dwPaletteSize, 
		(BITMAPINFO *)lpbi, DIB_RGB_COLORS);           

	//�ָ���ɫ��               
	if (hOldPal)           
	{           
		::SelectPalette(hDC,   (HPALETTE)hOldPal,   TRUE);           
		RealizePalette(hDC);           
		::ReleaseDC(NULL,   hDC);           
	}           
	
	//����λͼ�ļ�               
	fh  = CreateFile(ApiWin::ToStringT(sFileName).c_str(),   GENERIC_WRITE,0,   NULL,   CREATE_ALWAYS,         
		FILE_ATTRIBUTE_NORMAL | FILE_FLAG_SEQUENTIAL_SCAN,   NULL);           

	if (fh     ==  INVALID_HANDLE_VALUE)         return     FALSE;           

	//     ����λͼ�ļ�ͷ           
	bmfHdr.bfType  = 0x4D42;     //     "BM"           
	dwDIBSize  = sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER)+dwPaletteSize+dwBmBitsSize;               
	bmfHdr.bfSize  = dwDIBSize;           
	bmfHdr.bfReserved1  = 0;           
	bmfHdr.bfReserved2  = 0;           
	bmfHdr.bfOffBits  = (DWORD)sizeof(BITMAPFILEHEADER)+(DWORD)sizeof(BITMAPINFOHEADER)+dwPaletteSize;           
	//     д��λͼ�ļ�ͷ           
	WriteFile(fh,   (LPSTR)&bmfHdr,   sizeof(BITMAPFILEHEADER),   &dwWritten,   NULL);           
	//     д��λͼ�ļ���������           
	WriteFile(fh,   (LPSTR)lpbi,   dwDIBSize,   &dwWritten,   NULL);           
	//���               
	GlobalUnlock(hDib);           
	GlobalFree(hDib);           
	CloseHandle(fh);           

	return     TRUE; 
}

HBITMAP CApiWinScreenShot::CopyScreenToBitmap( LPRECT lpRect )
{
	HDC hScrDC, hMemDC; 
	// ��Ļ���ڴ��豸������ 
	HBITMAP hBitmap, hOldBitmap; 
	// λͼ��� 
	int nX, nY, nX2, nY2; 
	// ѡ���������� 
	int nWidth, nHeight; 
	// λͼ��Ⱥ͸߶� 
	int xScrn, yScrn; 
	// ��Ļ�ֱ���

	// ȷ��ѡ������Ϊ�վ��� 
	if (IsRectEmpty(lpRect)) 
		return NULL; 
	//Ϊ��Ļ�����豸������ 
	hScrDC = CreateDC(_T("DISPLAY"), NULL, NULL, NULL); 
	//Ϊ��Ļ�豸�����������ݵ��ڴ��豸������ 
	hMemDC = CreateCompatibleDC(hScrDC); 
	// ���ѡ���������� 
	nX = lpRect->left; 
	nY = lpRect->top; 
	nX2 = lpRect->right; 
	nY2 = lpRect->bottom; 
	// �����Ļ�ֱ��� 
	xScrn = GetDeviceCaps(hScrDC, HORZRES); 
	yScrn = GetDeviceCaps(hScrDC, VERTRES); 
	//ȷ��ѡ�������ǿɼ��� 
	if (nX <0) 
		nX = 0; 
	if (nY <0) 
		nY = 0; 
	if (nX2 > xScrn) 
		nX2 = xScrn; 
	if (nY2 > yScrn) 
		nY2 = yScrn; 
	nWidth = nX2 - nX; 
	nHeight = nY2 - nY; 
	// ����һ������Ļ�豸��������ݵ�λͼ 
	hBitmap = CreateCompatibleBitmap 
		(hScrDC, nWidth, nHeight); 
	// ����λͼѡ���ڴ��豸�������� 
	hOldBitmap = (HBITMAP)SelectObject(hMemDC, hBitmap); 
	// ����Ļ�豸�����������ڴ��豸�������� 
	BitBlt(hMemDC, 0, 0, nWidth, nHeight, 
		hScrDC, nX, nY, SRCCOPY); 
	//�õ���Ļλͼ�ľ�� 
	hBitmap = (HBITMAP)SelectObject(hMemDC, hOldBitmap); 
	//��� 
	DeleteDC(hScrDC); 
	DeleteDC(hMemDC); 
	// ����λͼ��� 
	return hBitmap; 
}


int CApiWinScreenShot::GetEncoderClsid( const WCHAR* format, CLSID* pClsid )
{
	UINT  num = 0;          // number of image encoders
	UINT  size = 0;         // size of the image encoder array in bytes

	ImageCodecInfo* pImageCodecInfo = NULL;

	//2.��ȡGDI+֧�ֵ�ͼ���ʽ�������������Լ�ImageCodecInfo����Ĵ�Ŵ�С
	GetImageEncodersSize(&num, &size);
	if(size == 0)
		return -1;  // Failure

	//3.ΪImageCodecInfo����������ռ�
	pImageCodecInfo = (ImageCodecInfo*)(malloc(size));
	if(pImageCodecInfo == NULL)
		return -1;  // Failure

	//4.��ȡ���е�ͼ���������Ϣ
	GetImageEncoders(num, size, pImageCodecInfo);

	//5.���ҷ��ϵ�ͼ���������Clsid
	for(UINT j = 0; j < num; ++j)
	{
		if( wcscmp(pImageCodecInfo[j].MimeType, format) == 0 )
		{
			*pClsid = pImageCodecInfo[j].Clsid;
			free(pImageCodecInfo);
			return j;  // Success
		}    
	}

	//6.�ͷŲ���3������ڴ�
	free(pImageCodecInfo);
	return -1;  // Failure
}


BOOL CApiWinScreenShot::ConvertToPng(const std::string& sFileNameBmp,const std::string& sFileNamePng)
{
	GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR gdiplusToken;
	WCHAR source_file[256]={0};//Ŀ���ļ�
	WCHAR out_file[256]={0};//����ļ�
	size_t converted = 0;
	mbstowcs_s(&converted, source_file,	sFileNameBmp.length()+1, sFileNameBmp.c_str(), _TRUNCATE);
	mbstowcs_s(&converted, out_file,	sFileNamePng.length()+1, sFileNamePng.c_str(), _TRUNCATE);
	//1.��ʼ��GDI+���Ա������GDI+�������Գɹ�����
	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
	CLSID   encoderClsid;
	Status  stat;
	//7.����Image���󲢼���ͼƬ
	Image*   image = new Image(source_file);
	// Get the CLSID of the PNG encoder.
	GetEncoderClsid(L"image/png", &encoderClsid);
	//8.����Image.Save��������ͼƬ��ʽת�������Ѳ���3)�õ���ͼ�������Clsid���ݸ���
	stat = image->Save(out_file, &encoderClsid, NULL);
	//9.�ͷ�Image����
	delete image;
	//10.��������GDI+��Դ
	GdiplusShutdown(gdiplusToken);
	return TRUE;
}

RECT CApiWinScreenShot::GetWindowsRect( HWND hwnd )
{
	::RECT rect;
	::GetWindowRect(hwnd,&rect);
	return rect;
}

#endif
