#pragma once
#include "Macro.h"
#include "MacroDefineBoost.h"
#include "IApiTool.h"

//�����ߺ��� ���Կ�ƽ̨ ��Ҫ��Macor.h����ʹ�õ�ʵ�� ����������
namespace ToolFrame
{
	//ʱ��
	TOOLFRAME_DLL time_t		GetNowTime();
	TOOLFRAME_DLL UINT64		GetNowTimeMill();
	TOOLFRAME_DLL const std::string& GetNowTimeString();
	TOOLFRAME_DLL std::string	GetNowTimeString(const std::string& sFormat);//��ȡ��ǰʱ����ַ���
	TOOLFRAME_DLL std::string	GetTodayDateString();
	TOOLFRAME_DLL time_t		CalLocalHour(int tTime);		//������������(ʱ���)
	TOOLFRAME_DLL time_t		CalLocalNextHour(int tTime);	//������һ������(ʱ���)
	TOOLFRAME_DLL time_t		CalLocalToNextHour(int tTime);	//���㵽��һ������� ʱ��

	//Ŀ¼
	TOOLFRAME_DLL std::string	GetWorkingDir();
	TOOLFRAME_DLL std::string	GetWriteableDir();
	TOOLFRAME_DLL std::string	GetCacheDir();

	TOOLFRAME_DLL bool			InitDirType();//��ʼ���ļ�������
	TOOLFRAME_DLL MapIntString& GetDirType();
	TOOLFRAME_DLL bool			AddDir(int eDirType,const std::string& sDir);
	TOOLFRAME_DLL std::string	GetDirByType(int eDirType);

	TOOLFRAME_DLL bool			SetWorkingDirWithExeDir();
	TOOLFRAME_DLL std::string	GetAbsPathByRelativePath( const std::string& sPath );//��ȡ����·��(�������·��)
	TOOLFRAME_DLL std::string	GetAbsPath(const std::string& sPath);				//��ȡ����·��(������·����������Ի��߾���)
	TOOLFRAME_DLL bool			IsAbsPath(const std::string& sPath);				//�Ƿ�Ϊ����·��
	
	TOOLFRAME_DLL bool			MakeDir(const std::string& sDir,int eDirType = DIR_TYPE_WRITEABLE);		//�����ļ���
	TOOLFRAME_DLL bool			RemoveDir(const std::string& sDir,int eDirType = DIR_TYPE_WRITEABLE);	//ɾ��Ŀ¼
	TOOLFRAME_DLL bool			CopyDir(const std::string& sSrcDir,const std::string& sDesDir);//�����ļ���(����)

	//�ļ�
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
	TOOLFRAME_DLL VectorString&		GetSearchDir();	//��ȡ����·��
	TOOLFRAME_DLL MapStringString&	GetFileIndex();	//��ȡ�ļ�����(���·�� -> ����·��)
	TOOLFRAME_DLL CMutexRecursive&	GetMutexFileIndex();//�ļ�������
	TOOLFRAME_DLL bool			AddSearchDir(const std::string& sDir);//�������·�� (�����ӵ�·���ᱻ��������)
	TOOLFRAME_DLL bool			IsInSearchDir(const std::string& sDir);//�ж��Ƿ��Ѿ���������·��
	TOOLFRAME_DLL bool			IsHasFileIndex(const std::string& sFile);	//�Ƿ�����ļ�����
	TOOLFRAME_DLL std::string	GetFileIndex(const std::string& sFileName);	//�Ƿ��Ѿ���������
	TOOLFRAME_DLL bool			AddFileIndex(const std::string& sFileName,const std::string& sPath);
	TOOLFRAME_DLL bool			RemoveFileIndex(const std::string& sFileName);
	TOOLFRAME_DLL bool			RemoveFileIndex();
	TOOLFRAME_DLL std::string	SearchFile(const std::string& sFileName);
	TOOLFRAME_DLL std::string	SearchFile(const std::string& sFileName,int eDirType);
	TOOLFRAME_DLL std::string	ReSearchFile(const std::string& sFileName);	//��������
	TOOLFRAME_DLL std::string	SmartSearchPath(const std::string& sFileName);//����ļ������� ���Ե�����·����ȥѰ��
	TOOLFRAME_DLL bool			IsFileCaseSensitive(const std::string& sPath);//�ļ�·����Сд�Ƿ�һ��
	TOOLFRAME_DLL bool&			IsCheckFileCaseSensitive();						//�Ƿ����ļ���Сд
	TOOLFRAME_DLL bool			SetCheckFileCaseSensitive(bool bCheck);

