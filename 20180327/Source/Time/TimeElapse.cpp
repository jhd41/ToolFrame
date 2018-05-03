#include "TimeElapse.h"

#include "ToolFrame.h"

NS_TOOL_FRAME_BEGIN

CTimeElapse::CTimeElapse(void)
{
	CLockWrite lock(_mutex);
	_uTimeBegin = ToolFrame::GetNowTimeMill();
	_bVaild = true;
}

CTimeElapse::CTimeElapse( const CTimeElapse& xElapse )
{
	*this = xElapse;
}

CTimeElapse::~CTimeElapse(void)
{
}

uint64 CTimeElapse::ReStart()
{
	CLockWrite lock(_mutex);

	uint64 uTimeNow = ToolFrame::GetNowTimeMill();
	return NoLockRestart(uTimeNow);
}

uint64 CTimeElapse::TimeElapsed() const
{
	CLockRead lock(_mutex);

	return NoLockTimeElapsed(ToolFrame::GetNowTimeMill());
}

uint64 CTimeElapse::TimeElapsed( uint64 uTimeNow ) const
{
	CLockRead lock(_mutex);
	return NoLockTimeElapsed(uTimeNow);
}

uint64 CTimeElapse::GetTimeBegin() const
{
	CLockRead lock(_mutex);

	return _uTimeBegin;
}

bool CTimeElapse::IsVaild() const
{
	CLockRead lock(_mutex);

	return _bVaild;
}

bool CTimeElapse::SetVaild( bool bVaild )
{
	CLockRead lock(_mutex);

	_bVaild = bVaild;
	return true;
}

CTimeElapse& CTimeElapse::operator=( const CTimeElapse& xElapse )
{
	CLockWrite lock(_mutex);

	CLockRead lockOhter(xElapse._mutex);
	_uTimeBegin = xElapse._uTimeBegin;
	_bVaild		= xElapse._bVaild;

	return *this;
}

uint64 CTimeElapse::NoLockTimeElapsed( uint64 uTimeNow ) const
{
	if (uTimeNow < _uTimeBegin)return 0;
	return uTimeNow - _uTimeBegin;
}

bool CTimeElapse::SetTimeBegin( uint64 uTimeBegin )
{
	CLockWrite lock(_mutex);

	_uTimeBegin = uTimeBegin;
	return true;
}

uint64 CTimeElapse::NoLockRestart( uint64 uTimeNow )
{
	uint64 uTimeElapse = NoLockTimeElapsed(uTimeNow);
	_uTimeBegin = uTimeNow;
	return uTimeElapse;
}

CMutexReadWrite& CTimeElapse::GetMutex() const
{
	return _mutex;
}

NS_TOOL_FRAME_END
