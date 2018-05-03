#pragma once
#include "Macro.h"
#include "IPool.h"
#include "MacroNet.h"
#include "MCreator.h"
#include "MMultiMap.h"
#include "TimeElapseEx.h"
#include "BufferStream.h"
#include "TBitTest.h"

NS_TOOL_FRAME_BEGIN

class IDataSession;

//////////////////////////////////////////////////////////////////////////
//Э������������ӿ�
class TOOLFRAME_DLL IDataReceiver
{
public:
	virtual bool OnConnected(uint uClientID) = 0;
	virtual bool OnConnectFailed(uint uClientID) = 0;
	virtual bool OnDisconnected(uint uClientID) = 0;
	virtual uint OnRecv(IDataSession* pSession) = 0;//���ش����˰��ĸ���
public:
	IDataReceiver();
	virtual ~IDataReceiver();
};

//////////////////////////////////////////////////////////////////////////
//Э���������л����
class TOOLFRAME_DLL IDataSerialize
{
public:
	virtual bool OnSerialize(IStreamPtr ptr)const;
public:
	IDataSerialize();
	virtual ~IDataSerialize();
};

//���ݻỰ
//˼·����:
//�ϲ㷢��ʱ һ�� ��д�� �����ͻ���� Ȼ�� �����͡�
//�ײ���յ����� ʱ һ���� ���յ� ��������ճء�
//���� ���ڷ����е� �Լ� ���ڴ����е� �ĳ� һ�� ���� �ⲿ���ܷ��ʡ�
//����� Ϊ���� �ڴ�� �� ���淢��ָ�룬�ϲ�֮���� Ч�ʸ���
//////////////////////////////////////////////////////////////////////////
struct XAcceptorKey
{
	std::string sAddress;
	int			nLinkType;

	bool operator <(const XAcceptorKey& other)const
	{
		if (nLinkType == other.nLinkType)
			return sAddress.compare(other.sAddress) < 0;

		return nLinkType < other.nLinkType;
	}
};

//////////////////////////////////////////////////////////////////////////
class IDataNet
	:public IPool
{
public:
	virtual bool		SetAddress(const VectorString& vAddress);//��Ҫ���Եĵ�ַ�б�
	virtual bool		SetAddress(const std::string& sAddress);//��ǰ�ĳ��Ե�ַ
	virtual bool		SetAccepterKey(const XAcceptorKey& key);
	virtual bool		InitBuffSize(size_t uRecvSize, size_t uSendSize,size_t uBlockSize);

	virtual size_t		SendData(const void* pBuffer, size_t uLen);	//ѹ�뻺���
	virtual size_t		SendData(const StreamBinaryPtr pBuffer);	//ѹ�뻺���
	virtual size_t		SendData(const IDataSerialize& xSerialize);	//ѹ�뻺���
	virtual bool		RecvDataSplice(StreamBinaryPtr pBuffer, bool bBack = true);//����ջ�����д����
	virtual bool		RecvDataSplice(StreamBufferPtr& pBuffer, bool bBack = true);
	virtual bool		SwapSendBuffer();		//�������ͻ����� ��Ϊ �����л�����
	virtual bool		SwapRecvBuffer();		//�������л����� ��Ϊ ������ɻ�����
	virtual bool		IsRecvingEmpty()const;	//���ջ������Ƿ�Ϊ��
	virtual bool		ClearSendingBuffer();	//�������л������ÿ�
	virtual StreamBinaryPtr	GetRecvedBuffer()const;//����ѽ��ջ�����
	virtual bool		ClearRecvedBuffer();
	virtual StreamBinaryPtr GetSendData()const;//��ȡ�����е�����(�������һ��boost���Ʒ��ͳɹ�������)
	virtual const XAcceptorKey& GetAccepterKey()const;

	virtual size_t		GetSendBufferSize()const;
	virtual size_t		GetRecvBufferSize()const;
	virtual size_t		GetBlockSize()const;
public:
	virtual	const std::string& GetConnectedAddress()const;
public:
	IDataNet();
	virtual ~IDataNet();
protected:
	XAcceptorKey	_xAcceptorKey;	//����������

	std::string		_sAddress;		//��ǰ���Եĵ�ַ
	VectorString	_vAddress;		//�����Եĵ�ַ

	size_t			_uRecvSize;		//���ջ�������С(0Ϊ����)
	size_t			_uSendSize;		//���ͻ�������С(0Ϊ����)
	size_t			_uBlockSize;	//��������Ԫ��С(���޵Ľ���/���ͻ����� ÿ�η���Ĵ�С)

	mutable	CMutexRecursive _mutexSend;	

	StreamBinaryPtr	_pSendWait;//�����ͻ�����
	StreamBufferPtr _pSending;	//�����л�����

	CTimeElapse _xElapseSend;
	CTimeElapse _xElapseSending;

	mutable	CMutexRecursive _mutexRecv;

	StreamBinaryPtr _pRecving;	//�����ջ�����(������������ д�� ������)
	StreamBinaryPtr _pRecved;	//���մ����л�����	
};

