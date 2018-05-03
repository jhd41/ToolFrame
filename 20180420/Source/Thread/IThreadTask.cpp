#include "IThreadTask.h"
#include "MThread.h"

NS_TOOL_FRAME_BEGIN

IThreadTask::IThreadTask(void)
{
	_pMgrTaskThread = &MThread::Singleton().GetTaskMgr();
}

IThreadTask::~IThreadTask(void)
{
	StopThread();
}

bool IThreadTask::StartThread( int nLoop /*= -1*/,uint uCount /*= 1*/,uint uTimeInterval/*=50*/ )
{
	if (uCount<=0)return false;

	CLockScoped lock(_mutex);
	if (!IThread::StartThread())return false;

	SetThreadStarted();
	return _pMgrTaskThread->AddTask(this,nLoop,uCount,uTimeInterval);
}

bool IThreadTask::ReqStopThread()
{
	CLockScoped lock(_mutex);

	if (IsThreadStarted())
		_pMgrTaskThread->RemoveTask(this);

	SetThreadStoped();
	return true;
}


NS_TOOL_FRAME_END
