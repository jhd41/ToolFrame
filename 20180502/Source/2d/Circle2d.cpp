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
	//�㵽Բ�ĵľ����Ƿ�С�ڰ뾶
	return _ptCenter.DistanceSquared(pt) <= ToolFrame::Power(_fRadius,2);
}

bool CCircle2d::IsContain( const CCircle2d& circle ) const
{
	//��Բ�ĵľ��� �Ƿ�С�ڰ뾶��
	return CalCenterDistanceSquared(circle) <= ToolFrame::Power(_fRadius - circle._fRadius,2);
}

bool CCircle2d::IsIntersect( const CCircle2d& circle ) const
{
	//��Բ�ĵľ��� �Ƿ� С�� �뾶֮��
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