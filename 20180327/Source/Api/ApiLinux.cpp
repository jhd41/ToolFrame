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
	//��������ID
	if (nProcessID < 0)	nProcessID = GetProcessId();

	//ִ�������л�ȡ����·�� get process name by shell
	std::stringstream sStream;
	sStream<<"readlink /proc/"<<nProcessID<<"/exe >pname.txt";
	system(sStream.str().c_str());
	
	//��ȡ�ļ�	open file
	std::string  sPath = ToolFrame::LoadFile("pname.txt");
	
	//ɾ����ʱ�ļ� remove file
	system("rm pname.txt");

	//����Linux���е��ļ�β��ʶ
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
	return syscall(SYS_gettid);  /*������ں�*/
}

void ApiLinux::ClearScreen()
{
	system( "clear ");
}

//�ж��Ƿ�ΪĿ¼
bool ApiLinux::IsDir(const char *path)
{
	struct stat statbuf;
	if(lstat(path, &statbuf) ==0)//lstat�����ļ�����Ϣ���ļ���Ϣ�����stat�ṹ��
	{
		return S_ISDIR(statbuf.st_mode) != 0;//S_ISDIR�꣬�ж��ļ������Ƿ�ΪĿ¼
	}
	return false;
}

//�ж��Ƿ�Ϊ�����ļ�
bool ApiLinux::IsFile(const char *path)
{
	struct stat statbuf;
	if(lstat(path, &statbuf) ==0)
		return S_ISREG(statbuf.st_mode) != 0;//�ж��ļ��Ƿ�Ϊ�����ļ�
	return false;
}

//�ж��Ƿ�������Ŀ¼
bool ApiLinux::IsSpecialDir(const char *path)
{
	return strcmp(path, ".") == 0 || strcmp(path, "..") == 0;
}

//�����������ļ�·��
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
	//����������ļ�����
	if(IsFile(sSrcDir)){
		if (ApiStd::CopyFile(sSrcDir,sDesDir))return true;

		//�������ļ�ʧ�ܳ��Դ����ļ����ٴθ���
		if (!MakeDir(ToolFrame::PickDir(sDesDir),DIR_TYPE_WRITEABLE))return false;
		return ApiStd::CopyFile(sSrcDir,sDesDir);
	}

	//����������ļ����򴴽��ļ��в�������Ŀ¼
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
