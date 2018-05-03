#pragma once

#include "Macro.h"
#include "MacroDefineEx.h"
#include "ConnectMonitor.h"
#include "TThreadSaftyList.h"
#include "CalCounter.h"
#include "BufferStream.h"

//短连接:需要的时候才连接 默认发送协议后 不保持连接
//SetReconnectMax	默认无限反复连接
//SetCacheMax		默认值为无限

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
	virtual bool OnErrCacheFull(const CTransitoryLinker* pLinker, StreamBinaryPtr pBuffer){return false;}//当发送缓冲区已满
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

		STATE_CONNECT,	//连接中
		STATE_NORMAL,	//已连接
		STATE_STOPING,	//停止中
		STATE_STOP,		//已停止
		STATE_RECONNECT,//重连中

		STATE_MAX,
	};
public:
	typedef TThreadSaftyListValue<StreamBinaryPtr>			QueueStreamBuffer;
public:
	virtual bool SetServerAddress(const std::string& sIP);		//设置IP地址(非线程安全)
	virtual bool SetServerAddress(const VectorString& vIP);
	virtual bool SetHandler(HTransitoryLinker* hHandler);	//设置处理器 可以不设置(非线程安全)
	virtual bool SetEnabled(bool bEnabled = true);			//标记是否初始化完成(默认 完成)
	virtual bool SetReconnectMax(int nCount);				//设置重连次数
	virtual bool SetCacheMax(uint uCount);					//设置发送缓冲区大小
	virtual bool SetResend(bool bResend);					//设置尝试重新发送之前断线失败的协议
	virtual bool SetRecvSize(size_t uSize);					//设置接收缓冲区大小
	virtual bool SetSendSize(size_t uSize);					//设置发送缓冲区大小
	virtual bool SetBlockSize(size_t uSize);					//设置缓冲区无限时每次分配大小(默认65535)
	virtual bool PushMsg(StreamBinaryPtr ptr,bool bSecret = true);//压入消息(线程安全)
	virtual bool SendMsg(StreamBinaryPtr ptr,bool bSecret = true);//直接发送
	virtual bool ClearMsg();								//清除没有发送的数据(线程安全)
	virtual bool SetKeepLink(bool bKeepLink = true);		//是否需要保持连接，默认不保持 (线程安全)
	virtual bool Connect();									//主动连接 可以不调用(线程安全)	
	virtual bool Stop(int nNetErrCode = NET_ERRCODE_ACTIVE);//停止连接(线程安全)	
	virtual bool IsStoped()const;							//是否已停止(线程安全)
	virtual bool ShutDown(bool bCallBack = true);			//停止服务
	virtual bool Disconnect(int nNetErrCode = NET_ERRCODE_ACTIVE);//断开连接(可能会继续重连)
	virtual bool ClearSendFaildBuffer();					//清除发送失败的缓存
	virtual int	 GetNetErrCode()const;						//获取网络错误代码
public:
	virtual bool IsEnabled()const;							//是否可用(线程安全)
	virtual bool IsKeepLink()const;							//是否保持连接 (线程安全)
	virtual bool IsConnected()const;						//是否连接上(线程安全)
	virtual size_t GetCacheCount()const;						//获取消息队列数(线程安全)
	virtual const VectorString& GetServerAddress()const;	//获取服务器地址(非线程安全)
	virtual const std::string&	GetConnectedAddress()const;	//获取连接到的服务器地址(线程安全)
	virtual uint GetClientID()const;						//获取ClientID(非线程安全)
	virtual size_t GetCacheMax()const;						//获取缓冲区大小
	virtual size_t GetCacheSize()const;						//获取缓冲区当前已使用大小
private:
	virtual bool CheckSendMsg();//多入口
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
	CBufferStream		_vCache;		//缓存的消息
	CConnectMonitor		_xMonitor;
	bool				_bKeepLink;
	HTransitoryLinker*	_hHandler;
	bool				_bEnable;
	bool				_bResend;		//重新尝试发送
	StreamBinaryPtr		_pSendBuffer;	//发送失败的协议

	mutable CMutexRecursive	_mutex;		//读写锁
};

NS_TOOL_FRAME_END