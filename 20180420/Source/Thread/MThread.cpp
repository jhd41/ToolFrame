#include "MThread.h"

NS_TOOL_FRAME_BEGIN

MThread::MThread(void)
{
}

MThread::~MThread(void)
{
	Stop();
}

CElasticThreadManager& MThread::GetElasticMgr()
{
	return _mgrElastic;
}

CTaskThreadManager& MThread::GetTaskMgr()
{
	return _mgrTask;
}

bool MThread::Stop()
{
	_mgrElastic.Stop();
	_mgrTask.Stop();
	_vThread.StopThread();
	return true;
}

bool MThread::AddThread( IThread* pThread )
{
	return _vThread.AddThread(pThread);
}

bool MThread::RemoveThread( IThread* pThread )
{
	return _vThread.RemoveThread(pThread);
}

NS_TOOL_FRAME_END
