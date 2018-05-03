#include "ToolPlat.h"

#include <assert.h>

#include "MacroDefineBoost.h"

#include "TArray.h"
#include "ToolStd.h"
#include "ToolHttp.h"

#include "ApiStd.h"

std::string ToolFrame::LoadFile( const std::string& sFileName ,int eDirType /*= DIR_TYPE_WORKING*/ )
{
	if (sFileName.empty())return ToolFrame::EmptyString();

	//使得系统变得迟缓
	DebugCrack();

	//整理
	std::string sFullPath = SearchFile(sFileName,eDirType);
	if (sFullPath.empty())return "";

	size_t uFileLen = GetFileLength(sFullPath,eDirType);
	if (uFileLen <=0 )return ToolFrame::EmptyString();

	ToolFrame::TArrayNew<char> buffer(uFileLen+1);
	buffer.SetZeroEnd();//设置结尾符号
	if (!LoadFile(sFullPath,buffer.GetPtr(),uFileLen,eDirType))return ToolFrame::EmptyString();

	return buffer.GetPtr();
}

bool ToolFrame::SaveFile( const std::string& sFileName,const std::string& sContent ,int eDirType /*= DIR_TYPE_WRITEABLE*/ )
{
	//工作目录视为不可写
	if (DIR_TYPE_WORKING == eDirType)return false;

	return SaveFile(sFileName,sContent.c_str(),sContent.length(),eDirType);
}

bool ToolFrame::LoadFile( const std::string& sFileName,void* pBuffer,size_t uLength,int eDirType /*= DIR_TYPE_WORKING*/ )
{
	if (sFileName.empty())return false;
	if (!pBuffer)return false;
	if (uLength<=0)return false;

	//使得系统变得迟缓
	DebugCrack();

	//整理
	std::string sFullPath = SearchFile(sFileName,eDirType);
	if (sFullPath.empty())return "";

	return GetApiTool()->LoadFile(sFullPath,pBuffer,uLength);
}

bool ToolFrame::SaveFile( const std::string& sFileName,const void* pBuffer,size_t uLength,int eDirType /*= DIR_TYPE_WRITEABLE*/ )
{
	if (sFileName.empty())return false;
	if (!pBuffer)return false;
	if (uLength<=0)return false;

	//工作目录视为不可写
	if (DIR_TYPE_WORKING == eDirType)return false;

	//使得系统变得迟缓
	DebugCrack();

	std::string sFullPath = FullPath(sFileName,eDirType);
	if (sFullPath.empty())return false;

	return GetApiTool()->SaveFile(sFullPath,pBuffer,uLength);
}

UINT64 ToolFrame::GetNowTimeMill()
{
	return GetApiTool()->GetNowTimeMill();
}

time_t ToolFrame::GetNowTime()
{
	return GetNowTimeMill() / 1000;//为了保证GetNowTime GetNowTimeMill 两个函数获取时间一致
}

const std::string& ToolFrame::GetNowTimeString()
{
	static std::string		sTime;
	static time_t			uTimeLast=0;
	static CMutexRecursive	mutex;

	CLockScoped lock(mutex);
	time_t uTime = GetNowTime();
	if (uTimeLast != uTime)
	{
		sTime = TimeToString(uTime);
		uTimeLast = uTime;
	}

	return sTime;
}

std::string ToolFrame::GetNowTimeString(const std::string& sFormat)
{
	time_t uTime = GetNowTime();
	return TimeToString(uTime,sFormat);
}

void ToolFrame::SetConsoleTextAttribute( int nColor )
{
	return GetApiTool()->SetConsoleTextAttribute(nColor);
}

void ToolFrame::Sleep( UINT64 nTimeMill )
{
	return GetApiTool()->Sleep(nTimeMill);
}

std::string ToolFrame::GetProcessName( int nProcessID )
{
	return GetApiTool()->GetProcessName(nProcessID);
}

std::string ToolFrame::GetProcessNameWithOutExt( int nProcessID )
{
	return GetApiTool()->GetProcessNameWithOutExt(nProcessID);
}

std::string ToolFrame::GetProcessNameWithOutExt()
{
	return GetApiTool()->GetProcessNameWithOutExt();
}

int ToolFrame::GetProcessId()
{
	return GetApiTool()->GetProcessId();
}

bool ToolFrame::SetWorkingDirWithExeDir()
{
	return GetApiTool()->SetWorkingDirWithExeDir();
}

