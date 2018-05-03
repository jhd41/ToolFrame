#pragma once
#include "Macro.h"

#if MACRO_TARGET_OS == MACRO_OS_LINUX

class ApiLinux
{
public:
	//时间
	static time_t		GetNowTime();
	static UINT64		GetNowTimeMill();//(毫秒)

	//获取进程ID
	static int			GetProcessId();
	static int			GetProcessId(const std::string& sProcessName);  //根据进程名，获取进程ID
	static std::string	GetProcessName( int nProcessID = -1);//根据进程ID，获取进程名字

	static std::string GetProcessPath(int nProcessID = -1);//根据进程ID 获取进程路径
	static std::string GetProcessDir(int nProcessID = -1);

	//目录
	std::string			GetDirByType(int eDirType);
	std::string			GetWorkingDir();

	static bool			IsAbsPath( const std::string& sPath );
	static bool			IsDir(const char *path);
	static bool			IsFile(const char *path);
	static bool			IsSpecialDir(const char *path);
	static void			GetFilePath(const char *path, const char *file_name, char *file_path);
	static void			RemoveDir(const char *path);
	static bool			CopyDir(const std::string& sSrcDir,const std::string& sDesDir);//复制文件夹(覆盖)

	static uint64		GetThreadId();

	static std::string	GetPlatformVer();

	//控制台
	static void			ClearScreen();

	static UINT64		GetProcessMemoryUsed();
	static UINT64		GetProcessMemoryFree();
}

#endif
