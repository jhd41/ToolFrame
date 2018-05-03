#include "TimeBar.h"
#include "ToolStd.h"
#include "MLoger.h"

#include "TimeOutQueue.h"
#include "TimeOut.h"

NS_TOOL_FRAME_BEGIN

CTimeBar::CTimeBar(void)
{
	SetParent(nullptr);
}

CTimeBar::~CTimeBar(void)
{
}

bool CTimeBar::IsEmpty() const
{
	return _vQueue.Empty();
}

bool CTimeBar::PushTime( CTimeNodePtr& pTime )
{
	_vQueue.Push(pTime);
	return true;
}

bool CTimeBar::Process( uint64 uTimeNow,uint64 uTimeProcess )
{
	CLockWrite lock(_vQueue.GetMutex(),true);
	if (!lock.IsLocked())return false;

	CTimeOut tTimeOut(uTimeProcess);
	while(!tTimeOut.IsTimeOut()){
		CTimeNodePtr pNodeTime = ToolFrame::GetFrontPtr(_vQueue.GetList());
		if (!pNodeTime)return false;

		CLockScoped lock(pNodeTime->GetMutex());

		//若还没有超时 则结算完成
		if (pNodeTime->IsEnable() && pNodeTime->GetTimeOut() >= uTimeNow)
			return false;

		ToolFrame::PopFront(_vQueue.GetList());

		if (pNodeTime->IsEnable())
		{
			ASSERT_LOG_ERROR(GetParent()->AddTimeOut(pNodeTime));
		}
	}

	return true;
}

bool CTimeBar::AddOutTime( uint64 uTimePaused )
{
	CLockWrite lock(_vQueue.GetMutex());
	QueueTime::StdList::const_iterator itr;
	foreach(itr,_vQueue.GetList()){
		CTimeNodePtr pNodeTime = *itr;
		ASSERT_LOG_ERROR(pNodeTime);

		CLockScoped lock(pNodeTime->GetMutex());

		pNodeTime->SetTimeOut(pNodeTime->GetTimeOut() + uTimePaused);
	}
	return true;
}

NS_TOOL_FRAME_END
