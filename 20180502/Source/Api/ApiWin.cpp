#include "ApiWin.h"

#if MACRO_TARGET_OS == MACRO_OS_WINDOWS
#pragma warning(disable:4996)
#pragma warning(disable:4091)
#include <tchar.h>

//#include <winsock2.h>
#include <iphlpapi.h>
#include <sys/timeb.h>
#include <winnls.h>

#include <shlwapi.h>

#include "ToolFrame.h"
#include "ApiStd.h"
#include "ApiWinScreenShot.h"

#include <dbghelp.h>
#include <TLHELP32.H>

#pragma comment(lib, "Psapi.lib")
#pragma comment(lib, "shlwapi.lib")

//获取网卡MAC地址

#pragma comment(lib, "IPHLPAPI.lib")

const unsigned char MICRO_UTF_LEAD_0 = 0xefU;
const unsigned char MICRO_UTF_LEAD_1 = 0xbbU;
const unsigned char MICRO_UTF_LEAD_2 = 0xbfU;

UINT64 ApiWin::GetNowTimeMill()
{
	struct timeb tp;
	ftime(&tp);
	return ((UINT64)(tp.time)*1000) + tp.millitm;
}

time_t ApiWin::GetNowTime()
{
	struct timeb tp;
	ftime(&tp);
	return tp.time;
}

std::string ApiWin::GetNowTimeString()
{
	__time64_t long_time;
	_time64( &long_time );
	
	return ToolFrame::TimeToString(long_time);
}

VectorString ApiWin::GetStrings( const char_t pSrc[] )
{
	VectorString vReturns;
	while(*pSrc){
		std::string_t sBuff = pSrc;
		vReturns.push_back(ToMulti(sBuff));
		pSrc += sBuff.length() + 1;
	}
	return vReturns;
}

VectorString ApiWin::GetIniScetionNames( const std::string& sFileName )
{
	char_t   szBuff[1024]={0};
	GetPrivateProfileSectionNames(szBuff,sizeof(szBuff),ToStringT(sFileName).c_str());

	return ApiWin::GetStrings(szBuff);
}

MapStringString ApiWin::GetIniSection(const std::string& sFileName,const std::string& sSection){
	MapStringString vReturn;
	char_t   szBuff[1024]={0};
	GetPrivateProfileSection(ToStringT(sSection).c_str(),szBuff,sizeof(szBuff),ToStringT(sFileName).c_str());

	VectorString vKeyValues = ApiWin::GetStrings(szBuff);
	VectorString::iterator itr;
	foreach(itr,vKeyValues){
		const std::string& sBuff = *itr;
		SSIZE_TYPE nIndex = sBuff.find("=");
		if(std::string::npos != nIndex){
			vReturn.insert(std::make_pair(sBuff.substr(0,nIndex),sBuff.substr(nIndex + 1,sBuff.length() - nIndex - 1)));
		}
	}
	return vReturn;
}
void ApiWin::GetIniValue(const std::string& sFileName,const std::string& sSection,const std::string& sKey,int& nValue,const int nDefault){
	nValue = GetPrivateProfileInt(ToStringT(sSection).c_str(),ToStringT(sKey).c_str(),nDefault,ToStringT(sFileName).c_str());
}

void ApiWin::GetIniValue(const std::string& sFileName,const std::string& sSection,const std::string& sKey,std::string& sValue,const std::string& sDefault){
	char_t   szBuff[256]={0};
	GetPrivateProfileString(ToStringT(sSection).c_str(),ToStringT(sKey).c_str(),ToStringT(sDefault).c_str(),szBuff,sizeof(szBuff),ToStringT(sFileName).c_str());
	sValue = ToMulti(szBuff);
}

void ApiWin::WriteIniValue(const std::string& sFileName,const std::string& sSection,const std::string& sKey,const std::string& sValue){
	WritePrivateProfileString(ToStringT(sSection).c_str(),ToStringT(sKey).c_str(),ToStringT(sValue).c_str(),ToStringT(sFileName).c_str());
}

bool ApiWin::CopyDir(const std::string& sSrcDir,const std::string& sDesDir) 
{ 
	std::string sSrcPath = ToolFrame::TrimDir(sSrcDir) + "*.*";
	HANDLE   hFile;WIN32_FIND_DATA   wfd;
	hFile = ApiFindFirstFile(sSrcPath,&wfd);
	if (INVALID_HANDLE_VALUE == hFile)return false;

	ApiCreateDirectory(sDesDir);

	do{
		std::string sFileName = ToMulti(wfd.cFileName);
		std::string sSrcFile = ToolFrame::TrimDir(sSrcDir) + sFileName;
		std::string sDesFile = ToolFrame::TrimDir(sDesDir) + sFileName;

		//处理文件夹
		if(wfd.dwFileAttributes   &   FILE_ATTRIBUTE_DIRECTORY) 
		{ 
			if (sFileName == "." || sFileName == "..")
				continue;

			ApiCreateDirectory(sDesFile); 
			CopyDir(sSrcFile,sDesFile);
			continue; 
		}
		//处理文件
		if (!CopyFile(ToStringT(sSrcFile).c_str(),ToStringT(sDesFile).c_str(),FALSE))
			return false;
	}while(::FindNextFile(hFile,&wfd));
	FindClose(hFile); 

	return true;
}

bool ApiWin::MakeDir( const std::string& sDir)
{
	return ApiMakeDir(sDir);
}

bool ApiWin::ApiMakeDir( const std::string& sDir )
{
	if (sDir.empty())return true;

	VectorString vDirs;
	ToolFrame::SplitString(vDirs,sDir,"/",true,true);

	std::string sCurDir;
	VectorString::iterator itr;
	foreach(itr,vDirs){
		sCurDir += *itr;
		ApiCreateDirectory(sCurDir);
	}

	return true;
}

void ApiWin::GbkToUtf8( const VectorString& vSrc,VectorString& vDes )
{
	for (size_t nIndex = 0;nIndex<vSrc.size();++nIndex)
	{
		vDes.push_back(GbkToUtf8(vSrc[nIndex]));
	}
}

void ApiWin::GbkToUtf8( VectorString& vStrings )
{
	for (size_t nIndex = 0;nIndex<vStrings.size();++nIndex)
	{
		vStrings[nIndex] = GbkToUtf8(vStrings[nIndex]);
	}
}

std::string ApiWin::GetExePath()
{
	return std::string(ApiGetModuleFileName());
}
std::string ApiWin::GetExeDir()
{
	return ToolFrame::PickDir(ApiGetModuleFileName());
}

std::string ApiWin::GetExeName()
{
	return ToolFrame::PickFileName(ApiGetModuleFileName());
}

std::string ApiWin::GetExeNameWithOutExt()
{
	return ToolFrame::PickFileNameWithOutExt(ApiGetModuleFileName());
}

bool ApiWin::GetFilesPath( VectorString& vDes,const std::string& sDir,const std::string& sFilter/*="*.*"*/,bool bExcept /*="false"*/)
{
	VectorString vFilter;
	ToolFrame::SplitString(vFilter,sFilter,",");
	if (vFilter.empty())
		vFilter.push_back("*.*");
	
	return GetFilesPath(vDes,sDir,vFilter,bExcept);
}

bool ApiWin::GetFilesPath( VectorString& vDes,std::string sDir,const VectorString& vSpec,bool bExcept)
{
	sDir = ToolFrame::TrimDir(sDir);

	HANDLE   hFile;WIN32_FIND_DATA   wfd;

	//首先查找当前目录下指定过滤文件
	{
		const std::string sPath = sDir + "*.*";
		hFile = ApiFindFirstFile(sPath,&wfd);
		if (INVALID_HANDLE_VALUE != hFile)
		{
			do{
				const std::string sFileName = ToMulti(wfd.cFileName);
				if (sFileName == ".")continue;
				if (sFileName == "..")continue;

				//如果是目录则递归
				if (FILE_ATTRIBUTE_DIRECTORY & wfd.dwFileAttributes)
				{
					if (!GetFilesPath(vDes,sDir + sFileName,vSpec,bExcept))
						return false;
				}else{
					//如果是文件
					if (!bExcept)
					{
						if (ApiPathMatchSpec(sFileName,vSpec))
							vDes.push_back(sDir + sFileName);
					}else
					{
						if (!ApiPathMatchSpec(sFileName,vSpec))
							vDes.push_back(sDir + sFileName);
					}
				}
			}while(::FindNextFile(hFile,&wfd));
		}

		FindClose(hFile); 
	}

	return true;
}

