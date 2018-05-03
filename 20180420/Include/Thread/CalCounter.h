#pragma once

#include "Macro.h"
#include "MacroDefineBoost.h"

NS_TOOL_FRAME_BEGIN

//计数器(线程安全)
template<typename T>
class TOOLFRAME_DLL TCalCounter
{
public:
	T		GetCount()const;			//获取值
	T		ClearCounter();				//清除值
	T		AddCount(T nCount = 1);		//增加值
	T		ReduceCount(T nCount = 1);	//减少值
	bool	IsZero()const;				//是否为零
	bool	IsError()const;				//是否出错
	bool	ClearError();				//清除错误标记(返回之前是否是错误的)
	bool	MarkError();				//标记为错误
public:
	TCalCounter& operator++();
	TCalCounter& operator++(int);

	TCalCounter& operator+=(T uCount);
	TCalCounter& operator+=(const TCalCounter& xCounter);

	TCalCounter operator+(T uCount)const;

	TCalCounter& operator--();
	TCalCounter& operator--(int);

	TCalCounter& operator-=(T uCount);
	TCalCounter& operator-=(const TCalCounter& xCounter);

	TCalCounter operator-(T uCount)const;
	TCalCounter& operator=(const TCalCounter& xCounter);


	operator T()const;
public:
	TCalCounter();
	TCalCounter(T uCount, bool bErr = false);
	TCalCounter(const TCalCounter& xCounter);
	virtual ~TCalCounter();
private:
	T						_uCounter;
	volatile bool			_bError;
	mutable CMutexReadWrite _mutex;
};

template<typename T>
TCalCounter<T>::TCalCounter()
{
	_uCounter = 0;
	_bError = false;
}

template<typename T>
TCalCounter<T>::TCalCounter(T uCount, bool bErr /*= false*/)
{
	_uCounter = uCount;
	_bError = bErr;
}

template<typename T>
TCalCounter<T>::TCalCounter(const TCalCounter<T>& xCounter)
{
	*this = xCounter;
}

template<typename T>
TCalCounter<T>::~TCalCounter()
{
}

template<typename T>
T TCalCounter<T>::GetCount() const
{
	CLockRead lock(_mutex);
	return _uCounter;
}

template<typename T>
T TCalCounter<T>::ClearCounter()
{
	CLockWrite lock(_mutex);

	T n = _uCounter;
	_uCounter = 0;
	return n;
}

template<typename T>
T TCalCounter<T>::AddCount(T nCount /*= 1*/)
{
	if (0 == nCount)
		return _uCounter;

	CLockWrite lock(_mutex);

	_uCounter += nCount;
	return _uCounter;
}

template<typename T>
T TCalCounter<T>::ReduceCount(T nCount /*= 1*/)
{
	CLockWrite lock(_mutex);

	if (nCount > _uCounter)
	{
		_uCounter = 0;
		MarkError();
		return _uCounter;
	}
	_uCounter -= nCount;
	return _uCounter;
}

template<typename T>
bool TCalCounter<T>::IsError() const
{
	return _bError;
}

template<typename T>
bool TCalCounter<T>::ClearError()
{
	bool bErr = _bError;
	_bError = false;
	return bErr;
}

template<typename T>
bool TCalCounter<T>::MarkError()
{
	_bError = true;
	return true;
}

template<typename T>
bool TCalCounter<T>::IsZero() const
{
	CLockRead lock(_mutex);
	return !_uCounter;
}

template<typename T>
TCalCounter<T>& TCalCounter<T>::operator++()
{
	AddCount();
	return *this;
}

template<typename T>
TCalCounter<T>& TCalCounter<T>::operator++(int)
{
	AddCount();
	return *this;
}

template<typename T>
TCalCounter<T>& TCalCounter<T>::operator+=(T uCount)
{
	AddCount(uCount);
	return *this;
}

template<typename T>
TCalCounter<T>& TCalCounter<T>::operator+=(const TCalCounter<T>& xCounter)
{
	AddCount(xCounter.GetCount());
	return *this;
}

template<typename T>
TCalCounter<T> TCalCounter<T>::operator+(T uCount) const
{
	TCalCounter xCounter(_uCounter);
	xCounter.AddCount(uCount);
	return xCounter;
}

template<typename T>
TCalCounter<T>& TCalCounter<T>::operator--()
{
	ReduceCount();
	return *this;
}

template<typename T>
TCalCounter<T>& TCalCounter<T>::operator--(int)
{
	ReduceCount();
	return *this;
}

template<typename T>
TCalCounter<T>& TCalCounter<T>::operator-=(T uCount)
{
	ReduceCount(uCount);
	return *this;
}

template<typename T>
TCalCounter<T>& TCalCounter<T>::operator-=(const TCalCounter<T>& xCounter)
{
	ReduceCount(xCounter.GetCount());
	return *this;
}

template<typename T>
TCalCounter<T> TCalCounter<T>::operator-(T uCount) const
{
	TCalCounter xCounter(_uCounter);
	xCounter.ReduceCount(uCount);
	return xCounter;
}

template<typename T>
TCalCounter<T>::operator T() const
{
	return _uCounter;
}

template<typename T>
TCalCounter<T>& TCalCounter<T>::operator=(const TCalCounter<T>& xCounter)
{
	CLockWrite lock(_mutex);
	CLockRead lockOther(xCounter._mutex);
	_uCounter = xCounter._uCounter;
	_bError = xCounter._bError;
	return *this;
}

typedef TCalCounter<size_t> CCalCounter;

typedef TCalCounter<int>	CCalCounterInt;
typedef TCalCounter<uint>	CCalCounterUint;
typedef TCalCounter<size_t> CCalCounterSize;
NS_TOOL_FRAME_END
