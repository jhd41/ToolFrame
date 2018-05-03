#pragma once

#include "Macro.h"
#include "MacroDefineEx.h"
#include "ConnectMonitor.h"
#include "TThreadSaftyList.h"
#include "CalCounter.h"
#include "BufferStream.h"

//������:��Ҫ��ʱ������� Ĭ�Ϸ���Э��� ����������
//SetReconnectMax	Ĭ�����޷�������
//SetCacheMax		Ĭ��ֵΪ����

NS_TOOL_FRAME_BEGIN
class TOOLFRAME_DLL CTransitoryLinker;
class TOOLFRAME_DLL HTransitoryLinker
{
public:
	virtual bool OnConnected(const CTransitoryLinker* pLinker){return false;}
	virtual bool OnConnectFaild(const CTransitoryLinker* pLinker){return false;}
	virtual bool OnDisconnected(const CTransitoryLinker* pLinker){return false;}
	virtual bool OnRecved(const CTransitoryLinker* pLinker,IMsgStream& msgStream){return false;}
	virtual bool OnSend(const CTransitoryLinker* pLinker, StreamBinaryPtr pBuffer,bool bSecret){return false;}
	virtual bool OnErrCacheFull(const CTransitoryLinker* pLinker, StreamBinaryPtr pBuffer){return false;}//�����ͻ���������
	virtual bool OnStateChanged(CTransitoryLinker* pLinker,int eState){return false;}
public:
	HTransitoryLinker(){}
	virtual ~HTransitoryLinker(){}
};

class TOOLFRAME_DLL CTransitoryLinker
	:public HConnectMonitor
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
	typedef TThreadSaftyListValue<StreamBinaryPtr>			QueueStreamBuffer;
public:
	virtual bool SetServerAddress(const std::string& sIP);		//����IP��ַ(���̰߳�ȫ)
	virtual bool SetServerAddress(const VectorString& vIP);
	virtual bool SetHandler(HTransitoryLinker* hHandler);	//���ô����� ���Բ�����(���̰߳�ȫ)
	virtual bool SetEnabled(bool bEnabled = true);			//����Ƿ��ʼ�����(Ĭ�� ���)
	virtual bool SetReconnectMax(int nCount);				//������������
	virtual bool SetCacheMax(uint uCount);					//���÷��ͻ�������С
	virtual bool SetResend(bool bResend);					//���ó������·���֮ǰ����ʧ�ܵ�Э��
	virtual bool SetRecvSize(size_t uSize);					//���ý��ջ�������С
	virtual bool SetSendSize(size_t uSize);					//���÷��ͻ�������С
	virtual bool SetBlockSize(size_t uSize);					//���û���������ʱÿ�η����С(Ĭ��65535)
	virtual bool PushMsg(StreamBinaryPtr ptr,bool bSecret = true);//ѹ����Ϣ(�̰߳�ȫ)
	virtual bool SendMsg(StreamBinaryPtr ptr,bool bSecret = true);//ֱ�ӷ���
	virtual bool ClearMsg();								//���û�з��͵�����(�̰߳�ȫ)
	virtual bool SetKeepLink(bool bKeepLink = true);		//�Ƿ���Ҫ�������ӣ�Ĭ�ϲ����� (�̰߳�ȫ)
	virtual bool Connect();									//�������� ���Բ�����(�̰߳�ȫ)	
	virtual bool Stop(int nNetErrCode = NET_ERRCODE_ACTIVE);//ֹͣ����(�̰߳�ȫ)	
	virtual bool IsStoped()const;							//�Ƿ���ֹͣ(�̰߳�ȫ)
	virtual bool ShutDown(bool bCallBack = true);			//ֹͣ����
	virtual bool Disconnect(int nNetErrCode = NET_ERRCODE_ACTIVE);//�Ͽ�����(���ܻ��������)
	virtual bool ClearSendFaildBuffer();					//�������ʧ�ܵĻ���
	virtual int	 GetNetErrCode()const;						//��ȡ����������
public:
	virtual bool IsEnabled()const;							//�Ƿ����(�̰߳�ȫ)
	virtual bool IsKeepLink()const;							//�Ƿ񱣳����� (�̰߳�ȫ)
	virtual bool IsConnected()const;						//�Ƿ�������(�̰߳�ȫ)
	virtual size_t GetCacheCount()const;						//��ȡ��Ϣ������(�̰߳�ȫ)
	virtual const VectorString& GetServerAddress()const;	//��ȡ��������ַ(���̰߳�ȫ)
	virtual const std::string&	GetConnectedAddress()const;	//��ȡ���ӵ��ķ�������ַ(�̰߳�ȫ)
	virtual uint GetClientID()const;						//��ȡClientID(���̰߳�ȫ)
	virtual size_t GetCacheMax()const;						//��ȡ��������С
	virtual size_t GetCacheSize()const;						//��ȡ��������ǰ��ʹ�ô�С
private:
	virtual bool CheckSendMsg();//�����
	virtual bool TrySend();
	virtual bool TryClose();
private:
	virtual bool OnConnected(CConnectMonitor* pConnectMonitor)override;
	virtual bool OnConnectFaild(CConnectMonitor* pConnectMonitor)override;
	virtual bool OnDisconnected(CConnectMonitor* pConnectMonitor)override;
	virtual bool OnRecved(CConnectMonitor* pConnectMonitor,ToolFrame::IMsgStream& msgStream)override;
	virtual bool OnStateChanged(CConnectMonitor* pConnectMonitor,int eState)override;
public:
	CTransitoryLinker(void);
	virtual ~CTransitoryLinker(void);
private:
	CBufferStream		_vCache;		//�������Ϣ
	CConnectMonitor		_xMonitor;
	bool				_bKeepLink;
	HTransitoryLinker*	_hHandler;
	bool				_bEnable;
	bool				_bResend;		//���³��Է���
	StreamBinaryPtr		_pSendBuffer;	//����ʧ�ܵ�Э��

	mutable CMutexRecursive	_mutex;		//��д��
};

NS_TOOL_FRAME_END