bool ApiWin::IsFileCaseSensitive( const std::string& sPath )
{
	std::string sDir = ToolFrame::TrimPath(sPath);
	if (sDir.empty())return "";

	std::stringstream sDirCur;//当前文件路径

	VectorString vDir;
	ToolFrame::SplitString(vDir,sDir,"/");
	if (vDir.empty())return false;

	//跳过根目录
	if (ToolFrame::IsAbsPath(sDir))
	{
		sDirCur<<vDir[0]<<"/";
		ToolFrame::EraseFront(vDir);
	}

	if (vDir.empty())return false;

	VectorString::const_iterator itr;
	foreach(itr,vDir){
		const std::string& sFileCur = *itr;
		sDirCur << sFileCur;

		HANDLE   hFile;WIN32_FIND_DATA   wfd;
		hFile = ApiWin::ApiFindFirstFile(sDirCur.str(),&wfd);
		if (INVALID_HANDLE_VALUE == hFile)
			return false;

		if (sFileCur != ApiWin::ToMulti(wfd.cFileName))
		{
			FindClose(hFile);
			return false;
		}

		FindClose(hFile);

		sDirCur<<"/";
	}

	return true;
}

bool ApiWin::IsUtf8( const std::string& Src,bool bCheckMicroUtfLead /*= true*/ )
{
	if (bCheckMicroUtfLead && IsMicroUtfLead(Src))return true;

	::MultiByteToWideChar(CP_UTF8, MB_ERR_INVALID_CHARS,Src.c_str(), -1, nullptr,0);
	return ERROR_NO_UNICODE_TRANSLATION != GetLastError();
}

bool ApiWin::IsGBK( const std::string& Src )
{
	::MultiByteToWideChar(CP_ACP, MB_ERR_INVALID_CHARS,Src.c_str(), -1, nullptr,0);
	return ERROR_NO_UNICODE_TRANSLATION != GetLastError();

}

void ApiWin::SetConsoleTextAttribute( int nColor )
{
	::SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), nColor);//设置字体颜色
}

std::string ApiWin::GetWorkingDir()
{
	return ToolFrame::TrimDir(ApiGetCurrentDirectory());
}

void ApiWin::SetWorkingDir( const std::string& sDir )
{
	ApiSetCurrentDirectory(sDir);
}

void ApiWin::SetWorkingDirWithExeDir()
{
	SetWorkingDir(GetExeDir());
}

void ApiWin::Sleep( UINT64 nTimeMill )
{
	::Sleep((DWORD)nTimeMill);
}

bool ApiWin::IsAbsPath( const std::string& sPath )
{
	return !ApiPathIsRelative(sPath);
}

uint64 ApiWin::GetThreadId()
{
	return ::GetCurrentThreadId();
}

std::string ApiWin::GetLanguageString()
{
	LCID localeID = ::GetUserDefaultLCID();
	unsigned short primaryLanguageID = localeID & 0xFF;

	switch (primaryLanguageID)
	{
		case LANG_CHINESE:
			return "zh";
			break;
		case LANG_ENGLISH:
			return "en";
			break;
		case LANG_FRENCH:
			return "fr";
			break;
		case LANG_ITALIAN:
			return "it";
			break;
		case LANG_GERMAN:
			return "de";
			break;
		case LANG_SPANISH:
			return "es";
			break;
		case LANG_RUSSIAN:
			return "ru";
			break;
	}

	return "";
}

void ApiWin::ClearScreen()
{
	system( "cls "); 
}

int ApiWin::GetProcessId()
{
	return ::GetCurrentProcessId();
}

bool ApiWin::GetProcessEntry32ByExePath( PROCESSENTRY32* proc,const std::string& sExePath )
{
	assert(proc);

	//初始化
	proc->dwSize = sizeof(PROCESSENTRY32);

	HANDLE hProcessSnap = ::CreateToolhelp32Snapshot(TH32CS_SNAPALL,0);//获取当前进程快照

	bool bFinded = false;
	if (Process32First(hProcessSnap, proc))
	{
		do 
		{
			if (sExePath == ToMulti(proc->szExeFile))
			{
				bFinded = true;
				break;
			}
		} while (Process32Next(hProcessSnap, proc));
	}
	::CloseHandle(hProcessSnap);
	return bFinded;
}

bool ApiWin::GetProcessEntry32ByProcessID( PROCESSENTRY32* proc, int nProcessID  )
{
	assert(proc);

	//初始化
	proc->dwSize = sizeof(PROCESSENTRY32);

	HANDLE hProcessSnap = ::CreateToolhelp32Snapshot(TH32CS_SNAPALL,0);//获取当前进程快照

	bool bFinded = false;
	if (Process32First(hProcessSnap, proc))
	{
		do 
		{
			if (proc->th32ProcessID == nProcessID)
			{
				bFinded = true;
				break;
			}
		} while (Process32Next(hProcessSnap, proc));
	}
	::CloseHandle(hProcessSnap);
	return bFinded;
}

std::string  ApiWin::GetProcessName( int nProcessID )
{
	PROCESSENTRY32 proc;
	if (!GetProcessEntry32ByProcessID(&proc,nProcessID))
		return "";
	return ToMulti(proc.szExeFile);
}

int ApiWin::GetProcessThreads( int nProcessID )
{
	PROCESSENTRY32 proc;
	if (!GetProcessEntry32ByProcessID(&proc,nProcessID))
		return 0;
	return proc.cntThreads;
}

UINT64 ApiWin::GetProcessMemoryUsed( int nProcessID )
{
	PROCESS_MEMORY_COUNTERS cb;
	if (!GetProcessMemoryCountersByProcessID(&cb,nProcessID))return 0;

	return cb.WorkingSetSize;
}

bool ApiWin::GetProcessMemoryCountersByProcessID( PROCESS_MEMORY_COUNTERS* mem, int nProcessID )
{
	assert(mem);
	bool bSucceed = false;
	//OpenProcess得到一个进程的句柄
	HANDLE hProcess = ::OpenProcess( PROCESS_ALL_ACCESS, FALSE, nProcessID );//注意:此语句在win2003系统下 可能会引起崩溃
	if (::GetProcessMemoryInfo(hProcess,mem,sizeof(PROCESS_MEMORY_COUNTERS)))
		bSucceed = true;

	::CloseHandle(hProcess);
	return bSucceed;
}

void ApiWin::Trace( const std::string& sMsg,const std::string& sTag )
{
	OutputDebugStringA(sMsg.c_str());
	OutputDebugStringA("\n");
}

bool ApiWin::ToMultiWide( const std::string& sSrc,std::wstring& sDes,int nSrcCode )
{
	if (sSrc.empty())return true;
	return ToMultiWide(sSrc.c_str(),sDes,nSrcCode);
}

bool ApiWin::ToMultiWide( const std::wstring& sSrc,std::string& sDes,int nSrcCode )
{
	if (sSrc.empty())return true;
	return ToMultiWide(sSrc.c_str(),sDes,nSrcCode);
}

bool ApiWin::ToMultiWide( const char* pSrc,std::wstring& sDes,int nSrcCode )
{
	if (!pSrc)return false;
	int nLen = ::MultiByteToWideChar(nSrcCode, 0,pSrc, -1, nullptr,0);			//计算目标长度
	if (nLen <= 0 )return false;

	wchar_t* pWideString = (wchar_t *) malloc(sizeof(wchar_t) * nLen);			//创建宽字符缓冲池
	if (!pWideString)return false;

	nLen = ::MultiByteToWideChar(nSrcCode, 0, pSrc, -1, pWideString, nLen);	//转换
	if (nLen <= 0){free(pWideString);return false;}

	sDes = pWideString;

	free(pWideString);
	return true;
}

bool ApiWin::ToMultiWide( const wchar_t* pSrc,std::string& sDes,int nSrcCode )
{
	if (!pSrc)return false;

	int nLen = ::WideCharToMultiByte(nSrcCode, 0, pSrc, -1, nullptr, 0, nullptr, nullptr);//计算目标长度	
	if (nLen <= 0 ){return false;}

	//创建多字节字符缓冲池 并转换
	char* pString = (char *) malloc(sizeof(char) * nLen);			//创建宽字符缓冲池
	if (!pString)return false;
	nLen = ::WideCharToMultiByte (nSrcCode, 0, pSrc, -1, pString, nLen, nullptr,nullptr);
	if (nLen <= 0){free(pString);return false;}

	sDes = pString;

	free(pString);
	return true;
}

std::string ApiWin::GbkToUtf8( const std::string& sSrc )
{
	if (sSrc.empty())return "";

	std::wstring sUnicode;std::string sDes;
	if (!ToMultiWide(sSrc,sUnicode,CP_ACP))return sDes;
	if (!ToMultiWide(sUnicode,sDes,CP_UTF8))return sDes;
	
	return sDes;
}

std::string ApiWin::Utf8ToGbk( const std::string& sSrc,bool bSkipMicroUtfLead/*=true*/ )
{
	if (sSrc.empty())return "";

	//跳过Utf头
	const char* pSrc = sSrc.c_str();
	if (bSkipMicroUtfLead && IsMicroUtfLead(sSrc))
		pSrc += GetMicroUtfLeadLength();

	std::wstring sUnicode;std::string sDes;
	if (!ToMultiWide(pSrc,sUnicode,CP_UTF8))return sDes;
	if (!ToMultiWide(sUnicode,sDes,CP_ACP))return sDes;

	return sDes;
}

