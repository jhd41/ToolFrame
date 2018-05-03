#pragma once
#include "Macro.h"

#if MACRO_TARGET_OS == MACRO_OS_ANDROID

#include <jni.h>

class ApiAndroid
{	
public:
	//��ʼ��
	static void				SetJavaVM(JavaVM* pJavaVM);

	//����
	static void				OutPut(const std::string& sMsg,const std::string& sTag);
	static void				LogDebug(const std::string& sMsg);

	//����
	static std::string		GetLanguageString();

	//ϵͳ
	static std::string		GetProcessName();	//��ȡ������
	static std::string 		GetPackageName();	//��ȡ����
	static std::string		GetDataDir();		//��ȡ����Ŀ¼
	static std::string		GetSourceDir();		//��ȡ��ԴĿ¼
	static std::string		GetCacheDir();		//��ȡ����Ŀ¼
	static std::string		GetFilesDir();		//��ȡ�ļ�Ŀ¼

	static std::string		GetDirByType(int eDirType);
	static std::string		GetPlatformVer();	//��ȡϵͳ�汾
	static std::string		GetModel();			//��ȡ�ֻ��ͺ�
	static bool				IsPad();			//�ж��Ƿ�Ϊƽ��
	static bool				Vibrator(int nMillTime);//��
	static bool				PlayVideo(const std::string& sUrl);//������Ƶ
	static bool				PlayVideo(const std::string& sUrl, const std::string& sType);//������Ƶ
	
	//��չ�ڴ�
	static bool				IsExtemalStorageReady();//��չ�ڴ��Ƿ�ɶ�д
	static std::string		GetExtemalStorageDir();	//��ȡ��չ�ڴ�Ŀ¼

	static bool        		IsAbsPath( const std::string& sPath );
	static uint64         	GetThreadId();
	static uint				GetThreadAmount();//��ȡ�߳���

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
	static bool				CopyDir(const std::string& sSrcDir,const std::string& sDesDir);//�����ļ���(����)

	static int				GetProcessId();
	static UINT64			GetProcessMemoryUsed();
	static UINT64			GetProcessMemoryFree();

	//����
	static bool				OpenUrl(const std::string& sUrl);//��ַ
	static std::string		GetNetWorkType();//��ȡ��������(���� "wap,2g,3g,wifi")
	static std::string		GetMacAddress();

	static int				GetResolutionWidth();//��ȡ�ֱ���(��)
	static int				GetResolutionHeight();//��ȡ�ֱ���(��)
	static std::string		GetOperatorName();//��ȡ��Ӫ������

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