//////////////////////////////////////////////////////////////////////////
class IDataSession
	:public IDataNet
{
public:
	enum EMarkNet{
		REQ_NET_QUEUE,

		REQ_CONNECT,
		REQ_RECV,
		REQ_SEND,
		REQ_CLOSE,
	};
	enum EMarkLogic{
		REQ_LOGIC_QUEUE,

		REQ_CONNECTED,
		REQ_RECVED,
		REQ_CLOSED,
	};
public:
	virtual	bool		Connect()=0;
	virtual size_t		Send()=0;//���ط����ֽ���
	virtual bool		Recv()=0;
	virtual bool		Close();

	virtual std::string GetRemoteAddress()const;
	virtual int64		ClearFreeTime();
public:
	virtual bool		TryClosing();
	virtual bool		IsClosing()const;

	virtual bool		TryMarkNet(int eMarkNet);//���ϱ�� ���� �Ƿ���Ҫѹ����������
	virtual bool		TryClearNet(int eMarkNet);

	virtual bool		TryMarkLogic(int eMarkLogic);
	virtual bool		TryClearLogic(int eMarkLogic);

	virtual bool		IsNetMarked(int eMarkNet)const;
	virtual bool		IsLogicMarked(int eMarkLogic)const;

	virtual bool		IsNetMarked()const;
	virtual bool		IsLogicMarked()const;

	virtual CMutexRecursive &	GetMutex()const;//ʹ�ñ�Sessionʱ ��Ҫ����
public:
	IDataSession(void);
	virtual ~IDataSession(void);
private:
	CFIELD_UINT(ClientID);
	CFIELD_ENUM(ELinkType,LinkType);
	CFIELD_INT(ErrCode);
	CFIELD_BOOL(Closed);
	CFIELD_BOOL(Connected);//��������(���߼����Ƿ���ù�OnConnected��OnDisconnected Ϊ׼)
	CFIELD_BOOL(CallBackRecv);//�´�����Ϣ���� �Ƿ����

	CFIELD_PTR(IDataReceiver*,Receiver,p);	//(�̰߳�ȫ�� _mutxUsing ά��)
protected:
	CTimeElapseEx			_xTimeFree;//����ʱ���ۼ�(������� �� ������� ʱ��֮��)
	mutable CMutexRecursive	_mutex;

	TBitTest<int> _xBitNet;
	TBitTest<int> _xBitLogic;

	bool		_bClosing;
};

typedef CSharePtr<IDataSession>		DataSessionPtr;

//���ݽ�����
//////////////////////////////////////////////////////////////////////////
class IDataAcceptor
	:public IDataNet
{
public:
	virtual bool WaitAccept(const std::string& sAddress)=0;
	virtual bool ReqClose();
	virtual	bool Close()=0;
public:
	bool	IsClosed();
public:
	IDataAcceptor(void);
	virtual ~IDataAcceptor(void);
private:
	CFIELD_ENUM(ELinkType,LinkType);
	CFIELD_PTR(IDataReceiver*,Receiver,p);
	CFIELD_STRING(Address);				//������ַ
private:
	CMutexReadWrite	_mutexClosed;
	bool			_bClosed;
};

typedef CSharePtr<IDataAcceptor>		DataAcceptorPtr;

//ϵͳ����
//////////////////////////////////////////////////////////////////////////
typedef bool (*FunDataSessionInit)();
typedef bool (*FunDataSessionRunOnce)();
typedef bool (*FunBroadCast)( const std::string& sPort,StreamBufferPtr ptr );

#define FUN_CREATE_DATA_SESSION(className,returnValue)		FUN_CREATE_REAL(className,DataSessionPtr,returnValue)
#define FUN_CREATE_DATA_ACCEPTOR(className,returnValue)		FUN_CREATE_REAL(className,DataAcceptorPtr,returnValue)

NS_TOOL_FRAME_END
