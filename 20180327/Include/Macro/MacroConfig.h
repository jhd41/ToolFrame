#pragma once
//表单
//注记:填写表单配置以编译想要的版本
//////////////////////////////////////////////////////////////////////////
//定义

//定义使用操作平台(MACRO_TARGET_OS)
#define MACRO_OS_UNKNOWN	0
#define MACRO_OS_IOS		1	//IOS
#define MACRO_OS_ANDROID	2	//安卓
#define MACRO_OS_WINDOWS	3	//Windows
#define MACRO_OS_MARMALADE	4	//MARMALADE(一个开发平台)
#define MACRO_OS_LINUX		5	//Linux
#define MACRO_OS_BADA		6	//BADA (三星研发的新型智能手机平台)
#define MACRO_OS_BLACKBERRY 7	//黑莓
#define MACRO_OS_MAC        8	//苹果
#define MACRO_OS_NACL       9
#define MACRO_OS_EMSCRIPTEN 10
#define MACRO_OS_TIZEN      11
#define MACRO_OS_QT5        12
#define MACRO_OS_WP8        13	//wphone
#define MACRO_OS_WINRT      14	//Arm版本win
#define MACRO_OS_MAX		14	//用于临界检查

//定义编译版本类型(MACRO_TARGET_VER)
#define MACRO_VER_UNKNOWN	0
#define MACRO_VER_DEBUG		1	//调试版本
#define MACRO_VER_RELEASE	2	//发布版本
#define MACRO_VER_MAX		2	//用于临界检查

//定义编译位数(MACRO_TARGET_BIT)
#define MACRO_BIT_UNKNOWN	0
#define MACRO_BIT_32		1	//32位版本
#define MACRO_BIT_64		2	//64位版本
#define MACRO_BIT_MAX		2	//用于临界检查

//定义架构集(MACRO_TARGET_ARCH)
#define MACRO_ARCH_UNKNOWN	0
#define MACRO_ARCH_ARM		1	//移动版本
#define MACRO_ARCH_X86		2	//PC版本
#define MACRO_ARCH_MAX		2	//用于临界检查

//定义字符集(MACRO_TARGET_FONT)
#define MACRO_FONT_UNKNOWN	0
#define MACRO_FONT_ANSI		1
#define MACRO_FONT_UNICODE	2
#define MACRO_FONT_MAX		2	//用于临界检查

//定义编译语言(MACRO_TARGET_CODE)
#define MACRO_CODE_UNKNOWN		0
#define MACRO_CODE_STD_C		1	//标准C语言
#define MACRO_CODE_C_PLUS_PLUS	2	//C++语言
#define MACRO_CODE_OBJ_C		3	//ObjC语言
#define MACRO_CODE_MAX			3	//用于临界检查

//定义目标文件(MACRO_TARGET_FILE)
#define MACRO_FILE_UNKNOWN		0
#define MACRO_FILE_EXE			1	//可执行文件
#define MACRO_FILE_LIB			2	//静态链接库
#define MACRO_FILE_DLL			3	//动态链接库
#define MACRO_FILE_MAX			3

//定义编译器(MACRO_TARGET_COMPILER)
#define MACRO_COMPILER_UNKNOWN	 0
#define MACRO_COMPILER_VC		 1
#define MACRO_COMPILER_GCC		 2
#define MACRO_COMPILER_SUNPRO_CC 3
#define MACRO_COMPILER_MAX		 3

//定义C++标准(MACRO_TARGET_STDC)
#define MACRO_STDC_UNKNOWN	0
#define MACRO_STDC_C89		1
#define MACRO_STDC_C89_1	2
#define MACRO_STDC_C99		3
#define MACRO_STDC_C11		4
#define MACRO_STDC_MAX		4

//导入用户设置
//////////////////////////////////////////////////////////////////////////
#include "MacroUserConfig.h"

//检查用户输入
#ifdef MACRO_TARGET_CODE
	#error MACRO_TARGET_CODE Must not Defined
#endif //MACRO_TARGET_CODE
#ifndef MACRO_LIB_BOOST
	#error MACRO_LIB_BOOST Must Be Defined.(please define MACRO_LIB_BOOST)
