#pragma once
#include "MacroServerCache.h"
#include "ISyncProcesser.h"
#include "DateTime.h"
#include "IHttpResponse.h"

NS_TOOL_FRAME_BEGIN

class IServerCache;
class HServerCache {
public:
	virtual bool OnCacheCreate(IServerCachePtr pCache, const XTopologyID& xSrcID, void* pUserData = nullptr, int nUserInt = 0) { return true; }
	virtual bool OnCacheDestory(IServerCachePtr pCache, const XTopologyID& xSrcID, void* pUserData = nullptr, int nUserInt = 0) { return true; }

	virtual bool OnCacheConnect(IServerCachePtr pCache, const XTopologyID& xSrcID, void* pUserData = nullptr, int nUserInt = 0) { return true; }			//请求连接(添加至连接列表 加载必要数据)
	virtual bool OnCacheConnected(IServerCachePtr pCache, const XTopologyID& xSrcID, void* pUserData = nullptr, int nUserInt = 0) { return true; }			//连接成功(加载额外数据)
	virtual bool OnCacheDisconnect(IServerCachePtr pCache, const XTopologyID& xSrcID, void* pUserData = nullptr, int nUserInt = 0) { return true; }			//断开连接(移除连接列表)

	virtual bool OnCacheProcessMsg(IServerCachePtr pCache, const XTopologyID& xSrcID, const XServerArg& xServerArg, const IMsgStream& msgBase) { return false; }
	virtual bool OnCacheProcessMsg(IServerCachePtr pCache, const XTopologyID& xSrcID, const XServerArg& xServerArg, StreamBinaryPtr pBuffer) { return false; }

	virtual bool OnCacheSave(IServerCachePtr pCache, const XTopologyID& xSrcID, void* pUserData = nullptr, int nUserInt = 0) { return false; }

	virtual bool OnCacheKick(IServerCachePtr pCache, const XTopologyID& xSrcID, void* pUserData = nullptr, int nUserInt = 0) { return false; }
	virtual bool OnCacheLogin(IServerCachePtr pCache, const XTopologyID& xSrcID,void* pUserData = nullptr, int nUserInt = 0) { return false; }		//登录成功

	virtual bool OnCacheSend(IServerCachePtr pCache, const XTopologyID& xSrcID, const IMsgStream& msgBase) { return false; }
	virtual bool OnCacheSend(IServerCachePtr pCache, const XTopologyID& xSrcID, StreamBinaryPtr pBuffer) { return false; }

	virtual bool OnCacheProcessHttp(IServerCachePtr pCache, const IHttpResponse& xResponse) { return false; }

	virtual bool OnCacheOperate(IServerCachePtr pCache, const XTopologyID& xSrcID, void* pUserData = nullptr, int nUserInt = 0) { return false; }//自定义操作
	
	//错误
public:
	virtual bool OnCacheCreateErr(IServerCachePtr pCache, const XTopologyID& xSrcID, void* pUserData = nullptr, int nUserInt = 0) { return false; }
	virtual bool OnCacheDestoryErr(IServerCachePtr pCache, const XTopologyID& xSrcID, void* pUserData = nullptr, int nUserInt = 0) { return false; }

	virtual bool OnCacheConnectErr(IServerCachePtr pCache, const XTopologyID& xSrcID, void* pUserData = nullptr, int nUserInt = 0) { return false; }			//请求连接(添加至连接列表 加载必要数据)
	virtual bool OnCacheConnectedErr(IServerCachePtr pCache, const XTopologyID& xSrcID, void* pUserData = nullptr, int nUserInt = 0) { return false; }			//连接成功(加载额外数据)
	virtual bool OnCacheDisconnectErr(IServerCachePtr pCache, const XTopologyID& xSrcID, void* pUserData = nullptr, int nUserInt = 0) { return false; }			//断开连接(移除连接列表)

	virtual bool OnCacheProcessMsgErr	(IServerCachePtr pCache, const XTopologyID& xSrcID, const XServerArg& xServerArg, const IMsgStream& msgBase) { return false; }
	virtual bool OnCacheProcessMsgErr	(IServerCachePtr pCache, const XTopologyID& xSrcID, const XServerArg& xServerArg, StreamBinaryPtr pBuffer) { return false; }

	virtual bool OnCacheSaveErr(IServerCachePtr pCache, const XTopologyID& xSrcID, void* pUserData = nullptr, int nUserInt = 0) { return false; }

