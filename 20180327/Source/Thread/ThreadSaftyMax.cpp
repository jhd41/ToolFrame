#include "ThreadSaftyMax.h"

NS_TOOL_FRAME_BEGIN

CThreadSaftyMax::CThreadSaftyMax(void)
{
	_nMax = 0;
}

CThreadSaftyMax::~CThreadSaftyMax(void)
{
}

int CThreadSaftyMax::SetMax( int nMax )
{
	CLockWrite lock(_xMutex);
	int nOld = _nMax;
	_nMax = nMax;
	return nOld;
}

int CThreadSaftyMax::AddMax( int nMax )
{
	CLockWrite lock(_xMutex);

	if (nMax > _nMax)
		_nMax = nMax;

	return _nMax;
}

int CThreadSaftyMax::GetMax() const
{
	CLockRead lock(_xMutex);
	return _nMax;
}

NS_TOOL_FRAME_END