// time_t ToolFrame::GetNowTime()
// {
// #if MACRO_TARGET_OS == MACRO_OS_WINDOWS
// 	return ApiWin::GetNowTime();
// #endif
// #if MACRO_TARGET_OS == MACRO_OS_LINUX
// 	return ApiLinux::GetNowTime();
// #endif
// 
// 	assert(false);
// 	return 0;
// }

// std::string ToolFrame::GetNowTimeString()
// {
// 	return ToolFrame::TimeToString(GetNowTime());
// }

std::string ToolFrame::GetProcessDir()
{
	return GetApiTool()->GetProcessDir();
}

std::string ToolFrame::GetProcessPath()
{
	return GetApiTool()->GetProcessPath();
}

std::string ToolFrame::GetAbsPathByRelativePath( const std::string& sPath )
{
	return GetWorkingDir() + sPath;
}

std::string ToolFrame::GetAbsPath( const std::string& sPath )
{
	if (IsAbsPath(sPath))return sPath;
	return GetAbsPathByRelativePath(sPath);
}

bool ToolFrame::IsAbsPath( const std::string& sPath )
{
	return GetApiTool()->IsAbsPath(sPath);
}

uint64 ToolFrame::GetThreadId()
{
	return GetApiTool()->GetThreadId();
}

uint ToolFrame::GetThreadAmount()
{
	return GetApiTool()->GetThreadAmount();
}

bool ToolFrame::MakeDir( const std::string& sDir,int eDirType )
{
	if (sDir.empty())return false;
	std::string sFullPath = FullPathDir(sDir,eDirType);
	if (sFullPath.empty())return false;
	return GetApiTool()->MakeDir(sFullPath);
}

int ToolFrame::GetLanguage()
{
	return GetApiTool()->TranLanguageString(GetApiTool()->GetLanguageString());
}

std::string ToolFrame::GetLanguageString()
{
	return GetApiTool()->GetLanguageString();
}

void ToolFrame::OutPut( const std::string& sMsg,const std::string& sTag ,bool bTrace)
{
	return GetApiTool()->OutPut(sMsg,sTag,bTrace);
}

void ToolFrame::ClearScreen()
{
	return GetApiTool()->ClearScreen();
}

size_t ToolFrame::GetFileLength( const std::string& sFileName,int eDirType /*= DIR_TYPE_WORKING*/ )
{
	std::string sFullPath = SearchFile(sFileName,eDirType);
	if (sFullPath.empty())return 0;
	return GetApiTool()->GetFileLength(sFullPath);
}

bool ToolFrame::IsFileExist( const std::string& sFileName,int eDirType /*= DIR_TYPE_WORKING*/ )
{
	std::string sFullPath = SearchFile(sFileName,eDirType);
	return !sFullPath.empty();
}

bool ToolFrame::RemoveFile( const std::string& sFileName,int eDirType /*= DIR_TYPE_WRITEABLE*/ )
{
	//工作目录视为不可写
	if (DIR_TYPE_WORKING == eDirType)return false;
	std::string sFullPath = FullPath(sFileName,eDirType);
	if (sFullPath.empty())return false;
	return GetApiTool()->RemoveFile(sFullPath);
}

bool ToolFrame::RenameFile( const std::string& sPathSrc,const std::string& sPathDes,int eDirType /*= DIR_TYPE_WRITEABLE*/ )
{
	//工作目录视为不可写
	if (DIR_TYPE_WORKING == eDirType)return false;

	std::string sFullPathSrc = FullPath(sPathSrc,eDirType);
	if (sFullPathSrc.empty())return false;
	std::string sFullPathDes = FullPath(sPathDes,eDirType);
	if (sFullPathDes.empty())return false;

	return GetApiTool()->RenameFile(sFullPathSrc,sFullPathDes);
}

bool ToolFrame::RemoveDir( const std::string& sDir,int eDirType /*= DIR_TYPE_WRITEABLE*/ )
{
	//工作目录视为不可写
	if (DIR_TYPE_WORKING == eDirType)return false;
	if (sDir.empty())return false;
	std::string sFullPath = FullPathDir(sDir,eDirType);
	if (sFullPath.empty())return false;
	return GetApiTool()->RemoveDir(sFullPath);
}

bool ToolFrame::SetConsoleHide()
{
	return GetApiTool()->SetConsoleHide();
}

std::string ToolFrame::GetConsoleTitle()
{
	return GetApiTool()->ApiGetConsoleTitle();
}

bool ToolFrame::SetConsoleTitle( const std::string & sTitle )
{
	return GetApiTool()->ApiSetConsoleTitle(sTitle);
}