std::wstring ApiWin::GbkToUnc( const std::string& sSrc )
{
	if (sSrc.empty())return std::wstring();

	std::wstring sDes;
	ToMultiWide(sSrc,sDes,CP_ACP);
	return sDes;
}

std::string ApiWin::UncToGbk( const std::wstring& sSrc )
{
	if (sSrc.empty())return "";

	std::string sDes;
	ToMultiWide(sSrc,sDes,CP_ACP);
	return sDes;
}

std::wstring ApiWin::Utf8ToUnc( const std::string& sSrc )
{
	if (sSrc.empty())return std::wstring();

	std::wstring sDes;
	ToMultiWide(sSrc,sDes,CP_UTF8);
	return sDes;
}

std::string ApiWin::UncToUtf8( const std::wstring& sSrc )
{
	if (sSrc.empty())return "";

	std::string sDes;
	ToMultiWide(sSrc,sDes,CP_UTF8);
	return sDes;
}

std::string ApiWin::UncToGbk( const std::string& sSrc )
{
	if (sSrc.empty())return "";

	std::wstring s = (const wchar_t*)sSrc.c_str();
	return UncToGbk(s);
}

std::string ApiWin::ToMulti( const std::wstring& sSrc )
{
	if (sSrc.empty())return "";

	std::string sDes;
	ToMultiWide(sSrc,sDes,CP_ACP);
	return sDes;
}

const std::string& ApiWin::ToMulti( const std::string& sSrc )
{
	return sSrc;
}

const std::wstring& ApiWin::ToWide( const std::wstring& sSrc )
{
	return sSrc;
}

std::wstring ApiWin::ToWide( const std::string& sSrc )
{
	if (sSrc.empty())return std::wstring();

	std::wstring sDes;
	ToMultiWide(sSrc,sDes,CP_ACP);
	return sDes;
}

bool ApiWin::ApiCreateDirectory( const std::string& sDir )
{
	return TRUE == CreateDirectory(ToStringT(sDir).c_str(),nullptr); 
}

std::string ApiWin::ApiGetModuleFileName()
{
	char_t szPath[MAX_PATH]={0};
	GetModuleFileName(nullptr,szPath,MAX_PATH);  //程序当前路径
	return ToMulti(szPath);
}


HANDLE ApiWin::ApiFindFirstFile( const std::string& sPath, WIN32_FIND_DATA* wfd )
{
	return ::FindFirstFile(ToStringT(sPath).c_str(),wfd);
}

std::string ApiWin::ApiGetCurrentDirectory()
{
	char_t szPath[MAX_PATH]={0};
	::GetCurrentDirectory(MAX_PATH,szPath);  //程序当前路径
	return ToolFrame::TrimDir(ToMulti(szPath));
}

bool ApiWin::ApiSetCurrentDirectory( const std::string& sDir )
{
	::SetCurrentDirectory(ToStringT(sDir).c_str());
	return true;
}

bool ApiWin::ApiStrCpy( const std::string& sSrc,wchar_t* pDes,int nLen)
{
	if (sSrc.empty())return true;

	return 0 < MultiByteToWideChar(CP_ACP, 0, sSrc.c_str(), -1, pDes, nLen);
}

bool ApiWin::ApiStrCpy( const std::string& sSrc,char* pDes,int nLen )
{
	return	0 == strcpy_s(pDes,sSrc.size()+1,sSrc.c_str());	
}

bool ApiWin::ApiPathMatchSpec( const std::string& sPath,const std::string& sSpec )
{
	return TRUE == PathMatchSpec(ToStringT(sPath).c_str(),ToStringT(sSpec).c_str());
}

bool ApiWin::ApiPathMatchSpec( const std::string& sPath,const VectorString& vSpec )
{
	VectorString::const_iterator itr;
	foreach(itr,vSpec){
		if (ApiPathMatchSpec(sPath,*itr))
			return true;
	}

	return false;
}

bool ApiWin::ApiDeleteFile( const std::string& sFile )
{
	return TRUE == DeleteFile(ToStringT(sFile).c_str());
}

bool ApiWin::ApiRemoveDirectory( const std::string& sDir )
{
	return TRUE == RemoveDirectory(ToStringT(sDir).c_str());
}

bool ApiWin::ApiPathIsRelative( const std::string& sDir )
{
	return TRUE == PathIsRelative(ToStringT(sDir).c_str());
}

bool ApiWin::ApiPathIsRoot( const std::string& sDir )
{
	return TRUE == PathIsRoot(ToStringT(sDir).c_str());
}

UINT ApiWin::ApiGetFileAttributes( const std::string& sDir )
{
	return GetFileAttributes(ToStringT(sDir).c_str());
}

bool ApiWin::IsDir( const std::string& sDir )
{
	UINT uFileAttributes = ApiGetFileAttributes(sDir);
	if (INVALID_FILE_ATTRIBUTES == uFileAttributes)
		return false;
	
	return !!(FILE_ATTRIBUTE_DIRECTORY & uFileAttributes);
}

bool ApiWin::SetConsoleHide()
{
	return TRUE == FreeConsole();
}

UINT64 ApiWin::GetProcessMemoryFree()
{
	MEMORYSTATUSEX status; 
	status.dwLength = sizeof(MEMORYSTATUSEX); 
	GlobalMemoryStatusEx(&status);

	return status.ullAvailPhys;
}

UINT64 ApiWin::GetProcessMemoryTotal()
{
	MEMORYSTATUSEX status; 
	status.dwLength = sizeof(MEMORYSTATUSEX); 
	GlobalMemoryStatusEx(&status);

	return status.ullTotalPhys; 
}

int ApiWin::GetProcessMemoryUsage()
{
	MEMORYSTATUSEX status; 
	status.dwLength = sizeof(MEMORYSTATUSEX); 
	GlobalMemoryStatusEx(&status);
	
	return status.dwMemoryLoad; 
}

UINT64 ApiWin::ApiCreateProcess( const std::string& sExeName,const std::string& sWorkingDir/*=""*/,const std::string& sCommandLine/*=""*/ )
{
	STARTUPINFO StartInfo; 
	PROCESS_INFORMATION pinfo; 
	//对程序的启动信息不作任何设定，全部清0 
	memset(&StartInfo,0,sizeof(STARTUPINFO)); 
	StartInfo.cb = sizeof(STARTUPINFO);//设定结构的大小

	BOOL ret=::CreateProcess( 
		(char_t*)ToStringT(sExeName).c_str(), //启动程序路径名 
		(char_t*)ToStringT(sCommandLine).c_str(), //参数（当exeName为nullptr时，可将命令放入参数前）
		nullptr, //使用默认进程安全属性 
		nullptr, //使用默认线程安全属性
		FALSE,//句柄不继承 
		NORMAL_PRIORITY_CLASS|CREATE_NEW_CONSOLE,//使用正常优先级 
		nullptr, //使用父进程的环境变量 
		sWorkingDir.empty() ? nullptr:ToStringT(sWorkingDir).c_str(), //指定工作目录 
		&StartInfo, //子进程主窗口如何显示 
		&pinfo); //用于存放新进程的返回信息

	return TRUE == ret ? pinfo.dwProcessId : 0;
}

bool ApiWin::TerminateProcess( int nProcessID )
{
	HANDLE hProcess = OpenProcess( PROCESS_ALL_ACCESS, FALSE, nProcessID ); 
	BOOL bSucceed =  ::TerminateProcess(hProcess,0);
	CloseHandle(hProcess);
	return TRUE == bSucceed;
}

int ApiWin::GetProcessIdByExePath( const std::string& sExePath )
{
	PROCESSENTRY32 proc;
	if (!GetProcessEntry32ByExePath(&proc,sExePath))
		return 0;
	return proc.th32ProcessID;
}

bool ApiWin::IsFile( const std::string& sFile )
{
	UINT uFileAttributes = ApiGetFileAttributes(sFile);
	if (INVALID_FILE_ATTRIBUTES == uFileAttributes)
		return false;

	return !(FILE_ATTRIBUTE_DIRECTORY & uFileAttributes);
}

size_t ApiWin::GetFileLength( const std::string& sFileName)
{
	return ApiStd::GetFileLength(sFileName); 
}

std::string ApiWin::GetDirByType( int eDirType )
{
	switch(eDirType)
	{
	case DIR_TYPE_WORKING:
		return GetWorkingDir();
		break;
	case DIR_TYPE_WRITEABLE:
		return GetExeDir();
		break;
	case DIR_TYPE_CACHE:
		return GetExeDir()+"Cache/";
		break;
	case DIR_TYPE_EXT_WORKING:
		return MAKE_STRING("C:/" << GetExeNameWithOutExt()<<"/");
		break;
	case DIR_TYPE_EXT_WRITEABLE:
		return MAKE_STRING("C:/" << GetExeNameWithOutExt() << "/");
		break;
	case DIR_TYPE_EXT_CACHE:
		return MAKE_STRING("C:/" << GetExeNameWithOutExt() << "/Cache/");
		break;
	case DIR_TYPE_EXT_ROOT:
		return "C:/";
		break;
	}

	return "";
}

