#include "ITaskMgr.h"

NS_TOOL_FRAME_BEGIN

ITaskMgr::ITaskMgr(void)
{
}

ITaskMgr::~ITaskMgr(void)
{
}

CTimeOutQueue& ITaskMgr::GetTimeOutQueue() 
{
	return _vTimeQueue;
}

bool ITaskMgr::RunOnce( uint64 uProcessTime )
{
	_vTimeQueue.ProcessTestTimeOut(uProcessTime);
	return true;
}

bool ITaskMgr::ProcessTask( uint64 uProcessTime )
{
	return _vTimeQueue.ProcessTimeOut(uProcessTime);
}

NS_TOOL_FRAME_END
