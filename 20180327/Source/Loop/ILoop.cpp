#include "ILoop.h"

NS_TOOL_FRAME_BEGIN

ILoop::ILoop(void)
{
	_bInitLoop = false;
}

ILoop::~ILoop(void)
{
}

bool ILoop::SetInitedLoop()
{
	if (_bInitLoop)return false;

	_bInitLoop = true;
	return true;
}

bool ILoop::IsInitedLoop() const
{
	return _bInitLoop;
}

NS_TOOL_FRAME_END
