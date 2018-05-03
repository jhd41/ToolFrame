#include "ISyncProcesserManager.h"

#include "ToolFrame.h"

#include "MLoger.h"

NS_TOOL_FRAME_BEGIN

ISyncProcesserManager::ISyncProcesserManager()
{
	_hHandler = this;
	_xDebugCheck.SetIntervalSec(1);
}

ISyncProcesserManager::~ISyncProcesserManager()
{
}

bool ISyncProcesserManager::SetHandler(HSyncProcesserManager* hHandler)
{
	_hHandler = hHandler;
	return true;
}

bool ISyncProcesserManager::SyncCreate(uint uProcesserID, uint uSecondID /*= INVALID_ID*/, int nUserInt /*= 0*/, void* pUserData /*= nullptr*/)
{
	CLockWrite lock(_vQueue.GetMutex());
	ISyncProcesserPtr pProcesser = ToolFrame::GetPtrValueByKey(_vProcesser, uProcesserID);
	if (!pProcesser) {
		pProcesser = _hHandler->OnCreateProcesser(nUserInt, pUserData);
		pProcesser->SetProcesserID(uProcesserID);
		pProcesser->SetSecondID(uSecondID);
		pProcesser->SetMgr(this);
		if (!AutoInsertProcesser(pProcesser))return false;
	}
	return true;
}

bool ISyncProcesserManager::SyncInsert(ISyncProcesserPtr pProcesser)
{
	CLockWrite lock(_vQueue.GetMutex());
	return AutoInsertProcesser(pProcesser);
}

bool ISyncProcesserManager::SyncInsertMakeProcesserID(ISyncProcesserPtr pProcesser)
{
	CLockWrite lock(_vQueue.GetMutex());
	pProcesser->SetProcesserID(MakeProcesserID());
	return AutoInsertProcesser(pProcesser);
}

bool ISyncProcesserManager::SyncInsertMakeSecondID(ISyncProcesserPtr pProcesser)
{
	CLockWrite lock(_vQueue.GetMutex());
	pProcesser->SetSecondID(MakeSecondID());
	return AutoInsertProcesser(pProcesser);
}

bool ISyncProcesserManager::SyncIsExist(uint uProcesserID) const
{
	if (INVALID_ID == uProcesserID)return false;

	CLockRead lock(_vQueue.GetMutex());
	return ToolFrame::IsHasKey(_vProcesser, uProcesserID);
}

bool ISyncProcesserManager::SyncIsExistSecondID(uint uSecondID) const
{
	if (INVALID_ID == uSecondID)return false;

	CLockRead lock(_vQueue.GetMutex());
	return ToolFrame::IsHasKey(_vSecond, uSecondID);
}

bool ISyncProcesserManager::ProcessRetry(uint64 uMillTime)
{
	CTimeOut timeout(uMillTime);

	if (!_vQueue.ProcessOperate(timeout))return false;

	//检查
	ASSERT_LOG_DEBUG_ERR(CheckDebug());
	return !timeout.IsTimeOut();
}

bool ISyncProcesserManager::SyncInsertSecond(uint uSecondID, ISyncProcesserPtr pProcesser)
{
	CLockWrite lock(_vQueue.GetMutex());
	return InsertSecond(uSecondID, pProcesser);
}

bool ISyncProcesserManager::SyncRemoveSecond(uint uSecondID)
{
	CLockWrite lock(_vQueue.GetMutex());
	return RemoveSecond(uSecondID);
}

bool ISyncProcesserManager::DebugCheck()
{
	//检查是不是所有的有操作的缓存 都在操作队列
	//统计(需要堵住所有操作 这样才正确)
 	CLockWrite lock(_vQueue.GetMutex());
 
 	MapSyncProcesser::const_iterator itr;
 	foreach(itr, _vProcesser) {
 		ISyncProcesserPtr pProcesser = itr->second;
 		ASSERT_LOG_ERROR(pProcesser);
 
 		//如果有操作 但不在队列
 		if (!pProcesser->GetOperateQueue().IsOperateEmpty() && _vQueue.IsOperateEmpty())
 		{
 			LOG_DEBUG_ERR("Queue ProcesserID:" << pProcesser->GetProcesserID()<<" OperateSize:"<< pProcesser->GetOperateQueue().GetOperateSize()<<" DelaySize:"<<pProcesser->GetOperateQueue().GetOperateDelaySize());
 			return false;
 		}
 
 		//如果已标记删除 但不在操作队列
 		if (pProcesser->IsMarkDeleted() && _vQueue.IsOperateEmpty())
 		{
 			LOG_DEBUG_ERR("Delete ProcesserID:" << pProcesser->GetProcesserID());
 			return false;
 		}
 
 		//如果已正常 但延迟队列还有
 		if (pProcesser->IsNormal() && !pProcesser->GetOperateQueue().IsOperateDelayEmpty())
 		{
 			LOG_DEBUG_ERR("Normal ProcesserID:" << pProcesser->GetProcesserID());
 			return false;
 		}
 	}
	return true;
}