bool ApiWin::SaveFile( const std::string& sFileName,const void* pBuffer,size_t uLength)
{
	return ApiStd::SaveFile(sFileName,pBuffer,uLength); 
}

bool ApiWin::LoadFile( const std::string& sFileName,void* pBuffer,size_t uLength)
{
	return ApiStd::LoadFile(sFileName,pBuffer,uLength);
}

bool ApiWin::IsFileExist( const std::string& sFileName)
{
	return ApiStd::IsFileExist(sFileName);
}

bool ApiWin::RemoveFile( const std::string& sFileName)
{
	return ApiDeleteFile(sFileName);
}

bool ApiWin::RemoveDir( const std::string sDir)
{
	return ApiRemoveDir(sDir);
}

bool ApiWin::ApiRemoveDir(std::string sDir){
	if (sDir.empty())return false;

	if (IsFile(sDir))
		return ApiDeleteFile(sDir);

	HANDLE   hFile;WIN32_FIND_DATA   wfd;

	sDir = ToolFrame::TrimDir(sDir);

	//首先查找当前目录下指定过滤文件
	const std::string sPath = sDir + "*.*";
	hFile = ApiFindFirstFile(sPath,&wfd);
	if (INVALID_HANDLE_VALUE != hFile)
	{
		do{
			const std::string sFileName = ToMulti(wfd.cFileName);
			if (sFileName == ".")continue;
			if (sFileName == "..")continue;

			//如果是目录则递归 如果是文件则删除
			if (FILE_ATTRIBUTE_DIRECTORY & wfd.dwFileAttributes)
			{
				if (!RemoveDir(sDir + sFileName))return false;
			}else{
				if (!ApiDeleteFile(sDir + sFileName))return false;
			}
		}while(::FindNextFile(hFile,&wfd));
	}
	FindClose(hFile); 

	if (IsDir(sDir))
		if (!ApiRemoveDirectory(sDir))return false;

	return true;
}

std::string ApiWin::GetMacAddress()
{
	return ApiGetFristMacAddress();
}
std::string ApiWin::GetIPAddress()
{
	//1.初始化wsa  
	WSADATA wsaData;  
	int ret=WSAStartup(MAKEWORD(2,2),&wsaData);  
	if (ret!=0)  
		return "";  
	
	//2.获取主机名  
	char hostname[256]={0};  
	ret=gethostname(hostname,sizeof(hostname));  
	if (ret==SOCKET_ERROR)  
		return "";  
	
	//3.获取主机ip  
	HOSTENT* host=gethostbyname(hostname);  
	if (host==NULL)  
		return "";  
	
	//4.转化为char*并拷贝返回  
	return ApiAddrToString(*(in_addr*)*host->h_addr_list);
}

BOOL ApiWin::ApiIsWinVerEqualTo(DWORD dwMajorVersion, DWORD dwMinorVersion)
{
	OSVERSIONINFOEXW osvi = {0};
	DWORDLONG dwlConditionMask = 0;

	// 1、初始化系统版本信息数据结构
	ZeroMemory(&osvi, sizeof(osvi));
	osvi.dwOSVersionInfoSize= sizeof(osvi);
	osvi.dwMajorVersion= dwMajorVersion;
	osvi.dwMinorVersion= dwMinorVersion;

	// 2、初始化条件掩码
	VER_SET_CONDITION(dwlConditionMask, VER_MAJORVERSION, VER_EQUAL);
	VER_SET_CONDITION(dwlConditionMask, VER_MINORVERSION, VER_EQUAL);

	return ::VerifyVersionInfoW(&osvi, VER_MAJORVERSION | VER_MINORVERSION, dwlConditionMask);
}


ApiWin::EWinVer ApiWin::GetPlatformVerEnum()
{
	OSVERSIONINFOEX osVersionInfoEx;
	osVersionInfoEx.dwOSVersionInfoSize=sizeof(osVersionInfoEx);
	if(!GetVersionEx((LPOSVERSIONINFO)&osVersionInfoEx))
		return WIN_VER_INVALID;
	
	switch(osVersionInfoEx.dwPlatformId)
	{
	case VER_PLATFORM_WIN32_NT:
		{
			if (ApiIsWinVerEqualTo(6, 4))
				return WIN_VER_WIN_10;
			if (ApiIsWinVerEqualTo(6, 3))
				return WIN_VER_WIN_8_1;
			if (ApiIsWinVerEqualTo(6, 2))
				return WIN_VER_WIN_8;
			if (ApiIsWinVerEqualTo(6, 1))
				return WIN_VER_WIN_7;
			if (ApiIsWinVerEqualTo(6, 0)) 
				return WIN_VER_WIN_VISTA;
			if (ApiIsWinVerEqualTo(5, 2))
				return WIN_VER_WIN_2003;
			if (ApiIsWinVerEqualTo(5, 1))
				return WIN_VER_WIN_XP;
			if (ApiIsWinVerEqualTo(4, 0))
				return WIN_VER_WIN_NT;
// 			if(osVersionInfoEx.dwMajorVersion==6 && osVersionInfoEx.dwMinorVersion==4)
// 				return WIN_VER_WIN_10;
// 			if(osVersionInfoEx.dwMajorVersion==6 && osVersionInfoEx.dwMinorVersion==3)
// 				return WIN_VER_WIN_8_1;
// 			if(osVersionInfoEx.dwMajorVersion==6 && osVersionInfoEx.dwMinorVersion==2)
// 				return WIN_VER_WIN_8;
// 			if(osVersionInfoEx.dwMajorVersion==6 && osVersionInfoEx.dwMinorVersion==1)
// 				return WIN_VER_WIN_7;
// 			if(osVersionInfoEx.dwMajorVersion==6 && osVersionInfoEx.dwMinorVersion==0)
// 				return WIN_VER_WIN_VISTA;
// 			if(osVersionInfoEx.dwMajorVersion==5 && osVersionInfoEx.dwMinorVersion==0)
// 				return WIN_VER_WIN_2000;
// 			if(osVersionInfoEx.dwMajorVersion==5 && osVersionInfoEx.dwMinorVersion==1)
// 				return WIN_VER_WIN_XP;
// 			if(osVersionInfoEx.dwMajorVersion==4 && osVersionInfoEx.dwMinorVersion==0)
// 				return WIN_VER_WIN_NT;
		}
		break;
	case VER_PLATFORM_WIN32_WINDOWS:
		{
			if(osVersionInfoEx.dwMajorVersion==4 && osVersionInfoEx.dwMinorVersion==10)
				return WIN_VER_WIN_98;
			if(osVersionInfoEx.dwMajorVersion==4 && osVersionInfoEx.dwMinorVersion==90)
				return WIN_VER_WIN_ME;

			return WIN_VER_WIN_95;
		}
		break;
	}

	return WIN_VER_INVALID;
}

std::string ApiWin::GetPlatformVer( EWinVer eWinVer )
{
	switch(eWinVer)
	{
	case WIN_VER_WIN_95:
		return "Windows 95";
		break;
	case WIN_VER_WIN_98:
		return "Windows 98";
		break;
	case WIN_VER_WIN_ME:
		return "Windows ME";
		break;
	case WIN_VER_WIN_NT:
		return "Windows NT";
		break;
	case WIN_VER_WIN_XP:
		return "Windows XP";
		break;
	case WIN_VER_WIN_2000:
		return "Windows 2000";
		break;
	case WIN_VER_WIN_2003:
		return "Windows 2003";
		break;
	case WIN_VER_WIN_VISTA:
		return "Windows Vista";
		break;
	case WIN_VER_WIN_7:
		return "Windows 7";
		break;
	case WIN_VER_WIN_8:
		return "Windows 8";
		break;
	case WIN_VER_WIN_8_1:
		return "Windows 8.1";
		break;
	case WIN_VER_WIN_10:
		return "Windows 10";
		break;
	}

	return "";
}

std::string ApiWin::GetPlatformVer()
{
	return GetPlatformVer(GetPlatformVerEnum());
}

bool ApiWin::GetSystemTimes( uint64* pIdleTime,uint64* pKernelTime,uint64* pUserTime )
{
	FILETIME idleTime;
	FILETIME kernelTime;
	FILETIME userTime;

	if (FALSE == ::GetSystemTimes( &idleTime, &kernelTime, &userTime ))return false;

	*pIdleTime		= ToUint64(idleTime);
	*pKernelTime	= ToUint64(kernelTime);
	*pUserTime		= ToUint64(userTime);

	return true;
}

uint64 ApiWin::ToUint64( const FILETIME& xTime )
{
	uint64 uTime = xTime.dwHighDateTime;
	uTime <<= 32;
	uTime |= xTime.dwLowDateTime ;
	return uTime;
}

bool ApiWin::IsExecutedMulit()
{
	return CalProcessCount(GetExeName()) > 1;
}

