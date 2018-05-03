#include "Segment2d.h"
#include "ToolFrame.h"

NS_TOOL_FRAME_BEGIN

CSegment2d::CSegment2d(void)
{
}

CSegment2d::CSegment2d( const CPoint2d& ptBegin,const CPoint2d& ptEnd )
{
	SetPointBegin(ptBegin);
	SetPointEnd(ptEnd);
}

CSegment2d::CSegment2d( const CSegment2d& seg )
{
	SetPointBegin(seg.GetPointBegin());
	SetPointEnd(seg.GetPointEnd());
}


CSegment2d::~CSegment2d(void)
{
}

bool CSegment2d::IsContain( const CPoint2d& pt ) const
{
	float f1 = (pt.GetY()-GetPointBegin().GetY())*(GetPointBegin().GetX()-GetPointEnd().GetX());
	float f2 = (GetPointBegin().GetY()-GetPointEnd().GetY())*(pt.GetX()-GetPointBegin().GetX());
	if (!ToolFrame::IsEqual(f1,f2))			//不在两点连成的直线上 
		return false;
	if (pt.GetX() < ToolFrame::Min(GetPointBegin().GetX(),GetPointEnd().GetX()))
		return false;
	if (pt.GetX() > ToolFrame::Max(GetPointBegin().GetX(),GetPointEnd().GetX()))
		return false;
	if (pt.GetY() < ToolFrame::Min(GetPointBegin().GetY(),GetPointEnd().GetY()))
		return false;
	if (pt.GetY() > ToolFrame::Max(GetPointBegin().GetY(),GetPointEnd().GetY()))
		return false;
											//不在该线段为对角线的矩形中
	return true;
}

bool CSegment2d::IsContain( const CSegment2d& seg ) const
{
	return IsContain(seg.GetPointBegin()) && IsContain(seg.GetPointEnd());
}

bool CSegment2d::IsIntersect( const CSegment2d& seg ) const
{
	float fBeginX = GetPointBegin().GetX();
	float fEndX = GetPointEnd().GetX();
	float fTargetBeginX = seg.GetPointBegin().GetX();
	float fTargetEndX = seg.GetPointEnd().GetX();
	float fBeginY = GetPointBegin().GetY();
	float fEndY = GetPointEnd().GetY();
	float fTargetBeginY = seg.GetPointBegin().GetY();
	float fTargetEndY = seg.GetPointEnd().GetY();

	if ((fBeginX-fEndX)!=(fTargetBeginX-fTargetEndX) && 0==(fBeginX-fEndX)*(fBeginY-fEndY) && 0==(fTargetBeginX-fTargetEndX)*(fTargetBeginY-fTargetEndY))	//特殊情况，一条平行X轴一条平行Y轴
	{
		if (ToolFrame::Max(fBeginX,fEndX) < ToolFrame::Min(fTargetBeginX,fTargetEndX))
			return false;
		if (ToolFrame::Max(fBeginY,fEndY) < ToolFrame::Min(fTargetBeginY,fTargetEndY))
			return false;
		if (ToolFrame::Max(fTargetBeginX,fTargetEndX) < ToolFrame::Min(fBeginX,fEndX))
			return false;
		if (ToolFrame::Max(fTargetBeginY,fTargetEndY) < ToolFrame::Min(fBeginY,fEndY))
			return false;
		return true;
	}

	float fDelta = CalDelta(fEndX-fBeginX,fTargetBeginX-fTargetEndX,fEndY-fBeginY,fTargetBeginY-fTargetEndY);  
	if ( ToolFrame::IsEqual(fDelta,0) )		// fDelta，表示两线段重合或平行   
		return false;  
	float fLanda = CalDelta(fTargetBeginX-fBeginX, fTargetBeginX-fTargetEndX, fTargetBeginY-fBeginY, fTargetBeginY-fTargetEndY) / fDelta;  
	if ( fLanda > 1 || fLanda < 0 )  
		return false;  
	double fMiu = CalDelta(fEndX-fBeginX, fTargetBeginX-fBeginX, fEndY-fBeginY, fTargetBeginY-fBeginY) / fDelta;  
	if ( fMiu > 1 || fMiu < 0 )  
		return false;  
	return true;  
}

float CSegment2d::GetLength() const
{
	return GetPointBegin().Distance(GetPointEnd());
}

float CSegment2d::GetLengthSquared() const
{
	return GetPointBegin().DistanceSquared(GetPointEnd());
}

ToolFrame::CPoint2d CSegment2d::GetMidPoint() const
{
	return GetPointBegin().GetMidPoint(GetPointEnd());
}

bool CSegment2d::operator==( const CSegment2d& seg ) const
{
	if (GetPointBegin() != seg.GetPointBegin())
	{
		return GetPointBegin() == seg.GetPointEnd() && GetPointEnd() == seg.GetPointBegin();
	}
	return GetPointEnd() == seg.GetPointEnd();
}

bool CSegment2d::operator!=( const CSegment2d& seg ) const
{
	if (GetPointBegin() != seg.GetPointBegin())
	{
		return GetPointBegin() != seg.GetPointEnd() ||  GetPointEnd() != seg.GetPointBegin();
	}
	return GetPointEnd() != seg.GetPointEnd();
}

float CSegment2d::CalDelta( float f1,float f2,float f3, float f4 ) const
{
	return f1 * f3 - f2 * f4;
}

NS_TOOL_FRAME_END