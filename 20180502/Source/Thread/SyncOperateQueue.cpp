#include "SyncOperateQueue.h"
#include "MDebug.h"

NS_TOOL_FRAME_BEGIN

CSyncOperateQueue::CSyncOperateQueue()
{
	_bPause = false;
	_bProcessContinue = true;

	_bOperateDelay = false;
}

CSyncOperateQueue::~CSyncOperateQueue()
{
}

bool CSyncOperateQueue::ProcessOperate(uint64 uMillTime)
{
	CTimeOut timeout(uMillTime);
	return ProcessOperate(timeout);
}

bool CSyncOperateQueue::ProcessOperate(CTimeOut& timeout)
{
	if (_vOperate.Empty())return true;

	CLockScoped lock(_mutex, true);
	if (!lock.IsLocked())return false;

	while (!timeout.IsTimeOut()) {
		IFunctionArgPtr pOperate = _vOperate.PopFrontPtr();
		if (!pOperate)return true;

		if (IsPauseProcess()) {
			DEBUG_POINT_TAG("CSyncOperateQueue::ProcessOperate Pause");
			_vOperatePause.PushBack(pOperate);
			continue;
		}

		DEBUG_POINT_TAG("CSyncOperateQueue::ProcessOperate");
		if (!pOperate->Call() && IsOperateDelay())
			_vOperateDelay.PushBack(pOperate);
	}

	return false;
}

bool CSyncOperateQueue::IsOperateEmpty() const
{
	return _vOperate.Empty();
}

size_t CSyncOperateQueue::GetOperateSize() const
{
	return _vOperate.Size();
}

bool CSyncOperateQueue::PauseProcess()
{
	CLockScoped lock(_mutex);

	if (_bPause)return false;
	_bPause = true;
	return true;
}

size_t CSyncOperateQueue::GetOperateDelaySize()const
{
	return _vOperateDelay.Size();
}

bool CSyncOperateQueue::ResumeProcess()
{
	CLockScoped lock(_mutex);

	if (!_bPause)return false;
	_bPause = false;

	_vOperate.Splice(_vOperatePause, false);
	return true;
}

bool CSyncOperateQueue::IsPauseProcess() const
{
	CLockScoped lock(_mutex);
	return _bPause;
}

bool CSyncOperateQueue::Clear()
{
	CLockScoped lock(_mutex);
	_vOperate.Clear();
	return true;
}

bool CSyncOperateQueue::SetOperateDelay(bool bOperateDelay)
{
	_bOperateDelay = bOperateDelay;
	return true;
}

bool CSyncOperateQueue::IsOperateDelay() const
{
	return _bOperateDelay;
}

bool CSyncOperateQueue::SetProcessContinue(bool bContinue)
{
	_bProcessContinue = bContinue;
	return true;
}

bool CSyncOperateQueue::IsProcessContinue() const
{
	return _bProcessContinue;
}

CMutexRecursive& CSyncOperateQueue::GetMutex() const
{
	return _mutex;
}

bool CSyncOperateQueue::PushOperateDelay(IFunctionArgPtr pAnyArg)
{
	return _vOperateDelay.PushBack(pAnyArg);
}

bool CSyncOperateQueue::SpliceOperateDelay()
{
	return _vOperate.Splice(_vOperateDelay, false);
}

bool CSyncOperateQueue::IsOperateDelayEmpty() const
{
	return _vOperateDelay.Empty();
}

NS_TOOL_FRAME_END