#include "TimeOutQueue.h"
#include "ToolFrame.h"
#include "MLoger.h"

NS_TOOL_FRAME_BEGIN

CTimeOutQueue::CTimeOutQueue(void)
{
	_pTimeOutQueue = nullptr;
	_bPaused = false;

	SetInterface(TIME_MODE_REAL);
}

CTimeOutQueue::~CTimeOutQueue(void)
{
	DeleteInterface();
}

CTimeNodePtr CTimeOutQueue::CreateTimerByAfterSec(HTimeOut* pCallBack, time_t uTimeAfter,bool bLoop,time_t uTimeDelay )
{
	ASSERT_LOG_ERROR(pCallBack);
	if (!pCallBack) return CTimeNodePtr();

	return CreateTimerByAfterMil(pCallBack,uTimeAfter * 1000,bLoop,uTimeDelay * 1000);
}

CTimeNodePtr CTimeOutQueue::CreateTimerByAfterMil( HTimeOut* pCallBack,UINT64 uTimeAfter,bool bLoop /*= false*/,UINT64 uTimeDelay/*=0*/ )
{
	ASSERT_LOG_ERROR(pCallBack);
	if (!pCallBack) return CTimeNodePtr();

	CTimeNodePtr ptr(new CTimeNode());
	ASSERT_LOG_ERROR(ptr->Init(bLoop,uTimeDelay,pCallBack));

	//添加到超时队列
	ASSERT_LOG_ERROR(AddTimerAfter(ptr,uTimeAfter));
	return ptr;
}

bool CTimeOutQueue::ClearEmptyTimebar()
{
	ClearEmptyTimebarAfter();
	ClearEmptyTimebarPoint();
	return true;
}

bool CTimeOutQueue::RemoveTimer( CTimeNodePtr& pTimeNode )
{
	if (!pTimeNode)return false;
	return pTimeNode->SetInvaild();
}

bool CTimeOutQueue::AddTimerAfter( CTimeNodePtr& pTimeNode,UINT64 uTimeAfter )
{
	//计算 超时时间
	pTimeNode->SetTimeOut(GetModeTimeNow() + uTimeAfter);
	
	//找到合适的TimeBar丢进去
	{
		CLockRead lock(_vTimeBarAfter.GetMutex());
		CTimeBarPtr pTimeBar = ToolFrame::GetPtrValueByKey(_vTimeBarAfter.GetMap(), uTimeAfter);
		if (pTimeBar)
			return pTimeBar->PushTime(pTimeNode);
	}

	//没有找到
	CLockWrite lock(_vTimeBarAfter.GetMutex());
	CTimeBarPtr pTimeBar = ToolFrame::GetPtrValueByKey(_vTimeBarAfter.GetMap(), uTimeAfter);
	if (!pTimeBar)
	{
		CTimeBarPtr ptr(new CTimeBar());
		ASSERT_LOG_ERROR(ptr);
		ptr->SetParent(this);

		ASSERT_LOG_ERROR(ToolFrame::Insert(_vTimeBarAfter.GetMap(), uTimeAfter, ptr));
		pTimeBar = ptr;

		//安全性检测
		ASSERT_LOG_ERROR(_vTimeBarAfter.GetMap().size() <= 1000);
	}

	ASSERT_LOG_ERROR(pTimeBar);
	return pTimeBar->PushTime(pTimeNode);
}

bool CTimeOutQueue::AddTimeOut( CTimeNodePtr ptr )
{
	_vTimeOut.Push(ptr);
	return true;
}

bool CTimeOutQueue::TestTimeOut( uint64 uTimeNow,uint64 uTimeProcess )
{
	if (IsPausing())return false;

	bool bTimeOut = false;
	CTimeOut tTimeOut(uTimeProcess);
	
	bTimeOut |= TestTimeOutPoint(uTimeNow,tTimeOut);
	bTimeOut |= TestTimeOutAfter(uTimeNow,tTimeOut);
	return bTimeOut;
}

bool CTimeOutQueue::TestTimeOut( uint64 uTimeProcess )
{
	return TestTimeOut(GetModeTimeNow(),uTimeProcess);
}

