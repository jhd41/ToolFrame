#include "ServerCacheManager.h"

#include "ToolFrame.h"

#include "MLoger.h"

#include "IServerCache.h"
#include "MSystem.h"

NS_TOOL_FRAME_BEGIN

CServerCacheManager::CServerCacheManager()
{
	_hCacheHandler = this;

	_bNeedSave = true;

	_bAutoDelete = false;
	_uTimeDelete = 1200;
	_uTimeCheck = 300;
}

CServerCacheManager::~CServerCacheManager()
{
}

bool CServerCacheManager::SyncConnect(const XTopologyID& xSrcID, uint uCacheID, void* pUserData /*= nullptr*/, int nUserInt /*= 0*/)
{
	return SyncCallProcesser<IServerCache>(uCacheID, &IServerCache::SyncConnect, xSrcID, pUserData, nUserInt);
}

bool CServerCacheManager::SyncConnected(const XTopologyID& xSrcID, uint uCacheID, void* pUserData /*= nullptr*/, int nUserInt /*= 0*/)
{
	return SyncCallProcesser<IServerCache>(uCacheID, &IServerCache::SyncConnected, xSrcID, pUserData, nUserInt);
}

bool CServerCacheManager::SyncDisconnect(const XTopologyID& xSrcID, uint uCacheID, void* pUserData /*= nullptr*/, int nUserInt /*= 0*/)
{
	return SyncCallProcesser<IServerCache>(uCacheID, &IServerCache::SyncDisconnect, xSrcID, pUserData, nUserInt);
}

bool CServerCacheManager::AsyncLogin(const XTopologyID& xSrcID, uint uCacheID, void* pUserData /*= nullptr*/, int nUserInt /*= 0*/)
{
	return AsyncCallProcesser<IServerCache>(uCacheID, &IServerCache::SyncLogin, xSrcID,pUserData, nUserInt);
}

bool CServerCacheManager::AsyncKick(const XTopologyID& xSrcID, uint uCacheID, void* pUserData /*= nullptr*/, int nUserInt /*= 0*/)
{
	return AsyncCallProcesser<IServerCache>(uCacheID, &IServerCache::SyncKick, xSrcID, pUserData, nUserInt);
}

bool CServerCacheManager::SyncProcessMsg(const XTopologyID& xSrcID, uint uCacheID, const XServerArg& xServerArg, StreamBinaryPtr pBuffer)
{
	return SyncCallProcesser<IServerCache>(uCacheID, (bool(IServerCache::*)(const XTopologyID&, const XServerArg&, StreamBinaryPtr)) &IServerCache::SyncProcessMsg, xSrcID, xServerArg, pBuffer);
}

bool CServerCacheManager::SyncProcessMsg(const XTopologyID& xSrcID, uint uCacheID, const XServerArg& xServerArg,const IMsgStream& msgBase)
{
	return SyncCallProcesser<IServerCache>(uCacheID, (bool(IServerCache::*)(const XTopologyID&, const XServerArg&, const IMsgStream&)) &IServerCache::SyncProcessMsg, xSrcID, xServerArg, msgBase);
}

bool CServerCacheManager::SyncUrlResponce(uint uCacheID, CUrlRequestTopologyPtr pRequest)
{
	return SyncCallProcesser<IServerCache>(uCacheID, &IServerCache::SyncUrlResponce, pRequest);
}

bool CServerCacheManager::AsyncSave(const XTopologyID& xSrcID, uint uCacheID, void* pUserData /*= nullptr*/, int nUserInt /*= 0*/)
{
	return AsyncCallProcesser<IServerCache>(uCacheID, &IServerCache::SyncSave, xSrcID, pUserData, nUserInt);
}

bool CServerCacheManager::SyncAllSend(const XTopologyID& xSrcID, const IMsgStream& msgBase)
{
	return SyncForEachCallProcesser<IServerCache>((bool(IServerCache::*)(const XTopologyID&, const IMsgStream&))&IServerCache::SyncSend, xSrcID, msgBase);
}

bool CServerCacheManager::SyncAllSend(const XTopologyID& xSrcID, StreamBinaryPtr pBuffer)
{
	return SyncForEachCallProcesser<IServerCache>((bool(IServerCache::*)(const XTopologyID&, StreamBinaryPtr))&IServerCache::SyncSend, xSrcID, pBuffer);
}

bool CServerCacheManager::SyncCalState(uint& uTotal, uint& uVaild, uint& uNormal, uint& uQueue, uint& uDelete, uint& uPerpairing, uint& uCache, uint& uOperateQueue, uint& uDelayOperateQueue) const
{
	return ISyncProcesserManager::SyncCalState(uTotal, uVaild, uNormal, uQueue, uDelete, uPerpairing, uCache,uOperateQueue,uDelayOperateQueue);
}

