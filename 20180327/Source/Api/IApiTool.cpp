#include "IApiTool.h"

#include <assert.h>

#include "ApiStd.h"
#include "ApiWin.h"
#include "ApiLinux.h"
#include "ApiIOS.h"
#include "ApiAndroid.h"
#include "ApiBoost.h"

#include "DeviceID.h"

#include "ToolFrame.h"

NS_TOOL_FRAME_BEGIN

IApiTool::IApiTool(void)
{
	SetApiTool(this);
}

IApiTool::~IApiTool(void)
{
}

bool IApiTool::SaveFile( const std::string& sFileName,const void* pBuffer,size_t uLength)
{
	//创建文件夹
	const std::string sDir = ToolFrame::PickDir(sFileName);
	if (!MakeDir(sDir))return false;

#if MACRO_TARGET_OS == MACRO_OS_WINDOWS
	return ApiWin::SaveFile(sFileName,pBuffer,uLength); 
#endif

#if MACRO_TARGET_OS == MACRO_OS_LINUX
	return ApiStd::SaveFile(sFileName,pBuffer,uLength); 
#endif

#if MACRO_TARGET_OS == MACRO_OS_IOS
	return ApiIOS::SaveFile(sFileName,pBuffer,uLength); 
#endif

#if MACRO_TARGET_OS == MACRO_OS_ANDROID
	return ApiAndroid::SaveFile(sFileName,pBuffer,uLength); 
#endif

#ifdef MACRO_LIB_BOOST
#endif

	assert(false);

	return ApiStd::SaveFile(sFileName,pBuffer,uLength); 
}

bool IApiTool::LoadFile( const std::string& sFileName,void* pBuffer,size_t uLength)
{
#if MACRO_TARGET_OS == MACRO_OS_WINDOWS
	return ApiWin::LoadFile(sFileName,pBuffer,uLength);
#endif

#if MACRO_TARGET_OS == MACRO_OS_LINUX
	return ApiStd::LoadFile(sFileName,pBuffer,uLength);
#endif

#if MACRO_TARGET_OS == MACRO_OS_IOS
	return ApiIOS::LoadFile(sFileName,pBuffer,uLength);
#endif

#if MACRO_TARGET_OS == MACRO_OS_ANDROID
	return ApiAndroid::LoadFile(sFileName,pBuffer,uLength);
#endif

#ifdef MACRO_LIB_BOOST
#endif

	assert(false);
	return ApiStd::LoadFile(sFileName,pBuffer,uLength);
}

bool IApiTool::MakeDir( const std::string& sDir)
{
#if MACRO_TARGET_OS == MACRO_OS_IOS
	return ApiIOS::MakeDir(sDir);
#endif

#if MACRO_TARGET_OS == MACRO_OS_LINUX

#endif

#if MACRO_TARGET_OS == MACRO_OS_WINDOWS
	return ApiWin::MakeDir(sDir);
#endif

#if MACRO_TARGET_OS == MACRO_OS_ANDROID
	return ApiAndroid::MakeDir(sDir);
#endif

#ifdef MACRO_LIB_BOOST

#endif

	assert(false);
	return 0;
}

bool IApiTool::RemoveDir( const std::string& sDir)
{
#if MACRO_TARGET_OS == MACRO_OS_WINDOWS
	return ApiWin::RemoveDir(sDir); 
#endif

#if MACRO_TARGET_OS == MACRO_OS_LINUX
	return ApiLinux::RemoveDir(sDir); 
#endif

#if MACRO_TARGET_OS == MACRO_OS_IOS
	return ApiIOS::RemoveDir(sDir); 
#endif

#if MACRO_TARGET_OS == MACRO_OS_ANDROID
	return ApiAndroid::RemoveDir(sDir); 
#endif

#ifdef MACRO_LIB_BOOST
#endif

	assert(false);

	return false; 
}


bool IApiTool::CopyDir( const std::string& sSrcDir,const std::string& sDesDir )
{
	if (sSrcDir.empty())return false;
	if (sDesDir.empty())return false;

#if MACRO_TARGET_OS == MACRO_OS_WINDOWS
	return ApiWin::CopyDir(sSrcDir,sDesDir); 
#endif

#if MACRO_TARGET_OS == MACRO_OS_LINUX
	return ApiLinux::CopyDir(sSrcDir,sDesDir); 
#endif

#if MACRO_TARGET_OS == MACRO_OS_IOS
	return ApiIOS::CopyDir(sSrcDir,sDesDir); 
#endif

#if MACRO_TARGET_OS == MACRO_OS_ANDROID
	return ApiAndroid::CopyDir(sSrcDir,sDesDir); 
#endif

#ifdef MACRO_LIB_BOOST
#endif

	assert(false);

	return false; 
}

UINT64 IApiTool::GetNowTimeMill()
{
#if MACRO_TARGET_OS == MACRO_OS_WINDOWS
	return ApiWin::GetNowTimeMill();
#endif

#if MACRO_TARGET_OS == MACRO_OS_LINUX
	return ApiLinux::GetNowTimeMill();
#endif

#if MACRO_TARGET_OS == MACRO_OS_IOS
	return ApiIOS::GetNowTimeMill();
#endif

#if MACRO_TARGET_OS == MACRO_OS_ANDROID
	return ApiAndroid::GetNowTimeMill();
#endif

#ifdef MACRO_LIB_BOOST
#endif

	assert(false);
	return 0;
}

