#pragma once

#include "MacroCocos2dx.h"

#ifdef MACRO_LIB_COCOS2D

#include "TransitoryLinker.h"
#include "SceneFrameMgr.h"
#include "EventTrigger.h"
#include "HTimeOut.h"
#include "TimeOut.h"
#include "HLog.h"
#include "HSystem.h"
#include "ResolverCoreManager.h"
#include "UserConnector.h"
#include "IAnyObj.h"
#include "TObjCreator.h"

#include "MSystem.h"
//��ע:
//���� ��������
//1.�˺�����:��½���������� 360��½ ����QQ��½ ���� ����ע�� �˺� ���� ���� ���� �Լ�ע��Ĺٷ���
//2.��������:�ϼܵ������� �������ṩ�����ϼܵ����������� ��ios�ϼ� �����ƶ�MM�ϼ� ���� ����Ϸ�ϼ� ���� �����ϼܡ�
//3.�ƹ�����:���۵�������������� �Ժ��ַ�ʽ ����� ��װ����Ϸ������������ �ǵ��Գ�װ���ķ�ʽ��

//��ע:
//ʹ�õ�SDKδ���Ƿ���������SDK��ͨ����������ͬ�ģ���Ҳ�в�ͬ������ʹ�� AnySDK ����� С��������

//���ӣ�һ����� ȥ���Գ�װ�� ���Գ� ��װ����ʱ�� ������װ���� ���ǵ� ͨ�� ����Ϸ�ϼܵ���Ϸ������֧������Ӧ�� ҲӦ����ʹ�õ� ����Ϸ֧����ʽ����֧�������� �� �ڽ�����Ϸʱ ȴ�� ʹ��QQ���˺Ž��е�¼�ģ����ӵ��� ��������ʹ��AnySDK�����

//��ע:windows ƽ̨�� Debugģʽ Ĭ�� �� ��� �ļ���Сд,Releaseģʽ�����
NS_TOOL_FRAME_BEGIN

