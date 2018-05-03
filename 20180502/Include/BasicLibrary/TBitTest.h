#pragma once
#include "Macro.h"
#include "MacroDefineBoost.h"

//将多个布尔变量存入一个指定变量(线程安全)

template<typename T>
class TBitTest
{
public:
	bool		IsMarked(uint uPos)const;

	bool		Mark(uint uPos);		//打上标记
	bool		Clear(uint uPos);

	bool		TryMark(uint uPos);		//尝试打标记 返回是否成功
	bool		TryClear(uint uPos);	//尝试清除标记 返回是否成功

	bool		IsMarked()const;
	bool		Clear();

	bool		SetValue(const T& t);
	const T&	GetValue()const;
public:
	TBitTest(void);
	virtual ~TBitTest(void);
private:
	T _t;
	mutable CMutexReadWrite _mutex;
};

template<typename T>
bool TBitTest<T>::TryClear( uint uPos )
{
	T t = 1;
	t<<=uPos;

	{
		CLockRead lock(_mutex);
		if (!(_t & t))return false;
	}

	CLockWrite lock(_mutex);
	if (!(_t & t))return false;
	t = ~t;
	_t &= t;
	return true;
}

template<typename T>
bool TBitTest<T>::Clear( uint uPos )
{
	CLockWrite lock(_mutex);

	T t = 1;
	t<<=uPos;
	t = ~t;
	_t &= t;
	return true;
}

template<typename T>
bool TBitTest<T>::TryMark( uint uPos )
{
	T t = 1;
	t<<=uPos;

	{
		CLockRead lock(_mutex);
		if (_t & t)return false;
	}

	CLockWrite lock(_mutex);
	if (_t & t)return false;
	return !!(_t |= t);
}

template<typename T>
const T& TBitTest<T>::GetValue() const
{
	CLockRead lock(_mutex);
	return _t;
}

template<typename T>
bool TBitTest<T>::SetValue(const T& t)
{
	CLockWrite lock(_mutex);
	_t = t;
	return true;
}

template<typename T>
bool TBitTest<T>::Clear()
{
	CLockWrite lock(_mutex);
	_t = 0;
	return true;
}

template<typename T>
bool TBitTest<T>::IsMarked() const
{
	CLockRead lock(_mutex);
	return !!_t;
}

template<typename T>
bool TBitTest<T>::IsMarked( uint uPos ) const
{
	CLockRead lock(_mutex);
	T t = 1;
	t<<=uPos;
	return !!(_t & t);
}

template<typename T>
bool TBitTest<T>::Mark( uint uPos )
{
	CLockWrite lock(_mutex);
	T t = 1;
	t<<=uPos;
	_t |= t;
	return true;
}

template<typename T>
TBitTest<T>::TBitTest( void )
{
	Clear();
}

template<typename T>
TBitTest<T>::~TBitTest( void )
{

}