void IApiTool::SetConsoleTextAttribute( int nColor )
{
#if MACRO_TARGET_OS == MACRO_OS_WINDOWS
	ApiWin::SetConsoleTextAttribute(nColor);
	return ;
#endif
}

void IApiTool::OutPut( const std::string& sMsg,const std::string& sTag/*=""*/,bool bTrace /*= true*/ )
{
#if MACRO_TARGET_OS == MACRO_OS_IOS
	return ApiStd::OutPut(sMsg);
#endif

#if MACRO_TARGET_OS == MACRO_OS_LINUX
	return ApiStd::OutPut(sMsg);
#endif

#if MACRO_TARGET_OS == MACRO_OS_WINDOWS
	if (bTrace)ApiWin::Trace(sMsg,sTag);
	return ApiStd::OutPut(sMsg);
#endif

#if MACRO_TARGET_OS == MACRO_OS_ANDROID
	return ApiAndroid::OutPut(sMsg,sTag);
#endif

	assert(false);
	return ApiStd::OutPut(sMsg);
}

void IApiTool::ClearScreen()
{
#if MACRO_TARGET_OS == MACRO_OS_IOS

#endif

#if MACRO_TARGET_OS == MACRO_OS_LINUX
	return ApiLinux::ClearScreen();
#endif

#if MACRO_TARGET_OS == MACRO_OS_WINDOWS
	return ApiWin::ClearScreen();
#endif

#if MACRO_TARGET_OS == MACRO_OS_ANDROID

#endif
}

bool IApiTool::SetConsoleHide()
{
#if MACRO_TARGET_OS == MACRO_OS_WINDOWS
	return ApiWin::SetConsoleHide(); 
#endif

#if MACRO_TARGET_OS == MACRO_OS_LINUX

#endif

#if MACRO_TARGET_OS == MACRO_OS_IOS

#endif

#if MACRO_TARGET_OS == MACRO_OS_ANDROID

#endif

#ifdef MACRO_LIB_BOOST
#endif

	return false; 
}

std::string IApiTool::ApiGetConsoleTitle()
{
#if MACRO_TARGET_OS == MACRO_OS_WINDOWS
	return ApiWin::ApiGetConsoleTitle(); 
#endif

#if MACRO_TARGET_OS == MACRO_OS_LINUX

#endif

#if MACRO_TARGET_OS == MACRO_OS_IOS

#endif

#if MACRO_TARGET_OS == MACRO_OS_ANDROID

#endif

#ifdef MACRO_LIB_BOOST
#endif

	return ""; 
}

bool IApiTool::ApiSetConsoleTitle( const std::string & sTitle )
{
#if MACRO_TARGET_OS == MACRO_OS_WINDOWS
	return ApiWin::ApiSetConsoleTitle(sTitle); 
#endif

#if MACRO_TARGET_OS == MACRO_OS_LINUX

#endif

#if MACRO_TARGET_OS == MACRO_OS_IOS

#endif

#if MACRO_TARGET_OS == MACRO_OS_ANDROID

#endif

#ifdef MACRO_LIB_BOOST
#endif

	return false; 
}

bool IApiTool::RenameFile( const std::string& sPathSrc,const std::string& sPathDes)
{
#if MACRO_TARGET_OS == MACRO_OS_WINDOWS
	return ApiStd::RenameFile(sPathSrc,sPathDes); 
#endif

#if MACRO_TARGET_OS == MACRO_OS_LINUX
	return ApiStd::RenameFile(sPathSrc,sPathDes); 
#endif

#if MACRO_TARGET_OS == MACRO_OS_IOS
	return ApiIOS::RenameFile(sPathSrc,sPathDes); 
#endif

#if MACRO_TARGET_OS == MACRO_OS_ANDROID
	return ApiAndroid::RenameFile(sPathSrc,sPathDes); 
#endif

#ifdef MACRO_LIB_BOOST
#endif

	assert(false);

	return ApiStd::RenameFile(sPathSrc,sPathDes); 
}

bool IApiTool::RemoveFile( const std::string& sFileName)
{
#if MACRO_TARGET_OS == MACRO_OS_WINDOWS
	return ApiWin::RemoveFile(sFileName); 
#endif

#if MACRO_TARGET_OS == MACRO_OS_LINUX
	return ApiStd::RemoveFile(sFileName); 
#endif

#if MACRO_TARGET_OS == MACRO_OS_IOS
	return ApiIOS::RemoveFile(sFileName); 
#endif

#if MACRO_TARGET_OS == MACRO_OS_ANDROID
	return ApiAndroid::RemoveFile(sFileName); 
#endif

#ifdef MACRO_LIB_BOOST
#endif

	assert(false);

	return ApiStd::RemoveFile(sFileName); 
}

bool IApiTool::IsFileExist( const std::string& sFileName)
{
#if MACRO_TARGET_OS == MACRO_OS_WINDOWS
	return ApiWin::IsFileExist(sFileName); 
#endif

#if MACRO_TARGET_OS == MACRO_OS_LINUX
	return ApiStd::IsFileExist(sFileName); 
#endif

#if MACRO_TARGET_OS == MACRO_OS_IOS
	return ApiIOS::IsFileExist(sFileName); 
#endif

#if MACRO_TARGET_OS == MACRO_OS_ANDROID
	return ApiAndroid::IsFileExist(sFileName); 
#endif

#ifdef MACRO_LIB_BOOST
#endif

	assert(false);

	return ApiStd::IsFileExist(sFileName); 
}