bool CTimeOutQueue::ProcessTimeOut(uint64 uTimeProcess)
{
	CTimeOut tTimeOut(uTimeProcess);
	while (!tTimeOut.IsTimeOut())
	{
		CTimeNodePtr pNodeTime = _vTimeOut.PopFrontPtr();
		if (!pNodeTime)return false;

		//回调
		{
			CLockScoped lock(pNodeTime->GetMutex());

			if (!pNodeTime->IsEnable())
				continue;

			//回调
			ASSERT_LOG_ERROR(pNodeTime->GetHandler());
			ASSERT_LOG_ERROR(pNodeTime->GetHandler()->OnTimeOut(pNodeTime));

			if (pNodeTime->IsLoop())
			{
				ASSERT_LOG_ERROR(AddTimerAfter(pNodeTime, pNodeTime->GetTimeDelay()));
			}
		}
	}

	return true;
}

bool CTimeOutQueue::Pause()
{
	if (IsPausing())return false;
	
	if (!_pTimeOutQueue->Pause())return false;
	_bPaused = true;
	return true;
}

bool CTimeOutQueue::Resume()
{
	if (!IsPausing())return false;

	if (!_pTimeOutQueue->Resume())return false;
	_bPaused = false;
	return true;
}

bool CTimeOutQueue::IsPausing() const
{
	return _bPaused;
}

CTimeNodePtr CTimeOutQueue::CreateTimerByPointSec( HTimeOut* pCallBack,time_t uTimePoint,bool bLoop /*= false*/,UINT64 uTimeDelay/*=0*/ )
{
	ASSERT_LOG_ERROR(pCallBack);
	if (!pCallBack) return CTimeNodePtr();

	return CreateTimerByPointMil(pCallBack,(uint64)uTimePoint * 1000,bLoop,uTimeDelay * 1000);
}

CTimeNodePtr CTimeOutQueue::CreateTimerByPointMil( HTimeOut* pCallBack,UINT64 uTimePoint,bool bLoop /*= false*/,UINT64 uTimeDelay/*=0*/ )
{
	ASSERT_LOG_ERROR(pCallBack);
	if (!pCallBack) return CTimeNodePtr();

	CTimeNodePtr ptr(new CTimeNode());
	ASSERT_LOG_ERROR(ptr->Init(bLoop,uTimeDelay,pCallBack));

	//添加到超时队列
	ASSERT_LOG_ERROR(AddTimerPoint(ptr,uTimePoint));
	return ptr;
}

bool CTimeOutQueue::AddTimerPoint( CTimeNodePtr& pTimeNode,UINT64 uTimePoint )
{
	//计算 超时时间
	pTimeNode->SetTimeOut(uTimePoint);

	//找到合适的TimeBar丢进去
	{
		CLockRead lock(_vTimeBarPoint.GetMutex());
		CTimeBarPtr pTimeBar = ToolFrame::GetPtrValueByKey(_vTimeBarPoint.GetMap(), uTimePoint);
		if (pTimeBar)
			return pTimeBar->PushTime(pTimeNode);
	}

	//没有找到合适的TimeBar
	CLockWrite lock(_vTimeBarPoint.GetMutex());
	CTimeBarPtr pTimeBar = ToolFrame::GetPtrValueByKey(_vTimeBarPoint.GetMap(), uTimePoint);
	if (!pTimeBar)
	{
		CTimeBarPtr ptr(new CTimeBar());
		ASSERT_LOG_ERROR(ptr);
		ptr->SetParent(this);

		ASSERT_LOG_ERROR(ToolFrame::Insert(_vTimeBarPoint.GetMap(), uTimePoint, ptr));
		pTimeBar = ptr;
	}

	ASSERT_LOG_ERROR(pTimeBar);
	return pTimeBar->PushTime(pTimeNode);
}

bool CTimeOutQueue::ClearEmptyTimebarAfter()
{
	CLockWrite lock(_vTimeBarAfter.GetMutex());

	MapTimeBar::StdMap& vMap = _vTimeBarAfter.GetMap();
	MapTimeBar::StdMap::iterator itr = vMap.begin();
	while(itr != vMap.end()){
		CTimeBarPtr pTimeBar = itr->second;
		ASSERT_LOG_ERROR(pTimeBar);
		if (pTimeBar->IsEmpty())
		{
			itr = ToolFrame::EraseByItr(vMap,itr);
		}else{
			++itr;
		}
	}

	return true;
}

bool CTimeOutQueue::ClearEmptyTimebarPoint()
{
	CLockWrite lock(_vTimeBarPoint.GetMutex());

	MapTimeBar::StdMap& vMap = _vTimeBarPoint.GetMap();
	MapTimeBar::StdMap::iterator itr = vMap.begin();
	while(itr != vMap.end()){
		CTimeBarPtr pTimeBar = itr->second;
		ASSERT_LOG_ERROR(pTimeBar);
		if (pTimeBar->IsEmpty())
		{
			itr = ToolFrame::EraseByItr(vMap,itr);
		}else{
			++itr;
		}
	}

	return true;
}

