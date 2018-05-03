#include "ThreadGroup.h"

#include "ToolFrame.h"
#include "MLoger.h"

NS_TOOL_FRAME_BEGIN

CThreadGroup::CThreadGroup(void)
{
}

CThreadGroup::~CThreadGroup(void)
{
	StopThread();
}

bool CThreadGroup::AddThread( IThread* pThread )
{
	if (!pThread)return false;

	_vThread.Push(pThread);
	return true;
}

bool CThreadGroup::RemoveThread( IThread* pThread )
{
	if (!pThread)return false;

	_vThread.EraseByValue(pThread);
	return true;
}

bool CThreadGroup::ReleaseThread(IThread* pThread)
{
	if (!pThread)return false;
	if (RemoveThread(pThread)) {
		_vCreator.EraseObj(pThread);
		pThread->Release();
	}
	return true;
}

bool CThreadGroup::RemoveThread()
{
	StopThread();

	_vThread.Clear();
	return true;
}

bool CThreadGroup::IsEmpty() const
{
	return _vThread.Empty();
}


bool CThreadGroup::StartThread()
{
	CLockRead lockRead(_vThread.GetMutex());

	ListThread::StdList::const_iterator itr;
	foreach(itr,_vThread.GetList()){
		IThread* pThread = *itr;
		ASSERT_LOG_ERROR(pThread);

		pThread->StartThread();
	}

	return true;
}

bool CThreadGroup::StopThread()
{
	if (!ReqStopThread())return false;

	//等待所有的线程退出
	while(!IsAllThreadStoped())
		ToolFrame::Sleep(10);

	return true;
}

bool CThreadGroup::IsAllThreadStoped() const
{
	CLockRead lockRead(_vThread.GetMutex());

	ListThread::StdList::const_iterator itr;
	foreach(itr,_vThread.GetList()){
		IThread* pThread = *itr;
		ASSERT_LOG_ERROR(pThread);

		if(!pThread->IsThreadStoped())
			return false;
	}

	return true;
}

bool CThreadGroup::ReqStopThread()const
{
	CLockRead lockRead(_vThread.GetMutex());

	ListThread::StdList::const_iterator itr;
	foreach(itr,_vThread.GetList()){
		IThread* pThread = *itr;
		ASSERT_LOG_ERROR(pThread);

		pThread->ReqStopThread();
	}

	return true;
}

size_t CThreadGroup::GetCount() const
{
	return _vThread.Size();
}

IThread* CThreadGroup::GetFrontThread()
{
	return _vThread.FrontPtr();
}

IThread* CThreadGroup::GetBackThread()
{
	return _vThread.BackPtr();
}

bool CThreadGroup::ReqStopFrontThread()
{
	CLockRead lockRead(_vThread.GetMutex());

	IThread* pThread = ToolFrame::GetFrontPtr(_vThread.GetList());
	if (!pThread)return false;

	pThread->ReqStopThread();
	return true;
}

bool CThreadGroup::ReqStopBackThread()
{
	CLockRead lockRead(_vThread.GetMutex());

	IThread* pThread = ToolFrame::GetBackPtr(_vThread.GetList());
	if (!pThread)return false;

	pThread->ReqStopThread();
	return true;
}

bool CThreadGroup::ReleaseFrontThread()
{
	CLockWrite lockRead(_vThread.GetMutex());

	IThread* pThread = ToolFrame::PopFrontPtr(_vThread.GetList());
	if (!pThread)return false;

	_vCreator.EraseObj(pThread);
	pThread->ReqStopThread();
	pThread->Release();
	return true;
}

bool CThreadGroup::ReleaseBackThread()
{
	CLockWrite lockRead(_vThread.GetMutex());

	IThread* pThread = ToolFrame::PopBackPtr(_vThread.GetList());
	if (!pThread)return false;

	_vCreator.EraseObj(pThread);
	pThread->ReqStopThread();
	pThread->Release();
	return true;
}

bool CThreadGroup::IsFrontThreadStarted() const
{
	CLockRead lockRead(_vThread.GetMutex());

	IThread* pThread = ToolFrame::GetFrontPtr(_vThread.GetList());
	if (!pThread)return false;

	return pThread->IsThreadStarted();
}

bool CThreadGroup::IsBackThreadStarted() const
{
	CLockRead lockRead(_vThread.GetMutex());

	IThread* pThread = ToolFrame::GetBackPtr(_vThread.GetList());
	if (!pThread)return false;

	return pThread->IsThreadStarted();
}

NS_TOOL_FRAME_END