size_t IApiTool::GetFileLength( const std::string& sFileName)
{
#if MACRO_TARGET_OS == MACRO_OS_WINDOWS
	return ApiWin::GetFileLength(sFileName); 
#endif

#if MACRO_TARGET_OS == MACRO_OS_LINUX
	return ApiStd::GetFileLength(sFileName); 
#endif

#if MACRO_TARGET_OS == MACRO_OS_IOS
	return ApiIOS::GetFileLength(sFileName); 
#endif

#if MACRO_TARGET_OS == MACRO_OS_ANDROID
	return ApiAndroid::GetFileLength(sFileName); 
#endif

#ifdef MACRO_LIB_BOOST
#endif

	assert(false);

	return ApiStd::GetFileLength(sFileName); 
}

bool IApiTool::SetWorkingDirWithExeDir()
{
#if MACRO_TARGET_OS == MACRO_OS_WINDOWS
	ApiWin::SetWorkingDir(ApiWin::GetExeDir());
	return true;
#endif

#if MACRO_TARGET_OS == MACRO_OS_LINUX

#endif

#ifdef MACRO_LIB_BOOST

#endif

	assert(false);

	return false;
}

bool IApiTool::IsAbsPath( const std::string& sPath )
{
#if MACRO_TARGET_OS == MACRO_OS_IOS
	return ApiIOS::IsAbsPath(sPath);
#endif

#if MACRO_TARGET_OS == MACRO_OS_LINUX
	return ApiLinux::IsAbsPath(sPath);
#endif

#if MACRO_TARGET_OS == MACRO_OS_WINDOWS
	return ApiWin::IsAbsPath(sPath);
#endif

#if MACRO_TARGET_OS == MACRO_OS_ANDROID
	return ApiAndroid::IsAbsPath(sPath);
#endif

	assert(false);
	return false;
}

int IApiTool::GetProcessId()
{
#if MACRO_TARGET_OS == MACRO_OS_WINDOWS
	return ApiWin::GetProcessId();
#endif

#if MACRO_TARGET_OS == MACRO_OS_LINUX
	return ApiLinux::GetProcessId();
#endif

#if MACRO_TARGET_OS == MACRO_OS_IOS
	return ApiIOS::GetProcessId();
#endif

#if MACRO_TARGET_OS == MACRO_OS_ANDROID
	return ApiAndroid::GetProcessId();
#endif

#ifdef MACRO_LIB_BOOST

#endif
	return 0;
}

std::string IApiTool::GetProcessPath()
{
#if MACRO_TARGET_OS == MACRO_OS_WINDOWS
	return ApiWin::GetExePath();
#endif

#if MACRO_TARGET_OS == MACRO_OS_LINUX
	return ApiLinux::GetProcessPath();
#endif

#if MACRO_TARGET_OS == MACRO_OS_IOS
	//return ToolIpad::GetProcessPath();
#endif

#ifdef MACRO_LIB_BOOST

#endif

	assert(false);
	return "";
}

std::string IApiTool::GetProcessName( int nProcessID )
{
#if MACRO_TARGET_OS == MACRO_OS_WINDOWS
	return ApiWin::GetProcessName(nProcessID);
#endif

#if MACRO_TARGET_OS == MACRO_OS_LINUX
	return ApiLinux::GetProcessName(nProcessID);
#endif

#if MACRO_TARGET_OS == MACRO_OS_IOS
	//return ApiIOS::GetProcessName(nProcessID);
#endif

#if MACRO_TARGET_OS == MACRO_OS_ANDROID
	//return ApiAndroid::GetProcessName(nProcessID);
	return "";
#endif
	assert(false);
	return "";
}

std::string IApiTool::GetProcessNameWithOutExt()
{
#if MACRO_TARGET_OS == MACRO_OS_IOS
	return ApiIOS::GetProcessNameWithOutExt();
#endif
#if MACRO_TARGET_OS == MACRO_OS_WINDOWS
	return ApiWin::GetExeNameWithOutExt();
#endif
#if MACRO_TARGET_OS == MACRO_OS_ANDROID
	return ApiAndroid::GetProcessName();
#endif

	return GetProcessNameWithOutExt(GetProcessId());
}

std::string IApiTool::GetProcessNameWithOutExt( int nProcessID )
{
	return ToolFrame::PickFileNameWithOutExt(GetProcessName(nProcessID));
}

std::string IApiTool::GetProcessDir()
{
#if MACRO_TARGET_OS == MACRO_OS_WINDOWS
	return ApiWin::GetExeDir();
#endif

#if MACRO_TARGET_OS == MACRO_OS_LINUX
	return ApiLinux::GetProcessDir();
#endif

#if MACRO_TARGET_OS == MACRO_OS_IOS
	return ApiIOS::GetMainBundleDir();
#endif

#if MACRO_TARGET_OS == MACRO_OS_ANDROID
	return ApiAndroid::GetDataDir();
#endif

#ifdef MACRO_LIB_BOOST

#endif

	assert(false);
	return "";
}

void IApiTool::Sleep( UINT64 nTimeMill )
{
#if MACRO_TARGET_OS == MACRO_OS_WINDOWS
	ApiWin::Sleep(nTimeMill);
	return ;
#endif

#if MACRO_TARGET_OS == MACRO_OS_ANDROID
	//ApiAndroid::Sleep(nTimeMill); JavaVM 最好再主线程中调用。
	//return ;
#endif

#ifdef MACRO_LIB_BOOST
	ApiBoost::Sleep(nTimeMill);
	return;
#endif

	assert(false);
}

