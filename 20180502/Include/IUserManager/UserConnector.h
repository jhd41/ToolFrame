#pragma once
#include "Macro.h"
#include "MacroNet.h"
#include "IMsgStream.h"
#include "TransitoryLinker.h"
#include "TimeOut.h"
#include "HTimeOut.h"

//用户连接器
//默认会反复尝试连接服务器，连接后 会一直保持连接

//SetReconnectMax	默认无限反复连接

NS_TOOL_FRAME_BEGIN
class TOOLFRAME_DLL CUserConnector;
//////////////////////////////////////////////////////////////////////////
class TOOLFRAME_DLL HUserConnector
{
public:
	virtual bool OnConnected		(CUserConnector* pConnector){return true;}
	virtual bool OnConnectFaild		(CUserConnector* pConnector){return true;}
	virtual bool OnDisconnected		(CUserConnector* pConnector){return true;}
	virtual bool OnRecved			(CUserConnector* pConnector,IMsgStream& msgStream){return false;}				//当接收时 返回true代表被正确处理 不会调用 接收加密 解密 协议毁掉
	virtual bool OnSend				(CUserConnector* pConnector, StreamBinaryPtr ptr,bool bSecret){return true;}		//当发送时,返回false 不发送
	virtual bool OnStateChanged(CUserConnector* pConnector, int eState) { return false; }

	virtual bool OnRecvEncrypted(CUserConnector* pConnector, IMsgStream& msgStream) { return false; }				//接收密文
	virtual bool OnRecvDecrypted(CUserConnector* pConnector, IMsgStream& msgStream) { return false; }				//接收明文
	virtual bool OnEncrypt(CUserConnector* pConnector, void* pBuffer, size_t uLength) { return false; }
	virtual bool OnEncryptFailed(CUserConnector* pConnector, void* pBuffer, size_t uLength) { return false; }
	virtual bool OnDecrypt(CUserConnector* pConnector, void* pBuffer, size_t uLength) { return false; }
	virtual bool OnDecryptFailed(CUserConnector* pConnector, void* pBuffer, size_t uLength) { return false; }

	virtual bool OnRefused(CUserConnector* pConnector) { return false; }
	virtual bool OnHeartTimeOut(CUserConnector* pConnector) { return false; }										//心跳超时
	virtual bool OnKeepHeartTimeOut(CUserConnector* pConnector) { return false; }										//需要发心跳包时

	virtual bool OnErrCacheFull(CUserConnector* pConnector, StreamBinaryPtr pBuffer) { return false; }//当发送缓冲区已满
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
	virtual bool OnSend(CUserConnector* pConnector, StreamBinaryPtr ptr, bool bSecret)override;				//当发送时,返回false 不发送
	virtual bool OnStateChanged(CUserConnector* pConnector, int eState)override;

	virtual bool OnRecvEncrypted(CUserConnector* pConnector, IMsgStream& msgStream)override;				//接收密文
	virtual bool OnRecvDecrypted(CUserConnector* pConnector, IMsgStream& msgStream)override;				//接收明文
	virtual bool OnEncrypt(CUserConnector* pConnector, void* pBuffer, size_t uLength)override;
	virtual bool OnEncryptFailed(CUserConnector* pConnector, void* pBuffer, size_t uLength)override;
	virtual bool OnDecrypt(CUserConnector* pConnector, void* pBuffer, size_t uLength)override;
	virtual bool OnDecryptFailed(CUserConnector* pConnector, void* pBuffer, size_t uLength)override;
	
	virtual bool OnRefused(CUserConnector* pConnector)override;
	virtual bool OnHeartTimeOut(CUserConnector* pConnector)override;										//心跳超时
	virtual bool OnKeepHeartTimeOut(CUserConnector* pConnector)override;									//需要发心跳包时

	virtual bool OnErrCacheFull(CUserConnector* pConnector, StreamBinaryPtr pBuffer)override;				//当发送缓冲区已满
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

		STATE_CONNECT,			//连接中
		STATE_CONNECTED,		//已连接
		STATE_STOPING,			//停止中
		STATE_STOP,				//已停止
		STATE_RECONNECT,		//重连中

		STATE_NORMAL,			//正常
		STATE_RECONNECT_FAILD,	//重连失败

		STATE_MAX,
	};
