#pragma once
#include "Macro.h"
#include "MacroDefineBoost.h"
#include "IApiTool.h"

//本工具函数 可以跨平台 需要在Macor.h定义使用的实现 函数库的类别
namespace ToolFrame
{
	//时间
	TOOLFRAME_DLL time_t		GetNowTime();
	TOOLFRAME_DLL UINT64		GetNowTimeMill();
	TOOLFRAME_DLL const std::string& GetNowTimeString();
	TOOLFRAME_DLL std::string	GetNowTimeString(const std::string& sFormat);//获取当前时间的字符串
	TOOLFRAME_DLL std::string	GetTodayDateString();
	TOOLFRAME_DLL time_t		CalLocalHour(int tTime);		//计算今天的整点(时间点)
	TOOLFRAME_DLL time_t		CalLocalNextHour(int tTime);	//计算下一个整点(时间点)
	TOOLFRAME_DLL time_t		CalLocalToNextHour(int tTime);	//计算到下一个整点的 时长

	//目录
	TOOLFRAME_DLL std::string	GetWorkingDir();
	TOOLFRAME_DLL std::string	GetWriteableDir();
	TOOLFRAME_DLL std::string	GetCacheDir();

	TOOLFRAME_DLL bool			InitDirType();//初始化文件夹类型
	TOOLFRAME_DLL MapIntString& GetDirType();
	TOOLFRAME_DLL bool			AddDir(int eDirType,const std::string& sDir);
	TOOLFRAME_DLL std::string	GetDirByType(int eDirType);

	TOOLFRAME_DLL bool			SetWorkingDirWithExeDir();
	TOOLFRAME_DLL std::string	GetAbsPathByRelativePath( const std::string& sPath );//获取绝对路径(输入相对路径)
	TOOLFRAME_DLL std::string	GetAbsPath(const std::string& sPath);				//获取绝对路径(对输入路径不考虑相对或者绝对)
	TOOLFRAME_DLL bool			IsAbsPath(const std::string& sPath);				//是否为绝对路径
	
	TOOLFRAME_DLL bool			MakeDir(const std::string& sDir,int eDirType = DIR_TYPE_WRITEABLE);		//创建文件夹
	TOOLFRAME_DLL bool			RemoveDir(const std::string& sDir,int eDirType = DIR_TYPE_WRITEABLE);	//删除目录
	TOOLFRAME_DLL bool			CopyDir(const std::string& sSrcDir,const std::string& sDesDir);//复制文件夹(覆盖)

	//文件
	TOOLFRAME_DLL bool			IsFileExist(const std::string& sFileName,int eDirType = DIR_TYPE_INVALID);
	TOOLFRAME_DLL size_t		GetFileLength(const std::string& sFileName,int eDirType = DIR_TYPE_INVALID);
	TOOLFRAME_DLL bool			SaveFile(const std::string& sFileName,const void* pBuffer,size_t uLength,int eDirType = DIR_TYPE_WRITEABLE);
	TOOLFRAME_DLL bool			LoadFile(const std::string& sFileName,void* pBuffer,size_t uLength,int eDirType = DIR_TYPE_INVALID);
	TOOLFRAME_DLL std::string	LoadFile( const std::string& sFileName ,int eDirType = DIR_TYPE_INVALID);
	TOOLFRAME_DLL bool			SaveFile( const std::string& sFileName,const std::string& sContent ,int eDirType = DIR_TYPE_WRITEABLE);
	TOOLFRAME_DLL bool			RemoveFile(const std::string& sFileName,int eDirType = DIR_TYPE_WRITEABLE);
	TOOLFRAME_DLL bool			RenameFile(const std::string& sPathSrc,const std::string& sPathDes,int eDirType = DIR_TYPE_WRITEABLE);
	TOOLFRAME_DLL bool			ReplaceFileContent(const std::string& sFile,const std::string& sSrc,const std::string& sDes);
	TOOLFRAME_DLL bool			ReplaceFileContent(const std::string& sFile,const MapStringString& vMapString);
	TOOLFRAME_DLL bool			InitSearchDir();
	TOOLFRAME_DLL VectorString&		GetSearchDir();	//获取搜索路径
	TOOLFRAME_DLL MapStringString&	GetFileIndex();	//获取文件索引(相对路径 -> 绝对路径)
	TOOLFRAME_DLL CMutexRecursive&	GetMutexFileIndex();//文件索引锁
	TOOLFRAME_DLL bool			AddSearchDir(const std::string& sDir);//添加搜索路径 (最后被添加的路径会被优先搜索)
	TOOLFRAME_DLL bool			IsInSearchDir(const std::string& sDir);//判断是否已经存在搜索路径
	TOOLFRAME_DLL bool			IsHasFileIndex(const std::string& sFile);	//是否存在文件索引
	TOOLFRAME_DLL std::string	GetFileIndex(const std::string& sFileName);	//是否已经被搜索过
	TOOLFRAME_DLL bool			AddFileIndex(const std::string& sFileName,const std::string& sPath);
	TOOLFRAME_DLL bool			RemoveFileIndex(const std::string& sFileName);
	TOOLFRAME_DLL bool			RemoveFileIndex();
	TOOLFRAME_DLL std::string	SearchFile(const std::string& sFileName);
	TOOLFRAME_DLL std::string	SearchFile(const std::string& sFileName,int eDirType);
	TOOLFRAME_DLL std::string	ReSearchFile(const std::string& sFileName);	//重新搜索
	TOOLFRAME_DLL std::string	SmartSearchPath(const std::string& sFileName);//如果文件不存在 尝试到其他路径下去寻找
	TOOLFRAME_DLL bool			IsFileCaseSensitive(const std::string& sPath);//文件路径大小写是否一致
	TOOLFRAME_DLL bool&			IsCheckFileCaseSensitive();						//是否检查文件大小写
	TOOLFRAME_DLL bool			SetCheckFileCaseSensitive(bool bCheck);

