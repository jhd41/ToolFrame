#pragma once

#include "Macro.h"

NS_TOOL_FRAME_BEGIN

class TOOLFRAME_DLL IApiTool
{
public:
	//ʱ��
	virtual UINT64		GetNowTimeMill();

	//Ŀ¼
	virtual std::string	GetDirByType(int eDirType);//����Ŀ¼���ͻ�ȡĿ¼ǰ׺

	virtual bool		SetWorkingDirWithExeDir();
	virtual bool		IsAbsPath(const std::string& sPath);//�Ƿ�Ϊ����·��
	virtual bool		MakeDir(const std::string& sDir);	//�����ļ���
	virtual bool		RemoveDir(const std::string& sDir);	//ɾ��Ŀ¼
	virtual bool		CopyDir(const std::string& sSrcDir,const std::string& sDesDir);//�����ļ���(����)

	//�ļ�
	virtual bool		IsFileExist(const std::string& sFileName);
	virtual size_t		GetFileLength(const std::string& sFileName);
	virtual bool		SaveFile(const std::string& sFileName,const void* pBuffer,size_t uLength);
	virtual bool		LoadFile(const std::string& sFileName,void* pBuffer,size_t uLength); 
	virtual bool		RemoveFile(const std::string& sFileName);
	virtual bool		RenameFile(const std::string& sPathSrc,const std::string& sPathDes);
	virtual bool		IsFileCaseSensitive( const std::string& sPath );

	//����̨
	virtual void		SetConsoleTextAttribute(int nColor);//��ɫֵ��ѯ FOREGROUND_RED �Ķ���
	virtual void		OutPut(const std::string& sMsg,const std::string& sTag="",bool bTrace = true);	//��ӡ
	virtual void		ClearScreen();
	virtual bool		SetConsoleHide();//���ؿ���̨
	virtual std::string	ApiGetConsoleTitle();	//��ȡ����̨����	
	virtual bool		ApiSetConsoleTitle(const std::string & sTitle);//���ÿ���̨���ڱ���

	//����
	virtual int			GetProcessId();
	virtual std::string	GetProcessPath();
	virtual std::string	GetProcessName( int nProcessID );//���ݽ���ID����ȡ��������
	virtual std::string	GetProcessNameWithOutExt();
	virtual std::string	GetProcessNameWithOutExt( int nProcessID );
	virtual std::string	GetProcessDir();

	virtual	UINT64		ApiCreateProcess(const std::string& sExePath,const std::string& sWorkingDir,const std::string& sCommandLine);
	virtual	int			GetProcessIdByExePath(const std::string& sExePath);
	virtual uint64		GetProcessMemoryUsed(int nProcessID);
	virtual uint64		GetProcessMemoryFree();//��ȡʣ���ڴ�
	virtual uint64		GetProcessMemoryTotal();//��ȡʣ���ڴ�
	virtual int			GetProcessMemoryUsage();//��ȡ�ڴ�ʹ����
	virtual bool		PurgeMemory(int nProcessID = -1);//�ڴ���� -1���л������ڴ�
	virtual bool		ReflashCpuState();	//ˢ��cpu״̬
	virtual int			GetCpuUsage();		//��ȡCPUռ����
	virtual int			GetCpuIdle();		//��ȡCPU������
	virtual int			GetCpuUsage(int nProcessID);		//��ȡCPUռ����
	virtual uint64		GetCpuUseTime(int nProcessID);//��ȡCPUռ����ʱ��
	virtual bool		TerminateProcess(int nProcessID);//��ֹ����
	virtual bool		IsExecutedMulit();		//�Ƿ�࿪
	virtual bool		ScreenShot(const std::string& sFileName);//��ͼ
	virtual std::string ApiGetCommandLine();//��ȡ������

	//����
	virtual	std::string GetMacAddress();
	virtual std::string GetIPAddress();
	virtual bool		OpenUrl(const std::string& sUrl);
	virtual std::string	GetNetWorkType();//��ȡ��������(���� "wap,2g,3g,wifi","lan")
	virtual bool		GetMacFlow(UINT64* upload,UINT64* download);					//��ȡ��������

	virtual int			GetResolutionWidth();	//��ȡ�ֱ���(��)
	virtual int			GetResolutionHeight();	//��ȡ�ֱ���(��)
	virtual std::string	GetOperatorName();		//��ȡ��Ӫ������

	virtual std::string	GetTcpPortInfoString(int nPort);//��ȡռ��ָ���˿ڵĽ�����Ϣ
	virtual std::string	GetTcpLickInfoString();			//��ȡ����Tcp���ӵĽ�����Ϣ
	virtual std::string	GetUdpPortInfoString(int nPort);
	virtual std::string	GetUdpLickInfoString();
	virtual bool		IsPortOccupied(int nPort);		//�ж϶˿��Ƿ�ռ��

	//�߳�
	virtual void		Sleep(UINT64 nTimeMill);
	virtual uint64		GetThreadId();
	virtual uint		GetThreadAmount();//��ȡ�߳���

	//����
	virtual std::string	GetCallStack();		//��ȡ���ö�ջ(Ĭ�ϻ�ȡ��ǰ���ö�ջ)
	virtual std::string	GetCallStackAll();	//��ȡ��ǰ���������̵߳ĵ��ö�ջ

	//�汾
	virtual int			GetCompileVer();	//��ȡ����汾(MACRO_VER_DEBUG)
	virtual bool		IsDebugVer();		//�Ƿ�Ϊ���԰汾
	virtual bool		IsReleaseVer();		//�Ƿ�Ϊ�����汾

	//ϵͳ
	virtual std::string GetDeviceID();		//��ȡ�豸ID��
	virtual std::string	GetLanguageString();//����
	virtual int			GetPlatform();		//��ȡ����ϵͳö��ֵ
	virtual std::string	GetPlatformVer();	//��ȡϵͳ�汾
	virtual std::string GetModel();			//��ȡ�ֻ��ͺ�
	virtual bool		SystemReboot();		//����
	virtual bool		SystemShutDown();	//�ػ�
	virtual bool		SystemLogOut();		//ע��
	virtual bool		SystemSetTime(uint64 uTime);//����ʱ��
	virtual bool		IsPad();			//�Ƿ�Ϊƽ��
	virtual bool		Vibrator(int nMillTime);//��
	virtual bool		PlayVideo(const std::string& sUrl);//��

	virtual std::string ToPlatformString(int ePlatform);//ת��ϵͳ����
	virtual int			TranPlatformString(const std::string& sPlatform);

	virtual std::string	ToLanguageString(int eLanguage);//����
	virtual int			TranLanguageString(const std::string& sLanguage);
public:
	IApiTool(void);
	virtual ~IApiTool(void);
};

NS_TOOL_FRAME_END