uint64 IApiTool::GetThreadId()
{
#if MACRO_TARGET_OS == MACRO_OS_IOS
	return ApiIOS::GetThreadId();
#endif

#if MACRO_TARGET_OS == MACRO_OS_LINUX
	return ApiLinux::GetThreadId();
#endif

#if MACRO_TARGET_OS == MACRO_OS_WINDOWS
	return ApiWin::GetThreadId();
#endif

#if MACRO_TARGET_OS == MACRO_OS_ANDROID
	return ApiAndroid::GetThreadId();
#endif

#ifdef MACRO_LIB_BOOST

#endif

	assert(false);
	return 0;
}

uint IApiTool::GetThreadAmount()
{
#if MACRO_TARGET_OS == MACRO_OS_IOS

#endif

#if MACRO_TARGET_OS == MACRO_OS_LINUX
	return ApiAndroid::GetThreadAmount();
#endif

#if MACRO_TARGET_OS == MACRO_OS_WINDOWS
	return ApiWin::GetThreadAmount();
#endif

#if MACRO_TARGET_OS == MACRO_OS_ANDROID
#endif

#ifdef MACRO_LIB_BOOST

#endif

	return 0;
}

std::string ToolFrame::IApiTool::GetCallStackAll()
{
#if MACRO_TARGET_OS == MACRO_OS_IOS

#endif

#if MACRO_TARGET_OS == MACRO_OS_LINUX

#endif

#if MACRO_TARGET_OS == MACRO_OS_WINDOWS
	return ApiWin::GetCallStackAll();
#endif

#if MACRO_TARGET_OS == MACRO_OS_ANDROID
	
#endif

#ifdef MACRO_LIB_BOOST

#endif

	return "";
}

std::string ToolFrame::IApiTool::GetCallStack()
{
#if MACRO_TARGET_OS == MACRO_OS_IOS

#endif

#if MACRO_TARGET_OS == MACRO_OS_LINUX

#endif

#if MACRO_TARGET_OS == MACRO_OS_WINDOWS
	return ApiWin::GetCallStack();
#endif

#if MACRO_TARGET_OS == MACRO_OS_ANDROID

#endif

#ifdef MACRO_LIB_BOOST

#endif

	return "";
}

std::string IApiTool::GetDeviceID()
{
	static CDeviceID xDeviceID;
	return xDeviceID.GetID();
}

std::string IApiTool::GetLanguageString()
{
#if MACRO_TARGET_OS == MACRO_OS_IOS
	return ApiIOS::GetLanguageString();
#endif

#if MACRO_TARGET_OS == MACRO_OS_LINUX

#endif

#if MACRO_TARGET_OS == MACRO_OS_WINDOWS
	return ApiWin::GetLanguageString();
#endif

#if MACRO_TARGET_OS == MACRO_OS_ANDROID
	return ApiAndroid::GetLanguageString();
#endif

	assert(false);
	return "";
}

UINT64 IApiTool::GetProcessMemoryFree()
{
#if MACRO_TARGET_OS == MACRO_OS_IOS
	return ApiIOS::GetProcessMemoryFree();
#endif

#if MACRO_TARGET_OS == MACRO_OS_LINUX
	return ApiLinux::GetProcessMemoryFree();
#endif

#if MACRO_TARGET_OS == MACRO_OS_WINDOWS
	return ApiWin::GetProcessMemoryFree();
#endif

#if MACRO_TARGET_OS == MACRO_OS_ANDROID
	return ApiAndroid::GetProcessMemoryFree();
#endif

	assert(false);
	return 0;
}

uint64 IApiTool::GetProcessMemoryTotal()
{
#if MACRO_TARGET_OS == MACRO_OS_IOS
	return ApiIOS::GetProcessMemoryUsed() + ApiIOS::GetProcessMemoryFree();
#endif

#if MACRO_TARGET_OS == MACRO_OS_LINUX
	return ApiLinux::GetProcessMemoryUsed() + ApiLinux::GetProcessMemoryFree();
#endif

#if MACRO_TARGET_OS == MACRO_OS_WINDOWS
	return ApiWin::GetProcessMemoryTotal();
#endif

#if MACRO_TARGET_OS == MACRO_OS_ANDROID
	return ApiAndroid::GetProcessMemoryUsed() + ApiAndroid::GetProcessMemoryFree();
#endif

	assert(false);
	return 0;
}

int IApiTool::GetProcessMemoryUsage()
{
#if MACRO_TARGET_OS == MACRO_OS_IOS
	return ApiIOS::GetProcessMemoryUsed() *100 / GetProcessMemoryTotal();
#endif

#if MACRO_TARGET_OS == MACRO_OS_LINUX
	return ApiLinux::GetProcessMemoryUsed() *100 / GetProcessMemoryTotal();
#endif

#if MACRO_TARGET_OS == MACRO_OS_WINDOWS
	return ApiWin::GetProcessMemoryUsage();
#endif

#if MACRO_TARGET_OS == MACRO_OS_ANDROID
	return ApiAndroid::GetProcessMemoryUsed() *100 / GetProcessMemoryTotal();
#endif

	assert(false);
	return 0;
}

UINT64 IApiTool::ApiCreateProcess( const std::string& sExePath,const std::string& sWorkingDir,const std::string& sCommandLine )
{
#if MACRO_TARGET_OS == MACRO_OS_IOS

#endif

#if MACRO_TARGET_OS == MACRO_OS_LINUX

#endif

#if MACRO_TARGET_OS == MACRO_OS_WINDOWS
	return ApiWin::ApiCreateProcess(sExePath,sWorkingDir,sCommandLine);
#endif

#if MACRO_TARGET_OS == MACRO_OS_ANDROID

#endif

	assert(false);
	return 0;
}

