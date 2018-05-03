#include "SwitcherNumber.h"
#include "ToolFrame.h"

NS_TOOL_FRAME_BEGIN

CSwitcherNumber ::CSwitcherNumber ()
{
	Init(0,0,0,true);
}

CSwitcherNumber ::CSwitcherNumber ( int nCur,int nRangeBegin,int nRangeEnd )
{
	Init(nCur,nRangeBegin,nRangeEnd,true);
}

CSwitcherNumber ::~CSwitcherNumber (void)
{
}

int CSwitcherNumber ::Add( int nValue )
{
	return SetCur(_nCur + nValue);
}

int CSwitcherNumber ::GetCur() const
{
	return _nCur;
}

bool CSwitcherNumber ::Init( int nCur,int nRangeBegin,int nRangeEnd,bool bLoop /*= true*/ )
{
	SetRangeInClosed(nRangeBegin,nRangeEnd);
	SetCur(nCur);
	SetLoop(bLoop);
	return IsInitVaild();
}

bool CSwitcherNumber ::IsInitVaild() const
{
	if (!ToolFrame::IsInClosedInterval(_nCur,_nRangeBegin,_nRangeEnd))return false;
	if (_nRangeBegin >= _nRangeEnd)return false;
	
	return true;
}

int CSwitcherNumber ::Reduce( int nValue /*= -1*/ )
{
	return Add(nValue);
}

int CSwitcherNumber ::SetCur( int nValue )
{
	_nCur = nValue;

	//不是循环模式
	if (!_bLoop)
	{
		if (_nCur > _nRangeEnd)
			_nCur = _nRangeEnd;
		if (_nCur < _nRangeBegin)
			_nCur = _nRangeBegin;
		return _nCur;
	}

	//循环模式
	int nRange = _nRangeEnd - _nRangeBegin + 1;
	if (0 ==nRange){
		_nCur = _nRangeEnd;
		return _nCur;
	}
	if (_nCur >= _nRangeBegin)
		return _nCur = _nRangeBegin + (_nCur - _nRangeBegin) % nRange;

	return _nCur = _nRangeBegin + (_nCur - _nRangeBegin) % nRange + nRange;
}

bool CSwitcherNumber ::SetRangeInClosed( int nRangeBegin,int nRangeEnd )
{
	if (nRangeBegin>nRangeEnd)return false;

	_nRangeBegin	= nRangeBegin;
	_nRangeEnd		= nRangeEnd;
	return true;
}

bool CSwitcherNumber ::SetRangeInOpen( int nRangeBegin,int nRangeEnd )
{
	return SetRangeInClosed(nRangeBegin-1,nRangeEnd+1);
}

bool CSwitcherNumber ::IsLoop() const
{
	return _bLoop;
}

bool CSwitcherNumber ::SetLoop( bool bLoop )
{
	_bLoop = bLoop;
	return true;
}

NS_TOOL_FRAME_END
