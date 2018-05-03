#include "Ray2d.h"

NS_TOOL_FRAME_BEGIN

CRay2d::CRay2d(void)
{
}

CRay2d::CRay2d( const CPoint2d& ptStart,const CPoint2d& ptPointDirect )
{
	SetPointStart(ptStart);
	SetPointDirect(ptPointDirect);
}

CRay2d::CRay2d( const CRay2d& ray )
{
	SetPointStart(ray.GetPointStart());
	SetPointDirect(ray.GetPointDirect());
}

CRay2d::~CRay2d(void)
{
}

bool CRay2d::IsInRay( const CPoint2d& pt )const
{
	//先检查是否在直线上
	if ((pt.GetX() - GetPointStart().GetX()) * (GetPointDirect().GetY() - GetPointStart().GetY()) != (GetPointDirect().GetX() - GetPointStart().GetX())*(pt.GetY() - GetPointStart().GetY()))
		return false;

	//比值不能为负数
	if (GetPointDirect().GetX() != GetPointStart().GetX())
	{
		if (1.0 * (pt.GetX() - GetPointStart().GetX()) / (GetPointDirect().GetX() - GetPointStart().GetX() ) > 0)
			return true;
	}
	if (GetPointDirect().GetY() != GetPointStart().GetY())
	{
		if (1.0 * (pt.GetY() - GetPointStart().GetY()) / (GetPointDirect().GetY() - GetPointStart().GetY() ) > 0)
			return true;
	}

	return false;	
}

bool CRay2d::operator==( const CRay2d& ray ) const
{
	if (GetPointStart() != ray.GetPointStart())return false;

	return IsInRay(ray.GetPointDirect());
}

CPoint2d CRay2d::CalDistancePoint( float fDistance ) const
{
	float fDistanceRay = _ptPointStart.Distance(_ptPointDirect);

	float fRate = fDistance / fDistanceRay;
	CPoint2d ptTriangle((_ptPointDirect.GetX() - _ptPointStart.GetX())*fRate,(_ptPointDirect.GetY() - _ptPointStart.GetY())*fRate);
	return ptTriangle + _ptPointStart;
}

NS_TOOL_FRAME_END
