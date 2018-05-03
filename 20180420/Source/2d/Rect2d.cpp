#include "Rect2d.h"
#include "ToolStd.h"

NS_TOOL_FRAME_BEGIN

CRect2d::CRect2d(void)
{
}

CRect2d::CRect2d( const CPoint2d& ptLeftBottom,const CPoint2d& ptRightTop )
{
	SetRect(ptLeftBottom,ptRightTop);
}

CRect2d::CRect2d( float x1,float y1,float x2,float y2 )
{
	SetRect(x1,y1,x2,y2);
}

CRect2d::CRect2d( const CPoint2d& ptWhole )
{
	SetRect(ptWhole,ptWhole);
}

CRect2d::~CRect2d(void)
{
}

float CRect2d::GetWidth() const
{
	return _ptRightTop.GetX() - _ptLeftBottom.GetX();
}

float CRect2d::GetHeight() const
{
	return _ptRightTop.GetY() - _ptLeftBottom.GetY();
}

bool CRect2d::IsContain( const CPoint2d& pt ) const
{
	return _ptLeftBottom.GetX() <= pt.GetX() && _ptLeftBottom.GetY() <= pt.GetY() && pt.GetX() <= _ptRightTop.GetX() && pt.GetY() <= _ptRightTop.GetY() ;
}

bool CRect2d::IsContain( const CRect2d& rect ) const
{
	return _ptLeftBottom.GetX() <= rect._ptLeftBottom.GetX() && _ptLeftBottom.GetY() <= rect._ptLeftBottom.GetY() && rect._ptRightTop.GetX() <= _ptRightTop.GetX() && rect._ptRightTop.GetY() <= _ptRightTop.GetY();
}

bool CRect2d::IsIntersect( const CRect2d& rect ) const
{
	CRect2d r;
	return CalIntersect(r,rect);
}

bool CRect2d::CalIntersect( CRect2d& rResult,const CRect2d& rect ) const
{
	rResult._ptLeftBottom.SetX(ToolFrame::Max(_ptLeftBottom.GetX(),rect._ptLeftBottom.GetX()));
	rResult._ptLeftBottom.SetY(ToolFrame::Max(_ptLeftBottom.GetY(),rect._ptLeftBottom.GetY()));

	rResult._ptRightTop.SetX(ToolFrame::Min(_ptRightTop.GetX(),rect._ptRightTop.GetX()));
	rResult._ptRightTop.SetY(ToolFrame::Min(_ptRightTop.GetY(),rect._ptRightTop.GetY()));

	return !(rResult._ptLeftBottom.GetX() >  rResult._ptRightTop.GetX() || rResult._ptLeftBottom.GetY() >  rResult._ptRightTop.GetY());
}

bool CRect2d::operator==( const CRect2d &rect ) const
{
	return _ptLeftBottom == rect._ptLeftBottom && _ptRightTop == rect._ptRightTop;
}

bool CRect2d::operator!=( const CRect2d &rect ) const
{
	return !(*this == rect);
}

void CRect2d::SetLeftBottom( float nX,float nY )
{
	_ptLeftBottom.SetXY(nX,nY);
}

void CRect2d::SetRightTop( float nX,float nY )
{
	_ptRightTop.SetXY(nX,nY);
}

bool CRect2d::IsValid() const
{
	return _ptLeftBottom < _ptRightTop;
}

CPoint2d CRect2d::GetMidPoint() const
{
	return _ptLeftBottom.GetMidPoint(_ptRightTop);
}

CPoint2d CRect2d::GetSize() const
{
	return CPoint2d(_ptRightTop.GetX() - _ptLeftBottom.GetX(),_ptRightTop.GetY() - _ptLeftBottom.GetY());
}

void CRect2d::SetRect( float x1,float y1,float x2,float y2 )
{
	_ptLeftBottom.SetXY(x1,y1);
	_ptRightTop.SetXY(x2,y2);
}

void CRect2d::SetRect( const CPoint2d& ptLeftBottom,const CPoint2d& ptRightTop )
{
	_ptLeftBottom	= ptLeftBottom;
	_ptRightTop		= ptRightTop;
}

void CRect2d::SetRectMid( const CPoint2d& ptMidPoint,const CPoint2d& ptSize )
{
	SetRect(ptMidPoint - ptSize/2 ,ptMidPoint + ptSize/2);
}

bool CRect2d::Contain( const CPoint2d& pt )
{
	if (IsContain(pt))return false;

	if (pt.GetX() < _ptLeftBottom.GetX())
		_ptLeftBottom.SetX(pt.GetX());
	if (pt.GetY() < _ptLeftBottom.GetY())
		_ptLeftBottom.SetY(pt.GetY());

	if (pt.GetX() > _ptRightTop.GetX())
		_ptRightTop.SetX(pt.GetX());

	if (pt.GetY() > _ptRightTop.GetY())
		_ptRightTop.SetY(pt.GetY());

	return true;
}

NS_TOOL_FRAME_END
	