#endif // MACRO_LIB_BOOST
#ifndef MACRO_LIB_TINYXML
	#error MACRO_LIB_TINYXML Must Be Defined.(please define MACRO_LIB_TINYXML)
#endif //MACRO_LIB_TINYXML

//补充未定义表单
//////////////////////////////////////////////////////////////////////////
//定义操作系统
#ifndef MACRO_TARGET_OS
	#define MACRO_TARGET_OS			MACRO_OS_UNKNOWN
#endif // MACRO_TARGET_OS

//定义编译版本
#ifndef MACRO_TARGET_VER
	#define MACRO_TARGET_VER		MACRO_VER_UNKNOWN
#endif // MACRO_TARGET_VER

//定义编译位数
#ifndef MACRO_TARGET_BIT
	#define MACRO_TARGET_BIT		MACRO_BIT_UNKNOWN
#endif // MACRO_TARGET_BIT

//定义架构集
#ifndef MACRO_TARGET_ARCH
	#define MACRO_TARGET_ARCH		MACRO_ARCH_UNKNOWN
#endif // MACRO_TARGET_ARCH

//定义字符集
#ifndef MACRO_TARGET_FONT
	#define MACRO_TARGET_FONT		MACRO_FONT_UNKNOWN
#endif // MACRO_TARGET_FONT

//定义编译语言
#ifndef MACRO_TARGET_CODE
	#define MACRO_TARGET_CODE		MACRO_CODE_UNKNOWN
#endif // MACRO_TARGET_CODE

//定义目标文件
#ifndef MACRO_TARGET_FILE
	#define MACRO_TARGET_FILE		MACRO_FILE_UNKNOWN
#endif // MACRO_TARGET_FILE

//定义目标编译器
#ifndef MACRO_TARGET_COMPILER
	#define MACRO_TARGET_COMPILER	MACRO_COMPILER_UNKNOWN
#endif // MACRO_TARGET_COMPILER

//定义目标标准
#ifndef MACRO_TARGET_STDC
	#define MACRO_TARGET_STDC		MACRO_STDC_UNKNOWN
#endif // MACRO_TARGET_STDC

//根据已定义信息推导其他信息
//////////////////////////////////////////////////////////////////////////

//COCOS2D_DEBUG
#if defined(COCOS2D_DEBUG)
	//推导使用了cocos2dx库
	#if !defined(MACRO_LIB_COCOS2D)
	#define MACRO_LIB_COCOS2D
	#endif
	
	//推导编译调试版本
	#if !MACRO_TARGET_VER
	#undef  MACRO_TARGET_VER
	#define MACRO_TARGET_VER MACRO_VER_DEBUG
	#endif

#endif //defined(COCOS2D_DEBUG)

//CC_TARGET_OS_IPHONE
#if defined(CC_TARGET_OS_IPHONE)
	//推导使用了cocos2dx库
	#if !defined(MACRO_LIB_COCOS2D)
	#define MACRO_LIB_COCOS2D
	#endif

	//推导目标平台
	#if !MACRO_TARGET_OS
	#undef  MACRO_TARGET_OS
	#define MACRO_TARGET_OS MACRO_OS_IOS
	#endif

	//推导CPU架构
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

//_WIN64 WIN64(必须先于win32判断)
#if defined(_WIN64) || defined(WIN64)
	//推导出平台
	#if !MACRO_TARGET_OS
	#undef  MACRO_TARGET_OS
	#define MACRO_TARGET_OS MACRO_OS_WINDOWS
	#endif

	//推导出64位
	#if !MACRO_TARGET_BIT
	#undef  MACRO_TARGET_BIT
	#define MACRO_TARGET_BIT MACRO_BIT_64
	#endif

	//推导CPU架构
	#if !MACRO_TARGET_ARCH
	#undef  MACRO_TARGET_ARCH
	#define MACRO_TARGET_ARCH MACRO_ARCH_X86
	#endif
#endif

//WIN32 _WIN32
#if defined(WIN32) || defined(_WIN32)
	//推导出平台
	#if !MACRO_TARGET_OS
	#undef  MACRO_TARGET_OS
	#define MACRO_TARGET_OS MACRO_OS_WINDOWS
	#endif

	//推导出32位
	#if !MACRO_TARGET_BIT
	#undef  MACRO_TARGET_BIT
	#define MACRO_TARGET_BIT MACRO_BIT_32
	#endif

	//推导CPU架构
	#if !MACRO_TARGET_ARCH
	#undef  MACRO_TARGET_ARCH
	#define MACRO_TARGET_ARCH MACRO_ARCH_X86
	#endif