static ToolFrame::IApiTool* g_pToolFrameApiTool=nullptr;

ToolFrame::IApiTool* ToolFrame::GetApiTool()
{
	if (!g_pToolFrameApiTool)
		g_pToolFrameApiTool = GetApiToolDefault();
	return g_pToolFrameApiTool;
}

void ToolFrame::SetApiTool( IApiTool* pApiTool )
{
	g_pToolFrameApiTool = pApiTool;
}

ToolFrame::IApiTool* ToolFrame::GetApiToolDefault()
{
	static IApiTool api;
	return &api;
}

UINT64 ToolFrame::GetProcessMemoryFree()
{
	return GetApiTool()->GetProcessMemoryFree();
}

uint64 ToolFrame::GetProcessMemoryTotal()
{
	return GetApiTool()->GetProcessMemoryTotal();
}

UINT64 ToolFrame::CreateProcess( const std::string& sExePath,const std::string& sWorkingDir/*=""*/,const std::string& sCommandLine/*=""*/ )
{
	return GetApiTool()->ApiCreateProcess(sExePath,sWorkingDir,sCommandLine);
}

std::string ToolFrame::GetCommandLine()
{
	return GetApiTool()->ApiGetCommandLine();
}

int ToolFrame::GetProcessIdByExePath( const std::string& sExePath )
{
	return GetApiTool()->GetProcessIdByExePath(sExePath);
}

bool ToolFrame::TerminateProcess( int nProcessID )
{
	return GetApiTool()->TerminateProcess(nProcessID);
}

bool ToolFrame::CopyDir( const std::string& sSrcDir,const std::string& sDesDir )
{
	return GetApiTool()->CopyDir(sSrcDir,sDesDir);
}

int ToolFrame::GetPlatform()
{
	return GetApiTool()->GetPlatform();
}

std::string ToolFrame::GetPlatformString()
{
	return GetApiTool()->ToPlatformString(GetApiTool()->GetPlatform());
}

std::string ToolFrame::ToPlatformString( int ePlatform )
{
	return GetApiTool()->ToPlatformString(ePlatform);
}

std::string ToolFrame::GetPlatformVer()
{
	return GetApiTool()->GetPlatformVer();
}

uint64 ToolFrame::GetProcessMemoryUsed( int nProcessID )
{
	return GetApiTool()->GetProcessMemoryUsed(nProcessID);
}

std::string ToolFrame::GetMacAddress()
{
	return GetApiTool()->GetMacAddress();
}

std::string ToolFrame::GetIPAddress()
{
	return GetApiTool()->GetIPAddress();
}

std::string ToolFrame::GetModel()
{
	return GetApiTool()->GetModel();
}

bool ToolFrame::IsExecutedMulit()
{
	return GetApiTool()->IsExecutedMulit();
}

bool ToolFrame::OpenUrl( const std::string& sUrl )
{
	return GetApiTool()->OpenUrl(GetFullUrl(sUrl));
}

std::string ToolFrame::GetNetWorkType()
{
	return GetApiTool()->GetNetWorkType();
}

int ToolFrame::GetResolutionWidth()
{
	return GetApiTool()->GetResolutionWidth();
}

int ToolFrame::GetResolutionHeight()
{
	return GetApiTool()->GetResolutionHeight();
}

std::string ToolFrame::GetOperatorName()
{
	return GetApiTool()->GetOperatorName();
}

int ToolFrame::TranPlatformString( const std::string& sPlatform )
{
	return GetApiTool()->TranPlatformString(sPlatform);
}

std::string ToolFrame::ToLanguageString(int eLanguage)
{
	return GetApiTool()->ToLanguageString(eLanguage);
}

int ToolFrame::TranLanguageString(const std::string& sLanguage)
{
	return GetApiTool()->TranLanguageString(sLanguage);
}

std::string ToolFrame::GetTodayDateString()
{
	return DateToString(GetNowTime());
}

bool ToolFrame::ReplaceFileContent( const std::string& sFile,const std::string& sSrc,const std::string& sDes )
{
	std::string sContent = ToolFrame::LoadFile(sFile);
	if (sContent.empty())return false;

	long nReplaced = ToolFrame::Replace(sContent,sSrc,sDes);
	if (nReplaced<=0)return true;

	return ToolFrame::SaveFile(sFile,sContent);
}

