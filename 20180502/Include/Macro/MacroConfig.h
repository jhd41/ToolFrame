#pragma once
//��
//ע��:��д�������Ա�����Ҫ�İ汾
//////////////////////////////////////////////////////////////////////////
//����

//����ʹ�ò���ƽ̨(MACRO_TARGET_OS)
#define MACRO_OS_UNKNOWN	0
#define MACRO_OS_IOS		1	//IOS
#define MACRO_OS_ANDROID	2	//��׿
#define MACRO_OS_WINDOWS	3	//Windows
#define MACRO_OS_MARMALADE	4	//MARMALADE(һ������ƽ̨)
#define MACRO_OS_LINUX		5	//Linux
#define MACRO_OS_BADA		6	//BADA (�����з������������ֻ�ƽ̨)
#define MACRO_OS_BLACKBERRY 7	//��ݮ
#define MACRO_OS_MAC        8	//ƻ��
#define MACRO_OS_NACL       9
#define MACRO_OS_EMSCRIPTEN 10
#define MACRO_OS_TIZEN      11
#define MACRO_OS_QT5        12
#define MACRO_OS_WP8        13	//wphone
#define MACRO_OS_WINRT      14	//Arm�汾win
#define MACRO_OS_MAX		14	//�����ٽ���

//�������汾����(MACRO_TARGET_VER)
#define MACRO_VER_UNKNOWN	0
#define MACRO_VER_DEBUG		1	//���԰汾
#define MACRO_VER_RELEASE	2	//�����汾
#define MACRO_VER_MAX		2	//�����ٽ���

//�������λ��(MACRO_TARGET_BIT)
#define MACRO_BIT_UNKNOWN	0
#define MACRO_BIT_32		1	//32λ�汾
#define MACRO_BIT_64		2	//64λ�汾
#define MACRO_BIT_MAX		2	//�����ٽ���

//����ܹ���(MACRO_TARGET_ARCH)
#define MACRO_ARCH_UNKNOWN	0
#define MACRO_ARCH_ARM		1	//�ƶ��汾
#define MACRO_ARCH_X86		2	//PC�汾
#define MACRO_ARCH_MAX		2	//�����ٽ���

//�����ַ���(MACRO_TARGET_FONT)
#define MACRO_FONT_UNKNOWN	0
#define MACRO_FONT_ANSI		1
#define MACRO_FONT_UNICODE	2
#define MACRO_FONT_MAX		2	//�����ٽ���

//�����������(MACRO_TARGET_CODE)
#define MACRO_CODE_UNKNOWN		0
#define MACRO_CODE_STD_C		1	//��׼C����
#define MACRO_CODE_C_PLUS_PLUS	2	//C++����
#define MACRO_CODE_OBJ_C		3	//ObjC����
#define MACRO_CODE_MAX			3	//�����ٽ���

//����Ŀ���ļ�(MACRO_TARGET_FILE)
#define MACRO_FILE_UNKNOWN		0
#define MACRO_FILE_EXE			1	//��ִ���ļ�
#define MACRO_FILE_LIB			2	//��̬���ӿ�
#define MACRO_FILE_DLL			3	//��̬���ӿ�
#define MACRO_FILE_MAX			3

//���������(MACRO_TARGET_COMPILER)
#define MACRO_COMPILER_UNKNOWN	 0
#define MACRO_COMPILER_VC		 1
#define MACRO_COMPILER_GCC		 2
#define MACRO_COMPILER_SUNPRO_CC 3
#define MACRO_COMPILER_MAX		 3

//����C++��׼(MACRO_TARGET_STDC)
#define MACRO_STDC_UNKNOWN	0
#define MACRO_STDC_C89		1
#define MACRO_STDC_C89_1	2
#define MACRO_STDC_C99		3
#define MACRO_STDC_C11		4
#define MACRO_STDC_MAX		4

//�����û�����
//////////////////////////////////////////////////////////////////////////
#include "MacroUserConfig.h"

//����û�����
#ifdef MACRO_TARGET_CODE
	#error MACRO_TARGET_CODE Must not Defined
#endif //MACRO_TARGET_CODE
#ifndef MACRO_LIB_BOOST
	#error MACRO_LIB_BOOST Must Be Defined.(please define MACRO_LIB_BOOST)
#endif // MACRO_LIB_BOOST
#ifndef MACRO_LIB_TINYXML
	#error MACRO_LIB_TINYXML Must Be Defined.(please define MACRO_LIB_TINYXML)