int ApiWin::CalProcessCount( const std::string& sExePath )
{
	int nCount = 0;

	PROCESSENTRY32 proc;

	//初始化
	proc.dwSize = sizeof(PROCESSENTRY32);

	HANDLE hProcessSnap = ::CreateToolhelp32Snapshot(TH32CS_SNAPALL,0);//获取当前进程快照

	if (Process32First(hProcessSnap, &proc))
	{
		do 
		{
			if (sExePath == ToMulti(proc.szExeFile))
				++nCount;
		} while (Process32Next(hProcessSnap, &proc));
	}
	::CloseHandle(hProcessSnap);
	return nCount;
}

bool ApiWin::OpenUrl(const std::string& sUrl){
	ShellExecute(nullptr, _T("open"), ToStringT(sUrl).c_str(), nullptr, nullptr, SW_SHOWNORMAL);
	return true;
}

bool ApiWin::DialogFileOpen(VectorString& vPath)
{
	TCHAR szFile[MAX_PATH+1024];
	TCHAR *p = nullptr;
	TCHAR Name[MAX_PATH];

	int i=1;
	memset(szFile,0, sizeof(szFile));
	OPENFILENAME ofn;
	ZeroMemory(&ofn, sizeof(OPENFILENAME));
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = nullptr;
	ofn.lpstrFilter = _T("*.*\0*.*\0");
	ofn.nMaxFile = sizeof(szFile)/sizeof(szFile[0]);
	ofn.lpstrFile = szFile;
	ofn.Flags = OFN_OVERWRITEPROMPT | OFN_HIDEREADONLY | OFN_PATHMUSTEXIST
		| OFN_ALLOWMULTISELECT | OFN_EXPLORER;
	if (GetOpenFileName(&ofn)) 
	{
		p=szFile;
	}

	TCHAR dir_buf[MAX_PATH+1024];
	if(p && p[0])
	{
		_tcscpy(dir_buf,p);
		p = p + _tcslen(dir_buf)+1;
		if(!p[0])
		{
			vPath.push_back(ToMulti(dir_buf));
			return true;
		}
		else
			_tcscat(dir_buf,_T("\\"));
	}

	TCHAR str[MAX_PATH] = {0};
	while(p && p[0])
	{
		_tcscpy(Name, p);
		_tcscat(str,dir_buf);
		_tcscat(str,Name);

		vPath.push_back(ToMulti(str));

		str[0]=0;
		p = p + _tcslen(Name)+1;
	}
	return !vPath.empty();
}

std::string ApiWin::GetModel()
{
	return "Windows";
}

std::string ApiWin::GetNetWorkType()
{
	std::string sNetWork = ApiGetActiveMacNetWorkType();
	if (!sNetWork.empty())return sNetWork;
	return ApiGetFristMacNetWorkType();
}

int ApiWin::GetResolutionWidth()
{
	return GetSystemMetrics(SM_CXSCREEN);
}

int ApiWin::GetResolutionHeight()
{
	return GetSystemMetrics(SM_CYSCREEN);
}

std::string ApiWin::GetOperatorName()
{
	return "";
}

std::string ApiWin::ApiGetFristMacAddress()
{
	std::string sMac;

	ULONG ulOutBufLen = sizeof(IP_ADAPTER_INFO);
	PIP_ADAPTER_INFO pAdapterInfo = (IP_ADAPTER_INFO*)malloc(sizeof(IP_ADAPTER_INFO));
	if(pAdapterInfo == nullptr)
		return false;
	// Make an initial call to GetAdaptersInfo to get the necessary size into the ulOutBufLen variable
	if(GetAdaptersInfo(pAdapterInfo, &ulOutBufLen) == ERROR_BUFFER_OVERFLOW) 
	{
		free(pAdapterInfo);
		pAdapterInfo = (IP_ADAPTER_INFO *)malloc(ulOutBufLen);
		if (pAdapterInfo == nullptr) 
			return false;
	}

	if(GetAdaptersInfo(pAdapterInfo, &ulOutBufLen) == NO_ERROR)
	{
		for(PIP_ADAPTER_INFO pAdapter = pAdapterInfo; pAdapter != nullptr; pAdapter = pAdapter->Next)
		{
			// 确保MAC地址的长度为 00-00-00-00-00-00
			if(pAdapter->AddressLength != 6)
				continue;
			char acMAC[32];
			sprintf_s(acMAC, "%02X-%02X-%02X-%02X-%02X-%02X",
				int (pAdapter->Address[0]),
				int (pAdapter->Address[1]),
				int (pAdapter->Address[2]),
				int (pAdapter->Address[3]),
				int (pAdapter->Address[4]),
				int (pAdapter->Address[5]));
			sMac = acMAC;
			break;
		}
	}

	free(pAdapterInfo);
	return sMac;
}

std::string ApiWin::ApiGetFristMacNetWorkType()
{
	std::string sNetWorkType;

	ULONG ulOutBufLen = sizeof(IP_ADAPTER_INFO);
	PIP_ADAPTER_INFO pAdapterInfo = (IP_ADAPTER_INFO*)malloc(sizeof(IP_ADAPTER_INFO));
	if(pAdapterInfo == nullptr)
		return false;
	// Make an initial call to GetAdaptersInfo to get the necessary size into the ulOutBufLen variable
	if(GetAdaptersInfo(pAdapterInfo, &ulOutBufLen) == ERROR_BUFFER_OVERFLOW) 
	{
		free(pAdapterInfo);
		pAdapterInfo = (IP_ADAPTER_INFO *)malloc(ulOutBufLen);
		if (pAdapterInfo == nullptr) 
			return false;
	}

	if(GetAdaptersInfo(pAdapterInfo, &ulOutBufLen) == NO_ERROR)
	{
		for(PIP_ADAPTER_INFO pAdapter = pAdapterInfo; pAdapter != nullptr; pAdapter = pAdapter->Next)
		{
			// 确保MAC地址的长度为 00-00-00-00-00-00
			if(pAdapter->AddressLength != 6)
				continue;

			sNetWorkType = ApiTranNetWorkType(pAdapter->Type);
		}
	}

	free(pAdapterInfo);
	return sNetWorkType;
}


std::string ApiWin::ApiGetActiveMacNetWorkType()
{
	std::string sNetWorkType;

	ULONG ulOutBufLen = sizeof(IP_ADAPTER_INFO);
	PIP_ADAPTER_INFO pAdapterInfo = (IP_ADAPTER_INFO*)malloc(sizeof(IP_ADAPTER_INFO));
	if(pAdapterInfo == nullptr)
		return false;
	// Make an initial call to GetAdaptersInfo to get the necessary size into the ulOutBufLen variable
	if(GetAdaptersInfo(pAdapterInfo, &ulOutBufLen) == ERROR_BUFFER_OVERFLOW) 
	{
		free(pAdapterInfo);
		pAdapterInfo = (IP_ADAPTER_INFO *)malloc(ulOutBufLen);
		if (pAdapterInfo == nullptr) 
			return false;
	}

	if(GetAdaptersInfo(pAdapterInfo, &ulOutBufLen) == NO_ERROR)
	{
		for(PIP_ADAPTER_INFO pAdapter = pAdapterInfo; pAdapter != nullptr; pAdapter = pAdapter->Next)
		{
			if (TRUE != pAdapterInfo->HaveWins)
				continue;
			
			// 确保MAC地址的长度为 00-00-00-00-00-00
			if(pAdapter->AddressLength != 6)
				continue;

			sNetWorkType = ApiTranNetWorkType(pAdapter->Type);
		}
	}

	free(pAdapterInfo);
	return sNetWorkType;
}

HWND ApiWin::GetConsoleWindow()
{
	return ::GetConsoleWindow();
}

bool ApiWin::ScreenShot( const std::string& sFileName )
{
	CApiWinScreenShot r;
	return r.SavePng(GetConsoleWindow(),sFileName);
}

std::string ApiWin::ApiGetCommandLine()
{
	return ToMulti(::GetCommandLine());
}

std::string ApiWin::ApiGetConsoleTitle()
{
	char_t szTitle[255]={0};
	::GetConsoleTitle(szTitle, sizeof(szTitle)); // 获取窗口标题
	return ToMulti(szTitle);
}

bool ApiWin::ApiSetConsoleTitle( const std::string & sTitle )
{
	return TRUE == ::SetConsoleTitle(ToStringT(sTitle).c_str());
}

CApiWinCpu& ApiWin::GetWinCpu()
{
	static CApiWinCpu g_apiWinCpu;
	return g_apiWinCpu;
}

bool ApiWin::ReflashCpuState()
{
	return GetWinCpu().Reflash();
}

int ApiWin::GetCpuUsage()
{
	return GetWinCpu().CalCpuUsage();
}
uint64 ApiWin::FileTimeToUtc( const FILETIME* ftime )
{
	LARGE_INTEGER li;

	li.LowPart = ftime->dwLowDateTime;
	li.HighPart = ftime->dwHighDateTime;
	return li.QuadPart/10000;
}

int ApiWin::GetProcesserNumber()
{
	SYSTEM_INFO info;
	GetSystemInfo(&info);
	return (int)info.dwNumberOfProcessors;
}