#endif

//_WINDOWS
#if defined(_WINDOWS)
	//推导出平台
	#if !MACRO_TARGET_OS
	#undef  MACRO_TARGET_OS
	#define MACRO_TARGET_OS MACRO_OS_WINDOWS
	#endif

	//推导CPU架构
	#if !MACRO_TARGET_ARCH
	#undef  MACRO_TARGET_ARCH
	#define MACRO_TARGET_ARCH MACRO_ARCH_X86
	#endif
#endif

//TARGET_OS_IPHONE __IPHONE__
#if defined(TARGET_OS_IPHONE)|| defined(__IPHONE__)
	//推导出平台
	#if !MACRO_TARGET_OS
	#undef  MACRO_TARGET_OS
	#define MACRO_TARGET_OS MACRO_OS_IOS
	#endif

	//推导出CPU架构
	#if !MACRO_TARGET_ARCH
	#undef  MACRO_TARGET_ARCH
	#define MACRO_TARGET_ARCH MACRO_ARCH_ARM
	#endif
#endif

//TARGET_IPHONE_SIMULATOR
#if defined(TARGET_IPHONE_SIMULATOR)
	//推导出平台
	#if !MACRO_TARGET_OS
	#undef  MACRO_TARGET_OS
	#define MACRO_TARGET_OS MACRO_OS_IOS
	#endif

	//推导出CPU架构
	#if !MACRO_TARGET_ARCH
	#undef  MACRO_TARGET_ARCH
	#define MACRO_TARGET_ARCH MACRO_ARCH_X86
	#endif
#endif

//ANDROID
#if defined(ANDROID)
	//推导出平台
	#if !MACRO_TARGET_OS
	#undef  MACRO_TARGET_OS
	#define MACRO_TARGET_OS MACRO_OS_ANDROID
	#endif

	//推导出CPU架构
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
	//推导出编译版本
	#if !MACRO_TARGET_VER
		#undef  MACRO_TARGET_VER
		#define MACRO_TARGET_VER MACRO_VER_DEBUG
	#endif
#endif

//NDEBUG
#if defined(NDEBUG)
	//推导出编译版本
	#if !MACRO_TARGET_VER
		#undef  MACRO_TARGET_VER
		#define MACRO_TARGET_VER MACRO_VER_RELEASE
	#endif
#endif

//UNICODE
#if defined(UNICODE)
	//推导出字符集
	#if !MACRO_TARGET_FONT
		#undef  MACRO_TARGET_FONT
		#define MACRO_TARGET_FONT MACRO_FONT_UNICODE
	#endif
#endif

//__LP64__
#if defined(__LP64__) && __LP64__
	//推导出编译位数
	#if !MACRO_TARGET_BIT
		#undef  MACRO_TARGET_BIT
		#define MACRO_TARGET_BIT MACRO_BIT_64
	#endif
#endif

//__STDC__
#if defined(__STDC__)
	//推导出编译语言
	#if !MACRO_TARGET_CODE
		#undef  MACRO_TARGET_CODE
		#define MACRO_TARGET_CODE MACRO_CODE_STD_C
	#endif
#endif

//__cplusplus
#if defined(__cplusplus)
	//推导出编译语言
	#if !MACRO_TARGET_CODE
		#undef  MACRO_TARGET_CODE
		#define MACRO_TARGET_CODE MACRO_CODE_C_PLUS_PLUS
	#endif
#endif

//__OBJC__
#if defined(__OBJC__)
	//推导出编译语言
	#if !MACRO_TARGET_CODE
		#undef  MACRO_TARGET_CODE
		#define MACRO_TARGET_CODE MACRO_CODE_OBJ_C
	#endif
#endif

//_USRDLL __DLL__
#if defined(_USRDLL) || defined(__DLL__)
	//推导出目标文件
	#if !MACRO_TARGET_FILE
		#undef  MACRO_TARGET_FILE
		#define MACRO_TARGET_FILE MACRO_FILE_DLL
	#endif
