#pragma once

#include "Macro.h"

//本工具函数只能在Windows下运行 

#if MACRO_TARGET_OS == MACRO_OS_WINDOWS
#include <windows.h>
#include <TLHELP32.H>
#include <psapi.h>
#include "ApiWinCpu.h"
#include <tcpmib.h>
#include <udpmib.h>

class TOOLFRAME_DLL ApiWin
{
public:
	//定义操作系统版本
	enum EWinVer{
		WIN_VER_INVALID,

		WIN_VER_WIN_95,
		WIN_VER_WIN_98,
		WIN_VER_WIN_ME,
		WIN_VER_WIN_NT,
		WIN_VER_WIN_XP,
		WIN_VER_WIN_2000,
		WIN_VER_WIN_2003,
		WIN_VER_WIN_VISTA,
		WIN_VER_WIN_7,
		WIN_VER_WIN_8,
		WIN_VER_WIN_8_1,//windows 8.1
		WIN_VER_WIN_10,
		WIN_VER_MAX,
	};

	typedef std::vector<MIB_TCPROW_OWNER_PID> VectorTcpInfo;
	typedef std::vector<MIB_UDPROW_OWNER_PID> VectorUdpInfo;
public:
	//时间
	static time_t			GetNowTime();//(秒)
	static UINT64			GetNowTimeMill();//(毫秒)

	static std::string		GetNowTimeString();

	static uint64			FileTimeToUtc(const FILETIME* ftime);

	//获取TickCount
	static UINT64			GetSysTickCount64();
	static UINT64			GetTickCount64();
	static UINT64			GetTickCount();

	//ini
	static VectorString		GetIniScetionNames( const std::string& sFileName );
	static MapStringString	GetIniSection(const std::string& sFileName,const std::string& sSection);
	static void				GetIniValue(const std::string& sFileName,const std::string& sSection,const std::string& sKey,int& nValue,			const int nDefault = 0);
	static void				GetIniValue(const std::string& sFileName,const std::string& sSection,const std::string& sKey,std::string& sValue,	const std::string& sDefault = "");
	static void				WriteIniValue(const std::string& sFileName,const std::string& sSection,const std::string& sKey,const std::string& sValue);
	
	//解析内存中的字符串格式(字符串1\0字符串2\0...字符串n\0\0)
	static VectorString		GetStrings( const char_t pSrc[] );

	//file
	static bool				IsFile(const std::string& sFile);
	static bool				CopyDir(const std::string& sSrcDir,const std::string& sDesDir);//复制文件夹(覆盖)
	static bool				MakeDir( const std::string& sDir);
	static bool				RemoveDir(const std::string sDir);
	static bool				SaveFile(const std::string& sFileName,const void* pBuffer,size_t uLength);
	static bool				LoadFile(const std::string& sFileName,void* pBuffer,size_t uLength); 
	static bool				IsFileExist(const std::string& sFileName);
	static bool				RemoveFile(const std::string& sFileName);

	//字符集转换
	static std::string		GbkToUtf8(const std::string& sSrc);	
	static std::string		Utf8ToGbk(const std::string& sSrc,bool bSkipMicroUtfLead=true);

	static std::wstring		GbkToUnc(const std::string& sSrc);
	static std::string		UncToGbk(const std::wstring& sSrc);

	static std::wstring		Utf8ToUnc(const std::string& sSrc);
	static std::string		UncToUtf8(const std::wstring& sSrc);

	static std::string		UncToGbk(const std::string& sSrc);

	//字符集转换 - 重载
	static void				GbkToUtf8(const VectorString& vSrc,VectorString& vDes);
	static void				GbkToUtf8(VectorString& vStrings);

	static bool				IsUtf8(const std::string& Src,bool bCheckMicroUtfLead = true);
	static bool				IsGBK(const std::string& Src);//不正确(待修复)

	static bool				IsMicroUtfLead(const std::string& sSrc);//是否是微软Utf头
	static uint				GetMicroUtfLeadLength();

	//目录
	static std::string		GetExePath();
	static std::string		GetExeDir();
	static std::string		GetExeName();
	static std::string		GetExeNameWithOutExt();
	static bool				GetFilesPath(VectorString& vDes,const std::string& sDir,const std::string& sFilter="*.*",bool bExcept = false);//获取目标目录下绝对路径
	static bool				GetFilesPath(VectorString& vDes,std::string sDir,const VectorString& vSpec,bool bExcept = false);//获取目标目录下绝对路径
	static bool				IsFileCaseSensitive(const std::string& sPath);//文件大小写敏感 是否一致
	static std::string		GetWorkingDir();
	static void				SetWorkingDir(const std::string& sDir);
	static void				SetWorkingDirWithExeDir();
	static bool				IsAbsPath( const std::string& sPath );
	static bool				IsDir(const std::string& sDir);
	static size_t			GetFileLength(const std::string& sFileName);
	static std::string		GetDirByType(int eDirType);