bool ApiWin::GetCpuTime(uint64& uCreationTime, uint64& uExitTime, uint64& uKernelTime, uint64& uUserTime, int nProcessID)
{
	FILETIME creation_time;
	FILETIME exit_time;
	FILETIME kernel_time;
	FILETIME user_time;

	HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, false, nProcessID);
	if (!GetProcessTimes(hProcess, &creation_time, &exit_time, &kernel_time, &user_time))
	{
		CloseHandle(hProcess);
		return false;
	}

	uCreationTime = FileTimeToUtc(&creation_time);
	uExitTime = FileTimeToUtc(&exit_time);
	uKernelTime = FileTimeToUtc(&kernel_time);
	uUserTime = FileTimeToUtc(&user_time);

	CloseHandle(hProcess);
	return true;
}

uint64 ApiWin::GetSystemTime()
{
	FILETIME now;
	GetSystemTimeAsFileTime(&now);
	return FileTimeToUtc(&now);
}

uint64 ApiWin::GetCpuUseTime(int nProcessID)
{
	uint64 uCreationTime = 0, uExitTime = 0, uKernelTime = 0, uUserTime = 0;
	if (!GetCpuTime(uCreationTime, uExitTime, uKernelTime, uUserTime, nProcessID))
		return 0;

	return uKernelTime + uUserTime;
}

int ApiWin::GetCpuUsage(uint64& uCreationTime, uint64& uExitTime, uint64& uKernelTime, uint64& uUserTime, int nProcessID)
{
	//cpu数量
	static int nProcessorCount = GetProcesserNumber();
	if (nProcessorCount <= 0)
		return -1;

	if (!GetCpuTime(uCreationTime, uExitTime, uKernelTime, uUserTime, nProcessID))
		return -1;

	//计算占用时间
	uint64 uSystemTime = GetSystemTime();
	uint64 uUseTime = (uKernelTime + uUserTime) / nProcessorCount;

	//最近一次时间
	static uint64 uLastUseTime = 0, uLastSystemTime = 0;
	if ((uLastSystemTime == 0) || (uLastUseTime == 0))
	{
		uLastSystemTime = uSystemTime;
		uLastUseTime = uUseTime;
		return -1;
	}

	uint64 uSystemTimeDelta = uSystemTime - uLastSystemTime;
	uint64 uUseTimeDelta = uUseTime - uLastUseTime;

	if (uSystemTimeDelta <= 0)
		return -1;

	//计算Cpu使用率
	//int nCpuUseage = (uUseTimeDelta * 100 + uSystemTimeDelta / 2) / uSystemTimeDelta;网上找来的公式

	int nCpuUseage = (int)(uUseTimeDelta * 100 / uSystemTimeDelta);//自己理解的公式

	uLastSystemTime = uSystemTime;
	uLastUseTime = uUseTime;

	return nCpuUseage;
}


int ApiWin::GetCpuUsage( int nProcessID )
{
	uint64 uCreationTime = 0, uExitTime = 0, uKernelTime = 0, uUserTime = 0;
	return GetCpuUsage(uCreationTime, uExitTime, uKernelTime, uUserTime, nProcessID);
}

int ApiWin::GetCpuIdle()
{
	return GetWinCpu().CalCpuIdle();
}

bool ApiWin::PurgeMemory( int nProcessID )
{
	return ApiEmptyWorkingSet(nProcessID);
}

HANDLE ApiWin::ApiGetProcessHandle( int nProcessID )
{
	return OpenProcess(PROCESS_ALL_ACCESS, FALSE, nProcessID);
}

bool ApiWin::SystemReboot()
{
	system( "shutdown -r -t 0" );
	return true;
}

bool ApiWin::SystemShutDown()
{
	system( "shutdown -a" );
	return true;
}

bool ApiWin::SystemLogOut()
{
	system( "shutdown -l" );
	return true;
}

bool ApiWin::SystemSetTime(uint64 uMillTime)
{
	SYSTEMTIME sys_MyLocalTime;
	time_t uTime = uMillTime / 1000;
	struct tm Xt;
	localtime_s(&Xt, &uTime);
	GetLocalTime(&sys_MyLocalTime);
	sys_MyLocalTime.wYear = Xt.tm_year + 1900;
	sys_MyLocalTime.wMonth = Xt.tm_mon + 1;
	sys_MyLocalTime.wDay = Xt.tm_mday;
	sys_MyLocalTime.wHour = Xt.tm_hour;
	sys_MyLocalTime.wMinute = Xt.tm_min;
	sys_MyLocalTime.wSecond = Xt.tm_sec;
	sys_MyLocalTime.wDayOfWeek = Xt.tm_wday;
	sys_MyLocalTime.wMilliseconds = uMillTime % 1000;

	SetLocalTime(&sys_MyLocalTime);
	return true;
}

std::string ApiWin::ApiTranNetWorkType( int eAdapterType )
{
	switch (eAdapterType)
	{
	case MIB_IF_TYPE_ETHERNET:
		return "EtherNet";
		break;
	case MIB_IF_TYPE_TOKENRING:
		return "TokenRing";
		break;
	case MIB_IF_TYPE_FDDI:
		return "FDDI";
		break;
	case MIB_IF_TYPE_PPP:
		return "PPP";
		break;
	case MIB_IF_TYPE_LOOPBACK:
		return "LoopBack";
		break;
	case MIB_IF_TYPE_SLIP:
		return "SLIP";
		break;
	case IF_TYPE_IEEE80211:
		return "Wireless";//无线
		break;
	}

	return MAKE_STRING(eAdapterType);
}

HWND ApiWin::GetHWNDByProcessID( int nProcessID )
{
	HWND hWnd = GetTopWindow(nullptr);
	while(hWnd){
		DWORD dwPid=0;
		DWORD dwTid = GetWindowThreadProcessId(hWnd,&dwPid);
		if (dwTid !=0 && dwPid == nProcessID)
		{
			return hWnd;
		}

		hWnd = GetNextWindow(hWnd,GW_HWNDNEXT);
	}
	return nullptr;
}

bool ApiWin::GetMacFlow(UINT64* upload,UINT64* download){
	if(!upload||!download) return false;

	static bool	s_bInit = false;
	static DWORD s_uLastUpBytes	=0;
	static DWORD s_uLastDownBytes=0;
	static CMutexRecursive s_mutex;

	CLockScoped lock(s_mutex);
	*upload=0;*download=0;

	PMIB_IFTABLE pIfTable=nullptr;
	DWORD dwSize = 0;
	//获取所需要的内存大小
	if(ERROR_INSUFFICIENT_BUFFER != GetIfTable(pIfTable, &dwSize, TRUE))
		return false;

	pIfTable=(PMIB_IFTABLE)malloc(dwSize);
	if (NO_ERROR != GetIfTable(pIfTable, &dwSize, TRUE)){
		free(pIfTable);
		return false;
	}

	//统计网卡总流量
	DWORD uUpBytes=0; DWORD uDownBytes=0;
	for (DWORD uIndex = 0; uIndex < pIfTable->dwNumEntries; ++uIndex){
		PMIB_IFROW pIfRow	=	&pIfTable->table[uIndex];
		uUpBytes	+=	pIfRow->dwOutOctets;
		uDownBytes	+=	pIfRow->dwInOctets;
	}
	
	//判断第一次
	if (!s_bInit)
	{
		*upload		=0;
		*download	=0;
		s_bInit		= true;
	}else{
		*upload		=	uUpBytes-s_uLastUpBytes;
		*download	=	uDownBytes-s_uLastDownBytes;
	}
	s_uLastDownBytes=	uDownBytes;
	s_uLastUpBytes	=	uUpBytes;

	free(pIfTable);
	return true;
}

uint ApiWin::GetThreadAmount(int nProcessID)
{
	if (nProcessID<0)
		nProcessID = GetProcessId();

	PROCESSENTRY32 proc;
	if (!GetProcessEntry32ByProcessID(&proc,nProcessID))
		return 0;
	return proc.cntThreads;
}