#endif

//_LIB __LIB__
#if defined(_LIB) || defined(__LIB__)
	//推导出目标文件
	#if !MACRO_TARGET_FILE
		#undef  MACRO_TARGET_FILE
		#define MACRO_TARGET_FILE MACRO_FILE_LIB
	#endif
#endif

//SS_MAKEDLL
#if defined(SS_MAKEDLL)
	//推导出目标文件
	#if !MACRO_TARGET_FILE
		#undef  MACRO_TARGET_FILE
		#define MACRO_TARGET_FILE MACRO_FILE_DLL
	#endif
#endif

//_MSC_VER
#if defined(_MSC_VER)
	//推导出目标编译器
	#if !MACRO_TARGET_COMPILER
	#undef  MACRO_TARGET_COMPILER
	#define MACRO_TARGET_COMPILER MACRO_COMPILER_VC
	#endif
#endif

//__GNUC__
#if defined(__GNUC__)
	//推导出目标编译器
	#if !MACRO_TARGET_COMPILER
	#undef  MACRO_TARGET_COMPILER
	#define MACRO_TARGET_COMPILER MACRO_COMPILER_GCC
	#endif
#endif

//_SUNPRO_C __SUNPRO_CC
#if defined(_SUNPRO_C) || defined(__SUNPRO_CC)
	//推导出目标编译器
	#if !MACRO_TARGET_COMPILER
	#undef  MACRO_TARGET_COMPILER
	#define MACRO_TARGET_COMPILER MACRO_COMPILER_SUNPRO_CC
	#endif
#endif

//__cplusplus 201103L
#if __cplusplus == 201103L
	//推导出目标C++标准
	#if !MACRO_TARGET_STDC
	#undef  MACRO_TARGET_STDC
	#define MACRO_TARGET_STDC MACRO_STDC_C11
	#endif
#endif

//__cplusplus 199711L
#if __cplusplus == 199711L
	//推导出目标C++标准
	#if !MACRO_TARGET_STDC
	#undef  MACRO_TARGET_STDC
	#define MACRO_TARGET_STDC MACRO_STDC_C99
	#endif
#endif

//__STDC__
#if defined(__STDC__)
	//推导出目标C++标准
	#if !MACRO_TARGET_STDC
		#undef  MACRO_TARGET_STDC
	
		#if defined(__STDC_VERSION__) && __STDC_VERSION__>=201112L 
		/* 符合C11标准的代码 */ 
		#define MACRO_TARGET_STDC  MACRO_STDC_C11
		#elif defined(__STDC_VERSION__) && __STDC_VERSION__>=19901L   
		/* 符合C99标准的代码 */ 
		#define MACRO_TARGET_STDC  MACRO_STDC_C99
		#elif defined(__STDC__VERSION__) && __STDC__VERSION__>=199409L   
		/* 符合C89及增补1标准的代码 */ 
		#define MACRO_TARGET_STDC  MACRO_STDC_C89_1
		#else   
		/* 符合C89但不包括增补1的标准代码 */ 
		#define MACRO_TARGET_STDC  MACRO_STDC_C89
		#endif  

	#endif
#endif
//给予默认缺省值
//////////////////////////////////////////////////////////////////////////
#if !MACRO_TARGET_BIT
	#undef  MACRO_TARGET_BIT
	#define MACRO_TARGET_BIT  MACRO_BIT_32
#endif

#if !MACRO_TARGET_ARCH
	#undef  MACRO_TARGET_ARCH
	#define MACRO_TARGET_ARCH  MACRO_ARCH_X86
#endif

#if !MACRO_TARGET_VER//如果仍然没有确定出编译版本，则视为编译release版本
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

//检查表单
//////////////////////////////////////////////////////////////////////////
//检查平台
#if !MACRO_TARGET_OS
	#error MACRO_TARGET_OS Error (please define MACRO_TARGET_OS)
#endif
#if (MACRO_TARGET_OS <= MACRO_OS_UNKNOWN) || (MACRO_TARGET_OS > MACRO_OS_MAX)
	#error MACRO_TARGET_OS Error (MACRO_TARGET_OS define error.)
#endif

