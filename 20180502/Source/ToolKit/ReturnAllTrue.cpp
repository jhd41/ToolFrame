#include "ReturnAllTrue.h"

NS_TOOL_FRAME_BEGIN
CReturnAllTrue::CReturnAllTrue(void)
{
	_bResult = true;
}

CReturnAllTrue::~CReturnAllTrue(void)
{
}

bool CReturnAllTrue::GetReturn() const
{
	return _bResult;
}

bool CReturnAllTrue::AddReturn( bool b )
{
	_bResult &= b;
	return _bResult;
}

bool CReturnAllTrue::operator+=( bool b )
{
	_bResult &= b;
	return _bResult;
}

CReturnAllTrue::operator bool(void)const
{
	return _bResult;
}

NS_TOOL_FRAME_END