#include "ITaskMgrThread.h"

NS_TOOL_FRAME_BEGIN

ITaskMgrThread::ITaskMgrThread(void)
{
}

ITaskMgrThread::~ITaskMgrThread(void)
{
}

bool ToolFrame::ITaskMgrThread::InitThread()
{
	return true;
}

bool ToolFrame::ITaskMgrThread::RunOnceThread()
{
	//ִ��һ��ʱ��
	RunOnce(100);

	//���ȴ�����������(���������һ�����������������ٴ���һ��)
	if (ProcessTask(100))
		ProcessTask(100);

	return true;
}

NS_TOOL_FRAME_END
