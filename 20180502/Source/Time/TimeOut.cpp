#include "TimeOut.h"

#include "ToolFrame.h"

NS_TOOL_FRAME_BEGIN

CTimeOut::CTimeOut()
{
	_uInterval = 0;
	_bVaild = false;
}

CTimeOut::CTimeOut( uint64 uTime )
{
	_uInterval = uTime;
	_bVaild = true;
}

CTimeOut::~CTimeOut(void)
{
}

bool CTimeOut::IsTimeOut() const
{
	if (IsNeverTimeout())return false;
	return _tElapse.TimeElapsed() >= _uInterval;
}

bool CTimeOut::IsTimeOutMill( uint64 uTimeNow ) const
{
	return IsTimeOutMill(uTimeNow,_uInterval);
}

bool CTimeOut::IsTimeOutMill( uint64 uTimeNow,uint64 uInterval ) const
{
	if (IsNeverTimeout(uInterval))return false;
	return _tElapse.TimeElapsed(uTimeNow) >= uInterval;
}

bool CTimeOut::IsTimeOutSec( time_t uTimeNow ) const
{
	return IsTimeOutMill(uint64(uTimeNow) * 1000,_uInterval);
}

bool CTimeOut::IsTimeOutSec( time_t uTimeNow,time_t uInterval ) const
{
	return IsTimeOutMill(uint64(uTimeNow) * 1000,uint64(uInterval) * 1000);
}

uint64 CTimeOut::TimeRemaining() const
{
	uint64 uTimeElapsed =  _tElapse.TimeElapsed();
	if (uTimeElapsed >= _uInterval)return 0;
	return _uInterval - uTimeElapsed;
}

uint64 CTimeOut::ReStart()
{
	return _tElapse.ReStart();
}

bool CTimeOut::SetIntervalMill( uint64 uInterval )
{
	_uInterval = uInterval;
	return true;
}

uint64 CTimeOut::GetIntervalMill() const
{
	return _uInterval;
}

bool CTimeOut::SetIntervalSec( time_t uInterval )
{
	return SetIntervalMill(uint64(uInterval) * 1000);
}

time_t CTimeOut::GetIntervalSec() const
{
	return _uInterval/1000;
}

uint64 CTimeOut::TimeElapsed() const
{
	return _tElapse.TimeElapsed();
}

uint64 CTimeOut::TimeElapsed(uint64 uTimeNow) const
{
	return _tElapse.TimeElapsed(uTimeNow);
}

bool CTimeOut::IsNeverTimeout() const
{
	return IsNeverTimeout(_uInterval);
}

bool CTimeOut::IsNeverTimeout( uint64 uInterval ) const
{
	return !uInterval;
}

bool CTimeOut::SetVaild( bool bVaild )
{
	_bVaild = bVaild;
	return true;
}

bool CTimeOut::IsVaild() const
{
	return _bVaild;
}

bool CTimeOut::TryTimeOutRestart()
{
	if (!IsTimeOut())return false;

	CLockWrite lock(_tElapse.GetMutex());

	if (IsNeverTimeout())return false;

	uint64 uTimeNow = ToolFrame::GetNowTimeMill();
	if (_tElapse.NoLockTimeElapsed(uTimeNow) < _uInterval)return false;
	_tElapse.NoLockRestart(uTimeNow);
	return true;
}

NS_TOOL_FRAME_END
