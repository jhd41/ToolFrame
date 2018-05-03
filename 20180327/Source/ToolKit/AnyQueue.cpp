#include "AnyQueue.h"

NS_TOOL_FRAME_BEGIN

CAnyQueue::CAnyQueue()
{
}


CAnyQueue::~CAnyQueue()
{
}

bool CAnyQueue::ProcessOne()
{
	IAnyArgPtr pOperate = _vOperate.PopFrontPtr();
	if (!pOperate)return false;

	pOperate->Call();
	return true;
}

bool CAnyQueue::Process(CTimeOut& timeout)
{
	while (!timeout.IsTimeOut()) {
		if (!ProcessOne())
			return true;
	}
	return false;
}

bool CAnyQueue::ProcessRetry(CTimeOut& timeout)
{
	QueueAnyArgPtr vFaild;
 	while (!timeout.IsTimeOut()) {
 		IAnyArgPtr pOperate = _vOperate.PopFrontPtr();
		if (!pOperate)break;
 
		if (!pOperate->Call())
			vFaild.PushBack(pOperate);
 	}
	_vOperate.Splice(vFaild);
 	return _vOperate.Empty();
}

bool CAnyQueue::Empty() const
{
	return _vOperate.Empty();
}

size_t CAnyQueue::Size() const
{
	return _vOperate.Size();
}

bool CAnyQueue::PushBack(IAnyArgPtr pAnyArg)
{
	return _vOperate.PushBack(pAnyArg);
}

IAnyArgPtr CAnyQueue::PopFrontPtr()
{
	return _vOperate.PopFrontPtr();
}

bool CAnyQueue::PushFront(IAnyArgPtr pAnyArg)
{
	return _vOperate.PushFront(pAnyArg);
}

IAnyArgPtr CAnyQueue::PopBackPtr()
{
	return _vOperate.PopBackPtr();
}

bool CAnyQueue::Splice(CAnyQueue& vQueue, bool bBack /*= true*/)
{
	return _vOperate.Splice(vQueue._vOperate, bBack);
}

bool CAnyQueue::Clear()
{
	return _vOperate.Clear();
}

CMutexReadWrite& CAnyQueue::GetMutex() const
{
	return _vOperate.GetMutex();
}

NS_TOOL_FRAME_END