	TOOLFRAME_DLL std::string	FullPath(const std::string& sFileName,int eDirType);//ƴװ���ļ�����·�� ������
	TOOLFRAME_DLL std::string	FullPathDir(const std::string& sDir,int eDirType);	//����·���ļ���

	//����̨
	TOOLFRAME_DLL void			SetConsoleTextAttribute(int nColor);//��ɫֵ��ѯ FOREGROUND_RED �Ķ���
	TOOLFRAME_DLL void			OutPut(const std::string& sMsg,const std::string& sTag="",bool bTrace = true);	//��ӡ
	TOOLFRAME_DLL void			ClearScreen();
	TOOLFRAME_DLL bool			SetConsoleHide();	//���ؿ���̨
	TOOLFRAME_DLL std::string	GetConsoleTitle();	//��ȡ����̨����	
	TOOLFRAME_DLL bool			SetConsoleTitle(const std::string & sTitle);//���ÿ���̨���ڱ���

	//����
	TOOLFRAME_DLL int			GetProcessId();
	TOOLFRAME_DLL std::string	GetProcessPath();
	TOOLFRAME_DLL bool			ScreenShot(const std::string& sFileName);//��ͼ

	TOOLFRAME_DLL std::string	GetProcessName( int nProcessID );//���ݽ���ID����ȡ��������
	TOOLFRAME_DLL std::string	GetProcessNameWithOutExt();
	TOOLFRAME_DLL std::string	GetProcessNameWithOutExt( int nProcessID );
	TOOLFRAME_DLL std::string	GetProcessDir();
	TOOLFRAME_DLL bool			IsExecutedMulit();				//�Ƿ����ж��

	TOOLFRAME_DLL UINT64		CreateProcess(const std::string& sExePath,const std::string& sWorkingDir="",const std::string& sCommandLine="");
	TOOLFRAME_DLL int			GetProcessIdByExePath(const std::string& sExePath);
	TOOLFRAME_DLL uint64		GetProcessMemoryUsed(int nProcessID);//��ȡʹ�õ��ڴ�
	TOOLFRAME_DLL uint64		GetProcessMemoryFree();//��ȡʣ���ڴ�
	TOOLFRAME_DLL uint64		GetProcessMemoryTotal();//��ȡ�ܹ��ڴ�
	TOOLFRAME_DLL int			GetProcessMemoryUsage();//��ȡ�ڴ�ʹ����
	TOOLFRAME_DLL bool			PurgeMemory(int nProcessID = -1);//�����ڴ� -1������������
	
	TOOLFRAME_DLL bool			ReflashCpuState();	//ˢ��cpu״̬
	TOOLFRAME_DLL int			GetCpuUsage();		//��ȡCPUռ����
	TOOLFRAME_DLL int			GetCpuIdle();		//��ȡCPU������
	TOOLFRAME_DLL int			GetCpuUsage(int nProcessID);		//��ȡCPUռ����
	TOOLFRAME_DLL uint64		GetCpuUseTime(int nProcessID);//��ȡCPUռ����ʱ��

	TOOLFRAME_DLL bool			TerminateProcess(int nProcessID);
	TOOLFRAME_DLL std::string	GetCommandLine();//��ȡ������
	
	//����
	TOOLFRAME_DLL std::string	GetMacAddress();
	TOOLFRAME_DLL std::string	GetIPAddress();
	TOOLFRAME_DLL bool			OpenUrl(const std::string& sUrl);//��Url.���Ҫ����ҳ�� �����http://��ͷ
	TOOLFRAME_DLL std::string	GetNetWorkType();//��ȡ��������(���� "wap,2g,3g,wifi","lan")
	TOOLFRAME_DLL bool			GetMacFlow(UINT64* upload,UINT64* download);					//��ȡ��������
	TOOLFRAME_DLL bool			IsPayNet();	//�Ƿ��Ǹ�������wap,2g,3g,wwan,δ֪����
	TOOLFRAME_DLL bool			IsFreeNet();//�Ƿ����������wifi lan
	TOOLFRAME_DLL std::string	GetTcpPortInfoString(int nPort);//��ȡռ��ָ���˿ڵĽ�����Ϣ(Tcp)
	TOOLFRAME_DLL std::string	GetTcpLickInfoString();			//��ȡ����Tcp���ӵĽ�����Ϣ
	TOOLFRAME_DLL std::string	GetUdpPortInfoString(int nPort);
	TOOLFRAME_DLL std::string	GetUdpLickInfoString();
	TOOLFRAME_DLL std::string	GetPortInfoString(int nPort);	//��ȡռ��ָ���˿ڵĽ�����Ϣ(����)
	TOOLFRAME_DLL bool			IsPortOccupied(int nPort);		//�ж϶˿��Ƿ�ռ��

	TOOLFRAME_DLL int			GetResolutionWidth();	//��ȡ�ֱ���(��)
	TOOLFRAME_DLL int			GetResolutionHeight();	//��ȡ�ֱ���(��)
	TOOLFRAME_DLL std::string	GetOperatorName();		//��ȡ��Ӫ������

	//�߳�
	TOOLFRAME_DLL void			Sleep(UINT64 nTimeMill);
	TOOLFRAME_DLL uint64		GetThreadId();
	TOOLFRAME_DLL uint			GetThreadAmount();//��ȡ�߳���

	//ϵͳ
	TOOLFRAME_DLL std::string	GetDeviceID();		//��ȡ�豸ID��
	TOOLFRAME_DLL int			GetLanguage();		//����
	TOOLFRAME_DLL std::string	GetLanguageString();//���Դ���(��׼)
	TOOLFRAME_DLL int			GetPlatform();		//��ȡ����ϵͳö��ֵ
	TOOLFRAME_DLL std::string	GetPlatformString();//��ȡϵͳ����(��ǰ)
	TOOLFRAME_DLL std::string	GetPlatformVer();	//��ȡϵͳ�汾
	TOOLFRAME_DLL std::string	GetModel();			//��ȡ�ֻ��ͺ�

	TOOLFRAME_DLL std::string	ToPlatformString(int ePlatform);//��ȡϵͳ����
	TOOLFRAME_DLL int			TranPlatformString(const std::string& sPlatform);

	TOOLFRAME_DLL std::string	ToLanguageString(int eLanguage);//����
	TOOLFRAME_DLL int			TranLanguageString(const std::string& sLanguage);

	TOOLFRAME_DLL bool			SystemReboot();		//����
	TOOLFRAME_DLL bool			SystemShutDown();	//�ػ�
	TOOLFRAME_DLL bool			SystemLogOut();		//ע��
	TOOLFRAME_DLL bool			SystemSetTime(uint64 uTime);//����ʱ��
	TOOLFRAME_DLL bool			IsPad();			//�Ƿ�Ϊƽ��
	TOOLFRAME_DLL bool			Vibrator(int nMillTime);//��
	TOOLFRAME_DLL bool			PlayVideo(const std::string& sUrl);//��

	//����
	TOOLFRAME_DLL bool			DebugCrack();		//ʹ��ϵͳ��óٻ� ���ӷ�϶��ʱ��
	TOOLFRAME_DLL bool			DebugSetCrack(bool bCrack = true);		//�ѷ����
	TOOLFRAME_DLL bool&			IsDebugCrack();
	TOOLFRAME_DLL std::string	GetCallStack();		//��ȡ���ö�ջ(Ĭ�ϻ�ȡ��ǰ���ö�ջ)
	TOOLFRAME_DLL std::string	GetCallStackAll();	//��ȡ��ǰ���������̵߳ĵ��ö�ջ

	//�汾
	TOOLFRAME_DLL int			GetCompileVer();	//��ȡ����汾(MACRO_VER_DEBUG)
	TOOLFRAME_DLL bool			IsDebugVer();		//�Ƿ�Ϊ���԰汾
	TOOLFRAME_DLL bool			IsReleaseVer();		//�Ƿ�Ϊ�����汾

	//ȫ�ֹ��ߵײ�(֧�ֵ�����ʵ��)
	TOOLFRAME_DLL IApiTool*		GetApiTool();
	TOOLFRAME_DLL void			SetApiTool(IApiTool* pApiTool);
	TOOLFRAME_DLL IApiTool*		GetApiToolDefault();//���Ĭ��Api��д����
};