#endif //MACRO_LIB_TINYXML

//����δ�����
//////////////////////////////////////////////////////////////////////////
//�������ϵͳ
#ifndef MACRO_TARGET_OS
	#define MACRO_TARGET_OS			MACRO_OS_UNKNOWN
#endif // MACRO_TARGET_OS

//�������汾
#ifndef MACRO_TARGET_VER
	#define MACRO_TARGET_VER		MACRO_VER_UNKNOWN
#endif // MACRO_TARGET_VER

//�������λ��
#ifndef MACRO_TARGET_BIT
	#define MACRO_TARGET_BIT		MACRO_BIT_UNKNOWN
#endif // MACRO_TARGET_BIT

//����ܹ���
#ifndef MACRO_TARGET_ARCH
	#define MACRO_TARGET_ARCH		MACRO_ARCH_UNKNOWN
#endif // MACRO_TARGET_ARCH

//�����ַ���
#ifndef MACRO_TARGET_FONT
	#define MACRO_TARGET_FONT		MACRO_FONT_UNKNOWN
#endif // MACRO_TARGET_FONT

//�����������
#ifndef MACRO_TARGET_CODE
	#define MACRO_TARGET_CODE		MACRO_CODE_UNKNOWN
#endif // MACRO_TARGET_CODE

//����Ŀ���ļ�
#ifndef MACRO_TARGET_FILE
	#define MACRO_TARGET_FILE		MACRO_FILE_UNKNOWN
#endif // MACRO_TARGET_FILE

//����Ŀ�������
#ifndef MACRO_TARGET_COMPILER
	#define MACRO_TARGET_COMPILER	MACRO_COMPILER_UNKNOWN
#endif // MACRO_TARGET_COMPILER

//����Ŀ���׼
#ifndef MACRO_TARGET_STDC
	#define MACRO_TARGET_STDC		MACRO_STDC_UNKNOWN
#endif // MACRO_TARGET_STDC

//�����Ѷ�����Ϣ�Ƶ�������Ϣ
//////////////////////////////////////////////////////////////////////////

//COCOS2D_DEBUG
#if defined(COCOS2D_DEBUG)
	//�Ƶ�ʹ����cocos2dx��
	#if !defined(MACRO_LIB_COCOS2D)
	#define MACRO_LIB_COCOS2D
	#endif
	
	//�Ƶ�������԰汾
	#if !MACRO_TARGET_VER
	#undef  MACRO_TARGET_VER
	#define MACRO_TARGET_VER MACRO_VER_DEBUG
	#endif

#endif //defined(COCOS2D_DEBUG)

//CC_TARGET_OS_IPHONE
#if defined(CC_TARGET_OS_IPHONE)
	//�Ƶ�ʹ����cocos2dx��
	#if !defined(MACRO_LIB_COCOS2D)
	#define MACRO_LIB_COCOS2D
	#endif

	//�Ƶ�Ŀ��ƽ̨
	#if !MACRO_TARGET_OS
	#undef  MACRO_TARGET_OS
	#define MACRO_TARGET_OS MACRO_OS_IOS
	#endif

	//�Ƶ�CPU�ܹ�
	#if !MACRO_TARGET_ARCH
	#undef  MACRO_TARGET_ARCH
	#define MACRO_TARGET_ARCH MACRO_ARCH_ARM
	#endif
#endif //defined(CC_TARGET_OS_IPHONE)

//_MFC_VER
#if defined(_MFC_VER)

#if !defined(MACRO_LIB_MFC)
#define MACRO_LIB_MFC
#endif

#endif //defined(_MFC_VER)

//_WIN64 WIN64(��������win32�ж�)
#if defined(_WIN64) || defined(WIN64)
	//�Ƶ���ƽ̨
	#if !MACRO_TARGET_OS
	#undef  MACRO_TARGET_OS
	#define MACRO_TARGET_OS MACRO_OS_WINDOWS
	#endif

	//�Ƶ���64λ
	#if !MACRO_TARGET_BIT
	#undef  MACRO_TARGET_BIT
	#define MACRO_TARGET_BIT MACRO_BIT_64
	#endif

	//�Ƶ�CPU�ܹ�
	#if !MACRO_TARGET_ARCH
	#undef  MACRO_TARGET_ARCH
	#define MACRO_TARGET_ARCH MACRO_ARCH_X86
	#endif
