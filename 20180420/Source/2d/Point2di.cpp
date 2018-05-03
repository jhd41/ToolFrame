#include "Point2di.h"
#include "ToolStd.h"

#define MATH_FLOAT_SMALL            1.0e-37f
#define MATH_TOLERANCE              2e-37f

#ifndef FLT_EPSILON
#define FLT_EPSILON     1.192092896e-07F
#endif // FLT_EPSILON

NS_TOOL_FRAME_BEGIN

CPoint2di::CPoint2di( void )
{
	SetX(0);
	SetY(0);
}

CPoint2di::CPoint2di( int nX,int nY )
{
	SetXY(nX,nY);
}

CPoint2di::CPoint2di( const CPoint2di& pt )
{
	SetXY(pt._nX,pt._nY);
}

CPoint2di::~CPoint2di( void )
{

}

bool CPoint2di::SetXY( int fX,int fY )
{
	SetX(fX);
	SetY(fY);

	return true;
}

bool CPoint2di::GetXY( int *fX,int *fY ) const
{
	*fX=_nX;
	*fY=_nY;

	return true;
}

bool CPoint2di::Swap( CPoint2di& ptPoint )
{
	ToolFrame::Swap(*this,ptPoint);
	return true;
}

CPoint2di CPoint2di::operator-( const CPoint2di &ptPoint ) const
{
	return CPoint2di(_nX-ptPoint._nX,_nY-ptPoint._nY);
}

CPoint2di CPoint2di::operator+( const CPoint2di &ptPoint ) const
{
	return CPoint2di(_nX+ptPoint._nX,_nY+ptPoint._nY);
}

CPoint2di& CPoint2di::operator+=( const CPoint2di &ptPoint )
{
	_nX += ptPoint._nX;
	_nY += ptPoint._nY;
	return *this;
}

CPoint2di& CPoint2di::operator-=( const CPoint2di &ptPoint )
{
	_nX -= ptPoint._nX;
	_nY -= ptPoint._nY;
	return *this;
}

bool CPoint2di::operator<( const CPoint2di &ptPoint ) const
{
	if (_nX == ptPoint._nX)return _nY < ptPoint._nY;
	return _nX < ptPoint._nX;
}

bool CPoint2di::operator<=( const CPoint2di &ptPoint ) const
{
	if (_nX == ptPoint._nX)return _nY <= ptPoint._nY;
	return _nX <= ptPoint._nX;
}

bool CPoint2di::operator==( const CPoint2di &ptPoint ) const
{
	return ToolFrame::IsEqual(_nX,ptPoint._nX) && ToolFrame::IsEqual(_nY,ptPoint._nY);
}

bool CPoint2di::operator!=( const CPoint2di &ptPoint ) const
{
	return _nX != ptPoint._nX || _nY != ptPoint._nY;
}

CPoint2di CPoint2di::GetMidPoint( const CPoint2di& ptPoint ) const
{
	return CPoint2di(_nX + (ptPoint._nX - _nX)/2,_nY + (ptPoint._nY - _nY)/2);
}

float CPoint2di::Distance( const CPoint2di& pt ) const
{
	return ToolFrame::Sqrt((float)DistanceSquared(pt));
}

int CPoint2di::DistanceSquared( const CPoint2di& pt ) const
{
	return (_nX - pt._nX) * (_nX - pt._nX) + (_nY - pt._nY) * (_nY - pt._nY);
}

CPoint2di CPoint2di::operator*( int fValue ) const
{
	return CPoint2di(_nX * fValue,_nY * fValue);
}

CPoint2di CPoint2di::operator /( int fValue ) const
{
	return CPoint2di(_nX / fValue,_nY / fValue);
}

double CPoint2di::GetAngle() const
{
	double fRadian = ToolFrame::ATan(_nY, _nX);
	return ToolFrame::RadianToAngel(fRadian);
}

double CPoint2di::GetAngle( const CPoint2di& other )const
{
	CPoint2di a2 = GetNormalized();
	CPoint2di b2 = other.GetNormalized();
	double angle = ToolFrame::ATan((float)a2.Cross(b2), (float)a2.Dot(b2));
	if( fabs(angle) < FLT_EPSILON ) return 0.f;
	return ToolFrame::RadianToAngel(angle);
}

CPoint2di& CPoint2di::operator*=( int fValue )
{
	_nX *= fValue;
	_nY *= fValue;
	return *this;
}

CPoint2di& CPoint2di::operator/=( int fValue )
{
	_nX /= fValue;
	_nY /= fValue;
	return *this;
}

int CPoint2di::Dot( const CPoint2di& v ) const
{
	return (_nX * v._nX + _nY * v._nY);
}

int CPoint2di::Cross( const CPoint2di& other ) const
{
	return _nX*other._nY - _nY*other._nX;
}

double CPoint2di::Length() const
{
	return sqrt(_nX * _nX + _nY * _nY);
}

double CPoint2di::LengthSquared() const
{
	return (_nX * _nX + _nY * _nY);
}

bool CPoint2di::Negate()
{
	_nX = -_nX;
	_nY = -_nY;
	return true;
}

bool CPoint2di::Normalize()
{
	float n = 1.f * _nX * _nX + _nY * _nY;
	// Already normalized.
	if (n == 1.0f)
		return false;

	n = sqrt(n);
	// Too close to zero.
	if (n < MATH_TOLERANCE)
		return false;

	n = 1.0f / n;
	_nX = (int)(_nX * n);
	_nY = (int)(_nY * n);

	return true;
}

CPoint2di CPoint2di::GetNormalized() const
{
	CPoint2di v(*this);
	v.Normalize();
	return v;
}

double CPoint2di::GetRotation() const
{
	double fRadian = ToolFrame::ATan(_nX,_nY);
	return ToolFrame::RadianToAngel(fRadian);
}

bool CPoint2di::SetRotation( float fRotation )
{
	//fRotationÊÇÓëYÖá¼Ð½Ç
	double fRadian = ToolFrame::AngelToRadian(fRotation);
	_nX = (int)ToolFrame::Sin(fRadian);
	_nY = (int)ToolFrame::Cos(fRadian);
	return true;
}

NS_TOOL_FRAME_END

