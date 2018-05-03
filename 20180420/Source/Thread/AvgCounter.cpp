#include "AvgCounter.h"

NS_TOOL_FRAME_BEGIN

CAvgCounter::CAvgCounter(void)
{
	_uValueTotal = 0;
	_uValueMax = 0;
	_uValueTimes = 0;

	_uMarkTotal = 0;
	_uMarkMax = 0;
	_uMarkTimes = 0;
}

CAvgCounter::CAvgCounter( const CAvgCounter& xCounter )
{
	*this = xCounter;
}

CAvgCounter::~CAvgCounter(void)
{
}

bool CAvgCounter::AddCount( uint64 uValue,bool bMark /*= false*/ )
{
	CLockWrite lock(_mutex);

	_uValueTotal += uValue;
	++_uValueTimes;

	if (uValue > _uValueMax)
		_uValueMax = uValue;

	if (bMark)
	{
		_uMarkTotal += uValue;
		++_uMarkTimes;

		if (uValue > _uMarkMax)
			_uMarkMax = uValue;
	}

	return true;
}

bool CAvgCounter::GetAvg( uint64* uTotal,uint* uTimes /*= nullptr*/,uint64* uValueMax /*= nullptr */,uint64* uAvg /*= nullptr*/, uint64* uMarkTotal /*= nullptr*/,uint* uMarkTimes /*= nullptr*/,uint64* uMarkMax /*= nullptr */,uint64* uMarkAvg /*= nullptr*/ )
{
	CLockRead lock(_mutex);

	if (uTotal)
		*uTotal		= _uValueTotal;

	if (uValueMax)
		*uValueMax	= _uValueMax;
	if (uTimes)
		*uTimes		= _uValueTimes;

	if (uAvg)
		*uAvg = _uValueTimes == 0 ? 0: _uValueTotal / _uValueTimes;

	if (uMarkTotal)
		*uMarkTotal	= _uMarkTotal;
	if (uMarkMax)
		*uMarkMax	= _uMarkMax;
	if (uMarkTimes)
		*uMarkTimes	= _uMarkTimes;

	if (uMarkAvg)
		*uMarkAvg = _uMarkTimes == 0 ? 0: _uMarkTotal / _uMarkTimes;
	return true;
}

bool CAvgCounter::Clear( uint64* uTotal,uint* uTimes,uint64* uValueMax ,uint64* uAvg, uint64* uMarkTotal,uint* uMarkTimes,uint64* uMarkMax ,uint64* uMarkAvg )
{
	CLockWrite lock(_mutex);

	if (uTotal)
		*uTotal		= _uValueTotal;

	if (uValueMax)
		*uValueMax	= _uValueMax;
	if (uTimes)
		*uTimes		= _uValueTimes;

	if (uAvg)
		*uAvg = _uValueTimes == 0 ? 0: _uValueTotal / _uValueTimes;

	if (uMarkTotal)
		*uMarkTotal	= _uMarkTotal;
	if (uMarkMax)
		*uMarkMax	= _uMarkMax;
	if (uMarkTimes)
		*uMarkTimes	= _uMarkTimes;

	if (uMarkAvg)
		*uMarkAvg = _uMarkTimes == 0 ? 0: _uMarkTotal / _uMarkTimes;

	_uValueTotal = 0;_uValueMax =0;_uValueTimes=0;
	_uMarkTotal = 0;_uMarkMax=0;_uMarkTimes =0;
	return true;
}

CAvgCounter& CAvgCounter::operator=( const CAvgCounter& xCounter )
{
	CLockWrite lock(_mutex);
	CLockRead lockOther(xCounter._mutex);

	_uValueTotal = xCounter._uValueTotal;		//总值
	_uValueMax	 = xCounter._uValueMax;			//峰值
	_uValueTimes = xCounter._uValueTimes;		//次数

	_uMarkTotal = xCounter._uMarkTotal;		//总值
	_uMarkMax	= xCounter._uMarkMax;			//峰值
	_uMarkTimes = xCounter._uMarkTimes;		//次数

	return *this;
}

NS_TOOL_FRAME_END
