#include "FunctionQueue.h"

NS_TOOL_FRAME_BEGIN

CFunctionQueue::CFunctionQueue()
{
}

CFunctionQueue::~CFunctionQueue()
{
}

bool CFunctionQueue::Push(bool bBack, IFunctionArgPtr ptr)
{
	return _vFunction.Push(bBack, ptr);
}

bool CFunctionQueue::ProcessOne()
{
	IFunctionArgPtr pOperate = _vFunction.PopFrontPtr();
	if (!pOperate)return false;

	pOperate->Call();
	return true;
}

bool CFunctionQueue::Process(CTimeOut& timeout)
{
	while (!timeout.IsTimeOut()) {
		if (!ProcessOne())
			return true;
	}
	return false;
}

bool CFunctionQueue::ProcessRetry(CTimeOut& timeout)
{
	QueueFunctionArgPtr vFaild;
 	while (!timeout.IsTimeOut()) {
 		IFunctionArgPtr pOperate = _vFunction.PopFrontPtr();
		if (!pOperate)break;
 
		if (!pOperate->Call())
			vFaild.PushBack(pOperate);
 	}
	_vFunction.Splice(vFaild);
 	return _vFunction.Empty();
}

bool CFunctionQueue::Empty() const
{
	return _vFunction.Empty();
}

size_t CFunctionQueue::Size() const
{
	return _vFunction.Size();
}

bool CFunctionQueue::PushBack(IFunctionArgPtr pFunctionArg)
{
	return _vFunction.PushBack(pFunctionArg);
}

IFunctionArgPtr CFunctionQueue::PopFrontPtr()
{
	return _vFunction.PopFrontPtr();
}

bool CFunctionQueue::PushFront(IFunctionArgPtr pFunctionArg)
{
	return _vFunction.PushFront(pFunctionArg);
}

IFunctionArgPtr CFunctionQueue::PopBackPtr()
{
	return _vFunction.PopBackPtr();
}

bool CFunctionQueue::Splice(CFunctionQueue& vQueue, bool bBack /*= true*/)
{
	return _vFunction.Splice(vQueue._vFunction, bBack);
}

bool CFunctionQueue::Clear()
{
	return _vFunction.Clear();
}

CMutexReadWrite& CFunctionQueue::GetMutex() const
{
	return _vFunction.GetMutex();
}

NS_TOOL_FRAME_END

