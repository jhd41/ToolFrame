#include "TimeAvg.h"

NS_TOOL_FRAME_BEGIN

CTimeAvg::CTimeAvg( void )
{
}

CTimeAvg::~CTimeAvg( void )
{

}
uint64 CTimeAvg::GetAvgTime() const
{
	return uint64(_avgValue.GetAvg());
}

uint64 CTimeAvg::AddTimeElapsed( uint64 uTimeElapsed )
{
	return uint64(_avgValue.AddValue((double)uTimeElapsed));
}

CTimeAvg::operator uint64() const
{
	return uint64(_avgValue);
}

NS_TOOL_FRAME_END
