#pragma once
#include "Macro.h"
#include "MacroNet.h"
#include "IMsgStream.h"
#include "TransitoryLinker.h"
#include "TimeOut.h"
#include "HTimeOut.h"

//�û�������
//Ĭ�ϻᷴ���������ӷ����������Ӻ� ��һֱ��������

//SetReconnectMax	Ĭ�����޷�������

NS_TOOL_FRAME_BEGIN
class TOOLFRAME_DLL CUserConnector;
//////////////////////////////////////////////////////////////////////////
class TOOLFRAME_DLL HUserConnector
{
public:
	virtual bool OnConnected		(CUserConnector* pConnector){return true;}
	virtual bool OnConnectFaild		(CUserConnector* pConnector){return true;}
	virtual bool OnDisconnected		(CUserConnector* pConnector){return true;}
	virtual bool OnRecved			(CUserConnector* pConnector,IMsgStream& msgStream){return false;}				//������ʱ ����true������ȷ���� ������� ���ռ��� ���� Э��ٵ�
	virtual bool OnSend				(CUserConnector* pConnector, StreamBinaryPtr ptr,bool bSecret){return true;}		//������ʱ,����false ������
	virtual bool OnStateChanged(CUserConnector* pConnector, int eState) { return false; }

	virtual bool OnRecvEncrypted(CUserConnector* pConnector, IMsgStream& msgStream) { return false; }				//��������
	virtual bool OnRecvDecrypted(CUserConnector* pConnector, IMsgStream& msgStream) { return false; }				//��������
	virtual bool OnEncrypt(CUserConnector* pConnector, void* pBuffer, size_t uLength) { return false; }
	virtual bool OnEncryptFailed(CUserConnector* pConnector, void* pBuffer, size_t uLength) { return false; }
	virtual bool OnDecrypt(CUserConnector* pConnector, void* pBuffer, size_t uLength) { return false; }
	virtual bool OnDecryptFailed(CUserConnector* pConnector, void* pBuffer, size_t uLength) { return false; }

	virtual bool OnRefused(CUserConnector* pConnector) { return false; }
	virtual bool OnHeartTimeOut(CUserConnector* pConnector) { return false; }										//������ʱ
	virtual bool OnKeepHeartTimeOut(CUserConnector* pConnector) { return false; }										//��Ҫ��������ʱ