public:
	virtual bool				SetHandler(HUserConnector* hHandler);
	virtual bool				SetHeartCheck(time_t tTimeCheck);			//设置心跳轮询时间(要小)
	virtual bool				SetHeartTimeOut(time_t tTimeOut);			//设置心跳超时时间(不稳定 时间区间为[超时时间,超时时间 + 轮询时间])
	virtual bool				SetHeartPing(time_t tTime);					//设置 发心跳时间(不稳定 时间区间为[超时时间,超时时间 + 轮询时间])
	virtual bool				SetServerAddress(const std::string& sAddress);
	virtual bool				SetServerAddress( const VectorString& vAddress );
	virtual bool				SetSecretKey(uint32 uAssID,uint32 uSecretKey,uint32 uTimeServer);//设置秘钥
	virtual bool				SetReconnectMax(int nCount);				//设置重连次数
	virtual bool				SetCacheMax(uint uCount);					//设置发送缓冲区大小
	virtual bool				SetReSend(bool bResend);					//设置 若掉线重新发送(默认掉线后清理没有发送完成的协议)
	virtual bool				SetKeepLink(bool bKeepLink = true);			//是否需要保持连接，默认保持 (线程安全)
	virtual bool				SetNetErrCode(int nNetErrCode);				//设置网络错误代号
	virtual bool				SetRecvSize(size_t uSize);					//设置接收缓冲区大小
	virtual bool				SetSendSize(size_t uSize);					//设置发送缓冲区大小
	virtual bool				SetBlockSize(size_t uSize);					//设置缓冲区无限时每次分配大小(默认65535)
	virtual bool				SetEncryptTransmission(bool bEncrypt);		//设置 加密传输 默认开启
	virtual bool				AutoKeepHeart(bool bAuto);					//设置 状态正常后自动保持心跳(默认开启)
public:
	virtual int					GetState()const;
	virtual uint				GetClientID()const;
	virtual const std::string&	GetConnectedAddress()const;
	virtual const VectorString& GetServerAddress()const;					//获取服务器地址(非线程安全)
	virtual uint32				GetSecretKey()const;
	virtual uint32				GetAssID()const;
	virtual int					GetNetErrCode()const;						//获取网络错误代码
	virtual bool				IsHasSecretKey()const;
	virtual bool				IsConnected()const;
	virtual bool				IsReSend()const;
	virtual bool				IsStoped()const;
	virtual bool				InvaildSecret(int nNetErrCode  = NET_ERRCODE_ACTIVE);//使连接无效
	virtual bool				IsEncryptTransmission()const;				//是否加密传输
	virtual bool				IsAutoKeepHeart()const;						//是否是自动保持心跳
	//心跳检测
public:
	virtual bool				StartHeartCheck();			//启动心跳检测
	virtual bool				StopHeartCheck();			//停止心跳检测
	virtual bool				StartKeepHeart(time_t tTime = 0);//保持心跳(至少存活时间)
	virtual bool				StopKeepHeart();			//停止保持心跳
public:
	virtual bool				Connect();
	virtual bool				Push(StreamBinaryPtr ptr,bool bSecret = true);	//压入队列
	virtual bool				Push(const IMsgStream& msgStream, bool bSecret = true);	//压入队列
	virtual bool				Send(StreamBinaryPtr ptr,bool bSecret = true);	//发送
	virtual bool				Send(const IMsgStream& msgStream, bool bSecret = true);	//压入队列
	virtual bool				ClearMsg();
	virtual bool				Disconnect(int nNetErrCode = NET_ERRCODE_ACTIVE, bool bClear = true);//断开连接(主动,放弃未发送消息)
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
	virtual bool OnErrCacheFull(const CTransitoryLinker* pLinker, StreamBinaryPtr pBuffer)override;//当发送缓冲区已满
	virtual bool OnStateChanged(CTransitoryLinker* pLinker,int eState)override;
public:
	virtual bool OnTimeOut( const CTimeNodePtr& pTimeNode )override;
private:
	virtual bool SetState(EState eState);
public:
	CUserConnector(void);
	virtual ~CUserConnector(void);
protected:
	CTransitoryLinker	_xTransitory;//短连接
	HUserConnector*		_hHandler;
	uint32				_uAssID;
	uint32				_uSecretKey;
	uint32				_uTimeServer;
	EState				_eState;
	bool				_bResend;		//重新发送
	int					_nNetErrCode;	//网络错误号
	bool				_bEncryptTransmission; //加密传输

	bool				_bAutoKeepHeart;//自动保持心跳
	time_t				_tTimeCheck;	//轮询时间
	time_t				_tTimePing;		//发心跳包时间
	CTimeNodePtr		_pTimerHeart;	//心跳 超时检查
	CTimeOut			_tTimeHeart;	//超时时间
	CTimeOut			_tTimeKeep;		//保持心跳时间
};

NS_TOOL_FRAME_END
