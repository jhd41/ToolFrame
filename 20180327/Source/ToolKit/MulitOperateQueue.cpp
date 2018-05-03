#include "MulitOperateQueue.h"
#include "MLoger.h"

NS_TOOL_FRAME_BEGIN

CMulitOperateQueue::CMulitOperateQueue()
{
	_bPause = false;

	_bOperateDelay = false;
}

CMulitOperateQueue::~CMulitOperateQueue()
{
}

bool CMulitOperateQueue::ProcessOperate(uint64 uMillTime)
{
	CTimeOut timeout(uMillTime);
	return ProcessOperate(timeout);
}

bool CMulitOperateQueue::ProcessOperate(CTimeOut& timeout)
{
	if (_vOperate.Empty())return true;

	while (!timeout.IsTimeOut()) {
		IFunctionArgPtr pOperate = _vOperate.PopFrontPtr();
		if (!pOperate)return true;

		switch (pOperate->GetUserInt())
		{
			case OPERATOR_READ:
				{
					CLockRead lock(_mutex, true);
					if (!lock.IsLocked()) {
						_vOperate.PushFront(pOperate);
						return false;
					}

					if (IsPauseProcess()) {
						_vOperatePause.PushBack(pOperate);
						continue;
					}

					if (!pOperate->Call() && IsOperateDelay())
						_vOperateDelay.PushBack(pOperate);
				}
				break;
			case OPERATOR_WRITE:
				{
					CLockWrite lock(_mutex, true);
					if (!lock.IsLocked()) {
						_vOperate.PushFront(pOperate);
						return false;
					}

					if (IsPauseProcess()) {
						_vOperatePause.PushBack(pOperate);
						continue;
					}

					if (!pOperate->Call() && IsOperateDelay())
						_vOperateDelay.PushBack(pOperate);
				}
				break;
			default:
				{
					LOG_ERROR_MSG(pOperate->GetUserInt());
				}
		}
	}

	return false;
}

bool CMulitOperateQueue::IsOperateEmpty() const
{
	return _vOperate.Empty();
}

size_t CMulitOperateQueue::GetOperateSize() const
{
	return _vOperate.Size();
}

bool CMulitOperateQueue::PauseProcess()
{
	CLockWrite lock(_mutexQueue);

	if (_bPause)return false;
	_bPause = true;
	return true;
}

size_t CMulitOperateQueue::GetOperateDelaySize()const
{
	return _vOperateDelay.Size();
}

bool CMulitOperateQueue::ResumeProcess()
{
	CLockWrite lock(_mutexQueue);

	if (!_bPause)return false;
	_bPause = false;

	_vOperate.Splice(_vOperatePause, false);
	return true;
}

bool CMulitOperateQueue::IsPauseProcess() const
{
	CLockRead lock(_mutexQueue);
	return _bPause;
}

bool CMulitOperateQueue::Clear()
{
	CLockWrite lock(_mutexQueue);
	_vOperate.Clear();
	return true;
}

bool CMulitOperateQueue::SetOperateDelay(bool bOperateDelay)
{
	CLockWrite lock(_mutexQueue);
	_bOperateDelay = bOperateDelay;
	return true;
}

bool CMulitOperateQueue::IsOperateDelay() const
{
	CLockWrite lock(_mutexQueue);
	return _bOperateDelay;
}

CMutexReadWrite& CMulitOperateQueue::GetMutex() const
{
	return _mutex;
}

bool CMulitOperateQueue::PushOperateDelay(IFunctionArgPtr pAnyArg)
{
	return _vOperateDelay.PushBack(pAnyArg);
}

bool CMulitOperateQueue::SpliceOperateDelay()
{
	return _vOperate.Splice(_vOperateDelay, false);
}

bool CMulitOperateQueue::IsOperateDelayEmpty() const
{
	return _vOperateDelay.Empty();
}

NS_TOOL_FRAME_END