std::string IApiTool::ApiGetCommandLine()
{
#if MACRO_TARGET_OS == MACRO_OS_IOS

#endif

#if MACRO_TARGET_OS == MACRO_OS_LINUX

#endif

#if MACRO_TARGET_OS == MACRO_OS_WINDOWS
	return ApiWin::ApiGetCommandLine();
#endif

#if MACRO_TARGET_OS == MACRO_OS_ANDROID

#endif

	assert(false);
	return 0;
}

int IApiTool::GetProcessIdByExePath( const std::string& sExePath )
{
#if MACRO_TARGET_OS == MACRO_OS_IOS

#endif

#if MACRO_TARGET_OS == MACRO_OS_LINUX

#endif

#if MACRO_TARGET_OS == MACRO_OS_WINDOWS
	return ApiWin::GetProcessIdByExePath(sExePath);
#endif

#if MACRO_TARGET_OS == MACRO_OS_ANDROID

#endif

	assert(false);
	return 0;
}

bool IApiTool::TerminateProcess( int nProcessID )
{
#if MACRO_TARGET_OS == MACRO_OS_IOS

#endif

#if MACRO_TARGET_OS == MACRO_OS_LINUX

#endif

#if MACRO_TARGET_OS == MACRO_OS_WINDOWS
	return ApiWin::TerminateProcess(nProcessID);
#endif

#if MACRO_TARGET_OS == MACRO_OS_ANDROID

#endif

	assert(false);
	return 0;
}

std::string IApiTool::GetDirByType( int eDirType )
{
#if MACRO_TARGET_OS == MACRO_OS_IOS
	return ApiIOS::GetDirByType(eDirType);
#endif

#if MACRO_TARGET_OS == MACRO_OS_LINUX
	return ApiLinux::GetDirByType(eDirType);
#endif

#if MACRO_TARGET_OS == MACRO_OS_WINDOWS
	return ApiWin::GetDirByType(eDirType);
#endif

#if MACRO_TARGET_OS == MACRO_OS_ANDROID
	return ApiAndroid::GetDirByType(eDirType);
#endif
	assert(false);
	return "";
}

int IApiTool::GetPlatform()
{
	return MACRO_TARGET_OS;
}

std::string IApiTool::ToPlatformString(int ePlatform)
{
	switch(ePlatform)
	{
	case MACRO_OS_IOS:
		return "IOS";
		break;
	case MACRO_OS_ANDROID:
		return "ANDROID";
		break;
	case MACRO_OS_WINDOWS:
		return "WINDOWS";
		break;
	case MACRO_OS_MARMALADE:
		return "MARMALADE";
		break;
	case MACRO_OS_LINUX:
		return "LINUX";
		break;
	case MACRO_OS_BADA:
		return "BADA";
		break;
	case MACRO_OS_BLACKBERRY:
		return "BLACKBERRY";
		break;
	case MACRO_OS_MAC:
		return "MAC";
		break;
	case MACRO_OS_NACL:
		return "NACL";
		break;
	case MACRO_OS_EMSCRIPTEN:
		return "EMSCRIPTEN";
		break;
	case MACRO_OS_TIZEN:
		return "TIZEN";
		break;
	case MACRO_OS_QT5:
		return "QT5";
		break;
	case MACRO_OS_WP8:
		return "WP8";
		break;
	case MACRO_OS_WINRT:
		return "WINRT";
		break;
	}

	return "";
}

int IApiTool::TranPlatformString(const std::string& sPlatform)
{
	std::string sSrc = sPlatform;
	ToolFrame::ToUpperCase(sSrc);
	if (sSrc == "IOS")
		return MACRO_OS_IOS;
	if (sSrc == "ANDROID")
		return MACRO_OS_ANDROID;
	if (sSrc == "WINDOWS")
		return MACRO_OS_WINDOWS;
	if (sSrc == "MARMALADE")
		return MACRO_OS_MARMALADE;
	if (sSrc == "LINUX")
		return MACRO_OS_LINUX;
	if (sSrc == "BADA")
		return MACRO_OS_BADA;
	if (sSrc == "BLACKBERRY")
		return MACRO_OS_BLACKBERRY;
	if (sSrc == "MAC")
		return MACRO_OS_MAC;
	if (sSrc == "NACL")
		return MACRO_OS_NACL;
	if (sSrc == "EMSCRIPTEN")
		return MACRO_OS_EMSCRIPTEN;
	if (sSrc == "TIZEN")
		return MACRO_OS_TIZEN;
	if (sSrc == "QT5")
		return MACRO_OS_QT5;
	if (sSrc == "WINRT")
		return MACRO_OS_WINRT;

	return MACRO_OS_UNKNOWN;
}

std::string ToolFrame::IApiTool::ToLanguageString(int eLanguage)
{
	switch (eLanguage)
	{
		case LANGUAGE_CHINESE:
			return "zh";
			break;
		case LANGUAGE_ENGLISH:
			return "en";
			break;
		case LANGUAGE_FRENCH:
			return "fr";
			break;
		case LANGUAGE_ITALIAN:
			return "it";
			break;
		case LANGUAGE_GERMAN:
			return "de";
			break;
		case LANGUAGE_SPANISH:
			return "es";
			break;
		case LANGUAGE_RUSSIAN:
			return "ru";
			break;
	}

	return "";
}

