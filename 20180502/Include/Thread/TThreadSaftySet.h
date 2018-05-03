#pragma once
#include "Macro.h"
#include "MacroDefineBoost.h"

//线程安全Set容器

NS_TOOL_FRAME_BEGIN

template<typename T>
class TOOLFRAME_DLL TThreadSaftySet
{
public:
	typedef std::set<T> StdSet;
public:
	bool Empty()const;
	void Clear();
	size_t Size()const;
	
	template<typename Arg>
	bool Insert(const Arg& t);

	template<typename Arg>
	bool EraseByKey(const Arg& t);

	template<typename Arg>
	bool IsHasKey(const Arg& t);
	
	//没有上锁 外部使用务必注意安全
	StdSet&			GetSet();
	const StdSet&	GetSet()const;

	//返回读写互斥锁(同一线程也可能死锁,慎用)
	CMutexReadWrite& GetMutex()const;

	//赋值
	TThreadSaftySet& operator = (const TThreadSaftySet& other);
public:
	TThreadSaftySet(void);
	TThreadSaftySet(const TThreadSaftySet& other);
	virtual ~TThreadSaftySet(void);
protected:
	mutable CMutexReadWrite	_mutex;
	StdSet					_vSet;
};

//////////////////////////////////////////////////////////////////////////
template<typename T>
TThreadSaftySet<T>::TThreadSaftySet(void)
{

}

template<typename T>
TThreadSaftySet<T>::TThreadSaftySet(const TThreadSaftySet& other)
{
	*this = other;
}

template<typename T>
TThreadSaftySet<T>::~TThreadSaftySet(void)
{

}

template<typename T>
bool TThreadSaftySet<T>::Empty() const
{
	CLockRead lock(_mutex);
	return _vSet.empty();
}

template<typename T>
void TThreadSaftySet<T>::Clear()
{
	CLockWrite lock(_mutex);
	return _vSet.clear();
}

template<typename T>
size_t TThreadSaftySet<T>::Size() const
{
	CLockRead lock(_mutex);
	return _vSet.size();
}

template<typename T>
typename TThreadSaftySet<T>::StdSet& TThreadSaftySet<T>::GetSet()
{
	return _vSet;
}

template<typename T>
const typename TThreadSaftySet<T>::StdSet& TThreadSaftySet<T>::GetSet() const
{
	return _vSet;
}

template<typename T>
CMutexReadWrite& TThreadSaftySet<T>::GetMutex() const
{
	return _mutex;
}

template<typename T>
TThreadSaftySet<T>& TThreadSaftySet<T>::operator=(const TThreadSaftySet<T>& other)
{
	CLockWrite	lockWrite(_mutex);
	CLockRead	lockRead(other._mutex);

	_vSet = other._vSet;
	return *this;
}

template<typename T>
template<typename Arg>
bool TThreadSaftySet<T>::EraseByKey(const Arg& t)
{
	CLockWrite lock(_mutex);

	size_t uSize = _vSet.size();
	_vSet.erase(t);
	return 1 == (uSize - _vSet.size());
}

template<typename T>
template<typename Arg>
bool TThreadSaftySet<T>::IsHasKey(const Arg& t)
{
	CLockRead lock(_mutex);
	return _vSet.find(t) != _vSet.end();
}

template<typename T>
template<typename Arg>
bool TThreadSaftySet<T>::Insert(const Arg& t)
{
	CLockWrite lock(_mutex);
	if (_vSet.find(t) != _vSet.end())return false;

	_vSet.insert(t);
	return true;
}

NS_TOOL_FRAME_END