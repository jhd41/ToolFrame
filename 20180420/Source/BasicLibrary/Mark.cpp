#include "Mark.h"

#include "ToolFrame.h"

NS_TOOL_FRAME_BEGIN

CMark::CMark(void)
{
}

CMark::~CMark(void)
{
}

bool CMark::TryMark( int nMark )
{
	if (IsMarked(nMark))return false;

	CLockWrite lock(_mutex);
	if (ToolFrame::IsHasValue(_vMark,nMark))return false;
	return ToolFrame::Insert(_vMark,nMark);
}

bool CMark::IsMarked( int nMark /*= INVALID_ID*/ ) const
{
	CLockRead lock(_mutex);
	return ToolFrame::IsHasValue(_vMark,nMark);
}

bool CMark::Clear( int nMark /*= INVALID_ID*/ )
{
	CLockWrite lock(_mutex);
	return ToolFrame::EraseByValue(_vMark,nMark);
}

bool CMark::ClearAll()
{
	CLockWrite lock(_mutex);
	ToolFrame::Clear(_vMark);
	return true;
}

NS_TOOL_FRAME_END