int IApiTool::TranLanguageString(const std::string& sLanguage)
{
	std::string sSrc = sLanguage;
	ToolFrame::ToLowerCase(sSrc);

	if (sSrc == "zh")
		return LANGUAGE_CHINESE;
	if (sSrc == "en")
		return LANGUAGE_ENGLISH;
	if (sSrc == "fr")
		return LANGUAGE_FRENCH;
	if (sSrc == "it")
		return LANGUAGE_ITALIAN;
	if (sSrc == "de")
		return LANGUAGE_GERMAN;
	if (sSrc == "es")
		return LANGUAGE_SPANISH;
	if (sSrc == "ru")
		return LANGUAGE_RUSSIAN;

	return LANGUAGE_INVALID;
}

std::string IApiTool::GetPlatformVer()
{
#if MACRO_TARGET_OS == MACRO_OS_IOS
	return ApiIOS::GetPlatformVer();
#endif

#if MACRO_TARGET_OS == MACRO_OS_LINUX
	return ApiLinux::GetPlatformVer();
#endif

#if MACRO_TARGET_OS == MACRO_OS_WINDOWS
	return ApiWin::GetPlatformVer();
#endif

#if MACRO_TARGET_OS == MACRO_OS_ANDROID
	return ApiAndroid::GetPlatformVer();
#endif

	assert(false);
	return "";
}

std::string IApiTool::GetMacAddress()
{
#if MACRO_TARGET_OS == MACRO_OS_IOS
	
#endif

#if MACRO_TARGET_OS == MACRO_OS_LINUX
	
#endif

#if MACRO_TARGET_OS == MACRO_OS_WINDOWS
	return ApiWin::GetMacAddress();
#endif

#if MACRO_TARGET_OS == MACRO_OS_ANDROID
	return ApiAndroid::GetMacAddress();
#endif

	return "";
}

std::string IApiTool::GetIPAddress()
{
#if MACRO_TARGET_OS == MACRO_OS_IOS

#endif

#if MACRO_TARGET_OS == MACRO_OS_LINUX

#endif

#if MACRO_TARGET_OS == MACRO_OS_WINDOWS
	return ApiWin::GetIPAddress();
#endif

#if MACRO_TARGET_OS == MACRO_OS_ANDROID

#endif

	return "";
}

uint64 IApiTool::GetProcessMemoryUsed( int nProcessID )
{
#if MACRO_TARGET_OS == MACRO_OS_IOS

#endif

#if MACRO_TARGET_OS == MACRO_OS_LINUX

#endif

#if MACRO_TARGET_OS == MACRO_OS_WINDOWS
	return ApiWin::GetProcessMemoryUsed(nProcessID);
#endif

#if MACRO_TARGET_OS == MACRO_OS_ANDROID

#endif

	assert(false);
	return 0;
}

std::string IApiTool::GetModel()
{
#if MACRO_TARGET_OS == MACRO_OS_IOS
	return ApiIOS::GetModel();
#endif

#if MACRO_TARGET_OS == MACRO_OS_LINUX
	return"";
#endif

#if MACRO_TARGET_OS == MACRO_OS_WINDOWS
	return ApiWin::GetModel();
#endif

#if MACRO_TARGET_OS == MACRO_OS_ANDROID
	return ApiAndroid::GetModel();
#endif

	assert(false);
	return 0;
}

bool IApiTool::IsExecutedMulit()
{
#if MACRO_TARGET_OS == MACRO_OS_IOS
	return false;
#endif

#if MACRO_TARGET_OS == MACRO_OS_LINUX
	return false;
#endif

#if MACRO_TARGET_OS == MACRO_OS_WINDOWS
	return ApiWin::IsExecutedMulit();
#endif

#if MACRO_TARGET_OS == MACRO_OS_ANDROID
	return false;
#endif

	assert(false);
	return 0;
}

bool IApiTool::OpenUrl( const std::string& sUrl )
{
#if MACRO_TARGET_OS == MACRO_OS_IOS
	return ApiIOS::OpenUrl(sUrl);
#endif

#if MACRO_TARGET_OS == MACRO_OS_LINUX
	return false;
#endif

#if MACRO_TARGET_OS == MACRO_OS_WINDOWS
	return ApiWin::OpenUrl(sUrl);
#endif

#if MACRO_TARGET_OS == MACRO_OS_ANDROID
	return ApiAndroid::OpenUrl(sUrl);
#endif

	assert(false);
	return 0;
}

std::string IApiTool::GetNetWorkType()
{
#if MACRO_TARGET_OS == MACRO_OS_IOS
	return ApiIOS::GetNetWorkType();
#endif

#if MACRO_TARGET_OS == MACRO_OS_LINUX
	return false;
#endif

#if MACRO_TARGET_OS == MACRO_OS_WINDOWS
	return ApiWin::GetNetWorkType();
#endif

#if MACRO_TARGET_OS == MACRO_OS_ANDROID
	return ApiAndroid::GetNetWorkType();
#endif

	assert(false);
	return 0;
}

bool IApiTool::GetMacFlow( UINT64* upload,UINT64* download )
{
#if MACRO_TARGET_OS == MACRO_OS_IOS
#endif

#if MACRO_TARGET_OS == MACRO_OS_LINUX
#endif

#if MACRO_TARGET_OS == MACRO_OS_WINDOWS
	return ApiWin::GetMacFlow(upload,download);
#endif

#if MACRO_TARGET_OS == MACRO_OS_ANDROID

#endif

	assert(false);
	return false;
}

