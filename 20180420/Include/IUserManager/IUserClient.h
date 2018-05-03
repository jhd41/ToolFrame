#pragma once

#include "Macro.h"
#include "MacroTopology.h"
#include "ISyncProcesser.h"
#include "IMsgStream.h"
#include "IUserClientResolver.h"
#include "IResolverManager.h"
#include "UrlRequestTopology.h"

NS_TOOL_FRAME_BEGIN

class IUserClient
	:public ISyncProcesser
	,public IResolverManager
{
public:
	virtual bool	SetTimeOut(uint uTimeOut);					//设置超时时长
	virtual bool	SetRecvPack(uint uRecvMax, uint uRecvPer);	//设置最大每X秒可以接收Y个包
	virtual bool	SetEncryptTransmission(bool bEncrypt);		//设置 加密传输 默认开启
	virtual bool	Init(uint uSrvID,uint uClientID, uint uAssID);
public:
	virtual bool	IsEncryptTransmission()const;				//是否加密传输
	virtual uint32  MakeSecretKey();	//产生秘钥
	virtual uint32	GetSecretKey()const;//获取秘钥
public:
	virtual bool SyncClientConnected(uint uClientID);
	virtual bool SyncClientDisconnected();
	virtual bool SyncClientRecvStream(const IMsgStream& msgStream);
	virtual bool SyncClientRecvBuffer(StreamBinaryPtr pMsgStream);
	virtual bool SyncClientUrlResponce(CUrlRequestTopologyPtr pRequest);

	virtual bool SyncServerRecved(const XServerArg& xServerArg,const IMsgStream& msgBase);

	virtual bool SyncCheck(time_t uTimeNow);
	virtual bool SyncTimeOut(const CTimeNodePtr& pTimeNode);
	virtual bool SyncDisconnected(bool bActive = true);

	virtual bool SyncSendClient(const IMsgStream& msgStream, bool bSecret = true);			//发送至客户端，若客户端掉线 则会缓存
	virtual bool SyncSendClient(const StreamBinaryPtr ptr, bool bSecret = true);
	virtual bool SyncSendClient(const std::string& sMsg, bool bSecret = true);
	virtual bool SyncSendClient(const void* pBuffer, size_t uLen, bool bSecret = true);
public:
	virtual bool OnClientConnected(uint uClientID);
	virtual bool OnClientDisconnected();
	virtual bool OnClientRecvStream(const IMsgStream& msgStream);
	virtual bool OnClientRecvBuffer(StreamBinaryPtr pMsgStream);
	virtual bool OnClientUrlResponce(CUrlRequestTopologyPtr pRequest);

	virtual bool OnServerRecved(const XServerArg& xServerArg, const IMsgStream& msgBase);

	virtual bool OnCheck(time_t uTimeNow);
	virtual bool OnResolverTimeOut(const CTimeNodePtr& pTimeNode);

	virtual bool SendClient(const IMsgStream& msgStream, bool bSecret = true);			//发送至客户端，若客户端掉线 则会缓存
	virtual bool SendClient(const StreamBinaryPtr ptr, bool bSecret = true);
	virtual bool SendClient(const std::string& sMsg, bool bSecret = true);
	virtual bool SendClient(const void* pBuffer, size_t uLen, bool bSecret = true);

	virtual bool Disconnect(bool bActive = true);

public:
	virtual bool	SetConnectServer(const MapIntInt& vServerConnect);
	virtual bool	AddConnectServer(int eSrvType, int nSrvID);
	virtual bool	RemoveConnectServer(int eSrvType);
	virtual int		FindConnectServer(int eSrvType);
private:
	virtual bool Send(const IMsgStream& msgStream, bool bSecret = true);
	virtual bool Send(const StreamBinaryPtr ptr, bool bSecret = true);
	virtual IUserClientResolver* FindTopUserClientResolver();
private:
	virtual bool OnResolveTimeOut(IResolverManager* pMgrResolver, const CTimeNodePtr& pTimeNode);						//结算超时(可能是多线程回调)
	virtual bool OnResolveOver(IResolverManager* pMgrResolver)override;

	//子类回调
protected:
	virtual bool	OnSend(StreamBinaryPtr ptr, bool bSecret);
	virtual bool	OnEncrypt(void* pBuffer, size_t uLength);	//加密
	virtual bool	OnDecrypt(void* pBuffer, size_t uLength);	//解密
	virtual bool	OnEncryptFaild(void* pBuffer, size_t uLength);	//加密
	virtual bool	OnDecryptFaild(void* pBuffer, size_t uLength);	//解密
public:
	IUserClient();
	virtual ~IUserClient();
private:
	CFIELD_UINT(ClientID);
	CFIELD_UINT(AssID);
	CFIELD_UINT(SrvID);
	CFIELD_REF(XTopologyID, TopologyID, x);
	CFIELD_UINT(UserID);
	CFIELD_BOOL(Connected);					//已连通
	CFIELD_BOOL(Closed);					//已关闭
	CFIELD_BOOL(ActiveDisconnect);			//主动断线
	CFIELD_REF(MapIntInt, ServerConnect, v);	//服务器连接表	
private:
	uint			_uTimeOut;		//超时时长
	CTimeOut		_tLastRecv;		//心跳时间(最近收包时间)
	uint			_tRecvMax;		//收取包上限
	CTimeOut		_tRecvBegin;	//收取包计时(规定时间内只能收取X个包)
	uint			_tRecvCount;	//收取个数
	uint32			_uSecretKey;	//秘钥
	bool			_bEncryptTransmission; //加密传输
};

NS_TOOL_FRAME_END
