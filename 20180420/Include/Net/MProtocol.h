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

//流程:
//本类拥有两条队列,逻辑线程处理队列,网络线程处理队列
//连接流程:
//逻辑线程 产生连接请求命令 压入网络线程处理队列 逻辑线程返回
//网络线程 循环处理网络线程处理队列  执行连接请求。
//待网络线程 连接返回之后,压入处理结果命令，压入逻辑线程处理队列。
//逻辑线程来处理队列的时候 取出命令 ，执行回调。
//发送流程、接收流程类似
NS_TOOL_FRAME_BEGIN
class TOOLFRAME_DLL MProtocol
	:public IThreadTask
{
	ST_INTANCE(MProtocol);
	//以下函数服务端调用
public:
	bool CreateServer(IDataReceiver* pReceiver,uint uPort,ELinkType eLinkType, size_t uRecvSize= 0xFFFF, size_t uSendSize= 0xFFFF, size_t uBlockSize = 0xFFFF);						//监听一个地址 返回最近一个将要被创建的ClientID (uBlockSize 不能为空)
	bool CreateServer(IDataReceiver* pReceiver,const std::string& sAddress,ELinkType eLinkType, size_t uRecvSize= 0xFFFF, size_t uSendSize= 0xFFFF, size_t uBlockSize = 0xFFFF);	//监听一个地址 返回最近一个将要被创建的ClientID	(uBlockSize 不能为空)
	bool CreateServer(IDataReceiver* pReceiver,const VectorString& vAddress,ELinkType eLinkType, size_t uRecvSize= 0xFFFF, size_t uSendSize= 0xFFFF, size_t uBlockSize = 0xFFFF);	//监听一系列地址 返回是否都成功					(uBlockSize 不能为空)
	bool CloseServer(const std::string& sAddress,ELinkType eLinkType);							//关闭一个地址
	bool CloseServer(int nPort,ELinkType eLinkType);
	bool IsCreatedServer(uint uPort,ELinkType eLinkType)const;
	bool IsCreatedServer(const std::string& sAddress,ELinkType eLinkType)const;

	bool SetConnectMax(uint uPort,						ELinkType eLinkType,uint uConnectMax);	//设置最大连接数
	bool SetConnectMax(const std::string& sAddress,		ELinkType eLinkType,uint uConnectMax);	//设置最大连接数
	uint GetConnectMax(const std::string& sAddress,		ELinkType eLinkType)const;				//获取最大连接数
	bool RemoveConnectMax(uint uPort,					ELinkType eLinkType);
	bool RemoveConnectMax(const std::string& sAddress,	ELinkType eLinkType);					//移除最大连接数限制
	uint GetConnected(const std::string& sAddress,		ELinkType eLinkType)const;				//获取当前已连接的数量

	//以下函数客户端调用
public:
	UINT Connect(IDataReceiver* pReceiver,const std::string& sAddress,ELinkType eLinkType, size_t uRecvSize= 0xFFFF, size_t uSendSize= 0xFFFF, size_t uBlockSize = 0xFFFF);		//连接一个地址 返回ClientID((uBlockSize 不能为空))
	UINT Connect(IDataReceiver* pReceiver,const VectorString& vAddress,ELinkType eLinkType, size_t uRecvSize= 0xFFFF, size_t uSendSize= 0xFFFF, size_t uBlockSize = 0xFFFF);	//连接一个地址 返回ClientID((uBlockSize 不能为空))

	//共有函数
public:
	bool Disconnect(UINT uClientID,bool bCallBack = true,int nErrCode = NET_ERRCODE_ACTIVE);		//关闭连接
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
	std::string			GetRemoteAddress(uint uClientID)const;//仅在TCP连接方式下有效
	const std::string&	GetConnectedAddress(uint uClientID)const;//获取连接成功的IP
	StreamBinaryPtr GetSendData(uint uClientID) const;//获取未发送数据
	bool			RecvDataSplice(UINT uClientID, StreamBinaryPtr ptr,bool bBack=true);//拼接到接收缓冲区，默认放到后面(会修改传入流)
	int				GetErrCode(uint uClientID)const;
	bool			MarkDelayRecv(uint uClientID);

	//以下函数外部调用
public:
	bool	StartUp();
	bool	ShutDown();//返回关闭是否成功
	bool	AddNetTaskThread(uint uCount = 1,uint uTimeInterval = 10);//添加到任务线程 网络任务
	bool	ProcessLogic(uint64 nMillSecond = 0 );	//处理逻辑层命令
	bool	ProcessNet(uint64 nMillSecond = 0 );	//处理网络层命令
	bool	ProcessBalance( uint64 uProcessTime = 0,uint64 uNetResloved = 50 );//均衡处理(尽可能使得 网络层 和 逻辑层 处理平衡) uNetResloved 为网络层保留处理时间 总处理时间为uProcessTime + uNetResloved 若uNetResloved为0,则视为和uProcessTime一样
	int		GetLinkType(uint uClientID)const;
	size_t	GetSessionNum()const;	//获得会话的总个数
	size_t	GetLogicQueueSize()const;	//获取逻辑消息总个数
	size_t	GetNetQueueSize()const;	//获取逻辑消息总个数
	size_t	ClearNetCounter();		//清除网络处理量统计
	size_t	ClearLogicCounter();	//清除网络处理量统计
	size_t	ClearPackCounter();		//清除网络处理量统计
	size_t	ClearSendCounter();		//清除网络处理量统计
	size_t	ClearRecvCounter();		//清除网络处理量统计
	size_t	GetNetCounter()const;	//获取网络处理量统计
	size_t	GetLogicCounter()const;	//获取网络处理量统计
	size_t	GetPackCounter()const;	//获取协议包处理量统计
	size_t	GetSendCount()const;	//获取发送字节数统计
	size_t	GetRecvCount()const;	//获取接收字节数统计
	int64	ClearFreeTime(uint uClientID);//清除某会话空闲时间
	uint	GetTimeSendAvg(uint64* uMax,uint64* uAvg );		//获取发送时间消耗
	uint	GetTimeSendingAvg(uint64* uMax,uint64* uAvg );	//获取发送中时间消耗

	//以下函数内部Session/Accecptor调用
public:
	DataSessionPtr	CreateSession(ELinkType eLinkType);		//仅仅是新建一个会话
	bool			DestroySession(DataSessionPtr ptr);	//释放会话
	bool			AddSession(DataSessionPtr ptr);		//添加会话(会分配ID)
	bool			RemoveSession(UINT uClientID);		//移除会话(会释放ID)
	DataSessionPtr	GetSession(UINT uClientID)const;

	DataAcceptorPtr	CreateAcceptor(ELinkType eLinkType);		//仅仅是新建一个会话
	DataAcceptorPtr	GetDataAcceptor(const std::string& sAddress,int eLinkType);

	bool			TimeElapsedSend(uint64 uTime);
	bool			TimeElapsedSending(uint64 uTime);

	bool			TryAddConnect(const XAcceptorKey& key);
	bool			TryRemoveConnect(const XAcceptorKey& key);
public:
	bool			ReqClosing(DataSessionPtr ptr,int nErrCode,bool bCallBack = true,bool bCallBackRecv = true);
	
	bool			OnConnected(DataSessionPtr ptr);	//连接成功
	bool			OnRecved(DataSessionPtr ptr);	

	//以下函数自身调用
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
		int				nCountMax;	//最大连接数
		int				nCount;		//当前连接数
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
	CFIELD_UINT(RecvSize);		//默认接收缓冲池大小 
	CFIELD_UINT(SendSize);		//默认发送缓冲池大小
	CFIELD_UINT(BlockSize);		//每块的大小(用于发送 接收 单元池大小)
private:
	QueueSession		_vQueueNet;		//网络队列
	QueueSession		_vQueueLogic;	//逻辑处理队列
	CIDMakerUint		_imClientID;	//ClientID分配器
	MapDataSessionPtr	_vSession;		//有效会话
	MapDataAcceptorPtr	_vAcceptor;		//有效接受器
	MapAcceptorConnect	_vConnect;		//连接最大数值
	bool				_bStartUp;		//启动的标志(用于若上层忘记启动)

	//处理量统计
	CCalCounter			_xPackCounter;	//处理包数
	CCalCounter			_xNetCounter;	//网络队列量
	CCalCounter			_xLogicCounter;	//逻辑队列量
	CCalCounter			_xSendCount;	//发送量
	CCalCounter			_xRecvCount;	//接收量
	CAvgCounter			_xSendAvg;		//平均发送时间
	CAvgCounter			_xSendingAvg;	//平均发送中时间

	//初始化函数
	MapFunSessionCreator		_vFunSessionCreator;
	MapFunAcceptorCreator		_vFunAcceptorCreator;
	MapFunSessionInit			_vFunSessionInit;
	MapFunSessionRunOnce		_vFunSessionRunOnce;
	MapFunBroadCast				_vFunBroadCast;
};
NS_TOOL_FRAME_END