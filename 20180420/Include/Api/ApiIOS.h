#pragma once

#include "Macro.h"

#if MACRO_TARGET_OS == MACRO_OS_IOS

typedef struct vm_statistics	*vm_statistics_t;
typedef struct vm_statistics	vm_statistics_data_t;

class ApiIOS
{
public:
	//Objcʵ��(����ʹ�á���ȷ�ʸ�)
	static std::string	GetRescoreceDir();
	static std::string	GetMainBundleDir();
	static std::string	GetExeutableDir();
	static std::string	GetCacheDir();
	static std::string	GetProcessNameWithOutExt();
	static uint64		GetThreadId();
	static bool			MakeDir(const std::string& sDir);
	static bool			IsAbsPath(const std::string& sPath);
	//����
	static std::string	GetLanguageString();
	
	//C++������ʵ��(������ʹ��)
	static UINT64		GetNowTimeMill();
	
	//Ŀ¼
	static std::string	GetDirByType(int eDirType);

    static std::string  GetWorkDir();//����ǰ����������ù���Ŀ¼ ���ؾ���·��
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
	static bool			CopyDir(const std::string& sSrcDir,const std::string& sDesDir);//�����ļ���(����)

    static std::string  GetDocumentDir();	//��õ�ǰ���̵�����Ŀ¼ �ĵ�
    static std::string  GetDownloadsDir();	//��õ�ǰ���̵�����Ŀ¼ ����
	static std::string	GetLocalCacheDir();	//��õ�ǰϵͳ�Ĺ���Ŀ¼ ����

	//�豸
    static std::string	GetDeviceName();
	static std::string	GetSystemName();// "iPhone OS"
	static std::string	GetSystemVersion();// "5.1.1"
	static std::string	GetModel();// "iPhone" on both devices
	static int			GetResolutionWidth();	//��ȡ�ֱ���(��)
	static int			GetResolutionHeight();	//��ȡ�ֱ���(��)
	static std::string	GetOperatorName();		//��ȡ��Ӫ��(��Ӫ�̹��Ҵ������Ӫ���������)

	static std::string	GetPlatformVer();

	static int			GetProcessId();
	static UINT64		GetProcessMemoryUsed();
	static UINT64		GetProcessMemoryFree();

	static bool			PlayVideo(const std::string& sUrl);	//������Ƶ
	static bool			Vibrator(int nMillTime);			//��

	static bool			IsPad();

	//��ַ
	static bool			OpenUrl(const std::string& sUrl);
	static std::string	GetNetWorkType();//��ȡ��������(���� "wap,2g,3g,wifi")

	//��ͼ
	static bool			ScreenShot(const std::string& sFileName);

	//Կ�״�
	static bool			StoreChain(const std::string& sKey, const std::string& sValue);	//�洢Կ�״�(�� ֵ)
	static std::string	ReadChain(const std::string& sKey);								//��ȡԿ�״�(��)
	static bool			DeleteChain(const std::string& sKey);							//ɾ��Կ�״�(��)
private:
	static bool			ApiRemoveDir(const std::string& sPath);
	static BOOL			ApiMemoryInfo(vm_statistics_data_t *vmStats);

};

#endif