bool ToolFrame::ReplaceFileContent(const std::string& sFile,const MapStringString& vMapString){
	std::string sContent = ToolFrame::LoadFile(sFile);
	if (sContent.empty())return false;

	long nReplaced = ToolFrame::Replace(sContent,vMapString);
	if (nReplaced<=0)return true;

	return ToolFrame::SaveFile(sFile,sContent);
}

bool ToolFrame::ScreenShot( const std::string& sFileName )
{
	return GetApiTool()->ScreenShot(sFileName);
}

bool ToolFrame::InitSearchDir()
{
	AddSearchDir(GetDirByType(DIR_TYPE_WORKING));
	AddSearchDir(GetDirByType(DIR_TYPE_PATCH));
	return true;
}

VectorString& ToolFrame::GetSearchDir()
{
	static VectorString g_vSearchDir;
	return g_vSearchDir;
}

bool ToolFrame::AddSearchDir( const std::string& sDir)
{
	if (IsInSearchDir(sDir))return false;

	VectorString& vSearchDir = GetSearchDir();
	vSearchDir.push_back(sDir);
	return true;
}

bool ToolFrame::IsInSearchDir( const std::string& sDir )
{
	return ToolFrame::IsHasValue(GetSearchDir(),sDir);
}

std::string ToolFrame::SearchFile( const std::string& sFileName )
{
	if (sFileName.empty())return ToolFrame::EmptyString();

	CLockScoped lock(GetMutexFileIndex());

	//整理路径
	std::string sFile = ApiStd::TrimPath(sFileName);

	if (ToolFrame::IsAbsPath(sFile))
		return GetApiTool()->IsFileExist(sFile) ? sFile:ToolFrame::EmptyString();

	//如果文件搜索过
	if (ToolFrame::IsHasFileIndex(sFileName))
		return GetFileIndex(sFileName);

	//相对路径
	VectorString::const_reverse_iterator itr;
	foreachR(itr,ToolFrame::GetSearchDir()){
		const std::string& sDir = *itr;

		std::string sFileName = sDir + sFile;
		if (GetApiTool()->IsFileExist(sFileName)){
			ToolFrame::AddFileIndex(sFile,sFileName);

			if (ToolFrame::IsCheckFileCaseSensitive() && !IsFileCaseSensitive(sFileName))
				ToolFrame::OutPut(MAKE_STRING("File: "<<sFileName<<" CaseSensitive!"));

			return sFileName;
		}
	}

	ToolFrame::AddFileIndex(sFile,ToolFrame::EmptyString());
	return ToolFrame::EmptyString();
}

std::string ToolFrame::SearchFile( const std::string& sFileName,int eDirType )
{
	CLockScoped lock(GetMutexFileIndex());

	if (!IsAbsPath(sFileName))
		return SearchFile(GetDirByType(eDirType)+sFileName);

	return SearchFile(sFileName);
}

std::string ToolFrame::ReSearchFile( const std::string& sFileName )
{
	if (sFileName.empty())return ToolFrame::EmptyString();

	CLockScoped lock(GetMutexFileIndex());

	RemoveFileIndex(sFileName);
	return SearchFile(sFileName);
}

bool ToolFrame::ReflashCpuState()
{
	return GetApiTool()->ReflashCpuState();
}

int ToolFrame::GetCpuUsage()
{
	return GetApiTool()->GetCpuUsage();
}

uint64 ToolFrame::GetCpuUseTime(int nProcessID)
{
	return GetApiTool()->GetCpuUseTime(nProcessID);
}

int ToolFrame::GetCpuUsage( int nProcessID )
{
	return GetApiTool()->GetCpuUsage(nProcessID);
}

int ToolFrame::GetCpuIdle()
{
	return GetApiTool()->GetCpuIdle();
}

int ToolFrame::GetProcessMemoryUsage()
{
	return GetApiTool()->GetProcessMemoryUsage();
}

bool ToolFrame::PurgeMemory( int nProcessID /*= -1*/ )
{
	return GetApiTool()->PurgeMemory(nProcessID);
}

bool ToolFrame::SystemReboot()
{
	return GetApiTool()->SystemReboot();
}

bool ToolFrame::SystemShutDown()
{
	return GetApiTool()->SystemShutDown();
}

bool ToolFrame::SystemLogOut()
{
	return GetApiTool()->SystemLogOut();
}

bool ToolFrame::IsPad()
{
	return GetApiTool()->IsPad();
}

bool ToolFrame::Vibrator(int nMillTime)
{
	return GetApiTool()->Vibrator(nMillTime);
}

bool ToolFrame::PlayVideo(const std::string& sUrl)
{
	return GetApiTool()->PlayVideo(sUrl);
}