int IApiTool::GetResolutionWidth()
{
#if MACRO_TARGET_OS == MACRO_OS_IOS
	return ApiIOS::GetResolutionWidth();
#endif

#if MACRO_TARGET_OS == MACRO_OS_LINUX
	return false;
#endif

#if MACRO_TARGET_OS == MACRO_OS_WINDOWS
	return ApiWin::GetResolutionWidth();
#endif

#if MACRO_TARGET_OS == MACRO_OS_ANDROID
	return ApiAndroid::GetResolutionWidth();
#endif

	assert(false);
	return 0;
}

int IApiTool::GetResolutionHeight()
{
#if MACRO_TARGET_OS == MACRO_OS_IOS
	return ApiIOS::GetResolutionHeight();
#endif

#if MACRO_TARGET_OS == MACRO_OS_LINUX
	return false;
#endif

#if MACRO_TARGET_OS == MACRO_OS_WINDOWS
	return ApiWin::GetResolutionHeight();
#endif

#if MACRO_TARGET_OS == MACRO_OS_ANDROID
	return ApiAndroid::GetResolutionHeight();
#endif

	assert(false);
	return 0;
}

std::string IApiTool::GetOperatorName()
{
#if MACRO_TARGET_OS == MACRO_OS_IOS
	return ApiIOS::GetOperatorName();
#endif

#if MACRO_TARGET_OS == MACRO_OS_LINUX
	return false;
#endif

#if MACRO_TARGET_OS == MACRO_OS_WINDOWS
	return ApiWin::GetOperatorName();
#endif

#if MACRO_TARGET_OS == MACRO_OS_ANDROID
	return ApiAndroid::GetOperatorName();
#endif

	assert(false);
	return 0;
}

bool IApiTool::ScreenShot( const std::string& sFileName )
{
#if MACRO_TARGET_OS == MACRO_OS_IOS
	return ApiIOS::ScreenShot(sFileName);
#endif

#if MACRO_TARGET_OS == MACRO_OS_LINUX
#endif

#if MACRO_TARGET_OS == MACRO_OS_WINDOWS
	return ApiWin::ScreenShot(sFileName);
#endif

#if MACRO_TARGET_OS == MACRO_OS_ANDROID
#endif

	return false;
}

bool IApiTool::ReflashCpuState()
{
#if MACRO_TARGET_OS == MACRO_OS_IOS
	
#endif

#if MACRO_TARGET_OS == MACRO_OS_LINUX
#endif

#if MACRO_TARGET_OS == MACRO_OS_WINDOWS
	return ApiWin::ReflashCpuState();
#endif

#if MACRO_TARGET_OS == MACRO_OS_ANDROID
#endif

	return false;
}

int IApiTool::GetCpuUsage()
{
#if MACRO_TARGET_OS == MACRO_OS_IOS

#endif

#if MACRO_TARGET_OS == MACRO_OS_LINUX
#endif

#if MACRO_TARGET_OS == MACRO_OS_WINDOWS
	return ApiWin::GetCpuUsage();
#endif

#if MACRO_TARGET_OS == MACRO_OS_ANDROID
#endif

	return 0;
}

int IApiTool::GetCpuUsage( int nProcessID )
{
#if MACRO_TARGET_OS == MACRO_OS_IOS

#endif

#if MACRO_TARGET_OS == MACRO_OS_LINUX
#endif

#if MACRO_TARGET_OS == MACRO_OS_WINDOWS
	return ApiWin::GetCpuUsage(nProcessID);
#endif

#if MACRO_TARGET_OS == MACRO_OS_ANDROID
#endif

	return 0;
}

uint64 IApiTool::GetCpuUseTime(int nProcessID)
{
#if MACRO_TARGET_OS == MACRO_OS_IOS

#endif

#if MACRO_TARGET_OS == MACRO_OS_LINUX
#endif

#if MACRO_TARGET_OS == MACRO_OS_WINDOWS
	return ApiWin::GetCpuUseTime(nProcessID);
#endif

#if MACRO_TARGET_OS == MACRO_OS_ANDROID
#endif

	return 0;
}

int IApiTool::GetCpuIdle()
{
#if MACRO_TARGET_OS == MACRO_OS_IOS

#endif

#if MACRO_TARGET_OS == MACRO_OS_LINUX
#endif

#if MACRO_TARGET_OS == MACRO_OS_WINDOWS
	return ApiWin::GetCpuIdle();
#endif

#if MACRO_TARGET_OS == MACRO_OS_ANDROID
#endif

	return 0;
}

bool IApiTool::PurgeMemory( int nProcessID /*= -1*/ )
{
#if MACRO_TARGET_OS == MACRO_OS_IOS

#endif

#if MACRO_TARGET_OS == MACRO_OS_LINUX
#endif

#if MACRO_TARGET_OS == MACRO_OS_WINDOWS
	return ApiWin::PurgeMemory(nProcessID);
#endif

#if MACRO_TARGET_OS == MACRO_OS_ANDROID
#endif

	return false;
}

bool IApiTool::SystemReboot()
{
#if MACRO_TARGET_OS == MACRO_OS_IOS

#endif

#if MACRO_TARGET_OS == MACRO_OS_LINUX
#endif

#if MACRO_TARGET_OS == MACRO_OS_WINDOWS
	return ApiWin::SystemReboot();
#endif

#if MACRO_TARGET_OS == MACRO_OS_ANDROID
#endif

	return false;
}

