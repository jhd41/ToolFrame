#pragma once

#include "Macro.h"

NS_TOOL_FRAME_BEGIN

//////////////////////////////////////////////////////////////////////////
//分配在栈里的数组
template<typename T, size_t uLenMax>
class TArray{
public:
	size_t		GetLength()const{return uLenMax;}
	T*			GetPtr(){return _t;}
	const T*	GetPtr()const{return _t;}
	bool		Zero(){memset(_t,0,uLenMax);return true;}
	bool		SetZeroEnd() { memset(_t + uLenMax - 1, 0, sizeof(T)); return true; }
	operator	const T*(void)const{return _t;}
	operator	T*(void){return _t;}
public:
	TArray(bool bZero = false){if (bZero)Zero();}
	virtual ~TArray(){}
private:
	T _t[uLenMax];
};

//////////////////////////////////////////////////////////////////////////
//分配在堆中的数组
template<typename T>
class TArrayNew {
public:
	size_t		GetLength()const { return _uLength; }
	T*			GetPtr() { return _p; }
	const T*	GetPtr()const { return _p; }
	//只适合没有虚表
public:
	bool		Zero() { memset(_p, 0, _uLength); return true; }
	bool		SetZeroEnd() { memset(_p + _uLength - 1, 0, sizeof(T)); return true; }
public:
	operator	const T*(void)const { return _p; }
	operator T*(void) { return _p; }
public:
	TArrayNew(size_t uLength, bool bZero = false) { _uLength = uLength; _p = new T[uLength]; if (bZero)Zero(); }

	//只适合没有虚表
	TArrayNew(const void* pSrc, size_t uLength) { _uLength = uLength; _p = new T[uLength]; memcpy(_p, pSrc, uLength); }
	virtual ~TArrayNew() { delete[] _p; }
private:
	T*		_p;
	size_t	_uLength;
};

//////////////////////////////////////////////////////////////////////////
//引用现有内存的数组
template<typename T>
class TArrayRef {
public:
	size_t		GetLength()const { return _uLength; }
	T*			GetPtr() { return _p; }
	const T*	GetPtr()const { return _p; }
	//只适合没有虚表
public:
	bool		Zero() { memset(_p, 0, _uLength); return true; }
	bool		SetZeroEnd() { memset(_p + _uLength - 1, 0, sizeof(T)); return true; }
public:
	operator	const T*(void)const { return _p; }
	operator T*(void) { return _p; }
public:
	TArrayRef(const void* pSrc, size_t uLength) {_p = (T*)pSrc; _uLength = uLength;}
	virtual ~TArrayRef() {}
private:
	T*		_p;
	size_t	_uLength;
};

//////////////////////////////////////////////////////////////////////////
//定义基本类型
typedef TArrayNew<char>				CArrayNewByte;
typedef TArrayNew<short>			CArrayNewShort;
typedef TArrayNew<long>				CArrayNewLong;
typedef TArrayNew<float>			CArrayNewFloat;
typedef TArrayNew<double>			CArrayNewDouble;
typedef TArrayNew<std::string>		CArrayNewString;

typedef TArrayRef<char>				CArrayRefByte;
typedef TArrayRef<short>			CArrayRefShort;
typedef TArrayRef<long>				CArrayRefLong;
typedef TArrayRef<float>			CArrayRefFloat;
typedef TArrayRef<double>			CArrayRefDouble;
typedef TArrayRef<std::string>		CArrayRefString;

NS_TOOL_FRAME_END