#endif

//WIN32 _WIN32
#if defined(WIN32) || defined(_WIN32)
	//�Ƶ���ƽ̨
	#if !MACRO_TARGET_OS
	#undef  MACRO_TARGET_OS
	#define MACRO_TARGET_OS MACRO_OS_WINDOWS
	#endif

	//�Ƶ���32λ
	#if !MACRO_TARGET_BIT
	#undef  MACRO_TARGET_BIT
	#define MACRO_TARGET_BIT MACRO_BIT_32
	#endif

	//�Ƶ�CPU�ܹ�
	#if !MACRO_TARGET_ARCH
	#undef  MACRO_TARGET_ARCH
	#define MACRO_TARGET_ARCH MACRO_ARCH_X86
	#endif
#endif

//_WINDOWS
#if defined(_WINDOWS)
	//�Ƶ���ƽ̨
	#if !MACRO_TARGET_OS
	#undef  MACRO_TARGET_OS
	#define MACRO_TARGET_OS MACRO_OS_WINDOWS
	#endif

	//�Ƶ�CPU�ܹ�
	#if !MACRO_TARGET_ARCH
	#undef  MACRO_TARGET_ARCH
	#define MACRO_TARGET_ARCH MACRO_ARCH_X86
	#endif
#endif

//TARGET_OS_IPHONE __IPHONE__
#if defined(TARGET_OS_IPHONE)|| defined(__IPHONE__)
	//�Ƶ���ƽ̨
	#if !MACRO_TARGET_OS
	#undef  MACRO_TARGET_OS
	#define MACRO_TARGET_OS MACRO_OS_IOS
	#endif

	//�Ƶ���CPU�ܹ�
	#if !MACRO_TARGET_ARCH
	#undef  MACRO_TARGET_ARCH
	#define MACRO_TARGET_ARCH MACRO_ARCH_ARM
	#endif
#endif

//TARGET_IPHONE_SIMULATOR
#if defined(TARGET_IPHONE_SIMULATOR)
	//�Ƶ���ƽ̨
	#if !MACRO_TARGET_OS
	#undef  MACRO_TARGET_OS
	#define MACRO_TARGET_OS MACRO_OS_IOS
	#endif

	//�Ƶ���CPU�ܹ�
	#if !MACRO_TARGET_ARCH
	#undef  MACRO_TARGET_ARCH
	#define MACRO_TARGET_ARCH MACRO_ARCH_X86
	#endif
#endif

//ANDROID
#if defined(ANDROID)
	//�Ƶ���ƽ̨
	#if !MACRO_TARGET_OS
	#undef  MACRO_TARGET_OS
	#define MACRO_TARGET_OS MACRO_OS_ANDROID
	#endif

	//�Ƶ���CPU�ܹ�
	#if !MACRO_TARGET_ARCH
	#undef  MACRO_TARGET_ARCH
	#define MACRO_TARGET_ARCH MACRO_ARCH_ARM
	#endif
#endif

// WinRT (Windows Store App)
#if defined(WINRT)
#undef  MACRO_TARGET_OS
#define MACRO_TARGET_OS			MACRO_OS_WINRT
#endif

// WP8 (Windows Phone 8 App)
#if defined(WP8)
	#undef  MACRO_TARGET_OS
	#define MACRO_TARGET_OS			MACRO_OS_WP8
#endif

//wophone
#if ! MACRO_TARGET_OS && defined(_TRANZDA_VM_)
	#undef  MACRO_TARGET_OS
	#define MACRO_TARGET_OS         MACRO_OS_WOPHONE
#endif

//linux
#if ! MACRO_TARGET_OS && defined(LINUX)
#undef  MACRO_TARGET_OS
#define MACRO_TARGET_OS         MACRO_OS_LINUX
#endif

//marmalade
#if ! MACRO_TARGET_OS && defined(MARMALADE)
#undef  MACRO_TARGET_OS
#define MACRO_TARGET_OS         MACRO_OS_MARMALADE
#endif

//bada
#if ! MACRO_TARGET_OS && defined(SHP)
#undef  MACRO_TARGET_OS
#define MACRO_TARGET_OS         MACRO_OS_BADA
#endif

//qnx
#if ! MACRO_TARGET_OS && defined(__QNX__)
	#undef  MACRO_TARGET_OS
	#define MACRO_TARGET_OS         MACRO_OS_QNX
#endif