bool ToolFrame::DebugCrack()
{
	if (IsDebugCrack() && IsDebugVer())
		ToolFrame::Sleep(100);

	return true;
}

bool ToolFrame::DebugSetCrack(bool bCrack /*= true*/)
{
	IsDebugCrack() = bCrack;
	return true;
}

bool& ToolFrame::IsDebugCrack()
{
	static bool g_bSystemCrack = false;
	return g_bSystemCrack;
}

std::string ToolFrame::GetCallStack()
{
	return GetApiTool()->GetCallStack();
}

std::string ToolFrame::GetCallStackAll()
{
	return GetApiTool()->GetCallStackAll();
}

time_t ToolFrame::CalLocalHour(int tTime)
{
	return ToolFrame::CalLocalHour(tTime,GetNowTime());
}

time_t ToolFrame::CalLocalNextHour( int tTime )
{
	return ToolFrame::CalLocalNextHour(tTime,GetNowTime());
}

time_t ToolFrame::CalLocalToNextHour( int tTime )
{
	return ToolFrame::CalLocalToNextHour(tTime,GetNowTime());
}

int ToolFrame::GetCompileVer()
{
	return GetApiTool()->GetCompileVer();
}

bool ToolFrame::IsDebugVer()
{
	return GetApiTool()->IsDebugVer();
}

bool ToolFrame::IsReleaseVer()
{
	return GetApiTool()->IsReleaseVer();
}

bool ToolFrame::GetMacFlow( UINT64* upload,UINT64* download )
{
	return GetApiTool()->GetMacFlow(upload,download);
}

std::string ToolFrame::GetDeviceID()
{
	return GetApiTool()->GetDeviceID();
}

MapStringString& ToolFrame::GetFileIndex()
{
	static MapStringString g_vSearchFile;
	return g_vSearchFile;
}

std::string ToolFrame::GetFileIndex( const std::string& sFileName )
{
	return ToolFrame::GetValueByKey(GetFileIndex(),sFileName,"");
}

bool ToolFrame::IsHasFileIndex( const std::string& sFile )
{
	return ToolFrame::IsHasKey(GetFileIndex(),sFile);
}

bool ToolFrame::AddFileIndex( const std::string& sFileName,const std::string& sPath )
{
	return ToolFrame::SafeInsert(GetFileIndex(),sFileName,sPath);
}

bool ToolFrame::RemoveFileIndex( const std::string& sKey )
{
	return ToolFrame::EraseByKey(GetFileIndex(),sKey) > 0;
}

bool ToolFrame::RemoveFileIndex()
{
	ToolFrame::Clear(GetFileIndex());
	return true;
}

bool ToolFrame::IsPayNet()
{
	//凡是认不到的网络都算做付费网络
	return !IsFreeNet();
}

bool ToolFrame::IsFreeNet()
{
	std::string sNetWorkType = GetNetWorkType();
	if (sNetWorkType == "wifi")
		return true;
	if (sNetWorkType == "lan")
		return true;

	if (sNetWorkType == "EtherNet")
		return true;
	if (sNetWorkType == "TokenRing")
		return true;
	if (sNetWorkType == "FDDI")
		return true;
	if (sNetWorkType == "PPP")
		return true;
	if (sNetWorkType == "LoopBack")
		return true;
	if (sNetWorkType == "SLIP")
		return true;
	if (sNetWorkType == "Wireless")
		return true;
	
	return false;
}

std::string ToolFrame::FullPath( const std::string& sFileName,int eDirType )
{
	if (ToolFrame::IsAbsPath(sFileName))
		return sFileName;

	return GetDirByType(eDirType) + sFileName;
}

std::string ToolFrame::FullPathDir( const std::string& sDir,int eDirType )
{
	if (ToolFrame::IsAbsPath(sDir))
		return sDir;
	
	return GetDirByType(eDirType) + sDir;
}

std::string ToolFrame::SmartSearchPath( const std::string& sFileName )
{
	CLockScoped lock(GetMutexFileIndex());

	std::string sFile = ApiStd::TrimPath(sFileName);
	if (!ToolFrame::IsAbsPath(sFile)){
		return ToolFrame::SearchFile(sFile);
	}
	
	//除去开头 目录 尝试到其他目录下去寻找
	const VectorString& vSearchDir = ToolFrame::GetSearchDir();
	VectorString::const_reverse_iterator itr;
	foreachR(itr,vSearchDir){
		const std::string& sDir = *itr;
		if (ToolFrame::IsBeginWith(sFile,sDir))
		{
			std::string sNewFile = sFile;
			ToolFrame::Replace(sNewFile,sDir,"");

			sNewFile = ToolFrame::SearchFile(sNewFile);
			if (!sNewFile.empty())return sNewFile;
		}
	}

	return "";
}

