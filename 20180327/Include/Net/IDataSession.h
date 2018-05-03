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
//协议数据链处理接口
class TOOLFRAME_DLL IDataReceiver
{
public:
	virtual bool OnConnected(uint uClientID) = 0;
	virtual bool OnConnectFailed(uint uClientID) = 0;
	virtual bool OnDisconnected(uint uClientID) = 0;
	virtual uint OnRecv(IDataSession* pSession) = 0;//返回处理了包的个数
public:
	IDataReceiver();
	virtual ~IDataReceiver();
};

//////////////////////////////////////////////////////////////////////////
//协议数据序列化借口
class TOOLFRAME_DLL IDataSerialize
{
public:
	virtual bool OnSerialize(IStreamPtr ptr)const;
public:
	IDataSerialize();
	virtual ~IDataSerialize();
};

//数据会话
//思路调整:
//上层发送时 一律 先写入 待发送缓冲池 然后 请求发送。
//底层接收到数据 时 一律先 接收到 待处理接收池。
//对于 正在发送中的 以及 正在处理中的 的池 一律 上锁 外部不能访问。
//缓冲池 为真正 内存池 不 保存发送指针，合并之后发送 效率更高
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
	virtual bool		SetAddress(const VectorString& vAddress);//需要尝试的地址列表
	virtual bool		SetAddress(const std::string& sAddress);//当前的尝试地址
	virtual bool		SetAccepterKey(const XAcceptorKey& key);
	virtual bool		InitBuffSize(size_t uRecvSize, size_t uSendSize,size_t uBlockSize);

	virtual size_t		SendData(const void* pBuffer, size_t uLen);	//压入缓冲池
	virtual size_t		SendData(const StreamBinaryPtr pBuffer);	//压入缓冲池
	virtual size_t		SendData(const IDataSerialize& xSerialize);	//压入缓冲池
	virtual bool		RecvDataSplice(StreamBinaryPtr pBuffer, bool bBack = true);//向接收缓冲区写数据
	virtual bool		RecvDataSplice(StreamBufferPtr& pBuffer, bool bBack = true);
	virtual bool		SwapSendBuffer();		//将待发送缓冲区 置为 发送中缓冲区
	virtual bool		SwapRecvBuffer();		//将接收中缓冲区 置为 接收完成缓冲区
	virtual bool		IsRecvingEmpty()const;	//接收缓冲区是否为空
	virtual bool		ClearSendingBuffer();	//将发送中缓冲区置空
	virtual StreamBinaryPtr	GetRecvedBuffer()const;//获得已接收缓冲区
	virtual bool		ClearRecvedBuffer();
	virtual StreamBinaryPtr GetSendData()const;//获取发送中的数据(包括最后一次boost声称发送成功的数据)
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
	XAcceptorKey	_xAcceptorKey;	//接受器类型

	std::string		_sAddress;		//当前尝试的地址
	VectorString	_vAddress;		//待尝试的地址

	size_t			_uRecvSize;		//接收缓冲区大小(0为无限)
	size_t			_uSendSize;		//发送缓冲区大小(0为无限)
	size_t			_uBlockSize;	//缓冲区单元大小(无限的接收/发送缓冲区 每次分配的大小)

	mutable	CMutexRecursive _mutexSend;	

	StreamBinaryPtr	_pSendWait;//待发送缓冲区
	StreamBufferPtr _pSending;	//发送中缓冲区

	CTimeElapse _xElapseSend;
	CTimeElapse _xElapseSending;

	mutable	CMutexRecursive _mutexRecv;

	StreamBinaryPtr _pRecving;	//待接收缓冲区(接收来的数据 写入 该区域)
	StreamBinaryPtr _pRecved;	//接收处理中缓冲区	
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
	virtual size_t		Send()=0;//返回发送字节数
	virtual bool		Recv()=0;
	virtual bool		Close();

	virtual std::string GetRemoteAddress()const;
	virtual int64		ClearFreeTime();
public:
	virtual bool		TryClosing();
	virtual bool		IsClosing()const;

	virtual bool		TryMarkNet(int eMarkNet);//打上标记 返回 是否需要压入待处理队列
	virtual bool		TryClearNet(int eMarkNet);

	virtual bool		TryMarkLogic(int eMarkLogic);
	virtual bool		TryClearLogic(int eMarkLogic);

	virtual bool		IsNetMarked(int eMarkNet)const;
	virtual bool		IsLogicMarked(int eMarkLogic)const;

	virtual bool		IsNetMarked()const;
	virtual bool		IsLogicMarked()const;

	virtual CMutexRecursive &	GetMutex()const;//使用本Session时 需要上锁
public:
	IDataSession(void);
	virtual ~IDataSession(void);
private:
	CFIELD_UINT(ClientID);
	CFIELD_ENUM(ELinkType,LinkType);
	CFIELD_INT(ErrCode);
	CFIELD_BOOL(Closed);
	CFIELD_BOOL(Connected);//已连接上(以逻辑层是否调用过OnConnected和OnDisconnected 为准)
	CFIELD_BOOL(CallBackRecv);//下次有消息包到 是否接收

	CFIELD_PTR(IDataReceiver*,Receiver,p);	//(线程安全靠 _mutxUsing 维护)
protected:
	CTimeElapseEx			_xTimeFree;//空闲时间累计(请求接收 到 接收完成 时间之和)
	mutable CMutexRecursive	_mutex;

	TBitTest<int> _xBitNet;
	TBitTest<int> _xBitLogic;

	bool		_bClosing;
};

typedef CSharePtr<IDataSession>		DataSessionPtr;

//数据接受器
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
	CFIELD_STRING(Address);				//监听地址
private:
	CMutexReadWrite	_mutexClosed;
	bool			_bClosed;
};

typedef CSharePtr<IDataAcceptor>		DataAcceptorPtr;

//系统函数
//////////////////////////////////////////////////////////////////////////
typedef bool (*FunDataSessionInit)();
typedef bool (*FunDataSessionRunOnce)();
typedef bool (*FunBroadCast)( const std::string& sPort,StreamBufferPtr ptr );

#define FUN_CREATE_DATA_SESSION(className,returnValue)		FUN_CREATE_REAL(className,DataSessionPtr,returnValue)
#define FUN_CREATE_DATA_ACCEPTOR(className,returnValue)		FUN_CREATE_REAL(className,DataAcceptorPtr,returnValue)

NS_TOOL_FRAME_END