// airplay
#if ! MACRO_TARGET_OS && defined(AIRPLAY)
	#undef  MACRO_TARGET_OS
	#define MACRO_TARGET_OS         MACRO_OS_AIRPLAY
#endif

//DEBUG _DEBUG
#if defined(DEBUG) || defined(_DEBUG)
	//�Ƶ�������汾
	#if !MACRO_TARGET_VER
		#undef  MACRO_TARGET_VER
		#define MACRO_TARGET_VER MACRO_VER_DEBUG
	#endif
#endif

//NDEBUG
#if defined(NDEBUG)
	//�Ƶ�������汾
	#if !MACRO_TARGET_VER
		#undef  MACRO_TARGET_VER
		#define MACRO_TARGET_VER MACRO_VER_RELEASE
	#endif
#endif

//UNICODE
#if defined(UNICODE)
	//�Ƶ����ַ���
	#if !MACRO_TARGET_FONT
		#undef  MACRO_TARGET_FONT
		#define MACRO_TARGET_FONT MACRO_FONT_UNICODE
	#endif
#endif

//__LP64__
#if defined(__LP64__) && __LP64__
	//�Ƶ�������λ��
	#if !MACRO_TARGET_BIT
		#undef  MACRO_TARGET_BIT
		#define MACRO_TARGET_BIT MACRO_BIT_64
	#endif
#endif

//__STDC__
#if defined(__STDC__)
	//�Ƶ�����������
	#if !MACRO_TARGET_CODE
		#undef  MACRO_TARGET_CODE
		#define MACRO_TARGET_CODE MACRO_CODE_STD_C
	#endif
#endif

//__cplusplus
#if defined(__cplusplus)
	//�Ƶ�����������
	#if !MACRO_TARGET_CODE
		#undef  MACRO_TARGET_CODE
		#define MACRO_TARGET_CODE MACRO_CODE_C_PLUS_PLUS
	#endif
#endif

//__OBJC__
#if defined(__OBJC__)
	//�Ƶ�����������
	#if !MACRO_TARGET_CODE
		#undef  MACRO_TARGET_CODE
		#define MACRO_TARGET_CODE MACRO_CODE_OBJ_C
	#endif
#endif

//_USRDLL __DLL__
#if defined(_USRDLL) || defined(__DLL__)
	//�Ƶ���Ŀ���ļ�
	#if !MACRO_TARGET_FILE
		#undef  MACRO_TARGET_FILE
		#define MACRO_TARGET_FILE MACRO_FILE_DLL
	#endif
#endif

//_LIB __LIB__
#if defined(_LIB) || defined(__LIB__)
	//�Ƶ���Ŀ���ļ�
	#if !MACRO_TARGET_FILE
		#undef  MACRO_TARGET_FILE
		#define MACRO_TARGET_FILE MACRO_FILE_LIB
	#endif
#endif

//SS_MAKEDLL
#if defined(SS_MAKEDLL)
	//�Ƶ���Ŀ���ļ�
	#if !MACRO_TARGET_FILE
		#undef  MACRO_TARGET_FILE
		#define MACRO_TARGET_FILE MACRO_FILE_DLL
	#endif
#endif

//_MSC_VER
#if defined(_MSC_VER)
	//�Ƶ���Ŀ�������
	#if !MACRO_TARGET_COMPILER
	#undef  MACRO_TARGET_COMPILER
	#define MACRO_TARGET_COMPILER MACRO_COMPILER_VC
	#endif
#endif

//__GNUC__
#if defined(__GNUC__)
	//�Ƶ���Ŀ�������
	#if !MACRO_TARGET_COMPILER
	#undef  MACRO_TARGET_COMPILER
	#define MACRO_TARGET_COMPILER MACRO_COMPILER_GCC
	#endif
#endif

//_SUNPRO_C __SUNPRO_CC
#if defined(_SUNPRO_C) || defined(__SUNPRO_CC)
	//�Ƶ���Ŀ�������
	#if !MACRO_TARGET_COMPILER
	#undef  MACRO_TARGET_COMPILER
	#define MACRO_TARGET_COMPILER MACRO_COMPILER_SUNPRO_CC
	#endif
#endif

//__cplusplus 201103L
#if __cplusplus == 201103L
	//�Ƶ���Ŀ��C++��׼
	#if !MACRO_TARGET_STDC
	#undef  MACRO_TARGET_STDC
	#define MACRO_TARGET_STDC MACRO_STDC_C11
	#endif