bool ToolFrame::AddDir( int eDirType,const std::string& sDir )
{
	return ToolFrame::SafeInsert(GetDirType(),eDirType,sDir);
}

MapIntString& ToolFrame::GetDirType()
{
	static MapIntString g_vDirType;
	return g_vDirType;
}

std::string ToolFrame::GetWorkingDir()
{
	return GetDirByType(DIR_TYPE_WORKING);
}

std::string ToolFrame::GetWriteableDir()
{
	return GetDirByType(DIR_TYPE_WRITEABLE);
}

std::string ToolFrame::GetCacheDir()
{
	return GetDirByType(DIR_TYPE_CACHE);
}

std::string ToolFrame::GetDirByType( int eDirType )
{
	if (DIR_TYPE_INVALID == eDirType)return ToolFrame::EmptyString();
	return ToolFrame::GetValueByKey(GetDirType(),eDirType,"");
}

bool ToolFrame::InitDirType()
{
	AddDir(DIR_TYPE_WORKING,		GetApiTool()->GetDirByType(DIR_TYPE_WORKING));
	AddDir(DIR_TYPE_WRITEABLE,		GetApiTool()->GetDirByType(DIR_TYPE_WRITEABLE));
	AddDir(DIR_TYPE_CACHE,			GetApiTool()->GetDirByType(DIR_TYPE_CACHE));
	AddDir(DIR_TYPE_PATCH,			GetApiTool()->GetDirByType(DIR_TYPE_WRITEABLE)+"Patch/");
	AddDir(DIR_TYPE_ARCHIVE,		GetApiTool()->GetDirByType(DIR_TYPE_WRITEABLE)+"Archive/");

	AddDir(DIR_TYPE_EXT_WORKING,	GetApiTool()->GetDirByType(DIR_TYPE_EXT_WORKING));
	AddDir(DIR_TYPE_EXT_WRITEABLE,	GetApiTool()->GetDirByType(DIR_TYPE_EXT_WRITEABLE));
	AddDir(DIR_TYPE_EXT_CACHE,		GetApiTool()->GetDirByType(DIR_TYPE_EXT_CACHE));
	AddDir(DIR_TYPE_EXT_PATCH,		GetApiTool()->GetDirByType(DIR_TYPE_EXT_WRITEABLE) + "Patch/");
	AddDir(DIR_TYPE_EXT_ARCHIVE,	GetApiTool()->GetDirByType(DIR_TYPE_EXT_WRITEABLE) + "Archive/");

	AddDir(DIR_TYPE_EXT_ROOT,		GetApiTool()->GetDirByType(DIR_TYPE_EXT_ROOT));
	return true;
}

std::string ToolFrame::GetTcpPortInfoString( int nPort )
{
	return GetApiTool()->GetTcpPortInfoString(nPort);
}

std::string ToolFrame::GetTcpLickInfoString()
{
	return GetApiTool()->GetTcpLickInfoString();
}

std::string ToolFrame::GetUdpPortInfoString( int nPort )
{
	return GetApiTool()->GetUdpPortInfoString(nPort);
}

std::string ToolFrame::GetUdpLickInfoString()
{
	return GetApiTool()->GetUdpLickInfoString();
}

std::string ToolFrame::GetPortInfoString(int nPort)
{
	std::stringstream sStream;
	sStream<<GetTcpPortInfoString(nPort);
	sStream<<GetUdpPortInfoString(nPort);

	return sStream.str();
}

bool ToolFrame::IsPortOccupied(int nPort)
{
	return GetApiTool()->IsPortOccupied(nPort);
}

bool ToolFrame::IsFileCaseSensitive(const std::string& sPath)
{
	return GetApiTool()->IsFileCaseSensitive(sPath);
}

bool ToolFrame::SetCheckFileCaseSensitive( bool bCheck )
{
	IsCheckFileCaseSensitive() = bCheck;
	return true;
}

bool& ToolFrame::IsCheckFileCaseSensitive()
{
	static bool g_bCheckFileCaseSensitive = false;
	return g_bCheckFileCaseSensitive;
}

CMutexRecursive& ToolFrame::GetMutexFileIndex()
{
	static CMutexRecursive g_mutex;
	return g_mutex;
}

