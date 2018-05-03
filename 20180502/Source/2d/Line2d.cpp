#include "Line2d.h"
#include "ToolFrame.h"

NS_TOOL_FRAME_BEGIN

CLine2d::CLine2d(void)
{
}

CLine2d::CLine2d( const CPoint2d& pt1,const CPoint2d& pt2 )
{
	SetPoint1(pt1);
	SetPoint2(pt2);
}

CLine2d::CLine2d( const CLine2d& line )
{
	SetPoint1(line.GetPoint1());
	SetPoint2(line.GetPoint2());
}

CLine2d::~CLine2d(void)
{
}

bool CLine2d::IsInLine( const CPoint2d& pt )const
{
	float f1 = (pt.GetY()-GetPoint1().GetY())*(GetPoint1().GetX()-GetPoint2().GetX());
	float f2 = (GetPoint1().GetY()-GetPoint2().GetY())*(pt.GetX()-GetPoint1().GetX());
	return ToolFrame::IsEqual(f1,f2);
}

bool CLine2d::operator==( const CLine2d& line ) const
{
	if (!IsInLine(line.GetPoint1()))return false;
	if (!IsInLine(line.GetPoint2()))return false;
	return true;
}

float CLine2d::CalAngle( const CLine2d& line )
{
	return (float)ToolFrame::RadianToAngel(CalRadian(line));
}

float CLine2d::CalRadian( const CLine2d& line )
{
	float fA1=INVALID_ID,fA2=INVALID_ID,fB1=INVALID_ID,fB2=INVALID_ID,fC1=INVALID_ID,fC2=INVALID_ID;
	CalCoefficient(fA1,fB1,fC1);
	line.CalCoefficient(fA2,fB2,fC2);
	return (float)ToolFrame::ACos(ToolFrame::Abs(fA1*fA2+fB1*fB2)/(ToolFrame::Sqrt(fA1*fA1+fB1*fB1)*ToolFrame::Sqrt(fA2*fA2+fB2*fB2)));
}

float CLine2d::Distance( const CPoint2d& pt )
{
	float fA=INVALID_ID,fB=INVALID_ID,fC=INVALID_ID;
	CalCoefficient(fA,fB,fC);
	if (0 == fA && 0 == fB)
		return 0;
	return ToolFrame::Sqrt(DistanceSquared(pt));
}

float CLine2d::DistanceSquared( const CPoint2d& pt )
{
	float fA=INVALID_ID,fB=INVALID_ID,fC=INVALID_ID;
	CalCoefficient(fA,fB,fC);
	if (0 == fA && 0 == fB)
		return 0;
	return ((fA*pt.GetX()+fB*pt.GetY()+fC)*(fA*pt.GetX()+fB*pt.GetY()+fC))/(fA*fA+fB*fB);
}

bool CLine2d::CalCoefficient( float& fA,float& fB,float& fC ) const
{
	fA = GetPoint2().GetY() - GetPoint1().GetY();
	fB = GetPoint1().GetX() - GetPoint2().GetX();
	fC = GetPoint1().GetY()*(GetPoint2().GetX() - GetPoint1().GetX())-GetPoint1().GetX()*(GetPoint2().GetY() - GetPoint1().GetY());
	return true;
}

NS_TOOL_FRAME_END