	TOOLFRAME_DLL std::string	FullPath(const std::string& sFileName,int eDirType);//拼装出文件完整路径 不搜索
	TOOLFRAME_DLL std::string	FullPathDir(const std::string& sDir,int eDirType);	//完整路径文件夹

	//控制台
	TOOLFRAME_DLL void			SetConsoleTextAttribute(int nColor);//颜色值查询 FOREGROUND_RED 的定义
	TOOLFRAME_DLL void			OutPut(const std::string& sMsg,const std::string& sTag="",bool bTrace = true);	//打印
	TOOLFRAME_DLL void			ClearScreen();
	TOOLFRAME_DLL bool			SetConsoleHide();	//隐藏控制台
	TOOLFRAME_DLL std::string	GetConsoleTitle();	//获取控制台标题	
	TOOLFRAME_DLL bool			SetConsoleTitle(const std::string & sTitle);//设置控制台窗口标题

	//进程
	TOOLFRAME_DLL int			GetProcessId();
	TOOLFRAME_DLL std::string	GetProcessPath();
	TOOLFRAME_DLL bool			ScreenShot(const std::string& sFileName);//截图

	TOOLFRAME_DLL std::string	GetProcessName( int nProcessID );//根据进程ID，获取进程名字
	TOOLFRAME_DLL std::string	GetProcessNameWithOutExt();
	TOOLFRAME_DLL std::string	GetProcessNameWithOutExt( int nProcessID );
	TOOLFRAME_DLL std::string	GetProcessDir();
	TOOLFRAME_DLL bool			IsExecutedMulit();				//是否运行多个

	TOOLFRAME_DLL UINT64		CreateProcess(const std::string& sExePath,const std::string& sWorkingDir="",const std::string& sCommandLine="");
	TOOLFRAME_DLL int			GetProcessIdByExePath(const std::string& sExePath);
	TOOLFRAME_DLL uint64		GetProcessMemoryUsed(int nProcessID);//获取使用的内存
	TOOLFRAME_DLL uint64		GetProcessMemoryFree();//获取剩余内存
	TOOLFRAME_DLL uint64		GetProcessMemoryTotal();//获取总共内存
	TOOLFRAME_DLL int			GetProcessMemoryUsage();//获取内存使用率
	TOOLFRAME_DLL bool			PurgeMemory(int nProcessID = -1);//回收内存 -1包括其他进程
	
	TOOLFRAME_DLL bool			ReflashCpuState();	//刷新cpu状态
	TOOLFRAME_DLL int			GetCpuUsage();		//获取CPU占用率
	TOOLFRAME_DLL int			GetCpuIdle();		//获取CPU空闲率
	TOOLFRAME_DLL int			GetCpuUsage(int nProcessID);		//获取CPU占用率
	TOOLFRAME_DLL uint64		GetCpuUseTime(int nProcessID);//获取CPU占用总时间

	TOOLFRAME_DLL bool			TerminateProcess(int nProcessID);
	TOOLFRAME_DLL std::string	GetCommandLine();//获取命令行
	
