#pragma once

#include "Macro.h"

//�����ߺ���ֻ����Windows������ 

#if MACRO_TARGET_OS == MACRO_OS_WINDOWS
#include <windows.h>
#include <TLHELP32.H>
#include <psapi.h>
#include "ApiWinCpu.h"
#include <tcpmib.h>
#include <udpmib.h>

class TOOLFRAME_DLL ApiWin
{
public:
	//�������ϵͳ�汾
	enum EWinVer{
		WIN_VER_INVALID,

		WIN_VER_WIN_95,
		WIN_VER_WIN_98,
		WIN_VER_WIN_ME,
		WIN_VER_WIN_NT,
		WIN_VER_WIN_XP,
		WIN_VER_WIN_2000,
		WIN_VER_WIN_2003,
		WIN_VER_WIN_VISTA,
		WIN_VER_WIN_7,
		WIN_VER_WIN_8,
		WIN_VER_WIN_8_1,//windows 8.1
		WIN_VER_WIN_10,
		WIN_VER_MAX,
	};

	typedef std::vector<MIB_TCPROW_OWNER_PID> VectorTcpInfo;
	typedef std::vector<MIB_UDPROW_OWNER_PID> VectorUdpInfo;
public:
	//ʱ��
	static time_t			GetNowTime();//(��)
	static UINT64			GetNowTimeMill();//(����)

	static std::string		GetNowTimeString();

	static uint64			FileTimeToUtc(const FILETIME* ftime);

	//��ȡTickCount
	static UINT64			GetSysTickCount64();
	static UINT64			GetTickCount64();
	static UINT64			GetTickCount();

	//ini
	static VectorString		GetIniScetionNames( const std::string& sFileName );
	static MapStringString	GetIniSection(const std::string& sFileName,const std::string& sSection);
	static void				GetIniValue(const std::string& sFileName,const std::string& sSection,const std::string& sKey,int& nValue,			const int nDefault = 0);
	static void				GetIniValue(const std::string& sFileName,const std::string& sSection,const std::string& sKey,std::string& sValue,	const std::string& sDefault = "");
	static void				WriteIniValue(const std::string& sFileName,const std::string& sSection,const std::string& sKey,const std::string& sValue);
	
	//�����ڴ��е��ַ�����ʽ(�ַ���1\0�ַ���2\0...�ַ���n\0\0)
	static VectorString		GetStrings( const char_t pSrc[] );

	//file
	static bool				IsFile(const std::string& sFile);
	static bool				CopyDir(const std::string& sSrcDir,const std::string& sDesDir);//�����ļ���(����)
	static bool				MakeDir( const std::string& sDir);
	static bool				RemoveDir(const std::string sDir);
	static bool				SaveFile(const std::string& sFileName,const void* pBuffer,size_t uLength);
	static bool				LoadFile(const std::string& sFileName,void* pBuffer,size_t uLength); 
	static bool				IsFileExist(const std::string& sFileName);
	static bool				RemoveFile(const std::string& sFileName);

	//�ַ���ת��
	static std::string		GbkToUtf8(const std::string& sSrc);	
	static std::string		Utf8ToGbk(const std::string& sSrc,bool bSkipMicroUtfLead=true);

	static std::wstring		GbkToUnc(const std::string& sSrc);
	static std::string		UncToGbk(const std::wstring& sSrc);

	static std::wstring		Utf8ToUnc(const std::string& sSrc);
	static std::string		UncToUtf8(const std::wstring& sSrc);

	static std::string		UncToGbk(const std::string& sSrc);

	//�ַ���ת�� - ����
	static void				GbkToUtf8(const VectorString& vSrc,VectorString& vDes);
	static void				GbkToUtf8(VectorString& vStrings);

	static bool				IsUtf8(const std::string& Src,bool bCheckMicroUtfLead = true);
	static bool				IsGBK(const std::string& Src);//����ȷ(���޸�)

	static bool				IsMicroUtfLead(const std::string& sSrc);//�Ƿ���΢��Utfͷ
	static uint				GetMicroUtfLeadLength();

	//Ŀ¼
	static std::string		GetExePath();
	static std::string		GetExeDir();
	static std::string		GetExeName();
	static std::string		GetExeNameWithOutExt();
	static bool				GetFilesPath(VectorString& vDes,const std::string& sDir,const std::string& sFilter="*.*",bool bExcept = false);//��ȡĿ��Ŀ¼�¾���·��
	static bool				GetFilesPath(VectorString& vDes,std::string sDir,const VectorString& vSpec,bool bExcept = false);//��ȡĿ��Ŀ¼�¾���·��
	static bool				IsFileCaseSensitive(const std::string& sPath);//�ļ���Сд���� �Ƿ�һ��
	static std::string		GetWorkingDir();
	static void				SetWorkingDir(const std::string& sDir);
	static void				SetWorkingDirWithExeDir();
	static bool				IsAbsPath( const std::string& sPath );
	static bool				IsDir(const std::string& sDir);
	static size_t			GetFileLength(const std::string& sFileName);
	static std::string		GetDirByType(int eDirType);

