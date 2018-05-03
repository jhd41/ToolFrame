#pragma once
#include <memory.h>
#include <time.h>
#include <stdarg.h>
#include <string.h>
#include <stdio.h>

#define sscanf_s sscanf

inline int __cdecl memcpy_s( void* pDes, int nSizeDes, const void* pSrc, int nSizeSrc )
{
	memcpy(pDes,pSrc,nSizeSrc);
	return 0;
}

inline int __cdecl strcpy_s( void* pDes, int nSizeSrc, const void* pSrc )
{
	memcpy(pDes,pSrc,nSizeSrc);
	return 0;
}

#if MACRO_TARGET_OS == MACRO_OS_WINDOWS || MACRO_TARGET_OS == MACRO_OS_IOS

inline int __cdecl localtime_s( tm* pTm,time_t* pTime )
{
	tm* pTemp = localtime(pTime);
	if (!pTemp)return -1;

	memcpy(pTm,pTemp,sizeof(tm));
	return 0;
}
#endif

#if MACRO_TARGET_OS == MACRO_OS_ANDROID || MACRO_TARGET_OS == MACRO_OS_LINUX
inline int __cdecl localtime_s( tm* pTm,time_t* pTime )
{
	localtime_r(pTime,pTm);
	return 0;
}
#endif

inline int __cdecl gmtime_s( tm* pTm,time_t* pTime )
{
	tm* pTemp = gmtime(pTime);
	if (!pTemp)return -1;

	memcpy(pTm,pTemp,sizeof(tm));
	return 0;
}

inline void __cdecl _snprintf_s( char* pDes,int nSizeIn,int nDesSize,const char* szFormat,... )
{
	va_list vaList;
	va_start(vaList, szFormat);
	vsprintf(pDes,szFormat,vaList);
	va_end(vaList);
}

inline void __cdecl sprintf_s(char* pDes, const char* szFormat, ...)
{
	va_list vaList;
	va_start(vaList, szFormat);
	vsprintf(pDes, szFormat, vaList);
	va_end(vaList);
}

inline int _snprintf( char *pDes, size_t sizeInBytes, const char *szFormat, ... )
{
	va_list vaList;
	va_start(vaList, szFormat);
	int nError = vsprintf(pDes,szFormat,vaList);
	va_end(vaList);
	return nError;
}

inline int sprintf_s( char *pDes, size_t sizeInBytes, const char *szFormat, ... )
{
	va_list vaList;
	va_start(vaList, szFormat);
	int nError = vsprintf(pDes,szFormat,vaList);
	va_end(vaList);
	return nError;
}

inline char* strtok_s( char* szStr,const char* szDelim,char ** szContext )
{
	*szContext = strtok(szStr,szDelim) ;
	return *szContext;
}

