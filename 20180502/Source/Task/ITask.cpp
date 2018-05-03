#include "ITask.h"
#include "ITaskMgr.h"

NS_TOOL_FRAME_BEGIN

ITask::ITask(void)
{
	_eState = INVALID_ID;
	_eStateOver = INVALID_ID;

	SetTaskMgrNull();
	SetTaskOver(false);
}

ITask::~ITask(void)
{
	RemoveTimer();
}

CMutexRecursive& ITask::GetMutex() const
{
	return _mutex;
}

bool ITask::Init()
{
	if (!GetTaskMgr())return false;
	CLockScoped lock(_mutex);

	return OnInit(_eState);
}

bool ITask::OnTimeOut( const CTimeNodePtr& pTimeNode )
{
	CLockScoped lock(_mutex);

	return OnTimeOut(_eState);
}

bool ITask::SetState( int eState )
{
	CLockScoped lock(_mutex);

	if (_eState == eState)return true;

	OnStateReclaim(_eState);

	_eState = eState;
	
	OnStateChanged(_eState);

	//¼ì²éÊÇ·ñ½áÊø
	if (INVALID_ID != _eStateOver && _eStateOver == eState)
		SetTaskOver(true);
	
	return true;
}

bool ITask::StartWaitBySecond( uint uSecond,bool bLoop /*= false*/,time_t uTimeDelay/*=0*/ )
{
	if (!RemoveTimer())return false;
	_pTimer = GetTaskMgr()->GetTimeOutQueue().CreateTimerByAfterSec(this,uSecond,bLoop,uTimeDelay);
	return !!_pTimer;
}

bool ITask::StartWaitByMill( uint64 uMillSecond,bool bLoop /*= false*/,time_t uTimeDelay/*=0*/ )
{
	if (!RemoveTimer())return false;
	_pTimer = GetTaskMgr()->GetTimeOutQueue().CreateTimerByAfterMil(this,uMillSecond,bLoop,uTimeDelay);
	return !!_pTimer;
}

bool ITask::CancelWait()
{
	return RemoveTimer();
}

bool ITask::SetOverState( int eState )
{
	_eStateOver = eState;
	return true;
}

bool ITask::RemoveTimer()
{
	if (!_pTimer)return true;
	
	GetTaskMgr()->GetTimeOutQueue().RemoveTimer(_pTimer);
	return true;
}

NS_TOOL_FRAME_END
