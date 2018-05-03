#include "TimeElapseEx.h"

NS_TOOL_FRAME_BEGIN

CTimeElapseEx::CTimeElapseEx(void)
{
	_uTimeElapse = 0;
	_uPauseElapse = 0;
	_bPause = false;
	ReStart();
}

CTimeElapseEx::~CTimeElapseEx(void)
{
}

uint64 CTimeElapseEx::ReStart()
{
	CLockWrite lock(_mutex);

	uint64 uLast = _uTimeElapse;
	if (!_bPause)
		uLast = _uTimeElapse + _xTimeElapse.ReStart();

	_uTimeElapse = 0;
	_uPauseElapse = 0;
	_bPause = false;

	return uLast;
}

uint64 CTimeElapseEx::TimeElapsed() const
{
	CLockRead lock(_mutex);

	if (_bPause)return _uTimeElapse;
	return _uTimeElapse + _xTimeElapse.TimeElapsed();
}

uint64 CTimeElapseEx::TimeElapsed( uint64 uTimeNow ) const
{
	CLockRead lock(_mutex);

	if (_bPause)return _uTimeElapse;
	return _uTimeElapse + _xTimeElapse.TimeElapsed(uTimeNow);
}

bool CTimeElapseEx::Pause()
{
	CLockWrite lock(_mutex);

	if (_bPause)return false;
	_bPause = true;
	_uTimeElapse += _xTimeElapse.ReStart();

	return true;
}

bool CTimeElapseEx::Resume()
{
	CLockWrite lock(_mutex);

	if (!_bPause)return false;
	_bPause = false;
	_uPauseElapse += _xTimeElapse.ReStart();

	return true;
}

bool CTimeElapseEx::IsPausing() const
{
	CLockRead lock(_mutex);
	return _bPause;
}

bool CTimeElapseEx::SetTimeBegin( uint64 uTimeBegin )
{
	CLockWrite lock(_mutex);
	return _xTimeElapse.SetTimeBegin(uTimeBegin);
}

NS_TOOL_FRAME_END
