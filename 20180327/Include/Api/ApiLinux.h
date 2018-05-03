#pragma once
#include "Macro.h"

#if MACRO_TARGET_OS == MACRO_OS_LINUX

class ApiLinux
{
public:
	//ʱ��
	static time_t		GetNowTime();
	static UINT64		GetNowTimeMill();//(����)

	//��ȡ����ID
	static int			GetProcessId();
	static int			GetProcessId(const std::string& sProcessName);  //���ݽ���������ȡ����ID
	static std::string	GetProcessName( int nProcessID = -1);//���ݽ���ID����ȡ��������

	static std::string GetProcessPath(int nProcessID = -1);//���ݽ���ID ��ȡ����·��
	static std::string GetProcessDir(int nProcessID = -1);

	//Ŀ¼
	std::string			GetDirByType(int eDirType);
	std::string			GetWorkingDir();

	static bool			IsAbsPath( const std::string& sPath );
	static bool			IsDir(const char *path);
	static bool			IsFile(const char *path);
	static bool			IsSpecialDir(const char *path);
	static void			GetFilePath(const char *path, const char *file_name, char *file_path);
	static void			RemoveDir(const char *path);
	static bool			CopyDir(const std::string& sSrcDir,const std::string& sDesDir);//�����ļ���(����)

	static uint64		GetThreadId();

	static std::string	GetPlatformVer();

	//����̨
	static void			ClearScreen();

	static UINT64		GetProcessMemoryUsed();
	static UINT64		GetProcessMemoryFree();
}

#endif
