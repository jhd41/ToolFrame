#pragma once
#include "Macro.h"
#include "MacroTopology.h"
#include "ISyncProcesserManager.h"
#include "IMsgStream.h"
#include "IUserClient.h"
#include "IDMaker.h"
#include "HTimeOut.h"

NS_TOOL_FRAME_BEGIN

class IUserClientManager
	:protected ISyncProcesserManager
	,public HTimeOut
{
public:
	virtual bool SetCheckTime(uint uTimeOut);				//设置轮询时间
	virtual bool SetTimeOut(uint uTimeOut);					//设置超时时间
	virtual bool SetRecvPack(uint uRecvMax, uint uRecvPer);	//设置最大每X秒可以接收Y个包
	virtual bool Init();
	virtual bool SyncDisconnectAll(bool bActive = true);			//断开连接
	virtual bool SyncDisconnect(uint uAssID, bool bActive = true);	//断开连接
	virtual bool SyncServerRecved(const XServerArg& xServerArg, const IMsgStream& msgBase);
	virtual bool SyncClientConnected(uint uClientID);
	virtual bool SyncClientDisconnect(uint uClientID);
	virtual bool SyncClientRecved(uint uClientID, const IMsgStream& msgStream);
	virtual bool SyncClientRecved(uint uClientID, IDataSession* pSession);

	virtual bool SyncSendClient(uint uClientID, const IMsgStream& msgStream, bool bSecret = true);			//发送至客户端，若客户端掉线 则会缓存
	virtual bool SyncSendClient(uint uClientID, StreamBinaryPtr ptr, bool bSecret = true);
	virtual bool SyncSendClient(uint uClientID, const std::string& sMsg, bool bSecret = true);
	virtual bool SyncSendClient(uint uClientID, const void* pBuffer, size_t uLen, bool bSecret = true);

	virtual bool SyncCalState(uint& uTotal, uint& uVaild, uint& uNormal, uint& uQueue, uint& uDelete, uint& uPerpairing, uint& uCache) const;//统计缓存的状态(总数，有效数，正常数 低性能 调试用)
public:
	virtual time_t			GetTimeOut()const;
	virtual time_t			GetCheckTime()const;
	virtual size_t			GetClientCount()const;
	virtual size_t			GetAssCount()const;
	virtual size_t			GetQueueSize()const;
	virtual bool			ProcessRetry(uint64 uMillTime);
private:
	virtual bool				OnTimeOut(const CTimeNodePtr& pTimeNode)override;
	virtual ISyncProcesserPtr	OnCreateProcesser(int nUserInt, void* pUserData)override;
	virtual bool				OnDestoryProcesser(ISyncProcesserPtr pProcesser)override;
public:
	CFIELD_UINT(SrvID);
public:
	IUserClientManager();
	virtual ~IUserClientManager();
public:
	CTimeNodePtr			_pTimerCheck;
	uint					_uCheckTime;//轮询 检测时间间隔
	uint					_uTimeOut;	//心跳超时时间
	uint					_uRecvMax;	//最大接收包数
	uint					_uRecvPer;	//最大接收包数刷新时间间隔

	bool					_bInit;		//初始化
};

NS_TOOL_FRAME_END