	virtual bool OnErrCacheFull(CUserConnector* pConnector, StreamBinaryPtr pBuffer) { return false; }//�����ͻ���������
public:
	HUserConnector(){}
	virtual ~HUserConnector(){}
};
//////////////////////////////////////////////////////////////////////////
class TOOLFRAME_DLL HUserConnectorLog
	:public HUserConnector
{
public:
	virtual bool OnConnected(CUserConnector* pConnector)override;
	virtual bool OnConnectFaild(CUserConnector* pConnector)override;
	virtual bool OnDisconnected(CUserConnector* pConnector)override;
	virtual bool OnRecved(CUserConnector* pConnector, IMsgStream& msgStream)override;
	virtual bool OnSend(CUserConnector* pConnector, StreamBinaryPtr ptr, bool bSecret)override;				//������ʱ,����false ������
	virtual bool OnStateChanged(CUserConnector* pConnector, int eState)override;

	virtual bool OnRecvEncrypted(CUserConnector* pConnector, IMsgStream& msgStream)override;				//��������
	virtual bool OnRecvDecrypted(CUserConnector* pConnector, IMsgStream& msgStream)override;				//��������
	virtual bool OnEncrypt(CUserConnector* pConnector, void* pBuffer, size_t uLength)override;
	virtual bool OnEncryptFailed(CUserConnector* pConnector, void* pBuffer, size_t uLength)override;
	virtual bool OnDecrypt(CUserConnector* pConnector, void* pBuffer, size_t uLength)override;
	virtual bool OnDecryptFailed(CUserConnector* pConnector, void* pBuffer, size_t uLength)override;
	
	virtual bool OnRefused(CUserConnector* pConnector)override;
	virtual bool OnHeartTimeOut(CUserConnector* pConnector)override;										//������ʱ
	virtual bool OnKeepHeartTimeOut(CUserConnector* pConnector)override;									//��Ҫ��������ʱ

	virtual bool OnErrCacheFull(CUserConnector* pConnector, StreamBinaryPtr pBuffer)override;				//�����ͻ���������
public:
	HUserConnectorLog() {}
	virtual ~HUserConnectorLog() {}
};
//////////////////////////////////////////////////////////////////////////
class TOOLFRAME_DLL CUserConnector
	:public HTransitoryLinker
	,public HTimeOut
	,public HUserConnectorLog
{
public:
	enum EState{
		STATE_INVAILD =0,

		STATE_CONNECT,			//������
		STATE_CONNECTED,		//������
		STATE_STOPING,			//ֹͣ��
		STATE_STOP,				//��ֹͣ
		STATE_RECONNECT,		//������

		STATE_NORMAL,			//����
		STATE_RECONNECT_FAILD,	//����ʧ��

		STATE_MAX,
	};
public:
	virtual bool				SetHandler(HUserConnector* hHandler);
	virtual bool				SetHeartCheck(time_t tTimeCheck);			//����������ѯʱ��(ҪС)
	virtual bool				SetHeartTimeOut(time_t tTimeOut);			//����������ʱʱ��(���ȶ� ʱ������Ϊ[��ʱʱ��,��ʱʱ�� + ��ѯʱ��])
	virtual bool				SetHeartPing(time_t tTime);					//���� ������ʱ��(���ȶ� ʱ������Ϊ[��ʱʱ��,��ʱʱ�� + ��ѯʱ��])
	virtual bool				SetServerAddress(const std::string& sAddress);
	virtual bool				SetServerAddress( const VectorString& vAddress );
	virtual bool				SetSecretKey(uint32 uAssID,uint32 uSecretKey,uint32 uTimeServer);//������Կ
	virtual bool				SetReconnectMax(int nCount);				//������������
	virtual bool				SetCacheMax(uint uCount);					//���÷��ͻ�������С
	virtual bool				SetReSend(bool bResend);					//���� ���������·���(Ĭ�ϵ��ߺ�����û�з�����ɵ�Э��)
	virtual bool				SetKeepLink(bool bKeepLink = true);			//�Ƿ���Ҫ�������ӣ�Ĭ�ϱ��� (�̰߳�ȫ)
	virtual bool				SetNetErrCode(int nNetErrCode);				//��������������
	virtual bool				SetRecvSize(size_t uSize);					//���ý��ջ�������С
	virtual bool				SetSendSize(size_t uSize);					//���÷��ͻ�������С
	virtual bool				SetBlockSize(size_t uSize);					//���û���������ʱÿ�η����С(Ĭ��65535)
	virtual bool				SetEncryptTransmission(bool bEncrypt);		//���� ���ܴ��� Ĭ�Ͽ���
	virtual bool				AutoKeepHeart(bool bAuto);					//���� ״̬�������Զ���������(Ĭ�Ͽ���)
public:
	virtual int					GetState()const;
	virtual uint				GetClientID()const;
	virtual const std::string&	GetConnectedAddress()const;
	virtual const VectorString& GetServerAddress()const;					//��ȡ��������ַ(���̰߳�ȫ)
	virtual uint32				GetSecretKey()const;
	virtual uint32				GetAssID()const;
	virtual int					GetNetErrCode()const;						//��ȡ����������
	virtual bool				IsHasSecretKey()const;
	virtual bool				IsConnected()const;
	virtual bool				IsReSend()const;
	virtual bool				IsStoped()const;
	virtual bool				InvaildSecret(int nNetErrCode  = NET_ERRCODE_ACTIVE);//ʹ������Ч
	virtual bool				IsEncryptTransmission()const;				//�Ƿ���ܴ���
	virtual bool				IsAutoKeepHeart()const;						//�Ƿ����Զ���������
	//�������
public:
	virtual bool				StartHeartCheck();			//�����������
	virtual bool				StopHeartCheck();			//ֹͣ�������
	virtual bool				StartKeepHeart(time_t tTime = 0);//��������(���ٴ��ʱ��)
	virtual bool				StopKeepHeart();			//ֹͣ��������
public:
	virtual bool				Connect();
	virtual bool				Push(StreamBinaryPtr ptr,bool bSecret = true);	//ѹ�����
	virtual bool				Push(const IMsgStream& msgStream, bool bSecret = true);	//ѹ�����
	virtual bool				Send(StreamBinaryPtr ptr,bool bSecret = true);	//����
	virtual bool				Send(const IMsgStream& msgStream, bool bSecret = true);	//ѹ�����
	virtual bool				ClearMsg();
	virtual bool				Disconnect(int nNetErrCode = NET_ERRCODE_ACTIVE, bool bClear = true);//�Ͽ�����(����,����δ������Ϣ)
	virtual bool				SetEnabled(bool bEnabled = true);
	virtual bool				MarkReconnectFailed(int nNetErrCode  = NET_ERRCODE_USER_RECONNECT_FAILD);

	virtual bool				MarkReconnect();
	virtual bool				MarkNormal();
public:
	virtual bool OnConnected(const CTransitoryLinker* pLinker)override;
	virtual bool OnConnectFaild(const CTransitoryLinker* pLinker)override;
	virtual bool OnDisconnected(const CTransitoryLinker* pLinker)override;
	virtual bool OnRecved(const CTransitoryLinker* pLinker,IMsgStream& msgStream)override;
	virtual bool OnSend(const CTransitoryLinker* pLinker, StreamBinaryPtr pBuffer,bool bSecret)override;
	virtual bool OnErrCacheFull(const CTransitoryLinker* pLinker, StreamBinaryPtr pBuffer)override;//�����ͻ���������
	virtual bool OnStateChanged(CTransitoryLinker* pLinker,int eState)override;
public:
	virtual bool OnTimeOut( const CTimeNodePtr& pTimeNode )override;
private:
	virtual bool SetState(EState eState);
public:
	CUserConnector(void);
	virtual ~CUserConnector(void);
protected:
	CTransitoryLinker	_xTransitory;//������
	HUserConnector*		_hHandler;
	uint32				_uAssID;
	uint32				_uSecretKey;
	uint32				_uTimeServer;
	EState				_eState;
	bool				_bResend;		//���·���
	int					_nNetErrCode;	//��������
	bool				_bEncryptTransmission; //���ܴ���

	bool				_bAutoKeepHeart;//�Զ���������
	time_t				_tTimeCheck;	//��ѯʱ��
	time_t				_tTimePing;		//��������ʱ��
	CTimeNodePtr		_pTimerHeart;	//���� ��ʱ���
	CTimeOut			_tTimeHeart;	//��ʱʱ��
	CTimeOut			_tTimeKeep;		//��������ʱ��
};

NS_TOOL_FRAME_END
