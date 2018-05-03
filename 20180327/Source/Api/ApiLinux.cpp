#include "ApiLinux.h"

#if MACRO_TARGET_OS == MACRO_OS_LINUX

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <iostream>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/timeb.h>
#include <sys/syscall.h>
#inclide <sys/sysinfo.h>

#include "ToolStd.h"

time_t ApiLinux::GetNowTime()
{
	struct timeb tp;
	ftime(&tp);
	return tp.time;
}

UINT64 ApiLinux::GetNowTimeMill()
{
	struct timeb tp;
	ftime(&tp);
	return ((UINT64)(tp.time)*1000) + tp.millitm;
}

int ApiLinux::GetProcessId(const std::string& sProcessName)
{
	int nProcessID = -1;
	//get process id by shell
	std::stringstream sStream;
	sStream<<"pidof "<<sProcessName<<" > pid.txt";
	system(sStream.str().c_str());
	
	//read file
	std::string sPid = ToolFrame::LoadFile("pid.txt");

	//remove file
	system("rm pid.txt");

	ToolFrame::ToValue(sPid,nProcessID);
	return nProcessID;
}

int ApiLinux::GetProcessId()
{
	return getpid();
}

std::string ApiLinux::GetProcessPath( int nProcessID )
{
	//修正进程ID
	if (nProcessID < 0)	nProcessID = GetProcessId();

	//执行命令行获取进程路径 get process name by shell
	std::stringstream sStream;
	sStream<<"readlink /proc/"<<nProcessID<<"/exe >pname.txt";
	system(sStream.str().c_str());
	
	//读取文件	open file
	std::string  sPath = ToolFrame::LoadFile("pname.txt");
	
	//删除临时文件 remove file
	system("rm pname.txt");

	//过滤Linux特有的文件尾标识
	if (!sPath.empty())
	{
		return sPath.substr(0,sPath.length()-1);
	}
	return sPath;
}

std::string ApiLinux::GetProcessName( int nProcessID )
{
	return ToolFrame::PickFileName(GetProcessPath(nProcessID));
}

std::string ApiLinux::GetProcessDir( int nProcessID /*= -1*/ )
{
	return ToolFrame::PickDir(GetProcessPath(nProcessID));
}

bool ApiLinux::IsAbsPath( const std::string& sPath )
{
	std::string sWorkingDir = GetWorkingDir();
	return ToolFrame::IsBeginWith(sPath,sWorkingDir);
}

uint64 ApiLinux::GetThreadId()
{
	return syscall(SYS_gettid);  /*这才是内涵*/
}

void ApiLinux::ClearScreen()
{
	system( "clear ");
}

//判断是否为目录
bool ApiLinux::IsDir(const char *path)
{
	struct stat statbuf;
	if(lstat(path, &statbuf) ==0)//lstat返回文件的信息，文件信息存放在stat结构中
	{
		return S_ISDIR(statbuf.st_mode) != 0;//S_ISDIR宏，判断文件类型是否为目录
	}
	return false;
}

//判断是否为常规文件
bool ApiLinux::IsFile(const char *path)
{
	struct stat statbuf;
	if(lstat(path, &statbuf) ==0)
		return S_ISREG(statbuf.st_mode) != 0;//判断文件是否为常规文件
	return false;
}

//判断是否是特殊目录
bool ApiLinux::IsSpecialDir(const char *path)
{
	return strcmp(path, ".") == 0 || strcmp(path, "..") == 0;
}

//生成完整的文件路径
void ApiLinux::GetFilePath(const char *path, const char *file_name,  char *file_path)
{
	strcpy(file_path, path);
	if(file_path[strlen(path) - 1] != '/')
		strcat(file_path, "/");
	strcat(file_path, file_name);
}

void ApiLinux::RemoveDir(const char *path)
{
	DIR *dir;
	dirent *dir_info;
	char file_path[PATH_MAX];
	if(IsFile(path))
	{
		remove(path);
		return;
	}
	if(IsDir(path))
	{
		if((dir = opendir(path)) == nullptr)
			return;
		while((dir_info = readdir(dir)) != nullptr)
		{
			GetFilePath(path, dir_info->d_name, file_path);
			if(IsSpecialDir(dir_info->d_name))
				continue;
			RemoveDir(file_path);
			rmdir(file_path);
		}
	}
}

UINT64 ApiLinux::GetProcessMemoryUsed()
{
	sysinfo info;
	sysinfo(&info);
	return info.mem_unit;
}

UINT64 ApiLinux::GetProcessMemoryFree()
{
	sysinfo info;
	sysinfo(&info);
	return info.freeram;
}

bool ApiLinux::CopyDir( const std::string& sSrcDir,const std::string& sDesDir )
{
	//如果传入是文件则复制
	if(IsFile(sSrcDir)){
		if (ApiStd::CopyFile(sSrcDir,sDesDir))return true;

		//若复制文件失败尝试创建文件夹再次复制
		if (!MakeDir(ToolFrame::PickDir(sDesDir),DIR_TYPE_WRITEABLE))return false;
		return ApiStd::CopyFile(sSrcDir,sDesDir);
	}

	//如果传入是文件夹则创建文件夹并复制子目录
	if (!MakeDir(sDesDir,DIR_TYPE_WRITEABLE))return false;

	DIR *dir  = opendir(sSrcDir.c_str());
	if( nullptr == dir)
		return false;

	dirent *dir_info = nullptr;
	while((dir_info = readdir(dir)) != nullptr)
	{
		if(ToolFrame::IsSpecialDir(dir_info->d_name))
			continue;

		if (!CopyDir(sSrcDir +"/" + dir_info->d_name,sDesDir +"/" + dir_info->d_name))return false;
	}

	return true;
}

std::string ApiLinux::GetDirByType( int eDirType )
{
	switch(eDirType)
	{
	case DIR_TYPE_WORKING:
		return GetWorkingDir();
		break;
	case DIR_TYPE_WRITEABLE:
		return GetWorkingDir();
		break;
	case DIR_TYPE_CACHE:
		return GetWorkingDir();
		break;
	}

	return "";
}

std::string ApiLinux::GetWorkingDir()
{
	char buf[PATH_MAX]={0};

	if(getcwd(buf, sizeof(buf)-1) != nullptr)
	{
		return ToolFrame::TrimDir(buf);
	}
	return "";
}

std::string ApiLinux::GetPlatformVer()
{
	return "";
}

#endif
