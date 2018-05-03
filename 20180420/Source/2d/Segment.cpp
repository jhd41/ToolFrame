#include "Segment.h"
#include "ToolFrame.h"

NS_TOOL_FRAME_BEGIN

CSegment::CSegment(void)
{
}

CSegment::CSegment( float fPositionBegin,float fPositionEnd )
{
	SetBegin(ToolFrame::Min(fPositionBegin,fPositionEnd));			//从小到大
	SetEnd(ToolFrame::Max(fPositionBegin,fPositionEnd));
}

CSegment::CSegment( const CSegment& seg )
{
	SetBegin(seg.GetBegin());
	SetEnd(seg.GetEnd());
}

CSegment::CSegment( int nPositionBegin,int nPositionEnd )
{
	SetBegin(ToolFrame::Min(nPositionBegin,nPositionEnd)*1.0f);			//强转
	SetEnd(ToolFrame::Max(nPositionBegin,nPositionEnd)*1.0f);
}


CSegment::~CSegment(void)
{
}

bool CSegment::IsContain( float fPosition ) const
{
	return ToolFrame::IsInClosedInterval(fPosition,GetBegin(),GetEnd());
}

bool CSegment::IsContain( const CSegment& seg ) const
{
	return ToolFrame::IsInClosedInterval(seg.GetBegin(),GetBegin(),GetEnd()) && ToolFrame::IsInClosedInterval(seg.GetEnd(),GetBegin(),GetEnd());
}

bool CSegment::IsIntersect( const CSegment& seg ) const
{
	return ToolFrame::IsInClosedInterval(seg.GetBegin(),GetBegin(),GetEnd()) || ToolFrame::IsInClosedInterval(seg.GetEnd(),GetBegin(),GetEnd());
}

bool CSegment::CalIntersect( CSegment& segSub,const CSegment& seg ) const
{
	if (!IsIntersect(seg))
		return false;
	segSub.SetBegin(ToolFrame::Max(GetBegin(),seg.GetBegin()));
	segSub.SetEnd(ToolFrame::Min(GetEnd(),seg.GetEnd()));
	return true;
}

float CSegment::GetLength() const
{
	return ToolFrame::AbsDifference(GetBegin(),GetEnd());
}

float CSegment::GetMidPosition() const
{
	return (GetBegin()+GetEnd()) / 2;
}

bool CSegment::operator==( const CSegment& seg ) const
{
	if(GetBegin() != seg.GetBegin())
	{
		return GetBegin() == seg.GetEnd() && GetEnd() == seg.GetBegin();
	}
	return GetEnd() == seg.GetEnd();
}

bool CSegment::operator!=( const CSegment& seg ) const
{
	if (GetBegin() != seg.GetBegin())
	{
		return GetBegin() != seg.GetEnd() || GetEnd() != seg.GetBegin();
	}
	return GetEnd() != seg.GetEnd();
}

bool CSegment::SetSegment( float fPositionBegin,float fPositionEnd )
{
	SetBegin(ToolFrame::Min(fPositionBegin,fPositionEnd));			//从小到大
	SetEnd(ToolFrame::Max(fPositionBegin,fPositionEnd));
	return true;
}

bool CSegment::SetSegment( const CSegment& seg )
{
	return SetSegment(seg.GetBegin(),seg.GetEnd());
}

bool CSegment::SetSegment( int nPositionBegin,int nPositionEnd )
{
	return SetSegment(nPositionBegin*1.0f,nPositionEnd*1.0f);
}

NS_TOOL_FRAME_END
