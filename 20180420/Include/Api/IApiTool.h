#pragma once

#include "Macro.h"

NS_TOOL_FRAME_BEGIN

class TOOLFRAME_DLL IApiTool
{
public:
	//时间
	virtual UINT64		GetNowTimeMill();

	//目录
	virtual std::string	GetDirByType(int eDirType);//根据目录类型获取目录前缀

	virtual bool		SetWorkingDirWithExeDir();
	virtual bool		IsAbsPath(const std::string& sPath);//是否为绝对路径
	virtual bool		MakeDir(const std::string& sDir);	//创建文件夹
	virtual bool		RemoveDir(const std::string& sDir);	//删除目录
	virtual bool		CopyDir(const std::string& sSrcDir,const std::string& sDesDir);//复制文件夹(覆盖)

	//文件
	virtual bool		IsFileExist(const std::string& sFileName);
	virtual size_t		GetFileLength(const std::string& sFileName);
	virtual bool		SaveFile(const std::string& sFileName,const void* pBuffer,size_t uLength);
	virtual bool		LoadFile(const std::string& sFileName,void* pBuffer,size_t uLength); 
	virtual bool		RemoveFile(const std::string& sFileName);
	virtual bool		RenameFile(const std::string& sPathSrc,const std::string& sPathDes);
	virtual bool		IsFileCaseSensitive( const std::string& sPath );

	//控制台
	virtual void		SetConsoleTextAttribute(int nColor);//颜色值查询 FOREGROUND_RED 的定义
	virtual void		OutPut(const std::string& sMsg,const std::string& sTag="",bool bTrace = true);	//打印
	virtual void		ClearScreen();
	virtual bool		SetConsoleHide();//隐藏控制台
	virtual std::string	ApiGetConsoleTitle();	//获取控制台标题	
	virtual bool		ApiSetConsoleTitle(const std::string & sTitle);//设置控制台窗口标题

	//进程
	virtual int			GetProcessId();
	virtual std::string	GetProcessPath();
	virtual std::string	GetProcessName( int nProcessID );//根据进程ID，获取进程名字
	virtual std::string	GetProcessNameWithOutExt();
	virtual std::string	GetProcessNameWithOutExt( int nProcessID );
	virtual std::string	GetProcessDir();

	virtual	UINT64		ApiCreateProcess(const std::string& sExePath,const std::string& sWorkingDir,const std::string& sCommandLine);
	virtual	int			GetProcessIdByExePath(const std::string& sExePath);
	virtual uint64		GetProcessMemoryUsed(int nProcessID);
	virtual uint64		GetProcessMemoryFree();//获取剩余内存
	virtual uint64		GetProcessMemoryTotal();//获取剩余内存
	virtual int			GetProcessMemoryUsage();//获取内存使用率
	virtual bool		PurgeMemory(int nProcessID = -1);//内存回收 -1所有机器的内存
	virtual bool		ReflashCpuState();	//刷新cpu状态
	virtual int			GetCpuUsage();		//获取CPU占用率
	virtual int			GetCpuIdle();		//获取CPU空闲率
	virtual int			GetCpuUsage(int nProcessID);		//获取CPU占用率
	virtual uint64		GetCpuUseTime(int nProcessID);//获取CPU占用总时间
	virtual bool		TerminateProcess(int nProcessID);//终止进程
	virtual bool		IsExecutedMulit();		//是否多开
	virtual bool		ScreenShot(const std::string& sFileName);//截图
	virtual std::string ApiGetCommandLine();//获取命令行

	//网络
	virtual	std::string GetMacAddress();
	virtual std::string GetIPAddress();
	virtual bool		OpenUrl(const std::string& sUrl);
	virtual std::string	GetNetWorkType();//获取网络类型(返回 "wap,2g,3g,wifi","lan")
	virtual bool		GetMacFlow(UINT64* upload,UINT64* download);					//获取网卡流量

	virtual int			GetResolutionWidth();	//获取分辨率(宽)
	virtual int			GetResolutionHeight();	//获取分辨率(高)
	virtual std::string	GetOperatorName();		//获取运营商名称

	virtual std::string	GetTcpPortInfoString(int nPort);//获取占用指定端口的进程信息
	virtual std::string	GetTcpLickInfoString();			//获取所有Tcp连接的进程信息
	virtual std::string	GetUdpPortInfoString(int nPort);
	virtual std::string	GetUdpLickInfoString();
	virtual bool		IsPortOccupied(int nPort);		//判断端口是否被占用

	//线程
	virtual void		Sleep(UINT64 nTimeMill);
	virtual uint64		GetThreadId();
	virtual uint		GetThreadAmount();//获取线程数

	//调试
	virtual std::string	GetCallStack();		//获取调用堆栈(默认获取当前调用堆栈)
	virtual std::string	GetCallStackAll();	//获取当前进程所有线程的调用堆栈

	//版本
	virtual int			GetCompileVer();	//获取编译版本(MACRO_VER_DEBUG)
	virtual bool		IsDebugVer();		//是否为调试版本
	virtual bool		IsReleaseVer();		//是否为发布版本

	//系统
	virtual std::string GetDeviceID();		//获取设备ID号
	virtual std::string	GetLanguageString();//语言
	virtual int			GetPlatform();		//获取操作系统枚举值
	virtual std::string	GetPlatformVer();	//获取系统版本
	virtual std::string GetModel();			//获取手机型号
	virtual bool		SystemReboot();		//重启
	virtual bool		SystemShutDown();	//关机
	virtual bool		SystemLogOut();		//注销
	virtual bool		SystemSetTime(uint64 uTime);//设置时间
	virtual bool		IsPad();			//是否为平板
	virtual bool		Vibrator(int nMillTime);//震动
	virtual bool		PlayVideo(const std::string& sUrl);//震动

	virtual std::string ToPlatformString(int ePlatform);//转换系统名称
	virtual int			TranPlatformString(const std::string& sPlatform);

	virtual std::string	ToLanguageString(int eLanguage);//语言
	virtual int			TranLanguageString(const std::string& sLanguage);
public:
	IApiTool(void);
	virtual ~IApiTool(void);
};

NS_TOOL_FRAME_END