	//����̨
	static void				SetConsoleTextAttribute(int nColor);//��ɫֵ��ѯ FOREGROUND_RED �Ķ���
	static void				ClearScreen();
	static bool				SetConsoleHide();//���ؿ���̨

	//�߳�
	static void				Sleep(UINT64 nTimeMill);
	static uint64			GetThreadId();
	static uint				GetThreadAmount(int nProcessID=-1);//��ȡ�߳���(Ĭ�ϱ�����)

	//����
	static int				GetProcessId();							//��ȡ��ǰ����ID
	static std::string		GetProcessName( int nProcessID );		//��ȡ��������
	static UINT64			GetProcessMemoryUsed(int nProcessID);	//��ȡ�����ڴ�ռ��
	static int				GetProcessThreads(int nProcessID);		//��ȡ�����߳���
	static UINT64			GetProcessMemoryFree();					//��ȡʣ�������ڴ�
	static UINT64			GetProcessMemoryTotal();				//��ȡ�ܹ������ڴ�
	static int				GetProcessMemoryUsage();				//��ȡ�ڴ�ʹ����
	static int				GetProcessIdByExePath(const std::string& sExePath);
	static int				CalProcessCount(const std::string& sExePath);//����ý��̱����и���
	static bool				TerminateProcess(int nProcessID);
	static bool				IsExecutedMulit();//�Ƿ����ж��
	static int				GetResolutionWidth();//��ȡ�ֱ���(��)
	static int				GetResolutionHeight();//��ȡ�ֱ���(��)
	static std::string		GetOperatorName();		//��ȡ��Ӫ������
	static bool				PurgeMemory(int nProcessID = -1);//�ڴ���� -1���л������ڴ�

	static CApiWinCpu&		GetWinCpu();
	static bool				ReflashCpuState();	//ˢ��cpu״̬
	static int				GetCpuUsage();		//��ȡCPUռ����
	static int				GetCpuIdle();		//��ȡCPU������
	static int				GetProcesserNumber();//��ȡCPU����
	static int				GetCpuUsage(int nProcessID);//��ȡCPUռ����
	static int				GetCpuUsage(uint64& uCreationTime, uint64& uExitTime, uint64& uKernelTime, uint64& uUserTime,int nProcessID);//��ȡCPUռ����
	static uint64			GetCpuUseTime(int nProcessID);//��ȡCPUռ����ʱ��
	static bool				GetCpuTime(uint64& uCreationTime, uint64& uExitTime, uint64& uKernelTime, uint64& uUserTime ,int nProcessID);
	static uint64			GetSystemTime();

	//ϵͳ
	static std::string		GetLanguageString();//��ȡ��ǰϵͳ����
	static EWinVer			GetPlatformVerEnum();	//��ȡϵͳ�汾
	static std::string		GetPlatformVer(EWinVer eWinVer);
	static std::string		GetPlatformVer();
	static std::string		GetModel();				//��ȡ�ֻ��ͺ�
	static bool				SystemReboot();			//����
	static bool				SystemShutDown();		//�ػ�
	static bool				SystemLogOut();			//ע��
	static bool				SystemSetTime(uint64 uMillTime);//����ʱ��

	//VC����
	static void				Trace( const std::string& sMsg,const std::string& sTag);		//��ӡ�ڿ���̨
	static std::string		GetCallStack(HANDLE hProcess = NULL, HANDLE hThread = NULL);	//��ȡ���ö�ջ(Ĭ�ϻ�ȡ��ǰ���ö�ջ)
	static std::string		GetCallStackAll();												//��ȡ��ǰ���������̵߳ĵ��ö�ջ

	//����
	static std::string		GetMacAddress();
	static std::string		GetIPAddress();
	static std::string		GetNetWorkType();//��ȡ��������(���� "wap,2g,3g,wifi")
	static bool				OpenUrl(const std::string& sUrl);//��ַ
	static bool				GetMacFlow(UINT64* upload,UINT64* download);					//��ȡ��������

	static bool				GetSystemTimes(uint64* pIdleTime,uint64* pKernelTime,uint64* pUserTime);
	static uint64			ToUint64(const FILETIME& xTime);

	static std::string		GetTcpPortInfoString(int nPort);
	static std::string		GetTcpLickInfoString();
	static std::string		GetUdpPortInfoString(int nPort);
	static std::string		GetUdpLickInfoString();

