#include "IThread.h"

#include "MacroDefineBoost.h"

#include "ToolFrame.h"
#include "MLoger.h"

#include "ThreadGroup.h"

NS_TOOL_FRAME_BEGIN

IThread::IThread(void)
{
	_bThreadStarted = false;
	_bThreadStoped = true;
	_bAutoRelease = false;
}

IThread::~IThread(void)
{
}

bool IThread::IsThreadStarted() const
{
	CLockRead lock(_mThreadMutex);
	return _bThreadStarted;
}

bool IThread::IsThreadStoped()const
{
	CLockRead lock(_mThreadMutex);
	return _bThreadStoped;
}

bool IThread::SetThreadStarted()
{
	CLockWrite lock(_mThreadMutex);
	_bThreadStarted = true;
	return true;
}

bool IThread::SetThreadStoped()
{
	{
		CLockWrite lock(_mThreadMutex);
		_bThreadStoped = true;
	}

	OnThreadStoped();
	return true;
}

bool IThread::ClearThreadStoped()
{
	CLockWrite lock(_mThreadMutex);
	_bThreadStoped = false;
	return true;
}

bool IThread::StopThread()
{
	if (_bThreadStoped)return true;
	
	if (!ReqStopThread())return false;

	while(!_bThreadStoped)
		ToolFrame::Sleep(10);
	return true;
}

bool IThread::AutoRelease()
{
	CLockWrite lock(_mThreadMutex);
	_bAutoRelease = true;
	return false;
}

bool IThread::IsAutoRelease() const
{
	CLockRead lock(_mThreadMutex);
	return _bAutoRelease;
}

bool IThread::Release()
{
	{
		CLockWrite lock(_mThreadMutex);
		if (_bThreadStarted && !_bThreadStoped) {
			_bAutoRelease = true;
			return true;
		}
	}

	delete this;
	return true;
}

bool IThread::StartThread()
{
	if (!_bThreadStoped)return false;
	if (!ClearThreadStoped())return false;
	
	return true;
}

bool IThread::OnThreadStoped()
{
	return true;
}
NS_TOOL_FRAME_END