	virtual bool OnCacheKickErr(IServerCachePtr pCache, const XTopologyID& xSrcID, void* pUserData = nullptr, int nUserInt = 0) { return false; }
	virtual bool OnCacheLoginErr(IServerCachePtr pCache, const XTopologyID& xSrcID, void* pUserData = nullptr, int nUserInt = 0) { return false; }		//登录成功

	virtual bool OnCacheSendErr(IServerCachePtr pCache, const XTopologyID& xSrcID, const IMsgStream& msgBase) { return false; }
	virtual bool OnCacheSendErr(IServerCachePtr pCache, const XTopologyID& xSrcID, StreamBinaryPtr pBuffer) { return false; }

	virtual bool OnCacheProcessHttpErr(IServerCachePtr pCache, const IHttpResponse& xResponse) { return false; }

	virtual bool OnCacheOperateErr		(IServerCachePtr pCache, const XTopologyID& xSrcID, void* pUserData = nullptr, int nUserInt = 0) { return false; }//自定义操作
public:
	HServerCache(){}
	virtual ~HServerCache(){}
};

class HServerCacheLog
	:public HServerCache
{
public:
	virtual bool OnCacheCreateErr(IServerCachePtr pCache, const XTopologyID& xSrcID, void* pUserData = nullptr, int nUserInt = 0)override;
	virtual bool OnCacheDestoryErr(IServerCachePtr pCache, const XTopologyID& xSrcID, void* pUserData = nullptr, int nUserInt = 0)override;

	virtual bool OnCacheConnectErr(IServerCachePtr pCache, const XTopologyID& xSrcID, void* pUserData = nullptr, int nUserInt = 0)override;			//请求连接(添加至连接列表 加载必要数据)
	virtual bool OnCacheConnectedErr(IServerCachePtr pCache, const XTopologyID& xSrcID, void* pUserData = nullptr, int nUserInt = 0)override;			//连接成功(加载额外数据)
	virtual bool OnCacheDisconnectErr(IServerCachePtr pCache, const XTopologyID& xSrcID, void* pUserData = nullptr, int nUserInt = 0)override;			//断开连接(移除连接列表)

	virtual bool OnCacheProcessMsgErr(IServerCachePtr pCache, const XTopologyID& xSrcID, const XServerArg& xServerArg, const IMsgStream& msgBase)override;
	virtual bool OnCacheProcessMsgErr(IServerCachePtr pCache, const XTopologyID& xSrcID, const XServerArg& xServerArg, StreamBinaryPtr pBuffer)override;

	virtual bool OnCacheSaveErr(IServerCachePtr pCache, const XTopologyID& xSrcID, void* pUserData = nullptr, int nUserInt = 0)override;

	virtual bool OnCacheKickErr(IServerCachePtr pCache, const XTopologyID& xSrcID, void* pUserData = nullptr, int nUserInt = 0)override;
	virtual bool OnCacheLoginErr(IServerCachePtr pCache, const XTopologyID& xSrcID, void* pUserData = nullptr, int nUserInt = 0)override;		//登录成功

	virtual bool OnCacheSendErr(IServerCachePtr pCache, const XTopologyID& xSrcID, const IMsgStream& msgBase)override;
	virtual bool OnCacheSendErr(IServerCachePtr pCache, const XTopologyID& xSrcID, StreamBinaryPtr pBuffer)override;

	virtual bool OnCacheProcessHttpErr(IServerCachePtr pCache, const IHttpResponse& xResponse)override;

	virtual bool OnCacheOperateErr(IServerCachePtr pCache, const XTopologyID& xSrcID, void* pUserData = nullptr, int nUserInt = 0)override;//自定义操作
public:
	HServerCacheLog() {}
	virtual ~HServerCacheLog() {}
};