std::string ApiWin::TcpInfoToString(const MIB_TCPROW_OWNER_PID* pTcpInfo){
	if (!pTcpInfo)return false;
	
	IN_ADDR     localAddr;    
	IN_ADDR     remoteAddr;   

	USHORT      usLocalPort;    
	USHORT      usRemotePort;  

	localAddr.S_un.S_addr = pTcpInfo->dwLocalAddr;    
	remoteAddr.S_un.S_addr = pTcpInfo->dwRemoteAddr;
	
	std::string sState;
	switch (pTcpInfo->dwState)    
	{    
	case MIB_TCP_STATE_CLOSED:
		sState = "CLOSED";
		break;    
	case MIB_TCP_STATE_LISTEN:    
		sState = "LISTENING"; 
		break;    
	case MIB_TCP_STATE_SYN_SENT:    
		sState = "SYN_SENT";   
		break;    
	case MIB_TCP_STATE_SYN_RCVD:    
		sState = "SYN_RCVD";  
		break;    
	case MIB_TCP_STATE_ESTAB:    
		sState = "ESTABLISHED"; 
		break;    
	case MIB_TCP_STATE_FIN_WAIT1: 
		sState = "FIN_WAIT_1"; 
		break;    
	case MIB_TCP_STATE_FIN_WAIT2: 
		sState = "FIN_WAIT_2";
		break;    
	case MIB_TCP_STATE_CLOSE_WAIT: 
		sState = "CLOSE_WAIT";  
		break;    
	case MIB_TCP_STATE_CLOSING:    
		sState = "CLOSING"; 
		break;    
	case MIB_TCP_STATE_LAST_ACK:    
		sState = "LAST_ACK";     
		break;    
	case MIB_TCP_STATE_TIME_WAIT:    
		sState = "TIME_WAIT";   
		break;    
	case MIB_TCP_STATE_DELETE_TCB:    
		sState = "DELETE_TCB";    
		break;    
	}    
	usLocalPort = ntohs((USHORT) pTcpInfo->dwLocalPort);    
	usRemotePort = sState ==  "LISTENING" ? 0 : ntohs((USHORT) pTcpInfo->dwRemotePort);    

	std::string sLocalAddr	= MAKE_STRING(ApiAddrToString(localAddr)<<":"<<usLocalPort);
	std::string sRemoteAddr = MAKE_STRING(ApiAddrToString(remoteAddr)<<":"<<usRemotePort);

	char szBuffer[2048]={0};
	sprintf(szBuffer, "  %-7s%-23s%-23s%-16s%d-%s", "TCP", sLocalAddr.c_str(), sRemoteAddr.c_str(), sState.c_str(), pTcpInfo->dwOwningPid,GetProcessName(pTcpInfo->dwOwningPid).c_str());    
	return szBuffer;
}

bool ApiWin::FindTcpPort(VectorTcpInfo& vInfo, int nPort)
{
	int                         iErrno;
	PMIB_TCPTABLE_OWNER_PID     pMibTcpTableOwnerPid = NULL;
	DWORD                       dwSize = 0;
	TCHAR                       szBuffer[1024];
	int                         i;

	//获取所需的空间大小
	if ((iErrno = GetExtendedTcpTable(NULL, &dwSize, TRUE, AF_INET, TCP_TABLE_OWNER_PID_ALL, 0)) != NO_ERROR)
	{
		if (iErrno != ERROR_INSUFFICIENT_BUFFER)
		{
			wsprintf(szBuffer, _T("GetExtendedTcpTable Error: %d\n"), iErrno);
			OutputDebugString(szBuffer);
			return FALSE;
		}
	}

	if (dwSize <= 0)return false;

	pMibTcpTableOwnerPid = (PMIB_TCPTABLE_OWNER_PID)malloc(dwSize);
	if (pMibTcpTableOwnerPid == NULL)
	{
		OutputDebugString(_T("malloc Error!\n"));
		return false;
	}

	if ((iErrno = GetExtendedTcpTable(pMibTcpTableOwnerPid, &dwSize, TRUE, AF_INET, TCP_TABLE_OWNER_PID_ALL, 0)) != NO_ERROR)
	{
		wsprintf(szBuffer, _T("GetExtendedTcpTable Error: %d\n"), iErrno);
		OutputDebugString(szBuffer);
		free(pMibTcpTableOwnerPid);
		return false;
	}

	for (i = 0; i < (int)pMibTcpTableOwnerPid->dwNumEntries; i++) {
		const MIB_TCPROW_OWNER_PID& tcpInfo = pMibTcpTableOwnerPid->table[i];
		USHORT uLocalPort = ntohs((USHORT)tcpInfo.dwLocalPort);
		if (uLocalPort == nPort)
		{
			vInfo.push_back(tcpInfo);
		}
	}

	free(pMibTcpTableOwnerPid);
	return !vInfo.empty();
}

std::string ApiWin::GetTcpPortInfoString(int nPort) {
	std::stringstream sStream;

	VectorTcpInfo vInfo;
	if (!FindTcpPort(vInfo, nPort))return "";
	VectorTcpInfo::const_iterator itr;
	foreach(itr, vInfo) {
		sStream << TcpInfoToString(&(*itr)) << std::endl;
	}

	return sStream.str();
}

std::string ApiWin::GetTcpLickInfoString(){
	std::stringstream			sStream;

	int                         iErrno;    
	PMIB_TCPTABLE_OWNER_PID     pMibTcpTableOwnerPid;    
	DWORD                       dwSize = 0;    
	TCHAR                       szBuffer[1024];    
	int                         i;    

	//获取所需的空间大小
	if ((iErrno = GetExtendedTcpTable(NULL, &dwSize, TRUE, AF_INET, TCP_TABLE_OWNER_PID_ALL, 0)) != NO_ERROR)    
	{    
		if (iErrno != ERROR_INSUFFICIENT_BUFFER)    
		{    
			wsprintf(szBuffer, _T("GetExtendedTcpTable Error: %d\n"), iErrno);    
			OutputDebugString(szBuffer);    
			return FALSE;  
		}    
	} 
	if (dwSize <= 0)return false;

	pMibTcpTableOwnerPid = (PMIB_TCPTABLE_OWNER_PID) malloc(dwSize);    
	if (pMibTcpTableOwnerPid == NULL)    
	{    
		OutputDebugString(_T("malloc Error!\n"));    
		return false;  
	}  

	if ((iErrno = GetExtendedTcpTable(pMibTcpTableOwnerPid, &dwSize, TRUE, AF_INET, TCP_TABLE_OWNER_PID_ALL, 0)) != NO_ERROR)    
	{    
		wsprintf(szBuffer, _T("GetExtendedTcpTable Error: %d\n"), iErrno);    
		OutputDebugString(szBuffer);    
		free(pMibTcpTableOwnerPid);
		return false;  
	}  

	for (i = 0; i < (int) pMibTcpTableOwnerPid->dwNumEntries; i++)    
		sStream<<TcpInfoToString(&pMibTcpTableOwnerPid->table[i])<<std::endl;

	free(pMibTcpTableOwnerPid);    
	return sStream.str();  
}

std::string ApiWin::GetUdpPortInfoString( int nPort )
{
	std::stringstream sStream;

	VectorUdpInfo vInfo;
	if (!FindUdpPort(vInfo, nPort))return "";
	VectorUdpInfo::const_iterator itr;
	foreach(itr, vInfo) {
		sStream << UdpInfoToString(&(*itr)) << std::endl;
	}

	return sStream.str();
}

std::string ApiWin::GetUdpLickInfoString()
{
	std::stringstream			sStream;

	int                         iErrno;    
	PMIB_UDPTABLE_OWNER_PID     pMibTcpTableOwnerPid;    
	DWORD                       dwSize = 0;    
	TCHAR                       szBuffer[1024];    
	int                         i;    

	//获取所需的空间大小
	if ((iErrno = GetExtendedUdpTable(NULL, &dwSize, TRUE, AF_INET, UDP_TABLE_OWNER_PID, 0)) != NO_ERROR)    
	{    
		if (iErrno != ERROR_INSUFFICIENT_BUFFER)    
		{    
			wsprintf(szBuffer, _T("GetExtendedUdpTable Error: %d\n"), iErrno);    
			OutputDebugString(szBuffer);    
			return FALSE;  
		}    
	} 
	if (dwSize <= 0)return false;

	pMibTcpTableOwnerPid = (PMIB_UDPTABLE_OWNER_PID) malloc(dwSize);    
	if (pMibTcpTableOwnerPid == NULL)    
	{    
		OutputDebugString(_T("malloc Error!\n"));    
		return false;  
	}  

	if ((iErrno = GetExtendedUdpTable(pMibTcpTableOwnerPid, &dwSize, TRUE, AF_INET, UDP_TABLE_OWNER_PID, 0)) != NO_ERROR)    
	{    
		wsprintf(szBuffer, _T("GetExtendedUdpTable Error: %d\n"), iErrno);    
		OutputDebugString(szBuffer);    
		free(pMibTcpTableOwnerPid);
		return false;  
	}

	for (i = 0; i < (int) pMibTcpTableOwnerPid->dwNumEntries; i++)    
		sStream<<UdpInfoToString(&pMibTcpTableOwnerPid->table[i])<<std::endl;

	free(pMibTcpTableOwnerPid);    
	return sStream.str();  
}