CMutexReadWrite& CServerCacheManager::GetMutex() const
{
	return ISyncProcesserManager::GetMutex();
}

const CServerCacheManager::MapServerCache& CServerCacheManager::GetServerCache() const
{
	return GetProcesser();
}

IServerCachePtr CServerCacheManager::FindServerCache(uint uCacheID)
{
	CLockRead lock(GetMutex());
	ISyncProcesserPtr pProcesser = FindProcesser(uCacheID);
	if (!pProcesser)return IServerCachePtr();
	
	IServerCache* pCache = pProcesser->ToProcesser<IServerCache>();
	if (!pCache)return IServerCachePtr();

	return pCache->GetCachePtr();
}

bool CServerCacheManager::SyncAllDestory(const XTopologyID& xSrcID /*= TOPOLOGY_ID_INVAILD*/, void* pUserData /*= nullptr*/, int nUserInt /*= 0*/)
{
	return SyncForEachCallProcesser<IServerCache>(&IServerCache::SyncDestory, xSrcID, pUserData, nUserInt);
}

bool CServerCacheManager::SyncAllProcessMsg(const XTopologyID& xSrcID, const XServerArg& xServerArg, const IMsgStream& msgBase)
{
	return SyncForEachCallProcesser<IServerCache>((bool(IServerCache::*)(const XTopologyID&, const XServerArg&, const IMsgStream&)) &IServerCache::SyncProcessMsg, xSrcID, xServerArg, msgBase);
}

bool CServerCacheManager::SyncAllProcessMsg(const XTopologyID& xSrcID, const XServerArg& xServerArg, StreamBinaryPtr pBuffer)
{
	return SyncForEachCallProcesser<IServerCache>((bool(IServerCache::*)(const XTopologyID&, const XServerArg&,StreamBinaryPtr)) &IServerCache::SyncProcessMsg, xSrcID, xServerArg, pBuffer);
}

bool CServerCacheManager::SyncAllSave(const XTopologyID& xSrcID /*= TOPOLOGY_ID_INVAILD*/, void* pUserData /*= nullptr*/, int nUserInt /*= 0*/)
{
	if (!_bNeedSave)return true;
	return SyncForEachCallProcesser<IServerCache>(&IServerCache::SyncSave, xSrcID, pUserData, nUserInt);
}

bool CServerCacheManager::SyncSend(const XTopologyID& xSrcID, uint uCacheID, const IMsgStream& msgBase)
{
	return SyncCallProcesser<IServerCache>(uCacheID, (bool(IServerCache::*)(const XTopologyID&,const IMsgStream&))&IServerCache::SyncSend, xSrcID, msgBase);
}

bool CServerCacheManager::SyncSend(const XTopologyID& xSrcID, uint uCacheID, StreamBinaryPtr pBuffer)
{
	return SyncCallProcesser<IServerCache>(uCacheID, (bool(IServerCache::*)(const XTopologyID&, StreamBinaryPtr))&IServerCache::SyncSend, xSrcID, pBuffer);
}

bool CServerCacheManager::SyncAllOperate(const XTopologyID& xSrcID /*= TOPOLOGY_ID_INVAILD*/, void* pUserData /*= nullptr*/, int nUserInt /*= 0*/)
{
	return SyncForEachCallProcesser<IServerCache>(&IServerCache::SyncOperate, xSrcID, pUserData, nUserInt);
}

bool CServerCacheManager::SyncAllOperate(const XTopologyID& xSrcID /*= TOPOLOGY_ID_INVAILD*/, int nUserInt /*= 0*/)
{
	return SyncAllOperate(xSrcID,nullptr, nUserInt);
}

bool CServerCacheManager::SyncOperate(const XTopologyID& xSrcID, uint uCacheID, void* pUserData /*= nullptr*/, int nUserInt /*= 0*/)
{
	return SyncCallProcesser<IServerCache>(uCacheID, &IServerCache::SyncOperate, xSrcID, pUserData, nUserInt);
}

bool CServerCacheManager::SyncOperate(const XTopologyID& xSrcID, uint uCacheID, int nUserInt /*= 0*/)
{
	return SyncOperate(xSrcID, uCacheID,nullptr, nUserInt);
}

bool CServerCacheManager::SetManagerHandler(HSyncProcesserManager* hHandler)
{
	return ISyncProcesserManager::SetHandler(hHandler);
}

bool CServerCacheManager::SetCacheHandler(HServerCache* hHandler)
{
	_hCacheHandler = hHandler;
	return true;
}

bool CServerCacheManager::SetNeedSave(bool bSave)
{
	_bNeedSave = bSave;
	return true;
}

bool CServerCacheManager::SetAutoDelete(bool bAuto)
{
	_bAutoDelete = bAuto;
	return true;
}

bool CServerCacheManager::SetDeleteTime(time_t uDelete /*= 1200*/)
{
	_uTimeDelete = uDelete;
	return true;
}

