#pragma once
#include "Macro.h"
#include "MacroDefineEx.h"
#include "MacroNet.h"
#include "IDataReceiverStream.h"
#include "BufferStream.h"
#include "HTimeOut.h"

//备注:本类是一个连接监视器,若被监视的连接断开了则会立刻重连
//先状态切换后回调事件 会先调用OnStateChanged 再调用 OnConnected OnDisconnected OnConnectFaild

NS_TOOL_FRAME_BEGIN
class TOOLFRAME_DLL CConnectMonitor;
class TOOLFRAME_DLL HConnectMonitor{
public:
	virtual bool OnConnected(CConnectMonitor* pConnectMonitor){return true;}
	virtual bool OnDisconnected(CConnectMonitor* pConnectMonitor){return true;}
	virtual bool OnConnectFaild(CConnectMonitor* pConnectMonitor){return true;}
	virtual uint OnRecved(CConnectMonitor* pConnectMonitor,IDataSession* pSession){ return false; }//先调用这个函数 再调用 OnRecved（IMsgStream） 返回 非 0值 则不再调用OnRecved（IMsgStream）
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

		STATE_CONNECT,	//连接中
		STATE_NORMAL,	//已连接
		STATE_STOPING,	//停止中
		STATE_STOP,		//已停止
		STATE_RECONNECT,//重连中

		STATE_MAX,
	};
public:
	bool	SetRecvSize(size_t uSize);	//设置接收缓冲区大小
	bool	SetSendSize(size_t uSize);	//设置发送缓冲区大小
	bool	SetBlockSize(size_t uSize);	//设置缓冲区无限时每次分配大小(默认65535)
	bool	SetServerAddress(const std::string& sServerIP);
	bool	SetFlushTime(uint uMillSec);//设置发送间隔
	bool	SetFlushTime(uint uMillSecBegin,uint uMillSecEnd);//设置发送间隔
public:
	bool	Start();//开始服务
	bool	Stop(int nNetErrCode = NET_ERRCODE_ACTIVE);	//停止服务
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
	uint	GetClientID()const;	//获取最近一次连接的ClientID
	uint	GetRealClientID()const;
	const std::string&	GetRomoteIP()const;					//获取远程IP
	const std::string&	GetConnectedAddress()const;			//获取最近连接成功的地址
	const std::string&	GetRomoteIP();						//获取远程IP
	const std::string&	GetConnectedAddress();				//获取最近连接成功的地址
	int		GetNetErrCode()const;							//获取最近连接的网络错误代码
	bool	Disconnect(int nNetErrCode = NET_ERRCODE_ACTIVE);//断开连接(可能会被重连)
private:
	bool	IsCanReconnect()const;						//是否还需要重连
	bool	Reconnect();
	bool	SetState(EState eState);
	bool	RandTimer();
public:
	virtual bool			OnConnected(UINT uClientID)override;
	virtual bool			OnConnectFailed(UINT uClientID)override;
	virtual bool			OnDisconnected(UINT uClientID)override;
	virtual uint			OnRecv(IDataSession* pSession)override;//返回处理了包的个数
	virtual bool			OnRecv( uint uClientID,IMsgStream& msgStream)override;
public:
	virtual bool OnTimeOut(const CTimeNodePtr& pTimeNode);
public:
	CConnectMonitor(void);
	virtual ~CConnectMonitor(void);
private:
	uint		_uRealClientID;		//服务器连接字
	EState		_eState;			//设置状态
	size_t		_uRecvSize;			//接收缓冲区尺寸
	size_t		_uSendSize;			//发送缓冲区尺寸
	size_t		_uBlockSize;		//缓冲区每次分配大小
	bool		_bConnected;		//已连接
	bool		_bShutDown;			//关闭
	CBufferStream _xFlushBuffer;	//发送缓冲区

	uint		_uFlushBegin;		//发送时间间隔起点
	uint		_uFlushEnd;			//发送时间间隔终点
	CTimeNodePtr _pTimerFlush;		//发送时间间隔

	uint		 _uClientID;		//服务器连接字(最近一次)
	std::string  _sConnectedAddress;//连接成功的地址(最近一次)
	std::string  _sRomoteIP;		//远程ID(最近一次)
private:
	CFIELD_UINT(ID);				//ID号
	CFIELD_INT(UserInt);			//用户int数据
	CFIELD_PTR(void*,UserPtr,p);	//用户指针数据
	CFIELD_VECTOR_STRING(ServerAddress);//服务器地址
	CFIELD_INT(ReconnectCount);		//重连次数
	CFIELD_INT(ReconnectMax);		//重连次数最大值(若为-1，则不停重连 默认-1)
	CFIELD_PTR(HConnectMonitor*,Handler,p);
};

NS_TOOL_FRAME_END
