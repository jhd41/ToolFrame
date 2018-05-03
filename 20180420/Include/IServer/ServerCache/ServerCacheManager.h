#pragma once
#include "MacroServerCache.h"
#include "ISyncProcesserManager.h"
#include "IDMaker.h"
#include "HTimeOut.h"
#include "IServerCache.h"

NS_TOOL_FRAME_BEGIN

class CServerCacheManager
	:protected ISyncProcesserManager
	,public HTimeOut
	,public HServerCache
{
public:
	typedef ISyncProcesserManager::MapSyncProcesser			MapServerCache;
public:
	virtual bool SetManagerHandler(HSyncProcesserManager* hHandler);
	virtual bool SetCacheHandler(HServerCache* hHandler);
	virtual bool SetNeedSave(bool bSave);
	virtual bool SetAutoDelete(bool bAuto);				//设置自动清理开关(默认关闭)
	virtual bool SetDeleteTime(time_t uDelete = 1200);	//删除缓存的时间 秒(超过指定时间 若无效 则自动清理 默认20分钟)
	virtual bool SetCheckTime(time_t uCheck = 300);		//检查时间 秒(默认 5分钟)
	virtual bool Init();
	virtual bool Run(uint64 uMillTime);
public:
	virtual size_t	GetVaildCount()const;			//获取有效用户个数
	virtual size_t	GetNormalCount()const;			//获取正常用户数
	virtual size_t	GetTotalCount()const;			//获取总缓存玩家个数
	virtual size_t	GetOperateCount()const;			//获取待操作队列数
	virtual size_t	ClearOperateProcess();			//清除操作处理量
	virtual bool	IsCached(uint uCacheID)const;	//是否存在指定缓存
public:
	virtual uint SyncCreateMakeID(const XTopologyID& xSrcID, void* pUserData = nullptr, int nUserInt = 0);//自动分配ID

	virtual bool SyncCreate(const XTopologyID& xSrcID, uint uCacheID, void* pUserData = nullptr, int nUserInt = 0);
	virtual bool SyncCreate(const XTopologyID& xSrcID, uint uCacheID, int nUserInt);
	virtual bool SyncDestory(const XTopologyID& xSrcID, uint uCacheID, void* pUserData = nullptr, int nUserInt = 0);

	virtual bool SyncConnect(const XTopologyID& xSrcID, uint uCacheID, void* pUserData = nullptr, int nUserInt = 0);			//请求连接(添加至连接列表 加载必要数据)
	virtual bool SyncConnected(const XTopologyID& xSrcID, uint uCacheID, void* pUserData = nullptr, int nUserInt = 0);			//连接成功(加载额外数据)
	virtual bool SyncDisconnect(const XTopologyID& xSrcID, uint uCacheID, void* pUserData = nullptr, int nUserInt = 0);			//断开连接(移除连接列表)

	virtual bool SyncProcessMsg(const XTopologyID& xSrcID, uint uCacheID, const XServerArg& xServerArg, const IMsgStream& msgBase);
	virtual bool SyncProcessMsg(const XTopologyID& xSrcID, uint uCacheID, const XServerArg& xServerArg, StreamBinaryPtr pBuffer);

	virtual bool AsyncSave(const XTopologyID& xSrcID, uint uCacheID,void* pUserData = nullptr, int nUserInt = 0);

	virtual bool AsyncKick (const XTopologyID& xSrcID, uint uCacheID, void* pUserData = nullptr, int nUserInt = 0);
	virtual bool AsyncLogin(const XTopologyID& xSrcID, uint uCacheID, void* pUserData = nullptr, int nUserInt = 0);		//登录成功

	virtual bool SyncSend(const XTopologyID& xSrcID, uint uCacheID, const IMsgStream& msgBase);
	virtual bool SyncSend(const XTopologyID& xSrcID, uint uCacheID, StreamBinaryPtr pBuffer);

	virtual bool SyncUrlResponce(uint uCacheID, CUrlRequestTopologyPtr pRequest);

	virtual bool SyncOperate(const XTopologyID& xSrcID, uint uCacheID, int nUserInt = 0);//自定义操作
	virtual bool SyncOperate(const XTopologyID& xSrcID, uint uCacheID, void* pUserData, int nUserInt = 0);//自定义操作

	virtual bool SyncAllProcessMsg(const XTopologyID& xSrcID, const XServerArg& xServerArg, const IMsgStream& msgBase);
	virtual bool SyncAllProcessMsg(const XTopologyID& xSrcID, const XServerArg& xServerArg, StreamBinaryPtr pBuffer);
	virtual bool SyncAllSave(const XTopologyID& xSrcID = TOPOLOGY_ID_INVAILD, void* pUserData = nullptr, int nUserInt = 0);
	virtual bool SyncAllDestory(const XTopologyID& xSrcID = TOPOLOGY_ID_INVAILD, void* pUserData = nullptr, int nUserInt = 0);
	virtual bool SyncAllOperate(const XTopologyID& xSrcID = TOPOLOGY_ID_INVAILD, int nUserInt = 0);//自定义操作
	virtual bool SyncAllOperate(const XTopologyID& xSrcID, void* pUserData, int nUserInt = 0);	//自定义操作
	virtual bool SyncAllSend(const XTopologyID& xSrcID, StreamBinaryPtr pBuffer);
	virtual bool SyncAllSend(const XTopologyID& xSrcID, const IMsgStream& msgBase);

	virtual bool SyncCalState(uint& uTotal, uint& uVaild, uint& uNormal, uint& uQueue, uint& uDelete, uint& uPerpairing, uint& uCache, uint& uOperateQueue, uint& uDelayOperateQueue) const;//统计缓存的状态(总数，有效数，正常数 低性能 调试用)
	//有锁，外部尽可能不要访问
public:
	virtual IServerCachePtr		FindServerCache(uint uCacheID);

	//以下无锁
public:
	virtual CMutexReadWrite&		GetMutex()const;
	virtual const MapServerCache&	GetServerCache()const;
private:
	virtual ISyncProcesserPtr OnCreateProcesser(int nUserInt, void* pUserData)override;
private:
	virtual bool OnTimeOut(const CTimeNodePtr& pTimeNode)override;
public:
	CServerCacheManager();
	virtual ~CServerCacheManager();
protected:
	CIDMakerUint			_vMakeID;

	bool					_bNeedSave;
	bool					_bAutoDelete;		//自动清理开关
	time_t					_uTimeDelete;		//删除缓存的时间
	time_t					_uTimeCheck;		//检查时间间隔
	CTimeNodePtr			_pTimerCheck;		//检查的计时器

	HServerCache*			_hCacheHandler;
};

NS_TOOL_FRAME_END