bool ISyncProcesserManager::ReqOperate(ISyncProcesserPtr pProcesser)
{
	if (pProcesser->GetOperateQueue().IsOperateEmpty())return false;
	_vQueue.PushOperateRead(ToolFrame::Bind(&ISyncProcesserManager::OnProcesserOperate, this), pProcesser);
	return true;
}

bool ISyncProcesserManager::ReqDelete(ISyncProcesserPtr pProcesser)
{
	if (!pProcesser->IsMarkDeleted())return false;
	_vQueue.PushOperateWrite(ToolFrame::Bind(&ISyncProcesserManager::OnProcesserDelete, this), pProcesser);
	return true;
}

bool ISyncProcesserManager::ReqInsertSecond(uint uSecondID, ISyncProcesserPtr pProcesser)
{
	if (INVALID_ID == uSecondID)return false;
	_vQueue.WriteOperate(ToolFrame::Bind(&ISyncProcesserManager::OnInsertSecond, this), uSecondID, pProcesser);
	return true;
}

bool ISyncProcesserManager::ReqRemoveSecond(uint uSecondID)
{
	if (INVALID_ID == uSecondID)return false;
	_vQueue.WriteOperate(ToolFrame::Bind(&ISyncProcesserManager::OnRemoveSecond, this), uSecondID);
	return true;
}

bool ISyncProcesserManager::AutoInsertProcesser(ISyncProcesserPtr pProcesser)
{
	if (!InsertProcesser(pProcesser))return false;
	InsertSecond(pProcesser->GetSecondID(),pProcesser);
	return true;
}

bool ISyncProcesserManager::AutoRemoveProcesser(ISyncProcesserPtr pProcesser)
{
	if (!RemoveProcesser(pProcesser->GetProcesserID()))return false;
	RemoveSecond(pProcesser->GetSecondID());
	return true;
}

bool ISyncProcesserManager::InsertProcesser(ISyncProcesserPtr pProcesser)
{
	if (INVALID_ID == pProcesser->GetProcesserID())return false;
	return ToolFrame::Insert(_vProcesser, pProcesser->GetProcesserID(), pProcesser);
}

bool ISyncProcesserManager::RemoveProcesser(uint uProcesserID)
{
	if (INVALID_ID == uProcesserID)return false;
	return ToolFrame::EraseByKey(_vProcesser, uProcesserID)>0;
}

ISyncProcesserPtr ISyncProcesserManager::FindProcesser(uint uProcesserID)
{
	if (INVALID_ID == uProcesserID)return ISyncProcesserPtr();

	return ToolFrame::GetPtrValueByKey(_vProcesser, uProcesserID);
}

ISyncProcesserPtr ISyncProcesserManager::FindProcesserSecond(uint uSecondID)
{
	if (INVALID_ID == uSecondID)return ISyncProcesserPtr();

	return ToolFrame::GetPtrValueByKey(_vSecond, uSecondID);
}

bool ISyncProcesserManager::InsertSecond(uint uSecondID,ISyncProcesserPtr pProcesser )
{
	if (INVALID_ID == uSecondID)return false;
	return ToolFrame::Insert(_vSecond, uSecondID, pProcesser);
}

bool ISyncProcesserManager::RemoveSecond(uint uSecondID)
{
	if (INVALID_ID == uSecondID)return false;
	return ToolFrame::EraseByKey(_vSecond, uSecondID)>0;
}

const ISyncProcesserManager::MapSyncProcesser& ISyncProcesserManager::GetProcesserSecond() const
{
	return _vSecond;
}

