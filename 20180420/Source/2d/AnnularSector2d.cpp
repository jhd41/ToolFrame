#include "AnnularSector2d.h"
#include "Line2d.h"
#include "ToolStd.h"

NS_TOOL_FRAME_BEGIN
CAnnularSector2d::CAnnularSector2d(void)
{
	SetCenter(CPoint2d(0,0));
}

CAnnularSector2d::CAnnularSector2d( float fInner,float fOuter,float fAngle,const CPoint2d& ptDirection )
{
	SetCenter(CPoint2d(0,0));
	SetInnerRadius(fInner);
	SetOuterRadius(fOuter);
	SetAngleRange(fAngle);
	_ptDirection = ptDirection;
}

CAnnularSector2d::CAnnularSector2d( float fInner,float fOuter,float fAngle,const CPoint2d& ptDirection,const CPoint2d& ptCenter )
{
	SetCenter(ptCenter);
	SetInnerRadius(fInner);
	SetOuterRadius(fOuter);
	SetAngleRange(fAngle);
	_ptDirection = ptDirection;
}

CAnnularSector2d::CAnnularSector2d( const CAnnularSector2d& sa )
{
	SetCenter(sa.GetCenter());
	SetInnerRadius(sa.GetInnerRadius());
	SetOuterRadius(sa.GetOuterRadius());
	SetAngleRange(sa.GetAngleRange());
	SetDirection(sa.GetDirection());
}

CAnnularSector2d::~CAnnularSector2d(void)
{
}

bool CAnnularSector2d::operator==( const CAnnularSector2d& sa ) const
{
	if (GetInnerRadius() != sa.GetInnerRadius())
		return false;
	if (GetOuterRadius() != sa.GetOuterRadius())
		return false;
	if (GetAngleRange() != sa.GetAngleRange())
		return false;
	if (GetDirection() != sa.GetDirection())
		return false;
	return true;
}

bool CAnnularSector2d::operator!=( const CAnnularSector2d& sa ) const
{
	if (GetInnerRadius() == sa.GetInnerRadius())
		return false;
	if (GetOuterRadius() == sa.GetOuterRadius())
		return false;
	if (GetAngleRange() == sa.GetAngleRange())
		return false;
	if (GetDirection() == sa.GetDirection())
		return false;
	return true;
}

bool CAnnularSector2d::IsContain( const CPoint2d& ptPoint ) const
{
	if (ptPoint == GetCenter())
		return true;
	//判断长度
	if (DistanceSquared(ptPoint) > GetOuterRadius()*GetOuterRadius())
		return false;
	if (DistanceSquared(ptPoint) < GetInnerRadius()*GetInnerRadius())
		return false;
	//判断向量夹角
	CPoint2d ptVecTarget = ptPoint-GetCenter();
	double fAngle = ToolFrame::Abs(GetDirection().GetAngle(ptVecTarget));
	if (fAngle > GetAngleRange() / 2)
		return false;
	return true;
}

float CAnnularSector2d::Distance( const CPoint2d& ptPoint ) const
{
	return ptPoint.Distance(GetCenter());
}

float CAnnularSector2d::DistanceSquared( const CPoint2d& ptPoint ) const
{
	return ptPoint.DistanceSquared(GetCenter());
}

bool CAnnularSector2d::SetAnnularSector2d( float fInner,float fOuter,float fAngle,const CPoint2d& ptDirection )
{
	SetCenter(CPoint2d(0,0));
	SetInnerRadius(fInner);
	SetOuterRadius(fOuter);
	SetAngleRange(fAngle);
	_ptDirection = ptDirection;
	return true;
}

bool CAnnularSector2d::SetAnnularSector2d( float fInner,float fOuter,float fAngle,const CPoint2d& ptDirection,const CPoint2d& ptCenter )
{
	SetCenter(ptCenter);
	SetInnerRadius(fInner);
	SetOuterRadius(fOuter);
	SetAngleRange(fAngle);
	_ptDirection = ptDirection;
	return true;
}

bool CAnnularSector2d::SetAnnularSector2d( const CAnnularSector2d& sa )
{
	SetCenter(sa.GetCenter());
	SetInnerRadius(sa.GetInnerRadius());
	SetOuterRadius(sa.GetOuterRadius());
	SetAngleRange(sa.GetAngleRange());
	SetDirection(sa.GetDirection());
	return true;
}

bool CAnnularSector2d::SetDirection( float fRotation )
{
	CPoint2d pt;
	pt.SetRotation(fRotation);
	return SetDirection(pt);
}

NS_TOOL_FRAME_END