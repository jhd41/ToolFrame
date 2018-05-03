#include "ReturnOneTrue.h"

NS_TOOL_FRAME_BEGIN
CReturnOneTrue::CReturnOneTrue(void)
{
	_bResult = false;
}

CReturnOneTrue::~CReturnOneTrue(void)
{
}

bool CReturnOneTrue::AddReturn( bool b )
{
	_bResult |= b;
	return _bResult;
}

bool CReturnOneTrue::GetReturn() const
{
	return _bResult;
}

bool CReturnOneTrue::operator+=( bool b )
{
	_bResult |= b;
	return _bResult;
}

CReturnOneTrue::operator bool(void)const
{
	return _bResult;
}

NS_TOOL_FRAME_END
