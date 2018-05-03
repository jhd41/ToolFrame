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
	//当前分辨率下每象素所占字节数       
	int     iBits;       
	//位图中每象素所占字节数       
	WORD     wBitCount;       
	//定义调色板大小，     位图中像素字节大小     ，位图文件大小     ，     写入文件字节数           
	DWORD     dwPaletteSize=0,   dwBmBitsSize=0,   dwDIBSize=0,   dwWritten=0;           
	//位图属性结构           
	BITMAP     Bitmap;               
	//位图文件头结构       
	BITMAPFILEHEADER     bmfHdr;               
	//位图信息头结构           
	BITMAPINFOHEADER     bi;               
	//指向位图信息头结构               
	LPBITMAPINFOHEADER     lpbi;               
	//定义文件，分配内存句柄，调色板句柄           
	HANDLE     fh,   hDib,   hPal,hOldPal=NULL;           

	//计算位图文件每个像素所占字节数           
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

	//为位图内容分配内存           
	hDib  = GlobalAlloc(GHND,dwBmBitsSize+dwPaletteSize+sizeof(BITMAPINFOHEADER));           
	lpbi  = (LPBITMAPINFOHEADER)GlobalLock(hDib);           
	*lpbi  = bi;           

	//     处理调色板               
	hPal  = GetStockObject(DEFAULT_PALETTE);           
	if (hPal)           
	{           
		hDC  = ::GetDC(NULL);           
		hOldPal = ::SelectPalette(hDC,(HPALETTE)hPal, FALSE);           
		RealizePalette(hDC);           
	}       

	//     获取该调色板下新的像素值           
	GetDIBits(hDC,hBitmap, 0,(UINT)Bitmap.bmHeight,
		(LPSTR)lpbi+ sizeof(BITMAPINFOHEADER)+dwPaletteSize, 
		(BITMAPINFO *)lpbi, DIB_RGB_COLORS);           

	//恢复调色板               
	if (hOldPal)           
	{           
		::SelectPalette(hDC,   (HPALETTE)hOldPal,   TRUE);           
		RealizePalette(hDC);           
		::ReleaseDC(NULL,   hDC);           
	}           
	
	//创建位图文件               
	fh  = CreateFile(ApiWin::ToStringT(sFileName).c_str(),   GENERIC_WRITE,0,   NULL,   CREATE_ALWAYS,         
		FILE_ATTRIBUTE_NORMAL | FILE_FLAG_SEQUENTIAL_SCAN,   NULL);           

	if (fh     ==  INVALID_HANDLE_VALUE)         return     FALSE;           

	//     设置位图文件头           
	bmfHdr.bfType  = 0x4D42;     //     "BM"           
	dwDIBSize  = sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER)+dwPaletteSize+dwBmBitsSize;               
	bmfHdr.bfSize  = dwDIBSize;           
	bmfHdr.bfReserved1  = 0;           
	bmfHdr.bfReserved2  = 0;           
	bmfHdr.bfOffBits  = (DWORD)sizeof(BITMAPFILEHEADER)+(DWORD)sizeof(BITMAPINFOHEADER)+dwPaletteSize;           
	//     写入位图文件头           
	WriteFile(fh,   (LPSTR)&bmfHdr,   sizeof(BITMAPFILEHEADER),   &dwWritten,   NULL);           
	//     写入位图文件其余内容           
	WriteFile(fh,   (LPSTR)lpbi,   dwDIBSize,   &dwWritten,   NULL);           
	//清除               
	GlobalUnlock(hDib);           
	GlobalFree(hDib);           
	CloseHandle(fh);           

	return     TRUE; 
}

