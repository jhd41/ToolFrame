#include "Point2d.h"
#include "ToolStd.h"

#define MATH_FLOAT_SMALL            1.0e-37f
#define MATH_TOLERANCE              2e-37f

#ifndef FLT_EPSILON
#define FLT_EPSILON     1.192092896e-07F
#endif // FLT_EPSILON

NS_TOOL_FRAME_BEGIN

CPoint2d::CPoint2d( void )
{
	SetX(0.0f);
	SetY(0.0f);
}

CPoint2d::CPoint2d( float fX,float fY )
{
	SetXY(fX,fY);
}

CPoint2d::CPoint2d( const CPoint2d& pt )
{
	SetXY(pt._fX,pt._fY);
}

CPoint2d::~CPoint2d( void )
{

}

bool CPoint2d::SetXY( float fX,float fY )
{
	SetX(fX);
	SetY(fY);

	return true;
}

bool CPoint2d::GetXY( float *fX,float *fY ) const
{
	*fX=_fX;
	*fY=_fY;

	return true;
}

bool CPoint2d::Swap( CPoint2d& ptPoint )
{
	ToolFrame::Swap(*this,ptPoint);
	return true;
}

CPoint2d CPoint2d::operator-( const CPoint2d &ptPoint ) const
{
	return CPoint2d(_fX-ptPoint._fX,_fY-ptPoint._fY);
}

CPoint2d CPoint2d::operator+( const CPoint2d &ptPoint ) const
{
	return CPoint2d(_fX+ptPoint._fX,_fY+ptPoint._fY);
}

CPoint2d& CPoint2d::operator+=( const CPoint2d &ptPoint )
{
	_fX += ptPoint._fX;
	_fY += ptPoint._fY;
	return *this;
}

CPoint2d& CPoint2d::operator-=( const CPoint2d &ptPoint )
{
	_fX -= ptPoint._fX;
	_fY -= ptPoint._fY;
	return *this;
}

bool CPoint2d::operator<( const CPoint2d &ptPoint ) const
{
	if (_fX == ptPoint._fX)return _fY < ptPoint._fY;
	return _fX < ptPoint._fX;
}

bool CPoint2d::operator<=( const CPoint2d &ptPoint ) const
{
	if (_fX == ptPoint._fX)return _fY <= ptPoint._fY;
	return _fX <= ptPoint._fX;
}

bool CPoint2d::operator==( const CPoint2d &ptPoint ) const
{
	return ToolFrame::IsEqual(_fX,ptPoint._fX) && ToolFrame::IsEqual(_fY,ptPoint._fY);
}

bool CPoint2d::operator!=( const CPoint2d &ptPoint ) const
{
	return _fX != ptPoint._fX || _fY != ptPoint._fY;
}

CPoint2d CPoint2d::GetMidPoint( const CPoint2d& ptPoint ) const
{
	return CPoint2d(_fX + (ptPoint._fX - _fX)/2,_fY + (ptPoint._fY - _fY)/2);
}

float CPoint2d::Distance( const CPoint2d& pt ) const
{
	return ToolFrame::Sqrt(DistanceSquared(pt));
}

float CPoint2d::DistanceSquared( const CPoint2d& pt ) const
{
	return ToolFrame::Power(_fX - pt._fX,2)+ToolFrame::Power(_fY - pt._fY,2);
}

CPoint2d CPoint2d::operator*( float fValue ) const
{
	return CPoint2d(_fX * fValue,_fY * fValue);
}

CPoint2d CPoint2d::operator /( float fValue ) const
{
	return CPoint2d(_fX / fValue,_fY / fValue);
}

double CPoint2d::GetAngle() const
{
	double fRadian = ToolFrame::ATan(_fY, _fX);
	return ToolFrame::RadianToAngel(fRadian);
}

double CPoint2d::GetAngle( const CPoint2d& other )const
{
	CPoint2d a2 = GetNormalized();
	CPoint2d b2 = other.GetNormalized();
	float angle = atan2f(a2.Cross(b2), a2.Dot(b2));
	if( fabs(angle) < FLT_EPSILON ) return 0.f;
	return ToolFrame::RadianToAngel(angle);
}

CPoint2d& CPoint2d::operator*=( float fValue )
{
	_fX *= fValue;
	_fY *= fValue;
	return *this;
}

CPoint2d& CPoint2d::operator/=( float fValue )
{
	_fX /= fValue;
	_fY /= fValue;
	return *this;
}

float CPoint2d::Dot( const CPoint2d& v ) const
{
	return (_fX * v._fX + _fY * v._fY);
}

float CPoint2d::Cross( const CPoint2d& other ) const
{
	return _fX*other._fY - _fY*other._fX;
}

double CPoint2d::Length() const
{
	 return sqrt(_fX * _fX + _fY * _fY);
}

double CPoint2d::LengthSquared() const
{
	 return (_fX * _fX + _fY * _fY);
}

bool CPoint2d::Negate()
{
	_fX = -_fX;
	_fY = -_fY;
	return true;
}

bool CPoint2d::Normalize()
{
	float n = _fX * _fX + _fY * _fY;
	// Already normalized.
	if (n == 1.0f)
		return false;

	n = sqrt(n);
	// Too close to zero.
	if (n < MATH_TOLERANCE)
		return false;

	n = 1.0f / n;
	_fX *= n;
	_fY *= n;

	return true;
}

CPoint2d CPoint2d::GetNormalized() const
{
	CPoint2d v(*this);
	v.Normalize();
	return v;
}

double CPoint2d::GetRotation() const
{
	double fRadian = ToolFrame::ATan(_fX,_fY);
	return ToolFrame::RadianToAngel(fRadian);
}

bool CPoint2d::SetRotation( float fRotation )
{
	//fRotationÊÇÓëYÖá¼Ð½Ç
	double fRadian = ToolFrame::AngelToRadian(fRotation);
	_fX = (float)ToolFrame::Sin(fRadian);
	_fY = (float)ToolFrame::Cos(fRadian);
	return true;
}

NS_TOOL_FRAME_END

