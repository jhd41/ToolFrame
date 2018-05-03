#pragma once
#include "Macro.h"

#if MACRO_TARGET_OS == MACRO_OS_ANDROID

#include <jni.h>

class ApiAndroid
{	
public:
	//初始化
	static void				SetJavaVM(JavaVM* pJavaVM);

	//调试
	static void				OutPut(const std::string& sMsg,const std::string& sTag);
	static void				LogDebug(const std::string& sMsg);

	//语言
	static std::string		GetLanguageString();

	//系统
	static std::string		GetProcessName();	//获取进程名
	static std::string 		GetPackageName();	//获取包名
	static std::string		GetDataDir();		//获取数据目录
	static std::string		GetSourceDir();		//获取资源目录
	static std::string		GetCacheDir();		//获取缓存目录
	static std::string		GetFilesDir();		//获取文件目录

	static std::string		GetDirByType(int eDirType);
	static std::string		GetPlatformVer();	//获取系统版本
	static std::string		GetModel();			//获取手机型号
	static bool				IsPad();			//判断是否为平板
	static bool				Vibrator(int nMillTime);//震动
	static bool				PlayVideo(const std::string& sUrl);//播放视频
	static bool				PlayVideo(const std::string& sUrl, const std::string& sType);//播放视频
	
	//扩展内存
	static bool				IsExtemalStorageReady();//扩展内存是否可读写
	static std::string		GetExtemalStorageDir();	//获取扩展内存目录

	static bool        		IsAbsPath( const std::string& sPath );
	static uint64         	GetThreadId();
	static uint				GetThreadAmount();//获取线程数

	static void				Sleep( int nTimeMill );
	static bool				MakeDir( const std::string& sDir);

	static UINT64      		GetNowTimeMill();

	static bool				IsFileExist(const std::string& sFileName);
	static size_t			GetFileLength(const std::string& sFileName);
	static bool				SaveFile(const std::string& sFileName,const void* pBuffer,size_t uLength);
	static bool				LoadFile(const std::string& sFileName,void* pBuffer,size_t uLength);
	static bool				RemoveFile(const std::string& sFileName);
	static bool				RenameFile(const std::string& sPathSrc,const std::string& sPathDes);	

	static bool				IsDir(const std::string& sDir);
	static bool				IsFile(const std::string& sPath);
	static bool				RemoveDir(const std::string& sPath);
	static bool				IsSpecialDir(const char *path);
	static bool				CopyDir(const std::string& sSrcDir,const std::string& sDesDir);//复制文件夹(覆盖)

	static int				GetProcessId();
	static UINT64			GetProcessMemoryUsed();
	static UINT64			GetProcessMemoryFree();

	//网络
	static bool				OpenUrl(const std::string& sUrl);//网址
	static std::string		GetNetWorkType();//获取网络类型(返回 "wap,2g,3g,wifi")
	static std::string		GetMacAddress();

	static int				GetResolutionWidth();//获取分辨率(宽)
	static int				GetResolutionHeight();//获取分辨率(高)
	static std::string		GetOperatorName();//获取运营商名称

	static void				ApiLogPrintVerbose(const std::string& sTag, const std::string& sMsg);
	static void				ApiLogPrintDebug(const std::string& sTag, const std::string& sMsg);
	static void				ApiLogPrintInfo(const std::string& sTag, const std::string& sMsg);
	static void				ApiLogPrintWarn(const std::string& sTag, const std::string& sMsg);
	static void				ApiLogPrintError(const std::string& sTag, const std::string& sMsg);
private:
	static bool				MakeDirWithJni(const std::string& sDir);
	static int64			GetThreadIdWithJni();
	static bool				ApiRemoveDir(const std::string& sPath);
};

#endif