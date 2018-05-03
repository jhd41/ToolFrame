#include "IUseRef.h"
#include "MLoger.h"

NS_TOOL_FRAME_BEGIN
IUseRef::IUseRef(void)
{
	_nUseCounter = 0;
}

IUseRef::~IUseRef(void)
{
	
}

int IUseRef::GetUseCounter() const
{
	CLockRead lock(_mutex);
	return _nUseCounter;
}

bool IUseRef::TryRetainUse()
{
	CLockWrite lock(_mutex);
	if (_nUseCounter)return false;
	return !!(++_nUseCounter);
}

int IUseRef::RetainUse()
{
	CLockWrite lock(_mutex);
	return ++_nUseCounter;
}

int IUseRef::ReleaseUse()
{
	ASSERT_LOG_ERROR(_nUseCounter >= 1);

	CLockWrite lock(_mutex);
	--_nUseCounter;
	return _nUseCounter;
}

bool IUseRef::IsZeroUse()const
{
	CLockRead lock(_mutex);
	return !_nUseCounter;
}

NS_TOOL_FRAME_END