class IServerCache
	:public ISyncProcesser
	,public HServerCacheLog
{
public:
	virtual bool					SetCacheID(uint uCacheID);
	virtual bool					SetCacheHandler(HServerCache* hHandler);

	virtual uint					GetCacheID()const;
	virtual IServerCachePtr			GetCachePtr();

	virtual bool					SetSingle(bool bSingle);		//单点登录(默认 true)
	virtual bool					IsSingle()const;				//是否是单点登录

	virtual const VectorTopologyID&	GetTopologyID()const;
	virtual bool					AddTopologyID(const XTopologyID& xTopologyID);
	virtual bool					RemoveTopologyID(const XTopologyID& xTopologyID);
	virtual bool					ClearTopologyID();				//设置拓扑ID无效
	virtual bool					IsTopologyIDEmpty()const;		//拓扑ID是否有效
	virtual bool					IsHasTopologyID(const XTopologyID& xTopologyID)const;		//是否存在拓扑ID
	virtual const XTopologyID&		GetTopologyIDSingle()const;					//获取唯一的拓扑ID
	
	virtual bool					MarkUpdated();	//标记有更新
	virtual const CDateTime&		GetTimeUpdate()const;

	virtual bool					MarkSaved();//标记存储过
	virtual const CDateTime&		GetTimeSave()const;
public:
	virtual bool SyncCreate(const XTopologyID& xSrcID, void* pUserData = nullptr, int nUserInt = 0);
	virtual bool SyncDestory(const XTopologyID& xSrcID, void* pUserData = nullptr, int nUserInt = 0);

	virtual bool SyncConnect(const XTopologyID& xSrcID, void* pUserData = nullptr, int nUserInt = 0);			//请求连接(添加至连接列表 加载必要数据)
	virtual bool SyncConnected(const XTopologyID& xSrcID, void* pUserData = nullptr, int nUserInt = 0);			//连接成功(加载额外数据)
	virtual bool SyncDisconnect(const XTopologyID& xSrcID, void* pUserData = nullptr, int nUserInt = 0);			//断开连接(移除连接列表)

	virtual bool SyncProcessMsg(const XTopologyID& xSrcID,  const XServerArg& xServerArg, const IMsgStream& msgBase);
	virtual bool SyncProcessMsg(const XTopologyID& xSrcID,  const XServerArg& xServerArg, StreamBinaryPtr pBuffer);

	virtual bool SyncSave(const XTopologyID& xSrcID,  void* pUserData = nullptr, int nUserInt = 0);

	virtual bool SyncKick (const XTopologyID& xSrcID, void* pUserData = nullptr, int nUserInt = 0);
	virtual bool SyncLogin(const XTopologyID& xSrcID, void* pUserData = nullptr, int nUserInt = 0);		//登录成功

	virtual bool SyncSend(const XTopologyID& xSrcID, const IMsgStream& msgBase);
	virtual bool SyncSend(const XTopologyID& xSrcID, StreamBinaryPtr pBuffer);

	virtual bool SyncProcessHttp(const IHttpResponse& xResponse);	//处理Http

	virtual bool SyncOperate(const XTopologyID& xSrcID, void* pUserData = nullptr, int nUserInt = 0);//自定义操作
public:
	virtual bool OnCreate(const XTopologyID& xSrcID, void* pUserData = nullptr, int nUserInt = 0);
	virtual bool OnCacheDestory(const XTopologyID& xSrcID, void* pUserData = nullptr, int nUserInt = 0);

	virtual bool OnCacheConnect(const XTopologyID& xSrcID, void* pUserData = nullptr, int nUserInt = 0);			//请求连接(添加至连接列表 加载必要数据)
	virtual bool OnCacheConnected(const XTopologyID& xSrcID, void* pUserData = nullptr, int nUserInt = 0);			//连接成功(加载额外数据)
	virtual bool OnCacheDisconnect(const XTopologyID& xSrcID, void* pUserData = nullptr, int nUserInt = 0);			//断开连接(移除连接列表)

	virtual bool OnCacheProcessMsg(const XTopologyID& xSrcID, const XServerArg& xServerArg, const IMsgStream& msgBase);
	virtual bool OnCacheProcessMsg(const XTopologyID& xSrcID, const XServerArg& xServerArg, StreamBinaryPtr pBuffer);

	virtual bool OnCacheSave(const XTopologyID& xSrcID, void* pUserData = nullptr, int nUserInt = 0);

	virtual bool OnCacheKick(const XTopologyID& xSrcID, void* pUserData = nullptr, int nUserInt = 0);
	virtual bool OnCacheLogin(const XTopologyID& xSrcID, void* pUserData = nullptr, int nUserInt = 0);		//登录成功

	virtual bool OnCacheSend(const XTopologyID& xSrcID, const IMsgStream& msgBase);
	virtual bool OnCacheSend(const XTopologyID& xSrcID, StreamBinaryPtr pBuffer);

	virtual bool OnCacheProcessHttp(const IHttpResponse& xResponse);	//处理Http

	virtual bool OnCacheOperate(const XTopologyID& xSrcID, void* pUserData = nullptr, int nUserInt = 0);//自定义操作
public:
	IServerCache();
	virtual ~IServerCache();
private:
	HServerCache* _hCacheHandler;

	bool			_bSingle;		//单点登录
	CDateTime		_tTimeUpdate;	//最近更新时间
	CDateTime		_tTimeSave;		//最近保存时间

	VectorTopologyID _vTopologyID;	//拓扑ID
};

NS_TOOL_FRAME_END
