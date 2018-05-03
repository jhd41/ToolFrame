#include "ISyncProcesser.h"

#include "ISyncProcesserManager.h"
#include "MLoger.h"

NS_TOOL_FRAME_BEGIN

ISyncProcesser::ISyncProcesser()
{
	_bDelete = false;
	_bNormal = false;
	_bVaild = false;


	SetProcesserID(INVALID_ID);
	SetSecondID(INVALID_ID);
	SetMgrNull();

	SetUserInt(0);
	SetUserDataNull();
}

ISyncProcesser::~ISyncProcesser()
{
}

bool ISyncProcesser::SetOperateDelay(bool bOperateDelay)
{
	return _vQueue.SetOperateDelay(bOperateDelay);
}

bool ISyncProcesser::IsOperateDelay() const
{
	return _vQueue.IsOperateDelay();
}

bool ISyncProcesser::PauseProcess()
{
	return _vQueue.PauseProcess();
}

bool ISyncProcesser::ResumeProcess()
{
	if (!_vQueue.ResumeProcess())return false;
	
	_vQueue.ProcessOperate();

	ReqMgrOperate();
	return true;
}

bool ISyncProcesser::IsPauseProcess() const
{
	return _vQueue.IsPauseProcess();
}

bool ISyncProcesser::MarkDeleted()
{
	//删除
	{
		CLockScoped lock(_vQueue.GetMutex());
		if (_bDelete)return false;
		_bDelete = true;

		//已经标记为删除 则 抛弃其余操作
		_vQueue.Clear();
	}
	
	ReqMgrDelete();
	return true;
}

bool ISyncProcesser::IsMarkDeleted() const
{
	CLockScoped lock(_vQueue.GetMutex());
	return _bDelete;
}

bool ISyncProcesser::ClearDeleted()
{
	CLockScoped lock(_vQueue.GetMutex());
	if (!_bDelete)return false;
	_bDelete = false;
	return true;
}

bool ISyncProcesser::ClearNormal()
{
	CLockScoped lock(_vQueue.GetMutex());
	if (!_bNormal)return false;
	_bNormal = false;
	GetMgr()->SyncClearNormal();
	return true;
}

bool ISyncProcesser::IsNormal() const
{
	CLockScoped lock(_vQueue.GetMutex());
	return _bNormal;
}

bool ISyncProcesser::MarkNormal()
{
	CLockScoped lock(_vQueue.GetMutex());
	if (_bNormal)return false;
	_bNormal = true;

	GetMgr()->SyncMarkNormal();
	_vQueue.SpliceOperateDelay();
	ReqMgrOperate();
	return true;
}

bool ISyncProcesser::MarkVaild()
{
	CLockScoped lock(_vQueue.GetMutex());
	if (_bVaild)return false;
	_bVaild = true;

	GetMgr()->SyncMarkVaild();
	return true;
}

bool ISyncProcesser::IsVaild() const
{
	CLockScoped lock(_vQueue.GetMutex());
	return _bVaild;
}

bool ISyncProcesser::ClearVaild()
{
	CLockScoped lock(_vQueue.GetMutex());
	if (!_bVaild)return false;
	_bVaild = false;

	GetMgr()->SyncClearVaild();
	return true;
}

const CSyncOperateQueue& ISyncProcesser::GetOperateQueue() const
{
	return _vQueue;
}

CSyncOperateQueue& ISyncProcesser::GetOperateQueue()
{
	return _vQueue;
}

ISyncProcesserPtr ISyncProcesser::GetSharePtr()
{
	return shared_from_this();
}

bool ISyncProcesser::ReqMgrOperate()
{
	if (!GetMgr())return false;
	return GetMgr()->ReqOperate(GetSharePtr());
}

bool ISyncProcesser::ReqMgrDelete()
{
	if (!GetMgr())return false;
	return GetMgr()->ReqDelete(GetSharePtr());
}

CMutexRecursive& ISyncProcesser::GetMutex() const
{
	return _vQueue.GetMutex();
}

bool ISyncProcesser::ReqMgrInsertSecond(uint uSecondID)
{
	if (!GetMgr())return false;
	return GetMgr()->ReqInsertSecond(uSecondID,GetSharePtr());
}

bool ISyncProcesser::ReqMgrRemoveSecond(uint uSecondID)
{
	if (!GetMgr())return false;
	return GetMgr()->ReqRemoveSecond(uSecondID);
}

NS_TOOL_FRAME_END
