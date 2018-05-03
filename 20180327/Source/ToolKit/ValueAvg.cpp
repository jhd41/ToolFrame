#include "ValueAvg.h"

NS_TOOL_FRAME_BEGIN

CValueAvg::CValueAvg( void )
{
	CLockWrite lock(_mutex);
	
	_fAvg = 0.f;
	_uCount=0;
}

CValueAvg::CValueAvg( const CValueAvg& xValueAvg )
{
	*this = xValueAvg;
}

CValueAvg::~CValueAvg( void )
{

}

double CValueAvg::GetAvg() const
{
	CLockRead lock(_mutex);
	return _fAvg;
}

double CValueAvg::AddValue( double fValue )
{
	CLockWrite lock(_mutex);
	
	++_uCount;
	return _fAvg = _fAvg *((_uCount-1)*1.0f/_uCount) + fValue/_uCount;
}

CValueAvg& CValueAvg::operator=( const CValueAvg& xValueAvg )
{
	CLockWrite lock(_mutex);

	CLockRead lockOhter(xValueAvg._mutex);
	_fAvg		= xValueAvg._fAvg;
	_uCount		= xValueAvg._uCount;

	return *this;
}

CValueAvg::operator double() const
{
	CLockWrite lock(_mutex);
	return _fAvg;
}

NS_TOOL_FRAME_END