#endif

//__cplusplus 199711L
#if __cplusplus == 199711L
	//�Ƶ���Ŀ��C++��׼
	#if !MACRO_TARGET_STDC
	#undef  MACRO_TARGET_STDC
	#define MACRO_TARGET_STDC MACRO_STDC_C99
	#endif
#endif

//__STDC__
#if defined(__STDC__)
	//�Ƶ���Ŀ��C++��׼
	#if !MACRO_TARGET_STDC
		#undef  MACRO_TARGET_STDC
	
		#if defined(__STDC_VERSION__) && __STDC_VERSION__>=201112L 
		/* ����C11��׼�Ĵ��� */ 
		#define MACRO_TARGET_STDC  MACRO_STDC_C11
		#elif defined(__STDC_VERSION__) && __STDC_VERSION__>=19901L   
		/* ����C99��׼�Ĵ��� */ 
		#define MACRO_TARGET_STDC  MACRO_STDC_C99
		#elif defined(__STDC__VERSION__) && __STDC__VERSION__>=199409L   
		/* ����C89������1��׼�Ĵ��� */ 
		#define MACRO_TARGET_STDC  MACRO_STDC_C89_1
		#else   
		/* ����C89������������1�ı�׼���� */ 
		#define MACRO_TARGET_STDC  MACRO_STDC_C89
		#endif  

	#endif
#endif
//����Ĭ��ȱʡֵ
//////////////////////////////////////////////////////////////////////////
#if !MACRO_TARGET_BIT
	#undef  MACRO_TARGET_BIT
	#define MACRO_TARGET_BIT  MACRO_BIT_32
#endif

#if !MACRO_TARGET_ARCH
	#undef  MACRO_TARGET_ARCH
	#define MACRO_TARGET_ARCH  MACRO_ARCH_X86
#endif

#if !MACRO_TARGET_VER//�����Ȼû��ȷ��������汾������Ϊ����release�汾
	#undef  MACRO_TARGET_VER
	#define MACRO_TARGET_VER	MACRO_VER_RELEASE
#endif

#if !MACRO_TARGET_FONT
	#undef  MACRO_TARGET_FONT
	#define MACRO_TARGET_FONT	MACRO_FONT_ANSI
#endif

#if !MACRO_TARGET_FILE
	#undef  MACRO_TARGET_FILE
	#define MACRO_TARGET_FILE  MACRO_FILE_EXE
#endif

//����
//////////////////////////////////////////////////////////////////////////
//���ƽ̨
#if !MACRO_TARGET_OS
	#error MACRO_TARGET_OS Error (please define MACRO_TARGET_OS)
#endif
#if (MACRO_TARGET_OS <= MACRO_OS_UNKNOWN) || (MACRO_TARGET_OS > MACRO_OS_MAX)
	#error MACRO_TARGET_OS Error (MACRO_TARGET_OS define error.)
#endif

//���汾
#if !MACRO_TARGET_VER
	#error MACRO_TARGET_VER Error (please define MACRO_TARGET_VER)
#endif
#if (MACRO_TARGET_VER <= MACRO_VER_UNKNOWN) || (MACRO_TARGET_VER > MACRO_VER_MAX)
	#error ACRO_TARGET_VER Error (MACRO_TARGET_VER define error.)
#endif

//���λ��
#if !MACRO_TARGET_BIT
#error MACRO_TARGET_BIT Error (please define MACRO_TARGET_BIT)
#endif

//���ܹ�
#if !MACRO_TARGET_ARCH
#error MACRO_TARGET_ARCH Error (please define MACRO_TARGET_ARCH)
#endif

//����ַ���
#if !MACRO_TARGET_FONT
#error MACRO_TARGET_FONT Error (please define MACRO_TARGET_FONT)
#endif
#if (MACRO_TARGET_FONT <= MACRO_FONT_UNKNOWN) || (MACRO_TARGET_FONT > MACRO_FONT_MAX)
#error MACRO_TARGET_FONT Error (MACRO_TARGET_FONT define error.)
#endif

//����������
#if !MACRO_TARGET_CODE
#error MACRO_TARGET_CODE Error (unkown MACRO_TARGET_CODE )
#endif
#if (MACRO_TARGET_CODE <= MACRO_CODE_UNKNOWN) || (MACRO_TARGET_CODE > MACRO_CODE_MAX)
#error MACRO_TARGET_CODE Error (MACRO_TARGET_CODE define error.)
#endif