	static std::string		TcpInfoToString(const MIB_TCPROW_OWNER_PID* pTcpInfo);
	static std::string		UdpInfoToString(const MIB_UDPROW_OWNER_PID* pTcpInfo);
	static bool				FindTcpPort(VectorTcpInfo& vInfo,int nPort);
	static bool				FindUdpPort(VectorUdpInfo& vInfo,int nPort);
	static bool				IsPortOccupied(int nPort);		//�ж϶˿��Ƿ�ռ��

	//�Ի���
	static bool				DialogFileOpen(VectorString& vPath);

	//���
	static HWND				GetConsoleWindow();//��ȡ����̨���
	static HWND				GetHWNDByProcessID(int nProcessID);

	static bool				ScreenShot(const std::string& sFileName); //��ͼ
public:
	static bool					GetProcessEntry32ByProcessID(PROCESSENTRY32* proc, int nProcessID );
	static bool					GetProcessEntry32ByExePath(PROCESSENTRY32* proc,const std::string& sExePath);
	static bool					GetProcessMemoryCountersByProcessID(PROCESS_MEMORY_COUNTERS* mem, int nProcessID );

	static bool					ToMultiWide(const std::string& sSrc,std::wstring& sDes,int nSrcCode);
	static bool					ToMultiWide(const std::wstring& sSrc,std::string& sDes,int nSrcCode);

	static bool					ToMultiWide(const char* pSrc,std::wstring& sDes,int nSrcCode);
	static bool					ToMultiWide(const wchar_t* pSrc,std::string& sDes,int nSrcCode);

	static	std::string			ToMulti(const std::wstring& sSrc);
	static	const std::string&	ToMulti(const std::string& sSrc);

	static	const std::wstring&	ToWide(const std::wstring& sSrc);
	static	std::wstring		ToWide(const std::string& sSrc);

#if MACRO_TARGET_FONT == MACRO_FONT_ANSI
	inline static const	std::string_t&	ToStringT(const std::string& sSrc){
		return sSrc;
	}
	inline static	std::string_t	ToStringT(const std::wstring& sSrc){
		return ToMulti(sSrc);
	}
#elif  MACRO_TARGET_FONT == MACRO_FONT_UNICODE
	inline static	std::string_t	ToStringT(const std::string& sSrc){
		return ToWide(sSrc);
	}
	inline static	const std::string_t&	ToStringT(const std::wstring& sSrc){
		return sSrc;
	} 
#endif

	//�ַ�������
	static bool			ApiStrCpy( const std::string& sSrc,wchar_t* pDes,int nLen);
	static bool			ApiStrCpy( const std::string& sSrc,char* pDes,int nLen); 
public:
	static UINT64		ApiCreateProcess(const std::string& sExeName,const std::string& sWorkingDir="",const std::string& sCommandLine="");
	static bool			ApiCreateDirectory(const std::string& sDir);
	static std::string	ApiGetCommandLine();
	static std::string	ApiGetModuleFileName();
	static std::string	ApiGetCurrentDirectory();
	static bool			ApiSetCurrentDirectory(const std::string& sDir);
	static HANDLE		ApiFindFirstFile(const std::string& sPath, WIN32_FIND_DATA* wfd);
	static bool			ApiPathMatchSpec(const std::string& sPath,const std::string& sSpec);//�Ƚ��Ƿ����ͨ���
	static bool			ApiPathMatchSpec(const std::string& sPath,const VectorString& vSpec);//�Ƚ��Ƿ����ͨ���
	static bool			ApiDeleteFile(const std::string& sFile);
	static bool			ApiRemoveDirectory(const std::string& sDir);
	static UINT			ApiGetFileAttributes(const std::string& sDir);
	static bool			ApiMakeDir( const std::string& sDir);
	static bool			ApiPathIsRelative(const std::string& sDir);
	static bool			ApiPathIsRoot(const std::string& sDir);
	static bool			ApiRemoveDir(std::string sDir);
	static std::string	ApiGetFristMacAddress();
	static std::string	ApiGetFristMacNetWorkType();
	static std::string	ApiGetActiveMacNetWorkType();
	static HANDLE		ApiGetProcessHandle(int nProcessID);
	static std::string	ApiTranNetWorkType(int eAdapterType);
	static BOOL			ApiIsWinVerEqualTo(DWORD dwMajorVersion, DWORD dwMinorVersion);

	static std::string	ApiAddrToString(struct in_addr in);
	static bool			ApiEmptyWorkingSet(int nProcessID);//���ڴ�д��Ӳ�̴Ӷ���С�ڴ�

	//����̨
	static std::string	ApiGetConsoleTitle();//��ȡ����̨���ڱ���
	static bool			ApiSetConsoleTitle(const std::string & sTitle);//���ÿ���̨���ڱ���
};

#endif