const ISyncProcesserManager::MapSyncProcesser& ISyncProcesserManager::GetProcesser() const
{
	return _vProcesser;
}

bool ISyncProcesserManager::OnProcesserOperate(ISyncProcesserPtr pProcesser)
{
	return pProcesser->GetOperateQueue().ProcessOperate(100);
}

bool ISyncProcesserManager::OnProcesserDelete(ISyncProcesserPtr pProcesser)
{
	//如果又没有Delete了跳过不处理
	{
		if (!pProcesser->IsMarkDeleted())
			return true;

		if (!pProcesser->GetOperateQueue().IsOperateEmpty())
			return false;

		if (pProcesser->IsVaild())
			return false;

		ASSERT_LOG_ERROR(AutoRemoveProcesser(pProcesser));
	}

	_hHandler->OnDestoryProcesser(pProcesser);
	return true;
}

bool ISyncProcesserManager::OnInsertSecond(uint uSecondID, ISyncProcesserPtr pProcesser)
{
	InsertSecond(uSecondID, pProcesser);
	return true;
}

bool ISyncProcesserManager::OnRemoveSecond(uint uSecondID)
{
	RemoveSecond(uSecondID);
	return true;
}

uint ISyncProcesserManager::MakeSecondID()
{
	return _xMaker.MakeID(_vProcesser);
}

uint ISyncProcesserManager::MakeProcesserID()
{
	return _xMakerSecond.MakeID(_vSecond);
}

size_t ISyncProcesserManager::GetProcesserSize() const
{
	CLockRead lock(_vQueue.GetMutex());
	return _vProcesser.size();
}

size_t ISyncProcesserManager::GetSecondSize() const
{
	CLockRead lock(_vQueue.GetMutex());
	return _vSecond.size();
}

size_t ISyncProcesserManager::GetQueueSize() const
{
	return _vQueue.GetOperateSize();
}

size_t ISyncProcesserManager::GetVaildCount() const
{
	return _uVaild;
}

size_t ISyncProcesserManager::GetNormalCount() const
{
	return _uNormal;
}

size_t ISyncProcesserManager::ClearQueueProcess()
{
	return _vQueue.ClearProcessCount();
}

CMutexReadWrite& ISyncProcesserManager::GetMutex() const
{
	return _vQueue.GetMutex();
}

bool ISyncProcesserManager::CheckDebug()
{
	if (!_xDebugCheck.TryTimeOutRestart())return true;

	return DebugCheck();
}

bool ISyncProcesserManager::SyncMarkNormal()
{
	_uNormal.AddCount();
	return true;
}

bool ISyncProcesserManager::SyncClearNormal()
{
	_uNormal.ReduceCount();
	return true;
}

bool ISyncProcesserManager::SyncMarkVaild()
{
	_uVaild.AddCount();
	return true;
}

bool ISyncProcesserManager::SyncClearVaild()
{
	_uVaild.ReduceCount();
	return true;
}

bool ISyncProcesserManager::SyncCalState(uint& uTotal, uint& uVaild, uint& uNormal, uint& uQueue, uint& uDelete, uint& uPerpairing, uint& uCache) const
{
	uQueue = 0;
	uDelete = 0;
	uVaild = 0;
	uNormal = 0;
	uPerpairing = 0;
	uCache = 0;

	//统计(需要堵住所有操作 这样才正确)
	CLockWrite lock(_vQueue.GetMutex());

	MapSyncProcesser::const_iterator itr;
	foreach(itr, _vProcesser) {
		ISyncProcesserPtr pProcesser = itr->second;
		ASSERT_LOG_ERROR(pProcesser);

		if (!pProcesser->GetOperateQueue().IsOperateEmpty())
			++uQueue;

		if (pProcesser->IsMarkDeleted())
			++uDelete;

		if (pProcesser->IsVaild())
			++uVaild;

		if (pProcesser->IsNormal() && !pProcesser->IsVaild())
			++uCache;

		if (pProcesser->IsNormal())
			++uNormal;
		else
			++uPerpairing;//断点调试用
	}

	uTotal = (uint)_vProcesser.size();

	ASSERT_LOG_ERROR(_uVaild == uVaild);
	ASSERT_LOG_ERROR(_uNormal == uNormal);
	ASSERT_LOG_ERROR(uPerpairing + uNormal == uTotal);
	return true;
}

NS_TOOL_FRAME_END