	//控制台
	static void				SetConsoleTextAttribute(int nColor);//颜色值查询 FOREGROUND_RED 的定义
	static void				ClearScreen();
	static bool				SetConsoleHide();//隐藏控制台

	//线程
	static void				Sleep(UINT64 nTimeMill);
	static uint64			GetThreadId();
	static uint				GetThreadAmount(int nProcessID=-1);//获取线程数(默认本进程)

	//进程
	static int				GetProcessId();							//获取当前进程ID
	static std::string		GetProcessName( int nProcessID );		//获取进程名字
	static UINT64			GetProcessMemoryUsed(int nProcessID);	//获取进程内存占用
	static int				GetProcessThreads(int nProcessID);		//获取进程线程数
	static UINT64			GetProcessMemoryFree();					//获取剩余物理内存
	static UINT64			GetProcessMemoryTotal();				//获取总共物理内存
	static int				GetProcessMemoryUsage();				//获取内存使用率
	static int				GetProcessIdByExePath(const std::string& sExePath);
	static int				CalProcessCount(const std::string& sExePath);//计算该进程被运行个数
	static bool				TerminateProcess(int nProcessID);
	static bool				IsExecutedMulit();//是否运行多个
	static int				GetResolutionWidth();//获取分辨率(宽)
	static int				GetResolutionHeight();//获取分辨率(高)
	static std::string		GetOperatorName();		//获取运营商名称
	static bool				PurgeMemory(int nProcessID = -1);//内存回收 -1所有机器的内存

	static CApiWinCpu&		GetWinCpu();
	static bool				ReflashCpuState();	//刷新cpu状态
	static int				GetCpuUsage();		//获取CPU占用率
	static int				GetCpuIdle();		//获取CPU空闲率
	static int				GetProcesserNumber();//获取CPU核数
	static int				GetCpuUsage(int nProcessID);//获取CPU占用率
	static int				GetCpuUsage(uint64& uCreationTime, uint64& uExitTime, uint64& uKernelTime, uint64& uUserTime,int nProcessID);//获取CPU占用率
	static uint64			GetCpuUseTime(int nProcessID);//获取CPU占用总时间
	static bool				GetCpuTime(uint64& uCreationTime, uint64& uExitTime, uint64& uKernelTime, uint64& uUserTime ,int nProcessID);
	static uint64			GetSystemTime();

	//系统
	static std::string		GetLanguageString();//获取当前系统语言
	static EWinVer			GetPlatformVerEnum();	//获取系统版本
	static std::string		GetPlatformVer(EWinVer eWinVer);
	static std::string		GetPlatformVer();
	static std::string		GetModel();				//获取手机型号
	static bool				SystemReboot();			//重启
	static bool				SystemShutDown();		//关机
	static bool				SystemLogOut();			//注销
	static bool				SystemSetTime(uint64 uMillTime);//设置时间

	//VC调试
	static void				Trace( const std::string& sMsg,const std::string& sTag);		//打印在控制台
	static std::string		GetCallStack(HANDLE hProcess = NULL, HANDLE hThread = NULL);	//获取调用堆栈(默认获取当前调用堆栈)
	static std::string		GetCallStackAll();												//获取当前进程所有线程的调用堆栈

	//网络
	static std::string		GetMacAddress();
	static std::string		GetIPAddress();
	static std::string		GetNetWorkType();//获取网络类型(返回 "wap,2g,3g,wifi")
	static bool				OpenUrl(const std::string& sUrl);//网址
	static bool				GetMacFlow(UINT64* upload,UINT64* download);					//获取网卡流量

	static bool				GetSystemTimes(uint64* pIdleTime,uint64* pKernelTime,uint64* pUserTime);
	static uint64			ToUint64(const FILETIME& xTime);

	static std::string		GetTcpPortInfoString(int nPort);
	static std::string		GetTcpLickInfoString();
	static std::string		GetUdpPortInfoString(int nPort);
	static std::string		GetUdpLickInfoString();