bool ApiWin::FindUdpPort(VectorUdpInfo& vInfo, int nPort)
{
	bool						bFind = false;
	int                         iErrno;
	PMIB_UDPTABLE_OWNER_PID     pMibTcpTableOwnerPid;
	DWORD                       dwSize = 0;
	TCHAR                       szBuffer[1024];
	int                         i;

	//获取所需的空间大小
	if ((iErrno = GetExtendedUdpTable(NULL, &dwSize, TRUE, AF_INET, UDP_TABLE_OWNER_PID, 0)) != NO_ERROR)
	{
		if (iErrno != ERROR_INSUFFICIENT_BUFFER)
		{
			wsprintf(szBuffer, _T("GetExtendedUdpTable Error: %d\n"), iErrno);
			OutputDebugString(szBuffer);
			return FALSE;
		}
	}
	if (dwSize <= 0)return false;

	pMibTcpTableOwnerPid = (PMIB_UDPTABLE_OWNER_PID)malloc(dwSize);
	if (pMibTcpTableOwnerPid == NULL)
	{
		OutputDebugString(_T("malloc Error!\n"));
		return false;
	}

	if ((iErrno = GetExtendedUdpTable(pMibTcpTableOwnerPid, &dwSize, TRUE, AF_INET, UDP_TABLE_OWNER_PID, 0)) != NO_ERROR)
	{
		wsprintf(szBuffer, _T("GetExtendedUdpTable Error: %d\n"), iErrno);
		OutputDebugString(szBuffer);
		free(pMibTcpTableOwnerPid);
		return false;
	}

	for (i = 0; i < (int)pMibTcpTableOwnerPid->dwNumEntries; i++) {
		const MIB_UDPROW_OWNER_PID& tcpInfo = pMibTcpTableOwnerPid->table[i];
		USHORT uLocalPort = ntohs((USHORT)tcpInfo.dwLocalPort);
		if (uLocalPort == nPort)
		{
			vInfo.push_back(tcpInfo);
		}
	}

	free(pMibTcpTableOwnerPid);
	return !vInfo.empty();
}

bool ApiWin::IsPortOccupied(int nPort)
{
	VectorTcpInfo vTcp;
	if (FindTcpPort(vTcp, nPort))return true;

	VectorUdpInfo vUdp;
	if (FindUdpPort(vUdp, nPort))return true;
	return false;
}

std::string ApiWin::UdpInfoToString(const MIB_UDPROW_OWNER_PID* pTcpInfo)
{
	if (!pTcpInfo)return false;

	IN_ADDR     localAddr;    

	USHORT      usLocalPort;    

	localAddr.S_un.S_addr = pTcpInfo->dwLocalAddr;    

	usLocalPort = ntohs((USHORT) pTcpInfo->dwLocalPort);    

	std::string sLocalAddr	= MAKE_STRING(ApiAddrToString(localAddr)<<":"<<usLocalPort);

	char szBuffer[2048]={0};
	sprintf(szBuffer, "  %-7s%-23s%d-%s", "UDP", sLocalAddr.c_str(), pTcpInfo->dwOwningPid,GetProcessName(pTcpInfo->dwOwningPid).c_str());    
	return szBuffer;
}

std::string ApiWin::ApiAddrToString( struct in_addr in )
{
	const char *p = inet_ntoa(in);
	if (!p)return "";
	return p;
}

bool ApiWin::ApiEmptyWorkingSet( int nProcessID )
{
	if (nProcessID < 0)
	{
		HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
		if (INVALID_HANDLE_VALUE == hSnapshot)return false;

		PROCESSENTRY32 pe = { sizeof(pe) };
		BOOL fOk;
		for (fOk = Process32First(hSnapshot, &pe); fOk; fOk = Process32Next(hSnapshot, &pe))
		{
			HANDLE hHandle = ApiWin::ApiGetProcessHandle(pe.th32ProcessID);
			EmptyWorkingSet(hHandle);
		}
		CloseHandle(hSnapshot);
		return true; 
	}

	HANDLE hHandle = ApiGetProcessHandle(nProcessID);
	return TRUE == EmptyWorkingSet(hHandle);
}

bool ApiWin::IsMicroUtfLead( const std::string& sSrc ) 

{
	if (sSrc.empty())return false;
	if (sSrc.length() < GetMicroUtfLeadLength())return false;

	const unsigned char* pU = (const unsigned char*)sSrc.c_str();
	return *(pU+0) && *(pU+0) == MICRO_UTF_LEAD_0
		&& *(pU+1) && *(pU+1) == MICRO_UTF_LEAD_1
		&& *(pU+2) && *(pU+2) == MICRO_UTF_LEAD_2 ;
}

uint ApiWin::GetMicroUtfLeadLength() 
{
	return sizeof(MICRO_UTF_LEAD_0) + sizeof(MICRO_UTF_LEAD_1) + sizeof(MICRO_UTF_LEAD_2);
}

std::string ApiWin::GetCallStack(HANDLE hProcess, HANDLE hThread) {
	std::stringstream sStream;

	CONTEXT context;

	if (NULL == hProcess)
		hProcess = GetCurrentProcess();
	if (NULL == hThread)
		hThread = GetCurrentThread();

	GetThreadContext(hThread, &context);
	__asm {call $ + 5}
	__asm {pop eax}
	__asm {mov context.Eip, eax}
	__asm {mov context.Ebp, ebp}
	__asm {mov context.Esp, esp}

	SymInitialize(hProcess, NULL, TRUE);

	STACKFRAME sf = { 0 };

	sf.AddrPC.Offset = context.Eip;
	sf.AddrPC.Mode = AddrModeFlat;

	sf.AddrFrame.Offset = context.Ebp;
	sf.AddrFrame.Mode = AddrModeFlat;

	sf.AddrStack.Offset = context.Esp;
	sf.AddrStack.Mode = AddrModeFlat;

	typedef struct tag_SYMBOL_INFO
	{
		IMAGEHLP_SYMBOL symInfo;
		TCHAR szBuffer[MAX_PATH];
	} SYMBOL_INFO, *LPSYMBOL_INFO;

	DWORD dwDisplament = 0;
	SYMBOL_INFO stack_info = { 0 };
	PIMAGEHLP_SYMBOL pSym = (PIMAGEHLP_SYMBOL)&stack_info;
	pSym->SizeOfStruct = sizeof(IMAGEHLP_SYMBOL);
	pSym->MaxNameLength = sizeof(SYMBOL_INFO) - offsetof(SYMBOL_INFO, symInfo.Name);
	IMAGEHLP_LINE ImageLine = { 0 };
	ImageLine.SizeOfStruct = sizeof(IMAGEHLP_LINE);

	while (StackWalk(IMAGE_FILE_MACHINE_I386, hProcess, hThread, &sf, &context, NULL, SymFunctionTableAccess, SymGetModuleBase, NULL))
	{
		SymGetSymFromAddr(hProcess, sf.AddrPC.Offset, &dwDisplament, pSym);
		SymGetLineFromAddr(hProcess, sf.AddrPC.Offset, &dwDisplament, &ImageLine);
		char szBuffer[1024] = { 0 };
		sprintf_s(szBuffer, "CallStack: %08x %30s  (FILE:%s LINE:%d)\n", pSym->Address, pSym->Name, ImageLine.FileName, ImageLine.LineNumber);
		sStream << szBuffer;
	}

	SymCleanup(hProcess);
	return sStream.str();
}

std::string ApiWin::GetCallStackAll() {
	std::stringstream sStream;

	HANDLE hCtSnpShot = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0);//枚举当前系统进程的线程
	if (INVALID_HANDLE_VALUE == hCtSnpShot)
		return "";

	THREADENTRY32 threadentry;
	threadentry.dwSize = sizeof(THREADENTRY32);
	if (!Thread32First(hCtSnpShot, &threadentry)) {
		CloseHandle(hCtSnpShot);
		return "";
	}

	DWORD uProcessID = GetCurrentProcessId();
	HANDLE hProcess = GetCurrentProcess();
	
	do
	{
		if (threadentry.th32OwnerProcessID == uProcessID)
		{
			HANDLE hThread = OpenThread(PROCESS_ALL_ACCESS, true, threadentry.th32ThreadID);

			sStream << "ThreadID:" << threadentry.th32ThreadID << std::endl;
			sStream << GetCallStack(hProcess, hThread);
			CloseHandle(hThread);
		}

	} while (Thread32Next(hCtSnpShot, &threadentry));

	return sStream.str();
}

//UINT64 ApiWin::GetSysTickCount64()
//{
//	static LARGE_INTEGER TicksPerSecond = {0};
//	LARGE_INTEGER Tick; 
//
//	if(!TicksPerSecond.QuadPart)
//	{
//		QueryPerformanceFrequency(&TicksPerSecond);
//	} 
//
//	QueryPerformanceCounter(&Tick); 
//
//	UINT64 Seconds = Tick.QuadPart/TicksPerSecond.QuadPart;
//	UINT64 LeftPart = Tick.QuadPart - (TicksPerSecond.QuadPart*Seconds);
//	UINT64 MillSeconds = LeftPart*1000/TicksPerSecond.QuadPart;
//	UINT64 Ret = Seconds*1000+MillSeconds;
//	_ASSERT(Ret>0);
//	return Ret;
//
//	return 0;
//}
//
//UINT64 ApiWin::GetTickCount64()
//{
//	return ::GetTickCount64();
//
//	return 0;
//}
//
//UINT64 ApiWin::GetTickCount()
//{
//	return ::GetTickCount();
//
//	return 0;
//}

#endif
