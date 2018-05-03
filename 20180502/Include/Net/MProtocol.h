#pragma once
#include "Macro.h"

#include "MacroNet.h"
#include "IDMaker.h"
#include "IDataSession.h"
#include "IThreadTask.h"
#include "CalCounter.h"
#include "AvgCounter.h"
#include "ThreadSaftyMax.h"
#include "TThreadSaftyMap.h"
#include "TThreadSaftyList.h"

//����:
//����ӵ����������,�߼��̴߳������,�����̴߳������
//��������:
//�߼��߳� ���������������� ѹ�������̴߳������ �߼��̷߳���
//�����߳� ѭ�����������̴߳������  ִ����������
//�������߳� ���ӷ���֮��,ѹ�봦�������ѹ���߼��̴߳�����С�
//�߼��߳���������е�ʱ�� ȡ������ ��ִ�лص���
//�������̡�������������
NS_TOOL_FRAME_BEGIN
class TOOLFRAME_DLL MProtocol
	:public IThreadTask
{
	ST_INTANCE(MProtocol);
	//���º�������˵���
public:
	bool CreateServer(IDataReceiver* pReceiver,uint uPort,ELinkType eLinkType, size_t uRecvSize= 0xFFFF, size_t uSendSize= 0xFFFF, size_t uBlockSize = 0xFFFF);						//����һ����ַ �������һ����Ҫ��������ClientID (uBlockSize ����Ϊ��)
	bool CreateServer(IDataReceiver* pReceiver,const std::string& sAddress,ELinkType eLinkType, size_t uRecvSize= 0xFFFF, size_t uSendSize= 0xFFFF, size_t uBlockSize = 0xFFFF);	//����һ����ַ �������һ����Ҫ��������ClientID	(uBlockSize ����Ϊ��)
	bool CreateServer(IDataReceiver* pReceiver,const VectorString& vAddress,ELinkType eLinkType, size_t uRecvSize= 0xFFFF, size_t uSendSize= 0xFFFF, size_t uBlockSize = 0xFFFF);	//����һϵ�е�ַ �����Ƿ񶼳ɹ�					(uBlockSize ����Ϊ��)
	bool CloseServer(const std::string& sAddress,ELinkType eLinkType);							//�ر�һ����ַ
	bool CloseServer(int nPort,ELinkType eLinkType);
	bool IsCreatedServer(uint uPort,ELinkType eLinkType)const;
	bool IsCreatedServer(const std::string& sAddress,ELinkType eLinkType)const;

	bool SetConnectMax(uint uPort,						ELinkType eLinkType,uint uConnectMax);	//�������������
	bool SetConnectMax(const std::string& sAddress,		ELinkType eLinkType,uint uConnectMax);	//�������������
	uint GetConnectMax(const std::string& sAddress,		ELinkType eLinkType)const;				//��ȡ���������
	bool RemoveConnectMax(uint uPort,					ELinkType eLinkType);
	bool RemoveConnectMax(const std::string& sAddress,	ELinkType eLinkType);					//�Ƴ��������������
	uint GetConnected(const std::string& sAddress,		ELinkType eLinkType)const;				//��ȡ��ǰ�����ӵ�����

	//���º����ͻ��˵���
public:
	UINT Connect(IDataReceiver* pReceiver,const std::string& sAddress,ELinkType eLinkType, size_t uRecvSize= 0xFFFF, size_t uSendSize= 0xFFFF, size_t uBlockSize = 0xFFFF);		//����һ����ַ ����ClientID((uBlockSize ����Ϊ��))
	UINT Connect(IDataReceiver* pReceiver,const VectorString& vAddress,ELinkType eLinkType, size_t uRecvSize= 0xFFFF, size_t uSendSize= 0xFFFF, size_t uBlockSize = 0xFFFF);	//����һ����ַ ����ClientID((uBlockSize ����Ϊ��))

	//���к���
public:
	bool Disconnect(UINT uClientID,bool bCallBack = true,int nErrCode = NET_ERRCODE_ACTIVE);		//�ر�����
	bool Send(UINT uClientID,				const void* pMsg,size_t uLen);
	bool Send(const VectorUint& vClientID,	const void* pMsg,size_t uLen);
	bool Send(UINT uClientID,				const std::string& sMsg);
	bool Send(const VectorUint& vClientID,	const std::string& sMsg);
	bool Send(UINT uClientID,				StreamBinaryPtr ptr);
	bool Send(const VectorUint& vClientID,	StreamBinaryPtr ptr);
	bool Send(UINT uClientID,				const IDataSerialize& xSerialize);
	bool Send(const VectorUint& vClientID,	const IDataSerialize& xSerialize);
	bool BroadCast(const std::string& sPort, ELinkType eLinkType, StreamBinaryPtr ptr);
	bool BroadCast(const std::string& sPort,ELinkType eLinkType,const void* pMsg,size_t uLen);
	bool BroadCast(const std::string& sPort, ELinkType eLinkType, StreamBufferPtr ptr);
	std::string			GetRemoteAddress(uint uClientID)const;//����TCP���ӷ�ʽ����Ч
	const std::string&	GetConnectedAddress(uint uClientID)const;//��ȡ���ӳɹ���IP
	StreamBinaryPtr GetSendData(uint uClientID) const;//��ȡδ��������
	bool			RecvDataSplice(UINT uClientID, StreamBinaryPtr ptr,bool bBack=true);//ƴ�ӵ����ջ�������Ĭ�Ϸŵ�����(���޸Ĵ�����)
	int				GetErrCode(uint uClientID)const;
	bool			MarkDelayRecv(uint uClientID);

	//���º����ⲿ����
public:
	bool	StartUp();
	bool	ShutDown();//���عر��Ƿ�ɹ�
	bool	AddNetTaskThread(uint uCount = 1,uint uTimeInterval = 10);//��ӵ������߳� ��������
	bool	ProcessLogic(uint64 nMillSecond = 0 );	//�����߼�������
	bool	ProcessNet(uint64 nMillSecond = 0 );	//�������������
	bool	ProcessBalance( uint64 uProcessTime = 0,uint64 uNetResloved = 50 );//���⴦��(������ʹ�� ����� �� �߼��� ����ƽ��) uNetResloved Ϊ����㱣������ʱ�� �ܴ���ʱ��ΪuProcessTime + uNetResloved ��uNetReslovedΪ0,����Ϊ��uProcessTimeһ��
	int		GetLinkType(uint uClientID)const;
	size_t	GetSessionNum()const;	//��ûỰ���ܸ���
	size_t	GetLogicQueueSize()const;	//��ȡ�߼���Ϣ�ܸ���
	size_t	GetNetQueueSize()const;	//��ȡ�߼���Ϣ�ܸ���
	size_t	ClearNetCounter();		//������紦����ͳ��
	size_t	ClearLogicCounter();	//������紦����ͳ��
	size_t	ClearPackCounter();		//������紦����ͳ��
	size_t	ClearSendCounter();		//������紦����ͳ��
	size_t	ClearRecvCounter();		//������紦����ͳ��
	size_t	GetNetCounter()const;	//��ȡ���紦����ͳ��
	size_t	GetLogicCounter()const;	//��ȡ���紦����ͳ��
	size_t	GetPackCounter()const;	//��ȡЭ���������ͳ��
	size_t	GetSendCount()const;	//��ȡ�����ֽ���ͳ��
	size_t	GetRecvCount()const;	//��ȡ�����ֽ���ͳ��
	int64	ClearFreeTime(uint uClientID);//���ĳ�Ự����ʱ��
	uint	GetTimeSendAvg(uint64* uMax,uint64* uAvg );		//��ȡ����ʱ������
	uint	GetTimeSendingAvg(uint64* uMax,uint64* uAvg );	//��ȡ������ʱ������

	//���º����ڲ�Session/Accecptor����
public:
	DataSessionPtr	CreateSession(ELinkType eLinkType);		//�������½�һ���Ự
	bool			DestroySession(DataSessionPtr ptr);	//�ͷŻỰ
	bool			AddSession(DataSessionPtr ptr);		//��ӻỰ(�����ID)
	bool			RemoveSession(UINT uClientID);		//�Ƴ��Ự(���ͷ�ID)
	DataSessionPtr	GetSession(UINT uClientID)const;

	DataAcceptorPtr	CreateAcceptor(ELinkType eLinkType);		//�������½�һ���Ự
	DataAcceptorPtr	GetDataAcceptor(const std::string& sAddress,int eLinkType);

	bool			TimeElapsedSend(uint64 uTime);
	bool			TimeElapsedSending(uint64 uTime);

	bool			TryAddConnect(const XAcceptorKey& key);
	bool			TryRemoveConnect(const XAcceptorKey& key);
public:
	bool			ReqClosing(DataSessionPtr ptr,int nErrCode,bool bCallBack = true,bool bCallBackRecv = true);
	
	bool			OnConnected(DataSessionPtr ptr);	//���ӳɹ�
	bool			OnRecved(DataSessionPtr ptr);	

	//���º����������
public:
	virtual	bool		InitThread();
	virtual bool		RunOnceThread();
public:
	virtual	bool		PushQueueNet(DataSessionPtr ptr);
	virtual	bool		PushQueueLogic(DataSessionPtr ptr);
public:
	MProtocol(void);
	virtual ~MProtocol(void);
private:
	typedef DataSessionPtr	(*FunDataSessionCreator)();
	typedef DataAcceptorPtr (*FunDataAcceptorCreator)();
	typedef bool			(*FunDataSessionInit)();
	typedef bool			(*FunDataSessionRunOnce)();
	typedef bool			(*FunBroadCast)( const std::string& sPort,StreamBufferPtr ptr );

	typedef std::map<ELinkType,FunDataSessionCreator>	MapFunSessionCreator;
	typedef std::map<ELinkType,FunDataAcceptorCreator>	MapFunAcceptorCreator;
	typedef std::map<ELinkType,FunDataSessionInit>		MapFunSessionInit;
	typedef std::map<ELinkType,FunDataSessionRunOnce>	MapFunSessionRunOnce;
	typedef std::map<ELinkType,FunBroadCast>			MapFunBroadCast;

	struct XAcceptorConnect
	{
		XAcceptorKey	key;
		int				nCountMax;	//���������
		int				nCount;		//��ǰ������
	};

	typedef TThreadSaftyListValue<DataSessionPtr>					QueueSession;
	typedef TThreadSaftyMapValue<UINT,DataSessionPtr>				MapDataSessionPtr;
	typedef TThreadSaftyMapValue<XAcceptorKey,DataAcceptorPtr>		MapDataAcceptorPtr;
	typedef TThreadSaftyMapValue<XAcceptorKey, XAcceptorConnect>	MapAcceptorConnect;
public:
	bool InsertFunSessionCreator	(ELinkType eLinkType,FunDataSessionCreator fn);
	bool InsertFunAcceptorCreator	(ELinkType eLinkType,FunDataAcceptorCreator fn);
	bool InsertFunSessionInit		(ELinkType eLinkType,FunDataSessionInit fn);
	bool InsertFunSessionRunOnce	(ELinkType eLinkType,FunDataSessionRunOnce fn);
	bool InsertFunBroadCast			(ELinkType eLinkType,FunBroadCast fn);
private:
	UINT PushConnect(IDataReceiver* pReceiver, const VectorString& vAddress, ELinkType eLinkType, size_t uRecvSize, size_t uSendSize, size_t uBlockSize);
private:
	CFIELD_UINT(RecvSize);		//Ĭ�Ͻ��ջ���ش�С 
	CFIELD_UINT(SendSize);		//Ĭ�Ϸ��ͻ���ش�С
	CFIELD_UINT(BlockSize);		//ÿ��Ĵ�С(���ڷ��� ���� ��Ԫ�ش�С)
private:
	QueueSession		_vQueueNet;		//�������
	QueueSession		_vQueueLogic;	//�߼��������
	CIDMakerUint		_imClientID;	//ClientID������
	MapDataSessionPtr	_vSession;		//��Ч�Ự
	MapDataAcceptorPtr	_vAcceptor;		//��Ч������
	MapAcceptorConnect	_vConnect;		//���������ֵ
	bool				_bStartUp;		//�����ı�־(�������ϲ���������)

	//������ͳ��
	CCalCounter			_xPackCounter;	//�������
	CCalCounter			_xNetCounter;	//���������
	CCalCounter			_xLogicCounter;	//�߼�������
	CCalCounter			_xSendCount;	//������
	CCalCounter			_xRecvCount;	//������
	CAvgCounter			_xSendAvg;		//ƽ������ʱ��
	CAvgCounter			_xSendingAvg;	//ƽ��������ʱ��

	//��ʼ������
	MapFunSessionCreator		_vFunSessionCreator;
	MapFunAcceptorCreator		_vFunAcceptorCreator;
	MapFunSessionInit			_vFunSessionInit;
	MapFunSessionRunOnce		_vFunSessionRunOnce;
	MapFunBroadCast				_vFunBroadCast;
};
NS_TOOL_FRAME_END