//�������ļ�
#if !MACRO_TARGET_FILE
#error MACRO_TARGET_FILE Error (unkown MACRO_TARGET_FILE )
#endif
#if (MACRO_TARGET_FILE <= MACRO_FILE_UNKNOWN) || (MACRO_TARGET_FILE > MACRO_FILE_MAX)
#error MACRO_TARGET_FILE Error (MACRO_TARGET_FILE define error.)
#endif

//����������

//������˲��(������cocos2dx ֻ֧�� ios,android)
#ifdef MACRO_LIB_PLUGIN_UM
	#if !(defined(MACRO_LIB_COCOS2D) && (MACRO_TARGET_OS == MACRO_OS_IOS || MACRO_TARGET_OS == MACRO_OS_ANDROID))
		#error MACRO_LIB_PLUGIN_UM Error (need MACRO_LIB_COCOS2D and os in ios,android )
	#endif
#endif // MACRO_LIB_PLUGIN_UM

//���TalkingData���(������cocos2dx ֻ֧�� ios,android)
#ifdef MACRO_LIB_PLUGIN_TK
#if !(defined(MACRO_LIB_COCOS2D) && (MACRO_TARGET_OS == MACRO_OS_IOS || MACRO_TARGET_OS == MACRO_OS_ANDROID))
#error MACRO_LIB_PLUGIN_TK Error (need MACRO_LIB_COCOS2D and os in ios,android )
#endif
#endif // MACRO_LIB_PLUGIN_TK

//��ȫ ���ùؼ���
//////////////////////////////////////////////////////////////////////////
//��ȫ����汾
#if MACRO_TARGET_VER == MACRO_VER_DEBUG
	#ifndef _DEBUG
		#define _DEBUG
	#endif
	#ifndef DEBUG
		#define DEBUG
	#endif
#endif
#if MACRO_TARGET_VER == MACRO_VER_RELEASE
	#ifndef NDEBUG
		#define NDEBUG
	#endif
#endif

#if MACRO_TARGET_OS == MACRO_OS_WINDOWS
	#ifndef _WINDOWS
		#define _WINDOWS
	#endif
#endif

#if (MACRO_TARGET_OS == MACRO_OS_WINDOWS) && (MACRO_TARGET_BIT == MACRO_BIT_32)
	#ifndef WIN32
		#define WIN32
	#endif
	
	#ifndef _WIN32
		#define _WIN32
	#endif
#endif

#if (MACRO_TARGET_OS == MACRO_OS_WINDOWS) && (MACRO_TARGET_BIT == MACRO_BIT_64)
	#ifndef WIN64
		#define WIN64
	#endif

	#ifndef _WIN64
		#define _WIN64
	#endif
#endif

//����DLL����(δ����,���ڱ����߾�������STL,��STL��DLL�������������صĴ���,��˷�����д����)
//////////////////////////////////////////////////////////////////////////
#if MACRO_TARGET_FILE == MACRO_FILE_LIB 
	#define TOOLFRAME_DLL
#elif MACRO_TARGET_FILE == MACRO_FILE_DLL 
	#define TOOLFRAME_DLL __declspec(dllexport)
#else
	#if defined(MACRO_USE_TOOLFRAME_DLL)
		#define TOOLFRAME_DLL __declspec(dllimport)
	#else
		#define TOOLFRAME_DLL
	#endif
#endif

//extern

//���뿪��
//////////////////////////////////////////////////////////////////////////
#if defined(MACRO_HIDE_CONSOLE)
	#if MACRO_TARGET_OS == MACRO_OS_WINDOWS
		#pragma comment( linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"" )
	#else
		#error This platform can not support hide console.
	#endif
#endif


//Ԥ����ע��:
//#pragma message("msg")									����ʱ����һ����Ϣ
//#pragma warning(disable:4507 34;once :4385;error:164 )	����ʱ���þ���
//#error msg												����ʱ����һ������
//#pragma init_seg(lib)										Ԥ����,�Ⱥ궨�嶼Ҫ��

//����Ϊ�ѷ�� д��:�ں������������ע����д�� @deprecated: ��Ǽ��ɡ�
//����:
 /** creates a RenderTexture object with width and height in Points and a pixel format, only RGB and RGBA formats are valid 
 @deprecated: This interface will be deprecated sooner or later.
 */
//////////////////////////////////////////////////////////////////////////