class TOOLFRAME_DLL IClientCore
	:public ISystemInit
	,public HUserConnector
	,public HLog
	,public HSystem
	,public HSceneFrameMgr
	,public HEventTrigger
{
public:
	typedef TObjCreator<IAnyObj> AnyObjCreator;
public:
	virtual bool				SetServerAddress(const VectorString& vAddress);//���÷�������ַ
	virtual bool				SetReconnect(int nReconnect = -1);		//������������Ĭ��Ϊ-1
	virtual bool				SetAllowMulit(bool bAllowMulit = false);//�����Ƿ�����࿪
	virtual bool				SetAutoPurgeCache(bool bAuto);			//�����Զ����ջ���
	virtual bool				SetNetErrCode(int nNetErrCode);			//��������������
	virtual bool				IsAutoPurgeCache()const;				//�Ƿ��Զ����ջ���
	virtual bool				Init();
	virtual bool				IsConnected()const;						//�Ƿ�������
	virtual bool				Connect();								//��ʼ���ӷ�����
	virtual bool				Disconnect(int nNetErrCode = NET_ERRCODE_ACTIVE,bool bClear = true);	//�Ͽ�����(����,����δ������Ϣ)
	virtual bool				SetAccountAnonymous();					//����ΪĬ���˺� ���� ������
	virtual int					GetNetErrCode()const;					//��ȡ����������
	virtual AnyObjCreator&		GetAnyObjCreator();
	virtual const AnyObjCreator& GetAnyObjCreator()const;

	//�ⲿ�ӿ�
public:
	virtual bool				OnPause();	//��ͣ
	virtual bool				OnResume();	//�ص���Ϸ
	virtual bool				OnScreenSizeChanged(int newWidth, int newHeight);
public:
	virtual bool				IsHasCachedMsg()const;	//�Ƿ��л����Э��
	virtual StreamBinaryPtr		PopCacheMsg();			//��������Э��
	virtual bool				ProcessCachedMsg();		//������Э��(һ��)
	virtual bool				ProcessCachedMsgAll();	//������Э��(����)
	virtual bool				ClearChachedMsg(bool bCacheMsg = false);	//������Э�� �� ��ֵ ������SetCacheMsg
	virtual int					PlaySound(const std::string& sSoundKey,bool bLoop = false)const;		//������Ч
	virtual int					PlayMusic(const std::string& sMusicKey,bool bLoop = true)const;			//��������
	virtual const std::string&	GetSoundFile(const std::string& sSoundKey)const;
	virtual const std::string&	GetString(const std::string& sID)const;									//��ȡ��Ϸ��ʾ����
	virtual const std::string	GetString(const std::string& sID,const MapStringString& vString)const;	//��ȡ��Ϸ��ʾ����	
	
	virtual time_t				SetServerTime(time_t uTime);		//���÷�����ʱ��
	virtual int					GetIntervalTime() const;			//��ȡ��ȡ�ͻ������������ʱ���
	virtual time_t				GetServerTime()const;				//��ȡ������ʱ��
	virtual int					CalIntervalTime(time_t uTime)const;	//����ʱ���

	//ҳ����ת
	virtual bool				SetGoToPage(int eGoToPage,int nArg1=0,int nArg2=0);
	virtual int					GetGoToPage()const;		//��ȡ��תҳ�� ö��ֵ
	virtual int					GetGoToArg1()const;
	virtual int					GetGoToArg2()const;
	virtual bool				IsGoToPageVaild()const;	//�Ƿ���Ҫ��תҳ��
	virtual bool				ClearGoToPage();		//�����תҳ��
public:
	virtual bool				SetState(int eState,int nArg1=0,int nArg2=0,int nArg3=0);
	virtual int					GetState()const;
	virtual int					GetStateArg1()const;
	virtual int					GetStateArg2()const;
	virtual int					GetStateArg3() const;
	virtual ISceneFrame*		FindRunningScene()const;
	virtual CEventTrigger&		GetEventTrigger();			//�¼�������
	virtual CSceneFrameMgr&		GetSceneMgr();				//����������
	virtual CUserConnector&		GetConnector();				//������
	virtual bool				IsAllowMulit()const;		//�Ƿ�����࿪
public:
	virtual bool				PushMsg(IMsgStream& msg,bool bSecret = true);		//ѹ����з���
	virtual bool				PushMsg(StreamBinaryPtr ptr,bool bSecret = true);
	virtual bool				SendMsg(IMsgStream& msg,bool bSecret = true);		//ֱ�ӷ���
	virtual bool				SendMsg(StreamBinaryPtr ptr,bool bSecret = true);
	virtual bool				Send(IMsgStream& msg,bool bSecret = true);			//��ͬ��PushMsg
	virtual bool				Send(StreamBinaryPtr ptr,bool bSecret = true);

	//����
public:
	CResolverCoreManager&		GetResolverCoreMgr();
	const CResolverCoreManager&	GetResolverCoreMgr()const;

	//��Ҫ����ʵ��
public:
	virtual bool OnSaveArchive();		//����浵
protected:
	virtual bool OnSceneChanged();		//�������л�
	virtual bool OnRootPageChanged();	//����ҳ���л�
	virtual bool OnNewPageAdd(IPage* pPage);		//����ҳ������
	virtual bool OnNewPageInited(IPage* pPage);		//����ҳ���ʼ�����
	virtual bool OnNewPageAllInited();			//��������ҳ���ʼ�����
protected:
	virtual bool OnConnected(uint uClientID);
	virtual bool OnConnectFaild(uint uClientID);
	virtual bool OnDisconnected(uint uClientID);
	virtual bool OnRefused(uint uClientID);
	virtual bool OnRecved(uint uClientID,IMsgStream& msgStream);
	virtual bool OnSend(StreamBinaryPtr ptr,bool bSecret);//����������ʱ

	//�����Ѵ���
protected:
	virtual bool OnConnected		(CUserConnector* pConnector)override;
	virtual bool OnConnectFaild		(CUserConnector* pConnector)override;
	virtual bool OnDisconnected		(CUserConnector* pConnector)override;
	virtual bool OnRecvEncrypted	(CUserConnector* pConnector,IMsgStream& msgStream)override {return false;}				//��������
	virtual bool OnRecvDecrypted	(CUserConnector* pConnector,IMsgStream& msgStream)override;								//��������
	virtual bool OnEncrypt			(CUserConnector* pConnector,void* pBuffer, size_t uLength)override {return false;}
	virtual bool OnEncryptFailed	(CUserConnector* pConnector,void* pBuffer, size_t uLength)override {return false;}
	virtual bool OnDecrypt			(CUserConnector* pConnector,void* pBuffer, size_t uLength)override {return false;}
	virtual bool OnDecryptFailed	(CUserConnector* pConnector,void* pBuffer, size_t uLength)override {return false;}
	virtual bool OnStateChanged		(CUserConnector* pConnector,int eState)override {return false;}
	virtual bool OnRecved			(CUserConnector* pConnector,IMsgStream& msgStream)override {return false;}
	virtual bool OnSend				(CUserConnector* pConnector,StreamBinaryPtr ptr,bool bSecret)override;
	virtual bool OnRefused			(CUserConnector* pConnector)override;
	virtual bool OnHeartTimeOut		(CUserConnector* pConnector)override;													//������ʱ
	virtual bool OnKeepHeartTimeOut	(CUserConnector* pConnector)override;													//��Ҫ��������ʱ
protected:
	virtual bool OnRecved(uint uClientID,IMsgStream& msgStream,bool bCacheMsg );
protected:
	virtual bool OnSystemInit()override;					//ϵͳ��ʼ��ʱ
	virtual	bool OnSystemProcess(uint64 uTime)override;		//��ѭ���ص�
	virtual bool OnSystemCleanUp()override;					//ϵͳ����(����false��ֹ����)
	virtual	bool OnSystemMemoryLow()override;				//�ڴ治��(����false��ֹ����)
protected:
	virtual bool OnLogMsg(const std::string& sLogLevel,const std::stringstream& sStreamLog)override;//������־ʱ(����false��ֹд��־)
protected:
	virtual bool OnEvent(const std::string& sEvent, const XEvent& xEvent)override;
public:
	CFIELD_INT(AppVer);					//��Ϸ�汾��
	CFIELD_STRING(AppVerString);		//��Ϸ�汾�ַ���
	CFIELD_INT(ResVer);					//��Դ�汾��

	CFIELD_VECTOR_STRING(UpdateServerIP);		//���·�������ַ

	CFIELD_STRING(DeviceChannel);		//����ע������
	CFIELD_STRING(DeviceAccount);		//�����˻�
	CFIELD_STRING(DevicePassword);		//��������

	CFIELD_INT(ZoneID);					//����
	CFIELD_INT(ServerID);				//������

	CFIELD_STRING(Channel);				//�˻�����
	CFIELD_STRING(Account);				//�˻��˺�
	CFIELD_STRING(Password);			//�˻�����

	CFIELD_STRING(ReleaseChannelID);	//��������
	CFIELD_STRING(PromotionChannelID);	//�ƹ�����

	CFIELD_STRING(SdkID);				//SDK ID

	CFIELD_BOOL(CacheMsg);				//����Э��

	CFIELD_STRING(Title);				//���ڱ�����(windows)
	CFIELD_REF(CPoint2d,Resolution,pt);	//���ڷֱ���(windows)

	CFIELD_BOOL(SleepFreeTime);			//�Ƿ���Ҫ�ڿ���ʱ˯��(�����Ż� Ĭ�Ϲر� ��Ϊ�޸�Դ��ķ�ʽ���Ӹ�Ч)
public:
	IClientCore(void);
	virtual ~IClientCore(void);
protected:
	int					_nIntervalTime;	//�ͻ������������ʱ���

	int					_eState;		//��Ϸ״̬
	int					_eStateArg1;	//��Ϸ״̬����1
	int					_eStateArg2;	//��Ϸ״̬����2
	int					_eStateArg3;	//��Ϸ״̬����3

	CUserConnector		_xConnector;	//������������
	
	CSceneFrameMgr		_vSceneMgr;		//����������

	bool				_bAllowMulit;	//����࿪

	ListStreamBinary	_vMsgCache;		//��Ϣ����

	MapStringString		_vString;		//��Ϸ��ʾ����
	MapStringString		_vSound;		//��Ϸ��Ч

	CResolverCoreManager _mgrResolver;	//�������

	//��תҳ��
	int			_eGoToPage;
	int			_nGoToArg1;
	int			_nGoToArg2;

	AnyObjCreator	_vAnyObjCreator;
};

NS_TOOL_FRAME_END

#endif //MACRO_LIB_COCOS2D
