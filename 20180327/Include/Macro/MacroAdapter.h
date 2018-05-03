#pragma once
//��ҳ��Ҫ��� �����ڸ���ƽ̨ �Լ� ����VS�汾�������

//����������ҪΪVS2012����������Ҫ��֤�˴�����VS2012�±����޾��� ����������
//�����ϵĻ����� �������ݶ�2003��2005��VS2008 �Լ�����ƽ̨��֧��

//ƽ̨����
//����Linux
#if MACRO_TARGET_OS == MACRO_OS_LINUX
	#define __cdecl 
	#define nullptr 0
	typedef unsigned int        UINT32, *PUINT32 ,UINT_PTR;
	#include "MacroAdapterMicroSoftFun.h"
#endif // Linux

//����IOS
#if MACRO_TARGET_OS == MACRO_OS_IOS
	#define __cdecl 
	//#define nullptr 0
	typedef unsigned int        UINT32, *PUINT32 ,UINT_PTR;
	#include "MacroAdapterMicroSoftFun.h"
#endif //IOS

//����Android
#if MACRO_TARGET_OS == MACRO_OS_ANDROID
// 	#if  MACRO_TARGET_STDC < MACRO_STDC_C11
// 		#define nullptr 0
// 	#endif
	#define __cdecl
	typedef unsigned int        UINT32, *PUINT32 ,UINT_PTR;
	#include "MacroAdapterMicroSoftFun.h"
#endif // Android

//����Windows
#if MACRO_TARGET_OS == MACRO_OS_WINDOWS
	//�汾ƥ��
	#ifdef _WIN64
		typedef __int64 INT_PTR, *PINT_PTR;
		typedef unsigned __int64 UINT_PTR, *PUINT_PTR;
	#else
		typedef unsigned int  UINT_PTR;
	#endif

	//VS�汾����
	#ifdef _MSC_VER

		#if _MSC_VER<1400 //����VS2005�汾ǰ��ȱ��
			#define for  if(0);else for   //���ÿ���Ч�ʣ��������Զ��Ż������õ�if(0) �����ʰٶ�
			
			#include "MacroAdapterMicroSoftFun.h"
		#endif // _MSC_VER<1400

		#if _MSC_VER>=1400 //VS2005�汾��,������ȫ����

		#endif	// _MSC_VER>=1400

	#endif	// _MSC_VER

	#ifndef _WIN32_WINNT
		#define _WIN32_WINNT 0x0501
	#endif
#endif	//OS_WINDOWS
