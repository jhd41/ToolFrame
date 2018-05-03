#pragma once

#include "Macro.h"

#if MACRO_TARGET_OS == MACRO_OS_IOS

typedef struct vm_statistics	*vm_statistics_t;
typedef struct vm_statistics	vm_statistics_data_t;

class ApiIOS
{
public:
	//Objc实现(优先使用。正确率高)
	static std::string	GetRescoreceDir();
	static std::string	GetMainBundleDir();
	static std::string	GetExeutableDir();
	static std::string	GetCacheDir();
	static std::string	GetProcessNameWithOutExt();
	static uint64		GetThreadId();
	static bool			MakeDir(const std::string& sDir);
	static bool			IsAbsPath(const std::string& sPath);
	//语言
	static std::string	GetLanguageString();
	
	//C++函数库实现(不优先使用)
	static UINT64		GetNowTimeMill();
	
	//目录
	static std::string	GetDirByType(int eDirType);

    static std::string  GetWorkDir();//调用前必须调用设置工作目录 返回绝对路径
	static bool			SetWorkDir(const std::string& sDir);

	static bool			IsFileExist(const std::string& sFileName);
	static size_t		GetFileLength(const std::string& sFileName);
	static bool			SaveFile(const std::string& sFileName,const void* pBuffer,size_t uLength);
	static bool			LoadFile(const std::string& sFileName,void* pBuffer,size_t uLength);
	static bool			RemoveFile(const std::string& sFileName);
	static bool			RenameFile(const std::string& sPathSrc,const std::string& sPathDes);	

	static bool			IsDir(const std::string& sDir);
	static bool			IsFile(const std::string& sPath);
	static bool			RemoveDir(const std::string& sPath);
	static bool			CopyDir(const std::string& sSrcDir,const std::string& sDesDir);//复制文件夹(覆盖)

    static std::string  GetDocumentDir();	//获得当前进程的特有目录 文档
    static std::string  GetDownloadsDir();	//获得当前进程的特有目录 下载
	static std::string	GetLocalCacheDir();	//获得当前系统的公共目录 缓存

	//设备
    static std::string	GetDeviceName();
	static std::string	GetSystemName();// "iPhone OS"
	static std::string	GetSystemVersion();// "5.1.1"
	static std::string	GetModel();// "iPhone" on both devices
	static int			GetResolutionWidth();	//获取分辨率(宽)
	static int			GetResolutionHeight();	//获取分辨率(高)
	static std::string	GetOperatorName();		//获取运营商(运营商国家代码和运营商网络代码)

	static std::string	GetPlatformVer();

	static int			GetProcessId();
	static UINT64		GetProcessMemoryUsed();
	static UINT64		GetProcessMemoryFree();

	static bool			PlayVideo(const std::string& sUrl);	//播放视频
	static bool			Vibrator(int nMillTime);			//震动

	static bool			IsPad();

	//网址
	static bool			OpenUrl(const std::string& sUrl);
	static std::string	GetNetWorkType();//获取网络类型(返回 "wap,2g,3g,wifi")

	//截图
	static bool			ScreenShot(const std::string& sFileName);

	//钥匙串
	static bool			StoreChain(const std::string& sKey, const std::string& sValue);	//存储钥匙串(键 值)
	static std::string	ReadChain(const std::string& sKey);								//读取钥匙串(键)
	static bool			DeleteChain(const std::string& sKey);							//删除钥匙串(键)
private:
	static bool			ApiRemoveDir(const std::string& sPath);
	static BOOL			ApiMemoryInfo(vm_statistics_data_t *vmStats);

};

#endif