bool CServerCacheManager::SetCheckTime(time_t uCheck /*= 300*/)
{
	_uTimeCheck = uCheck;
	return true;
}

bool CServerCacheManager::Init()
{
	if (_pTimerCheck)return false;

	_pTimerCheck = MSystem::Singleton().GetTimeOutQueque().CreateTimerByAfterSec(this, _uTimeCheck, true, _uTimeCheck);
	return true;
}

bool CServerCacheManager::Run(uint64 uMillTime)
{
	return ProcessRetry(uMillTime); 
}

size_t CServerCacheManager::GetVaildCount() const
{
	return ISyncProcesserManager::GetVaildCount();
}

size_t CServerCacheManager::GetNormalCount() const
{
	return ISyncProcesserManager::GetNormalCount();
}

size_t CServerCacheManager::GetTotalCount() const
{
	return GetProcesserSize();
}

size_t CServerCacheManager::GetOperateCount() const
{
	return GetQueueSize();
}

size_t CServerCacheManager::ClearOperateProcess()
{
	return ClearQueueProcess();
}

bool CServerCacheManager::IsCached(uint uCacheID) const
{
	return SyncIsExist(uCacheID);
}

uint CServerCacheManager::SyncCreateMakeID(const XTopologyID& xSrcID,void* pUserData /*= nullptr*/, int nUserInt /*= 0*/)
{
	CLockWrite lock(GetMutex());
	uint uCacheID = _vMakeID.MakeID(_vProcesser);

	ASSERT_LOG_DEBUG_ERR(!ToolFrame::IsHasKey(_vProcesser, uCacheID));

	ISyncProcesserPtr pProcesser = _hHandler->OnCreateProcesser(nUserInt, pUserData);
	if (!pProcesser)return false;

	pProcesser->SetProcesserID(uCacheID);
	pProcesser->SetMgr(this);

	IServerCache* pCache = pProcesser->ToProcesser<IServerCache>();
	if (!pCache)return false;

	pCache->SetCacheHandler(_hCacheHandler);
	pCache->SetUserData(pUserData);
	pCache->SetUserInt(nUserInt);
	

	ASSERT_LOG_ERROR(ToolFrame::Insert(_vProcesser, pCache->GetProcesserID(), pProcesser));

	pCache->SyncCreate(xSrcID, pUserData, nUserInt);
	return uCacheID;
}

bool CServerCacheManager::SyncCreate(const XTopologyID& xSrcID, uint uCacheID, void* pUserData /*= nullptr*/, int nUserInt /*= 0*/)
{
	if (INVALID_ID == uCacheID)return false;

	CLockWrite lock(GetMutex());
	ISyncProcesserPtr pProcesser = ToolFrame::GetPtrValueByKey(_vProcesser, uCacheID);
	if (!pProcesser) {
		pProcesser = _hHandler->OnCreateProcesser(nUserInt, pUserData);

		pProcesser->SetProcesserID(uCacheID);
		pProcesser->SetMgr(this);

		IServerCache* pCache = pProcesser->ToProcesser<IServerCache>();
		if (!pCache)return false;
		
		pCache->SetCacheHandler(_hCacheHandler);
		pCache->SetUserInt(nUserInt);
		pCache->SetUserData(pUserData);

		ASSERT_LOG_ERROR(ToolFrame::Insert(_vProcesser, pCache->GetProcesserID(), pProcesser));

		pCache->SyncCreate(xSrcID, pUserData, nUserInt);
		return true;
	}

	//如果已存在 也得触发创建事件
	IServerCache* pCache = pProcesser->ToProcesser<IServerCache>();
	if (!pCache)return false;
	pCache->SyncCreate(xSrcID, pUserData, nUserInt);
	return true;
}

bool CServerCacheManager::SyncCreate(const XTopologyID& xSrcID, uint uCacheID, int nUserInt)
{
	return SyncCreate(xSrcID, uCacheID, nullptr, nUserInt);
}

bool CServerCacheManager::SyncDestory(const XTopologyID& xSrcID, uint uCacheID, void* pUserData /*= nullptr*/, int nUserInt /*= 0*/)
{
	return SyncCallProcesser<IServerCache>(uCacheID, &IServerCache::SyncDestory, xSrcID, pUserData, nUserInt);
}

ISyncProcesserPtr CServerCacheManager::OnCreateProcesser(int nUserInt, void* pUserData)
{
	return IServerCachePtr(new IServerCache());
}

bool CServerCacheManager::OnTimeOut(const CTimeNodePtr& pTimeNode)
{
	if (_pTimerCheck == pTimeNode)
	{
		//清理所有的缓存
		if (_bAutoDelete)
			SyncAllDestory();
		return true;
	}

	return false;
}

NS_TOOL_FRAME_END
