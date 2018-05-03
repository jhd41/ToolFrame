#include "IThreadSafty.h"

#include "MThread.h"

NS_TOOL_FRAME_BEGIN

IThreadSafty::IThreadSafty(void)
{
}

IThreadSafty::~IThreadSafty(void)
{
}

bool IThreadSafty::StartThread( uint uTimeInterval/*=50*/ )
{
	if (!IThreadNew::StartThread(uTimeInterval))return false;

	return MThread::Singleton().AddThread(this);
}

bool ToolFrame::IThreadSafty::SetThreadStoped()
{
	MThread::Singleton().RemoveThread(this);

	return IThreadNew::SetThreadStoped();
}

NS_TOOL_FRAME_END