//检查版本
#if !MACRO_TARGET_VER
	#error MACRO_TARGET_VER Error (please define MACRO_TARGET_VER)
#endif
#if (MACRO_TARGET_VER <= MACRO_VER_UNKNOWN) || (MACRO_TARGET_VER > MACRO_VER_MAX)
	#error ACRO_TARGET_VER Error (MACRO_TARGET_VER define error.)
#endif

//检查位数
#if !MACRO_TARGET_BIT
#error MACRO_TARGET_BIT Error (please define MACRO_TARGET_BIT)
#endif

//检查架构
#if !MACRO_TARGET_ARCH
#error MACRO_TARGET_ARCH Error (please define MACRO_TARGET_ARCH)
#endif

//检查字符集
#if !MACRO_TARGET_FONT
#error MACRO_TARGET_FONT Error (please define MACRO_TARGET_FONT)
#endif
#if (MACRO_TARGET_FONT <= MACRO_FONT_UNKNOWN) || (MACRO_TARGET_FONT > MACRO_FONT_MAX)
#error MACRO_TARGET_FONT Error (MACRO_TARGET_FONT define error.)
#endif

//检查编译语言
#if !MACRO_TARGET_CODE
#error MACRO_TARGET_CODE Error (unkown MACRO_TARGET_CODE )
#endif
#if (MACRO_TARGET_CODE <= MACRO_CODE_UNKNOWN) || (MACRO_TARGET_CODE > MACRO_CODE_MAX)
#error MACRO_TARGET_CODE Error (MACRO_TARGET_CODE define error.)
#endif

//检查编译文件
#if !MACRO_TARGET_FILE
#error MACRO_TARGET_FILE Error (unkown MACRO_TARGET_FILE )
#endif
#if (MACRO_TARGET_FILE <= MACRO_FILE_UNKNOWN) || (MACRO_TARGET_FILE > MACRO_FILE_MAX)
#error MACRO_TARGET_FILE Error (MACRO_TARGET_FILE define error.)
#endif

//检查第三方库

//检查友盟插件(依赖于cocos2dx 只支持 ios,android)
#ifdef MACRO_LIB_PLUGIN_UM
	#if !(defined(MACRO_LIB_COCOS2D) && (MACRO_TARGET_OS == MACRO_OS_IOS || MACRO_TARGET_OS == MACRO_OS_ANDROID))
		#error MACRO_LIB_PLUGIN_UM Error (need MACRO_LIB_COCOS2D and os in ios,android )
	#endif
#endif // MACRO_LIB_PLUGIN_UM

//检查TalkingData插件(依赖于cocos2dx 只支持 ios,android)
#ifdef MACRO_LIB_PLUGIN_TK
#if !(defined(MACRO_LIB_COCOS2D) && (MACRO_TARGET_OS == MACRO_OS_IOS || MACRO_TARGET_OS == MACRO_OS_ANDROID))
#error MACRO_LIB_PLUGIN_TK Error (need MACRO_LIB_COCOS2D and os in ios,android )
#endif
#endif // MACRO_LIB_PLUGIN_TK

//补全 常用关键字
//////////////////////////////////////////////////////////////////////////
//补全编译版本
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

//编译DLL导出(未测试,由于本工具经常返回STL,而STL与DLL导出将付出沉重的代价,因此放弃此写法。)
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

//编译开关
//////////////////////////////////////////////////////////////////////////
#if defined(MACRO_HIDE_CONSOLE)
	#if MACRO_TARGET_OS == MACRO_OS_WINDOWS
		#pragma comment( linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"" )
	#else
		#error This platform can not support hide console.
	#endif
#endif


//预编译注记:
//#pragma message("msg")									编译时产生一条消息
//#pragma warning(disable:4507 34;once :4385;error:164 )	编译时设置警告
//#error msg												编译时产生一条错误
//#pragma init_seg(lib)										预编译,比宏定义都要早

//声明为已否决 写法:在函数声明上面的注释里写上 @deprecated: 标记即可。
//例子:
 /** creates a RenderTexture object with width and height in Points and a pixel format, only RGB and RGBA formats are valid 
 @deprecated: This interface will be deprecated sooner or later.
 */
//////////////////////////////////////////////////////////////////////////

