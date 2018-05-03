#pragma once
#include "Macro.h"
#include "MacroDefineEx.h"
#include "MacroNet.h"
#include "IDataReceiverStream.h"
#include "BufferStream.h"
#include "HTimeOut.h"

//��ע:������һ�����Ӽ�����,�������ӵ����ӶϿ��������������
//��״̬�л���ص��¼� ���ȵ���OnStateChanged �ٵ��� OnConnected OnDisconnected OnConnectFaild

NS_TOOL_FRAME_BEGIN
class TOOLFRAME_DLL CConnectMonitor;
class TOOLFRAME_DLL HConnectMonitor{
public:
	virtual bool OnConnected(CConnectMonitor* pConnectMonitor){return true;}
	virtual bool OnDisconnected(CConnectMonitor* pConnectMonitor){return true;}
	virtual bool OnConnectFaild(CConnectMonitor* pConnectMonitor){return true;}
	virtual uint OnRecved(CConnectMonitor* pConnectMonitor,IDataSession* pSession){ return false; }//�ȵ���������� �ٵ��� OnRecved��IMsgStream�� ���� �� 0ֵ ���ٵ���OnRecved��IMsgStream��
	virtual bool OnRecved(CConnectMonitor* pConnectMonitor,IMsgStream& msgStream){ return false; }

	virtual bool OnStateChanged(CConnectMonitor* pConnectMonitor,int eState){return true;}
public:
	HConnectMonitor(){}
	virtual ~HConnectMonitor(){}
};

class TOOLFRAME_DLL CConnectMonitor
	:public IDataReceiverStream
	,public HTimeOut
{
public:
	enum EState{
		STATE_INVAILD =0,

		STATE_CONNECT,	//������
		STATE_NORMAL,	//������
		STATE_STOPING,	//ֹͣ��
		STATE_STOP,		//��ֹͣ
		STATE_RECONNECT,//������

		STATE_MAX,
	};
public:
	bool	SetRecvSize(size_t uSize);	//���ý��ջ�������С
	bool	SetSendSize(size_t uSize);	//���÷��ͻ�������С
	bool	SetBlockSize(size_t uSize);	//���û���������ʱÿ�η����С(Ĭ��65535)
	bool	SetServerAddress(const std::string& sServerIP);
	bool	SetFlushTime(uint uMillSec);//���÷��ͼ��
	bool	SetFlushTime(uint uMillSecBegin,uint uMillSecEnd);//���÷��ͼ��
public:
	bool	Start();//��ʼ����
	bool	Stop(int nNetErrCode = NET_ERRCODE_ACTIVE);	//ֹͣ����
	bool	ShutDown(bool bCallBack = true);
	EState	GetState()const;
	bool	IsConnected()const;
	bool	IsStoped()const;
	bool	IsShutDown()const;
	bool	Send(StreamBinaryPtr ptr)const;
	bool	Send(const void* pMsg, size_t uLen)const;
	bool	Send(const IDataSerialize& serialize) const;
	bool	Send(const std::string& sMsg)const;
	bool	Push(StreamBinaryPtr ptr);
	uint	GetClientID()const;	//��ȡ���һ�����ӵ�ClientID
	uint	GetRealClientID()const;
	const std::string&	GetRomoteIP()const;					//��ȡԶ��IP
	const std::string&	GetConnectedAddress()const;			//��ȡ������ӳɹ��ĵ�ַ
	const std::string&	GetRomoteIP();						//��ȡԶ��IP
	const std::string&	GetConnectedAddress();				//��ȡ������ӳɹ��ĵ�ַ
	int		GetNetErrCode()const;							//��ȡ������ӵ�����������
	bool	Disconnect(int nNetErrCode = NET_ERRCODE_ACTIVE);//�Ͽ�����(���ܻᱻ����)
private:
	bool	IsCanReconnect()const;						//�Ƿ���Ҫ����
	bool	Reconnect();
	bool	SetState(EState eState);
	bool	RandTimer();
public:
	virtual bool			OnConnected(UINT uClientID)override;
	virtual bool			OnConnectFailed(UINT uClientID)override;
	virtual bool			OnDisconnected(UINT uClientID)override;
	virtual uint			OnRecv(IDataSession* pSession)override;//���ش����˰��ĸ���
	virtual bool			OnRecv( uint uClientID,IMsgStream& msgStream)override;
public:
	virtual bool OnTimeOut(const CTimeNodePtr& pTimeNode);
public:
	CConnectMonitor(void);
	virtual ~CConnectMonitor(void);
private:
	uint		_uRealClientID;		//������������
	EState		_eState;			//����״̬
	size_t		_uRecvSize;			//���ջ������ߴ�
	size_t		_uSendSize;			//���ͻ������ߴ�
	size_t		_uBlockSize;		//������ÿ�η����С
	bool		_bConnected;		//������
	bool		_bShutDown;			//�ر�
	CBufferStream _xFlushBuffer;	//���ͻ�����

	uint		_uFlushBegin;		//����ʱ�������
	uint		_uFlushEnd;			//����ʱ�����յ�
	CTimeNodePtr _pTimerFlush;		//����ʱ����

	uint		 _uClientID;		//������������(���һ��)
	std::string  _sConnectedAddress;//���ӳɹ��ĵ�ַ(���һ��)
	std::string  _sRomoteIP;		//Զ��ID(���һ��)
private:
	CFIELD_UINT(ID);				//ID��
	CFIELD_INT(UserInt);			//�û�int����
	CFIELD_PTR(void*,UserPtr,p);	//�û�ָ������
	CFIELD_VECTOR_STRING(ServerAddress);//��������ַ
	CFIELD_INT(ReconnectCount);		//��������
	CFIELD_INT(ReconnectMax);		//�����������ֵ(��Ϊ-1����ͣ���� Ĭ��-1)
	CFIELD_PTR(HConnectMonitor*,Handler,p);
};

NS_TOOL_FRAME_END