	//网络
	TOOLFRAME_DLL std::string	GetMacAddress();
	TOOLFRAME_DLL std::string	GetIPAddress();
	TOOLFRAME_DLL bool			OpenUrl(const std::string& sUrl);//打开Url.如果要打开网页的 务必以http://开头
	TOOLFRAME_DLL std::string	GetNetWorkType();//获取网络类型(返回 "wap,2g,3g,wifi","lan")
	TOOLFRAME_DLL bool			GetMacFlow(UINT64* upload,UINT64* download);					//获取网卡流量
	TOOLFRAME_DLL bool			IsPayNet();	//是否是付费网络wap,2g,3g,wwan,未知网络
	TOOLFRAME_DLL bool			IsFreeNet();//是否是免费网络wifi lan
	TOOLFRAME_DLL std::string	GetTcpPortInfoString(int nPort);//获取占用指定端口的进程信息(Tcp)
	TOOLFRAME_DLL std::string	GetTcpLickInfoString();			//获取所有Tcp连接的进程信息
	TOOLFRAME_DLL std::string	GetUdpPortInfoString(int nPort);
	TOOLFRAME_DLL std::string	GetUdpLickInfoString();
	TOOLFRAME_DLL std::string	GetPortInfoString(int nPort);	//获取占用指定端口的进程信息(所有)
	TOOLFRAME_DLL bool			IsPortOccupied(int nPort);		//判断端口是否被占用

	TOOLFRAME_DLL int			GetResolutionWidth();	//获取分辨率(宽)
	TOOLFRAME_DLL int			GetResolutionHeight();	//获取分辨率(高)
	TOOLFRAME_DLL std::string	GetOperatorName();		//获取运营商名称

	//线程
	TOOLFRAME_DLL void			Sleep(UINT64 nTimeMill);
	TOOLFRAME_DLL uint64		GetThreadId();
	TOOLFRAME_DLL uint			GetThreadAmount();//获取线程数

	//系统
	TOOLFRAME_DLL std::string	GetDeviceID();		//获取设备ID号
	TOOLFRAME_DLL int			GetLanguage();		//语言
	TOOLFRAME_DLL std::string	GetLanguageString();//语言代号(精准)
	TOOLFRAME_DLL int			GetPlatform();		//获取操作系统枚举值
	TOOLFRAME_DLL std::string	GetPlatformString();//获取系统名称(当前)
	TOOLFRAME_DLL std::string	GetPlatformVer();	//获取系统版本
	TOOLFRAME_DLL std::string	GetModel();			//获取手机型号

	TOOLFRAME_DLL std::string	ToPlatformString(int ePlatform);//获取系统名称
	TOOLFRAME_DLL int			TranPlatformString(const std::string& sPlatform);

	TOOLFRAME_DLL std::string	ToLanguageString(int eLanguage);//语言
	TOOLFRAME_DLL int			TranLanguageString(const std::string& sLanguage);

	TOOLFRAME_DLL bool			SystemReboot();		//重启
	TOOLFRAME_DLL bool			SystemShutDown();	//关机
	TOOLFRAME_DLL bool			SystemLogOut();		//注销
	TOOLFRAME_DLL bool			SystemSetTime(uint64 uTime);//设置时间
	TOOLFRAME_DLL bool			IsPad();			//是否为平板
	TOOLFRAME_DLL bool			Vibrator(int nMillTime);//震动
	TOOLFRAME_DLL bool			PlayVideo(const std::string& sUrl);//震动

	//调试
	TOOLFRAME_DLL bool			DebugCrack();		//使得系统变得迟缓 增加缝隙的时间
	TOOLFRAME_DLL bool			DebugSetCrack(bool bCrack = true);		//裂缝产生
	TOOLFRAME_DLL bool&			IsDebugCrack();
	TOOLFRAME_DLL std::string	GetCallStack();		//获取调用堆栈(默认获取当前调用堆栈)
	TOOLFRAME_DLL std::string	GetCallStackAll();	//获取当前进程所有线程的调用堆栈

	//版本
	TOOLFRAME_DLL int			GetCompileVer();	//获取编译版本(MACRO_VER_DEBUG)
	TOOLFRAME_DLL bool			IsDebugVer();		//是否为调试版本
	TOOLFRAME_DLL bool			IsReleaseVer();		//是否为发布版本

	//全局工具底层(支持第三方实现)
	TOOLFRAME_DLL IApiTool*		GetApiTool();
	TOOLFRAME_DLL void			SetApiTool(IApiTool* pApiTool);
	TOOLFRAME_DLL IApiTool*		GetApiToolDefault();//获得默认Api读写对象
};
