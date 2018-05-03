#include "ITaskMgrThread.h"

NS_TOOL_FRAME_BEGIN

ITaskMgrThread::ITaskMgrThread(void)
{
}

ITaskMgrThread::~ITaskMgrThread(void)
{
}

bool ITaskMgrThread::InitThread()
{
	return true;
}

bool ITaskMgrThread::RunOnceThread()
{
	//执行一次时钟
	RunOnce(100);

	//优先处理所有任务(如果处理了一次任务还有其他任务再处理一次)
	if (!ProcessTask(100))
		ProcessTask(100);

	return true;
}

NS_TOOL_FRAME_END
