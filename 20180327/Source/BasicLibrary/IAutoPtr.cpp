#include "IAutoPtr.h"
#include "MLoger.h"

NS_TOOL_FRAME_BEGIN
IAutoPtr::IAutoPtr(void)
{
	_nRefCounter = 1;
	_bAutoDelete = true;
}

IAutoPtr::~IAutoPtr(void)
{
	
}

int IAutoPtr::GetRefCounter() const
{
	CLockRead lock(_mutex);
	return _nRefCounter;
}

bool IAutoPtr::AutoDelete(bool bAuto)
{
	CLockWrite lock(_mutex);
	_bAutoDelete = bAuto;
	return true;
}

bool IAutoPtr::IsAutoDelete() const
{
	CLockRead lock(_mutex);
	return _bAutoDelete;
}

int IAutoPtr::Retain()
{
	CLockWrite lock(_mutex);
	return ++_nRefCounter;
}

int IAutoPtr::Release()
{
	ASSERT_LOG_ERROR(_nRefCounter >= 1);

	{
		CLockWrite lock(_mutex);
		--_nRefCounter;
	}
	
	bool bDelete = false;
	{
		CLockRead lock(_mutex);
		bDelete = _nRefCounter <= 0 && _bAutoDelete;
	}
	if (bDelete)
	{
		delete this;
		return 0;
	}
	return _nRefCounter;
}

bool IAutoPtr::IsZeroRef()const
{
	CLockRead lock(_mutex);
	return !_nRefCounter;
}

NS_TOOL_FRAME_END