HBITMAP CApiWinScreenShot::CopyScreenToBitmap( LPRECT lpRect )
{
	HDC hScrDC, hMemDC; 
	// 屏幕和内存设备描述表 
	HBITMAP hBitmap, hOldBitmap; 
	// 位图句柄 
	int nX, nY, nX2, nY2; 
	// 选定区域坐标 
	int nWidth, nHeight; 
	// 位图宽度和高度 
	int xScrn, yScrn; 
	// 屏幕分辨率

	// 确保选定区域不为空矩形 
	if (IsRectEmpty(lpRect)) 
		return NULL; 
	//为屏幕创建设备描述表 
	hScrDC = CreateDC(_T("DISPLAY"), NULL, NULL, NULL); 
	//为屏幕设备描述表创建兼容的内存设备描述表 
	hMemDC = CreateCompatibleDC(hScrDC); 
	// 获得选定区域坐标 
	nX = lpRect->left; 
	nY = lpRect->top; 
	nX2 = lpRect->right; 
	nY2 = lpRect->bottom; 
	// 获得屏幕分辨率 
	xScrn = GetDeviceCaps(hScrDC, HORZRES); 
	yScrn = GetDeviceCaps(hScrDC, VERTRES); 
	//确保选定区域是可见的 
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
	// 创建一个与屏幕设备描述表兼容的位图 
	hBitmap = CreateCompatibleBitmap 
		(hScrDC, nWidth, nHeight); 
	// 把新位图选到内存设备描述表中 
	hOldBitmap = (HBITMAP)SelectObject(hMemDC, hBitmap); 
	// 把屏幕设备描述表拷贝到内存设备描述表中 
	BitBlt(hMemDC, 0, 0, nWidth, nHeight, 
		hScrDC, nX, nY, SRCCOPY); 
	//得到屏幕位图的句柄 
	hBitmap = (HBITMAP)SelectObject(hMemDC, hOldBitmap); 
	//清除 
	DeleteDC(hScrDC); 
	DeleteDC(hMemDC); 
	// 返回位图句柄 
	return hBitmap; 
}


int CApiWinScreenShot::GetEncoderClsid( const WCHAR* format, CLSID* pClsid )
{
	UINT  num = 0;          // number of image encoders
	UINT  size = 0;         // size of the image encoder array in bytes

	ImageCodecInfo* pImageCodecInfo = NULL;

	//2.获取GDI+支持的图像格式编码器种类数以及ImageCodecInfo数组的存放大小
	GetImageEncodersSize(&num, &size);
	if(size == 0)
		return -1;  // Failure

	//3.为ImageCodecInfo数组分配足额空间
	pImageCodecInfo = (ImageCodecInfo*)(malloc(size));
	if(pImageCodecInfo == NULL)
		return -1;  // Failure

	//4.获取所有的图像编码器信息
	GetImageEncoders(num, size, pImageCodecInfo);

	//5.查找符合的图像编码器的Clsid
	for(UINT j = 0; j < num; ++j)
	{
		if( wcscmp(pImageCodecInfo[j].MimeType, format) == 0 )
		{
			*pClsid = pImageCodecInfo[j].Clsid;
			free(pImageCodecInfo);
			return j;  // Success
		}    
	}

	//6.释放步骤3分配的内存
	free(pImageCodecInfo);
	return -1;  // Failure
}


BOOL CApiWinScreenShot::ConvertToPng(const std::string& sFileNameBmp,const std::string& sFileNamePng)
{
	GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR gdiplusToken;
	WCHAR source_file[256]={0};//目标文件
	WCHAR out_file[256]={0};//输出文件
	size_t converted = 0;
	mbstowcs_s(&converted, source_file,	sFileNameBmp.length()+1, sFileNameBmp.c_str(), _TRUNCATE);
	mbstowcs_s(&converted, out_file,	sFileNamePng.length()+1, sFileNamePng.c_str(), _TRUNCATE);
	//1.初始化GDI+，以便后续的GDI+函数可以成功调用
	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
	CLSID   encoderClsid;
	Status  stat;
	//7.创建Image对象并加载图片
	Image*   image = new Image(source_file);
	// Get the CLSID of the PNG encoder.
	GetEncoderClsid(L"image/png", &encoderClsid);
	//8.调用Image.Save方法进行图片格式转换，并把步骤3)得到的图像编码器Clsid传递给它
	stat = image->Save(out_file, &encoderClsid, NULL);
	//9.释放Image对象
	delete image;
	//10.清理所有GDI+资源
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
