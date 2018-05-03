#pragma once

#include "Macro.h"
#include <assert.h>

NS_TOOL_FRAME_BEGIN

template<typename T,uint uRowMax,uint uColMax>
class TArray2d{
public:
	uint		GetLength()const{return uRowMax * uColMax;}
	T*			GetPtr(){return _t;}
	const T*	GetPtr()const{return _t;}
	bool		Zero(){memset(_t,0,uRowMax * uColMax);return true;}
	operator	const T*(void)const{return _t;}
	operator	T*(void){return _t;}
	T&			GetValue(uint uRow,uint uCol)const{
		assert(uRow <= uRowMax && uCol <= uColMax);
		return _t[uRowMax][uColMax];
	}
public:
	TArray2d(bool bZero = false){if (bZero)Zero();}
	virtual ~TArray2d(){}
private:
	T _t[uRowMax][uColMax];
};

template<typename T>
class TArray2dNew{
public:
	UINT		GetLength()const{return _uLength;}
	T*			GetPtr(){return _p;}
	const T*	GetPtr()const{return _p;}
	bool		Zero(){memset(_p,0,_uLength);return true;}
	operator	const T*(void)const{return _p;}
	operator	T*(void){return _p;}
	T&			GetValue(uint uRow,uint uCol)const{
		assert(uRow <= _uRow && uCol <= _uCol);
		return _p[uRow * _uCol + uCol];
	}
	uint		GetRow()const{return _uRow;}
	int			GetCol()const{return _uCol;}
	bool		IsVaildIndex(uint uRow,uint uCol)const{
		return uRow < _uRow && uCol < _uCol ;
	}

	bool		ReSize(uint uRow,uint uCol,bool bZero = false){
		if (uRow<=0 || uCol<=0)return false;

		if (_p)delete[] _p;
		_uRow = uRow;_uCol = uCol; _uLength = uRow * uCol;
		_p = new T[_uLength];
		if (bZero)Zero();
		return true;
	}
public:
	TArray2dNew(){_p=nullptr;_uCol=0;_uLength=0;_uRow=0;}
	TArray2dNew(uint uRow,uint uCol,bool bZero = false){_uRow = uRow;_uCol = uCol; _uLength = uRow * uCol;_p = new T[_uLength];if (bZero)Zero();}
	virtual ~TArray2dNew(){ delete[] _p;}
private:
	T*		_p;
	uint	_uLength;
	uint	_uCol;
	uint	_uRow;
};

NS_TOOL_FRAME_END