bool CTimeOutQueue::TestTimeOutAfter( uint64 uTimeNow,const CTimeOut& tTimeOut )
{
	if (IsPausing())return false;
	
	//算法备注:
	//虽然力求时间总和都不超时,但是为了能够使得超时队列的每一项都能够有相同
	CLockRead lock(_vTimeBarAfter.GetMutex());

	if (ToolFrame::IsEmpty(_vTimeBarAfter.GetMap()))return false;

	uint64	uTimeAvg = tTimeOut.TimeRemaining() / _vTimeBarAfter.GetMap().size();

	MapTimeBar::StdMap::const_iterator itr;
	foreach(itr,_vTimeBarAfter.GetMap()){
		if (tTimeOut.IsTimeOut())
			return true;

		CTimeBarPtr pTimeBar = itr->second;
		ASSERT_LOG_ERROR(pTimeBar);
		pTimeBar->Process(uTimeNow,uTimeAvg);
	}
	return false;
}

bool CTimeOutQueue::TestTimeOutPoint( uint64 uTimeNow,const CTimeOut& tTimeOut )
{
	if (IsPausing())return false;

	bool bClearEmptyBar=false;
	{
		//算法备注:
		//由于时间已经排序，所以只需要计算第一个就可以了。
		CLockRead lock(_vTimeBarPoint.GetMutex());

		MapTimeBar::StdMap::const_iterator itr;
		foreach(itr,_vTimeBarPoint.GetMap()){
			if (tTimeOut.IsTimeOut())
				return true;

			uint64 uTimePoint = itr->first;
			if (uTimePoint >= uTimeNow)
				break;

			CTimeBarPtr pTimeBar = itr->second;
			ASSERT_LOG_ERROR(pTimeBar);

			pTimeBar->Process(uTimeNow,tTimeOut.TimeRemaining());

			if (pTimeBar->IsEmpty())
				bClearEmptyBar = true;
		}
	}
	if (bClearEmptyBar)
		ClearTimeOutTimeBarPoint(uTimeNow);
	return false;
}

bool CTimeOutQueue::ResumeAfter( uint64 uTimePaused )
{
	CLockWrite lock(_vTimeBarAfter.GetMutex());

	MapTimeBar::StdMap& vMap = _vTimeBarAfter.GetMap();
	MapTimeBar::StdMap::iterator itr = vMap.begin();
	foreach(itr,vMap){
		CTimeBarPtr pTimeBar = itr->second;
		ASSERT_LOG_ERROR(pTimeBar);
		pTimeBar->AddOutTime(uTimePaused);
	}
	return true;
}

bool CTimeOutQueue::ResumePoint( uint64 uTimePaused )
{
	CLockWrite lock(_vTimeBarPoint.GetMutex());

	MapTimeBar::StdMap vMapNew;

	MapTimeBar::StdMap& vMapOld = _vTimeBarPoint.GetMap();
	MapTimeBar::StdMap::iterator itr = vMapOld.begin();
	foreach(itr,vMapOld){
		uint64		uTimePoint=itr->first;
		CTimeBarPtr pTimeBar = itr->second;
		ASSERT_LOG_ERROR(pTimeBar);

		pTimeBar->AddOutTime(uTimePaused);
		ASSERT_LOG_ERROR(ToolFrame::Insert(vMapNew,uTimePoint,pTimeBar));
	}
	_vTimeBarPoint.SetMap(vMapNew);

	return true;
}

bool CTimeOutQueue::ClearTimeOutTimeBarPoint(uint64 uTimeNow)
{
	if (_vTimeBarPoint.Empty())return false;

	CLockWrite(_vTimeBarPoint.GetMutex());

	MapTimeBar::StdMap& vMap = _vTimeBarPoint.GetMap();
	MapTimeBar::StdMap::iterator itr = vMap.begin();
	while(itr != vMap.end()){
		uint64 uTimePoint = itr->first;
		if (uTimePoint >= uTimeNow)
			break;
		CTimeBarPtr pTimeBar = itr->second;
		ASSERT_LOG_ERROR(pTimeBar);
		if (pTimeBar->IsEmpty())
		{
			itr = ToolFrame::EraseByItr(vMap,itr);
		}else{
			++itr;
		}
	}

	return true;
}

