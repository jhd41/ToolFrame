#pragma once

#include "IServer.h"
#include "TopologyLogic.h"
#include "IThreadTask.h"
#include "HLog.h"
#include "HSystem.h"
#include "ServerCacheManager.h"
#include "UrlRequestTopology.h"

NS_TOOL_FRAME_BEGIN

class IServerLogic
	:public IServer
	,public HTopologyLogic
	,public HLog
	,public HSystem
	,public HServerCacheLog
	,public HUrlRequest
{
public:
	virtual bool Init();	//初始化
public:
	virtual int		GetServerID()const;
	virtual int		GetServerType()const;
	virtual bool	SetStateNormal();
	virtual bool	SetStateStop();
	virtual bool	SetCacheVaild(size_t uCacheVaild);
	virtual bool	SetCacheTotal(size_t uCacheTotal);
	virtual bool	SetProcesserCount(size_t uCacheTotal);
	virtual bool	SetQueueSize(size_t uQueueSize);//设置队列长度
	virtual bool	SetQueueProcess(size_t uQueueProcess );//设置队列处理量
	virtual bool	SetDebugReport(bool bReport);
	virtual bool	IsDebugReport()const;
	virtual bool	IsInited()const;
	virtual bool	SetInited(bool bInited);
	
	virtual CServerCacheManager&		GetCacheManager();
	virtual const CServerCacheManager&	GetCacheManager()const;
public:
	virtual uint	FindServerID(uint uClientID)const;
	virtual uint	FindClientID(uint uServerID)const;									//找个ClientID

	virtual uint	SendClientID(uint uClientID,const IMsgStream& msg,const XTopologyID& uID,uint32 uUserID)const;
	virtual uint	SendClientID(uint uClientID,const IMsgStream& msg,const XTopologyID& uID)const;
	virtual uint	SendClientID(uint uClientID,const IMsgStream& msg)const;

	virtual uint	SendClientID(uint uClientID,StreamBinaryPtr ptr,const XTopologyID& uID,uint32 uUserID)const;

	virtual uint	SendSrvID(int nServerID,const IMsgStream& msg,const XTopologyID& uID = TOPOLOGY_ID_INVAILD)const;//发送给指定服务器 返回 ClientID
	virtual uint	SendSrvID(int nServerID, StreamBinaryPtr ptr,const XTopologyID& uID = TOPOLOGY_ID_INVAILD)const;
	virtual uint	SendSrvID(int nServerID,const IMsgStream& msg,const XTopologyID& uID,uint32 uUserID)const;
	virtual uint	SendSrvID(int nServerID, StreamBinaryPtr ptr,const XTopologyID& uID,uint32 uUserID)const;

	virtual uint	SendSrvID(const XTopologyID& xSrcID, StreamBinaryPtr ptr,uint32 uUserID)const;
	virtual uint	SendSrvID(const XTopologyID& xSrcID, StreamBinaryPtr ptr)const;
	virtual uint	SendSrvID(const XTopologyID& xSrcID,const IMsgStream& msg,uint32 uUserID)const;
	virtual uint	SendSrvID(const XTopologyID& xSrcID,const IMsgStream& msg)const;

	//以根据服务器的运行类型寻找合适的发送方式进行发送
	virtual uint	SendSrvType(int eSrvType, const IMsgStream& msg)const;										//返回ClientID
	virtual uint	SendSrvType(int eSrvType, const XTopologyID& xSrcID, const IMsgStream& msg)const;				//返回ClientID
	virtual uint	SendSrvType(int eSrvType, const XTopologyID& xSrcID, const IMsgStream& msg, uint uUserID)const;//返回ClientID

	//以随机的方式进行发送
	virtual uint	SendRandom(int eSrvType,const IMsgStream& msg)const;										//返回ClientID
	virtual uint	SendRandom(int eSrvType,const XTopologyID& xSrcID,const IMsgStream& msg)const;					//返回ClientID
	virtual uint	SendRandom(int eSrvType,const XTopologyID& xSrcID,const IMsgStream& msg,uint uUserID)const;	//返回ClientID
	
	//以平衡的方式进行发送
	virtual uint	SendBalance(int eSrvType, const IMsgStream& msg)const;										//返回ClientID
	virtual uint	SendBalance(int eSrvType, const XTopologyID& xSrcID, const IMsgStream& msg)const;				//返回ClientID
	virtual uint	SendBalance(int eSrvType, const XTopologyID& xSrcID, const IMsgStream& msg, uint uUserID)const;//返回ClientID

	//广播
	virtual bool	BoardCast(int eSrvType,const IMsgStream& msg,const XTopologyID& xSrcID = TOPOLOGY_ID_INVAILD,uint uUserID=INVALID_ID)const;

	//发送至网关
	virtual uint	SendGateWaySrv(const XTopologyID& uID, const IMsgStream& msg)const;
	virtual uint	SendGateWaySrv(const XTopologyID& uID, StreamBinaryPtr ptr)const;
	virtual bool	SendGateWaySrv(const VectorTopologyID& vTopologyID, const IMsgStream& msg)const;
	virtual bool	SendGateWaySrv(const VectorTopologyID& vTopologyID, StreamBinaryPtr ptr)const;

	//发送Url请求
	virtual CUrlRequestTopologyPtr	UrlRequest(const XTopologyID& xSrcID, uint uID, int eType, const std::string& sUrl, uint uSrvID = INVALID_ID);
	virtual CUrlRequestTopologyPtr	UrlRequest(const XTopologyID& xSrcID, uint uID, CUrlRequestTopologyPtr pRequest);
	virtual CUrlRequestTopologyPtr	UrlRequest(const XTopologyID& xSrcID, const std::string& sUrl);
	virtual CUrlRequestTopologyPtr	UrlRequest(const std::string& sUrl);
	//调试
	virtual bool DebugReport();
protected:
	virtual bool OnFinished(IUrlRequestPtr pRequest) override;
protected:
	virtual bool OnServerAllConnected()override;
	virtual bool OnServerReport()override;
	virtual bool OnServerSave()override;
	virtual bool OnServerCleanUp()override;		//清理缓存
	virtual bool OnServerStopService()override;
	virtual bool OnServerShutDown()override;
	virtual bool OnServerRecved(const XServerArg& xServerArg, IMsgStream& msgBase)override;
	virtual std::string OnServerDebug(const VectorString& vDebug)override;//调试进程
public:
	virtual bool OnSendFaild(int nServerID,const XTopologyID& uID, StreamBinaryPtr ptr)const;
public:
	virtual bool OnRunElasticThread()override;		//执行弹性线程，返回是否超时
	virtual bool OnRunElasticThreadExtra();	//额外部分 返回是否超时(子类主要继承这个函数)
public:
	IServerLogic(void);
	virtual ~IServerLogic(void);
protected:
	CTopologyLogic			_xTopologyLogic;
	bool					_bInited;
	bool					_bDebugReport;
	CServerCacheManager		_mgrCache;
};

NS_TOOL_FRAME_END
