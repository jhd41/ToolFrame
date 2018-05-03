#pragma once
//本页主要完成 代码在各个平台 以及 各个VS版本间的适配

//本代码框架主要为VS2012服务，我们首要保证此代码在VS2012下编译无警告 编译正常。
//在以上的基础上 才来兼容对2003、2005、VS2008 以及其他平台的支持

//平台适配
//适配Linux
#if MACRO_TARGET_OS == MACRO_OS_LINUX
	#define __cdecl 
	#define nullptr 0
	typedef unsigned int        UINT32, *PUINT32 ,UINT_PTR;
	#include "MacroAdapterMicroSoftFun.h"
#endif // Linux

//适配IOS
#if MACRO_TARGET_OS == MACRO_OS_IOS
	#define __cdecl 
	//#define nullptr 0
	typedef unsigned int        UINT32, *PUINT32 ,UINT_PTR;
	#include "MacroAdapterMicroSoftFun.h"
#endif //IOS

//适配Android
#if MACRO_TARGET_OS == MACRO_OS_ANDROID
// 	#if  MACRO_TARGET_STDC < MACRO_STDC_C11
// 		#define nullptr 0
// 	#endif
	#define __cdecl
	typedef unsigned int        UINT32, *PUINT32 ,UINT_PTR;
	#include "MacroAdapterMicroSoftFun.h"
#endif // Android

//适配Windows
#if MACRO_TARGET_OS == MACRO_OS_WINDOWS
	//版本匹配
	#ifdef _WIN64
		typedef __int64 INT_PTR, *PINT_PTR;
		typedef unsigned __int64 UINT_PTR, *PUINT_PTR;
	#else
		typedef unsigned int  UINT_PTR;
	#endif

	//VS版本适配
	#ifdef _MSC_VER

		#if _MSC_VER<1400 //消除VS2005版本前的缺陷
			#define for  if(0);else for   //不用考虑效率，编译器自动优化掉无用的if(0) 不懂问百度
			
			#include "MacroAdapterMicroSoftFun.h"
		#endif // _MSC_VER<1400

		#if _MSC_VER>=1400 //VS2005版本后,几个安全函数

		#endif	// _MSC_VER>=1400

	#endif	// _MSC_VER

	#ifndef _WIN32_WINNT
		#define _WIN32_WINNT 0x0501
	#endif
#endif	//OS_WINDOWS