bool CTimeOutQueue::SetInterface( ETimeMode eTimeMode )
{
	DeleteInterface();

	ITimeOutQueue* pTimeOutQueue = nullptr;
	switch (eTimeMode)
	{
	case TIME_MODE_REAL:
		pTimeOutQueue = new CTimeOutQueueReal();
		break;
	case TIME_MODE_SEQ:
		pTimeOutQueue = new CTimeOutQueueSeq();
		break;
	}

	if (!pTimeOutQueue)return false;
	
	//初始化
	pTimeOutQueue->SetTimeOutQueue(this);

	//赋值
	_pTimeOutQueue = pTimeOutQueue;
	return true;
}

uint64 CTimeOutQueue::SetModeTimeNow( uint64 uTimeNow )
{
	if (!_pTimeOutQueue)return 0;
	return _pTimeOutQueue->SetTimeNow(uTimeNow);
}

uint64 CTimeOutQueue::GetModeTimeNow() const
{
	if (!_pTimeOutQueue)return 0;
	return _pTimeOutQueue->GetTimeNow();
}

bool CTimeOutQueue::SetInterface( ITimeOutQueue* pTimeOutQueue )
{
	if (!pTimeOutQueue)return false;

	_pTimeOutQueue = pTimeOutQueue;
	return true;
}

int CTimeOutQueue::GetTimeMode() const
{
	if (!_pTimeOutQueue)return INVALID_ID;
	return _pTimeOutQueue->GetTimeMode();
}

bool CTimeOutQueue::DeleteInterface()
{
	if (!_pTimeOutQueue)return true;

	delete _pTimeOutQueue;
	_pTimeOutQueue = nullptr;
	return true;
}

ITimeOutQueue* CTimeOutQueue::GetInterface() const
{
	return _pTimeOutQueue;
}

//////////////////////////////////////////////////////////////////////////
ITimeOutQueue::ITimeOutQueue()
{
	_eTimeMode = INVALID_ID;
	_pTimeOutQueue = nullptr;
}

ITimeOutQueue::~ITimeOutQueue()
{

}

uint64 ITimeOutQueue::GetTimeNow() const
{
	return 0;
}

uint64 ITimeOutQueue::SetTimeNow( uint64 uTimeNow )
{
	return 0;
}

int ITimeOutQueue::GetTimeMode() const
{
	return _eTimeMode;
}

bool ITimeOutQueue::Pause()
{
	return false;
}

bool ITimeOutQueue::Resume()
{
	return false;
}

CTimeOutQueue* ITimeOutQueue::GetTimeOutQueue() const
{
	return _pTimeOutQueue;
}

bool ITimeOutQueue::SetTimeOutQueue( CTimeOutQueue* pTimeOutQueue )
{
	_pTimeOutQueue = pTimeOutQueue;
	return true;
}

//////////////////////////////////////////////////////////////////////////
CTimeOutQueueReal::CTimeOutQueueReal()
{
	_eTimeMode = TIME_MODE_REAL;
	_tTimeElapse.SetVaild(false);
}

CTimeOutQueueReal::~CTimeOutQueueReal()
{

}

uint64 CTimeOutQueueReal::GetTimeNow() const
{
	return ToolFrame::GetNowTimeMill();
}

bool CTimeOutQueueReal::Pause()
{
	_tTimeElapse.SetVaild(true);
	_tTimeElapse.ReStart();
	return false;
}

bool CTimeOutQueueReal::Resume()
{
	_tTimeElapse.SetVaild(false);

	uint64 uTimePaused = _tTimeElapse.TimeElapsed();

	GetTimeOutQueue()->ResumeAfter(uTimePaused);
	GetTimeOutQueue()->ResumePoint(uTimePaused);
	return false;
}
//////////////////////////////////////////////////////////////////////////
CTimeOutQueueSeq::CTimeOutQueueSeq()
{
	_eTimeMode = TIME_MODE_SEQ;
	_uSeqTimeNow = 0;
}

CTimeOutQueueSeq::~CTimeOutQueueSeq()
{

}

uint64 CTimeOutQueueSeq::GetTimeNow() const
{
	return _uSeqTimeNow;
}

uint64 CTimeOutQueueSeq::SetTimeNow( uint64 uTimeNow )
{
	return _uSeqTimeNow = uTimeNow;
}

bool CTimeOutQueueSeq::Pause()
{
	return true;
}

bool CTimeOutQueueSeq::Resume()
{
	return true;
}

NS_TOOL_FRAME_END