	static std::string		TcpInfoToString(const MIB_TCPROW_OWNER_PID* pTcpInfo);
	static std::string		UdpInfoToString(const MIB_UDPROW_OWNER_PID* pTcpInfo);
	static bool				FindTcpPort(VectorTcpInfo& vInfo,int nPort);
	static bool				FindUdpPort(VectorUdpInfo& vInfo,int nPort);
	static bool				IsPortOccupied(int nPort);		//判断端口是否被占用

	//对话框
	static bool				DialogFileOpen(VectorString& vPath);

	//句柄
	static HWND				GetConsoleWindow();//获取控制台句柄
	static HWND				GetHWNDByProcessID(int nProcessID);

	static bool				ScreenShot(const std::string& sFileName); //截图
public:
	static bool					GetProcessEntry32ByProcessID(PROCESSENTRY32* proc, int nProcessID );
	static bool					GetProcessEntry32ByExePath(PROCESSENTRY32* proc,const std::string& sExePath);
	static bool					GetProcessMemoryCountersByProcessID(PROCESS_MEMORY_COUNTERS* mem, int nProcessID );

	static bool					ToMultiWide(const std::string& sSrc,std::wstring& sDes,int nSrcCode);
	static bool					ToMultiWide(const std::wstring& sSrc,std::string& sDes,int nSrcCode);

	static bool					ToMultiWide(const char* pSrc,std::wstring& sDes,int nSrcCode);
	static bool					ToMultiWide(const wchar_t* pSrc,std::string& sDes,int nSrcCode);

	static	std::string			ToMulti(const std::wstring& sSrc);
	static	const std::string&	ToMulti(const std::string& sSrc);

	static	const std::wstring&	ToWide(const std::wstring& sSrc);
	static	std::wstring		ToWide(const std::string& sSrc);

#if MACRO_TARGET_FONT == MACRO_FONT_ANSI
	inline static const	std::string_t&	ToStringT(const std::string& sSrc){
		return sSrc;
	}
	inline static	std::string_t	ToStringT(const std::wstring& sSrc){
		return ToMulti(sSrc);
	}
#elif  MACRO_TARGET_FONT == MACRO_FONT_UNICODE
	inline static	std::string_t	ToStringT(const std::string& sSrc){
		return ToWide(sSrc);
	}
	inline static	const std::string_t&	ToStringT(const std::wstring& sSrc){
		return sSrc;
	} 
#endif

	//字符串拷贝
	static bool			ApiStrCpy( const std::string& sSrc,wchar_t* pDes,int nLen);
	static bool			ApiStrCpy( const std::string& sSrc,char* pDes,int nLen); 
public:
	static UINT64		ApiCreateProcess(const std::string& sExeName,const std::string& sWorkingDir="",const std::string& sCommandLine="");
	static bool			ApiCreateDirectory(const std::string& sDir);
	static std::string	ApiGetCommandLine();
	static std::string	ApiGetModuleFileName();
	static std::string	ApiGetCurrentDirectory();
	static bool			ApiSetCurrentDirectory(const std::string& sDir);
	static HANDLE		ApiFindFirstFile(const std::string& sPath, WIN32_FIND_DATA* wfd);
	static bool			ApiPathMatchSpec(const std::string& sPath,const std::string& sSpec);//比较是否符合通配符
	static bool			ApiPathMatchSpec(const std::string& sPath,const VectorString& vSpec);//比较是否符合通配符
	static bool			ApiDeleteFile(const std::string& sFile);
	static bool			ApiRemoveDirectory(const std::string& sDir);
	static UINT			ApiGetFileAttributes(const std::string& sDir);
	static bool			ApiMakeDir( const std::string& sDir);
	static bool			ApiPathIsRelative(const std::string& sDir);
	static bool			ApiPathIsRoot(const std::string& sDir);
	static bool			ApiRemoveDir(std::string sDir);
	static std::string	ApiGetFristMacAddress();
	static std::string	ApiGetFristMacNetWorkType();
	static std::string	ApiGetActiveMacNetWorkType();
	static HANDLE		ApiGetProcessHandle(int nProcessID);
	static std::string	ApiTranNetWorkType(int eAdapterType);
	static BOOL			ApiIsWinVerEqualTo(DWORD dwMajorVersion, DWORD dwMinorVersion);

	static std::string	ApiAddrToString(struct in_addr in);
	static bool			ApiEmptyWorkingSet(int nProcessID);//将内存写入硬盘从而减小内存

	//控制台
	static std::string	ApiGetConsoleTitle();//获取控制台窗口标题
	static bool			ApiSetConsoleTitle(const std::string & sTitle);//设置控制台窗口标题
};

#endif