bool IApiTool::SystemShutDown()
{
#if MACRO_TARGET_OS == MACRO_OS_IOS

#endif

#if MACRO_TARGET_OS == MACRO_OS_LINUX
#endif

#if MACRO_TARGET_OS == MACRO_OS_WINDOWS
	return ApiWin::SystemShutDown();
#endif

#if MACRO_TARGET_OS == MACRO_OS_ANDROID
#endif

	return false;
}

bool IApiTool::SystemLogOut()
{
#if MACRO_TARGET_OS == MACRO_OS_IOS

#endif

#if MACRO_TARGET_OS == MACRO_OS_LINUX
#endif

#if MACRO_TARGET_OS == MACRO_OS_WINDOWS
	return ApiWin::SystemLogOut();
#endif

#if MACRO_TARGET_OS == MACRO_OS_ANDROID
#endif

	return false;
}

bool ToolFrame::IApiTool::IsPad()
{
#if MACRO_TARGET_OS == MACRO_OS_IOS
	return ApiIOS::IsPad();
#endif

#if MACRO_TARGET_OS == MACRO_OS_LINUX
#endif

#if MACRO_TARGET_OS == MACRO_OS_WINDOWS
#endif

#if MACRO_TARGET_OS == MACRO_OS_ANDROID
	return ApiAndroid::IsPad();
#endif

	return false;
}

int IApiTool::GetCompileVer()
{
	return MACRO_TARGET_VER;
}

bool IApiTool::IsDebugVer()
{
	return MACRO_TARGET_VER == MACRO_VER_DEBUG;
}

bool IApiTool::IsReleaseVer()
{
	return MACRO_TARGET_VER == MACRO_VER_RELEASE;
}

std::string IApiTool::GetTcpPortInfoString( int nPort )
{
#if MACRO_TARGET_OS == MACRO_OS_IOS

#endif

#if MACRO_TARGET_OS == MACRO_OS_LINUX
#endif

#if MACRO_TARGET_OS == MACRO_OS_WINDOWS
	return ApiWin::GetTcpPortInfoString(nPort);
#endif

#if MACRO_TARGET_OS == MACRO_OS_ANDROID
#endif

	return "";
}

std::string IApiTool::GetTcpLickInfoString()
{
#if MACRO_TARGET_OS == MACRO_OS_IOS

#endif

#if MACRO_TARGET_OS == MACRO_OS_LINUX
#endif

#if MACRO_TARGET_OS == MACRO_OS_WINDOWS
	return ApiWin::GetTcpLickInfoString();
#endif

#if MACRO_TARGET_OS == MACRO_OS_ANDROID
#endif

	return "";
}

std::string IApiTool::GetUdpPortInfoString( int nPort )
{
#if MACRO_TARGET_OS == MACRO_OS_IOS

#endif

#if MACRO_TARGET_OS == MACRO_OS_LINUX
#endif

#if MACRO_TARGET_OS == MACRO_OS_WINDOWS
	return ApiWin::GetUdpPortInfoString(nPort);
#endif

#if MACRO_TARGET_OS == MACRO_OS_ANDROID
#endif

	return "";
}

std::string IApiTool::GetUdpLickInfoString()
{
#if MACRO_TARGET_OS == MACRO_OS_IOS

#endif

#if MACRO_TARGET_OS == MACRO_OS_LINUX
#endif

#if MACRO_TARGET_OS == MACRO_OS_WINDOWS
	return ApiWin::GetUdpLickInfoString();
#endif

#if MACRO_TARGET_OS == MACRO_OS_ANDROID
#endif

	return "";
}

bool IApiTool::IsPortOccupied(int nPort)
{
#if MACRO_TARGET_OS == MACRO_OS_IOS

#endif

#if MACRO_TARGET_OS == MACRO_OS_LINUX
#endif

#if MACRO_TARGET_OS == MACRO_OS_WINDOWS
	return ApiWin::IsPortOccupied(nPort);
#endif

#if MACRO_TARGET_OS == MACRO_OS_ANDROID
#endif

	return false;
}

bool IApiTool::IsFileCaseSensitive(const std::string& sPath)
{
#if MACRO_TARGET_OS == MACRO_OS_IOS
	return true;
#endif

#if MACRO_TARGET_OS == MACRO_OS_LINUX
	return true;
#endif

#if MACRO_TARGET_OS == MACRO_OS_WINDOWS
	return ApiWin::IsFileCaseSensitive(sPath);
#endif

#if MACRO_TARGET_OS == MACRO_OS_ANDROID
	return true;
#endif

	return true;
}

bool IApiTool::Vibrator(int nMillTime)
{
#if MACRO_TARGET_OS == MACRO_OS_IOS
	return ApiIOS::Vibrator(nMillTime);
#endif

#if MACRO_TARGET_OS == MACRO_OS_LINUX
	return true;
#endif

#if MACRO_TARGET_OS == MACRO_OS_WINDOWS
#endif

#if MACRO_TARGET_OS == MACRO_OS_ANDROID
	return ApiAndroid::Vibrator(nMillTime);
#endif

	return true;
}

bool IApiTool::PlayVideo(const std::string& sUrl)
{
#if MACRO_TARGET_OS == MACRO_OS_IOS
	return ApiIOS::PlayVideo(sUrl);
#endif

#if MACRO_TARGET_OS == MACRO_OS_LINUX
	return true;
#endif

#if MACRO_TARGET_OS == MACRO_OS_WINDOWS
#endif

#if MACRO_TARGET_OS == MACRO_OS_ANDROID
	return ApiAndroid::PlayVideo(sUrl);
#endif

	return true;
}

NS_TOOL_FRAME_END
