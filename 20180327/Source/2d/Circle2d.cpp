#include "Circle2d.h"
#include "ToolFrame.h"

NS_TOOL_FRAME_BEGIN
CCircle2d::CCircle2d(void)
{
}

CCircle2d::~CCircle2d(void)
{
}

const CPoint2d& CCircle2d::GetCenter() const
{
	return _ptCenter;
}

float CCircle2d::GetRadius() const
{
	return _fRadius;
}

bool CCircle2d::IsContain( const CPoint2d& pt ) const
{
	//点到圆心的距离是否小于半径
	return _ptCenter.DistanceSquared(pt) <= ToolFrame::Power(_fRadius,2);
}

bool CCircle2d::IsContain( const CCircle2d& circle ) const
{
	//两圆心的距离 是否小于半径差
	return CalCenterDistanceSquared(circle) <= ToolFrame::Power(_fRadius - circle._fRadius,2);
}

bool CCircle2d::IsIntersect( const CCircle2d& circle ) const
{
	//两圆心的距离 是否 小于 半径之和
	return CalCenterDistanceSquared(circle) <= ToolFrame::Power(_fRadius + circle._fRadius,2);
}

float CCircle2d::CalCenterDistance( const CCircle2d& circle ) const
{
	return _ptCenter.Distance(circle._ptCenter);
}

float CCircle2d::CalCenterDistanceSquared( const CCircle2d& circle ) const
{
	return _ptCenter.DistanceSquared(circle._ptCenter);
}

NS_TOOL_FRAME_END