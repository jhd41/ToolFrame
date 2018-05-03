#pragma once

#include "Macro.h"
#include "MacroDefineBoost.h"

//线程安全映射表

NS_TOOL_FRAME_BEGIN

template<typename T, typename K>
class TOOLFRAME_DLL TThreadSaftyMap
{
public:
	typedef std::map<T, K> StdMap;
public:
	bool Empty()const;
	void Clear();
	size_t Size()const;
	bool Insert(const T& t, const K& k);//插入(若已存在则插入失败)
	K	GetValueByKey(const T& t)const;//获取值(若找不到会崩溃 多线程安全起见需要拷贝返回值)
	
	template<typename TDefault>
	K	GetValueByKey(const T& t,const TDefault& tDefault)const;//获取值(若找不到会崩溃 多线程安全起见需要拷贝返回值)

	bool EraseByKey(const T& t);
	bool IsHasKey(const T& t)const;

	//返回不上锁的容器
	StdMap&			GetMap();
	const StdMap&	GetMap()const;
	bool			SetMap(const StdMap& vMap);

	//返回读写互斥锁(同一线程也可能死锁,慎用)
	CMutexReadWrite& GetMutex()const;

	//赋值
	TThreadSaftyMap& operator = (const TThreadSaftyMap& other);
public:
	TThreadSaftyMap(void);
	TThreadSaftyMap(const TThreadSaftyMap& other);
	virtual ~TThreadSaftyMap(void);
protected:
	mutable CMutexReadWrite	_mutex;
	StdMap					 _vMap;
};

template<typename T, typename K>
class TThreadSaftyMapValue
	:public TThreadSaftyMap<T, K>
{
	typedef TThreadSaftyMap<T, K> Supper;
public:
	//通过Key查找值 返回值的拷贝 若获取不到则创建 多线程安全起见需要拷贝返回值
	K	GetValueByKeyForce(const T& t,bool bTryRead = true);

	//通过Key查找值 返回值的引用 若获取不到则创建(注意多线程)
	K&	GetValueRefByKeyForce(const T& t, bool bTryRead = true);

	//多线程安全起见需要拷贝返回值
	K	GetPtrValueByKey(const T& t)const;

	//插入键 返回是否插入，如果之前已经存在 返回false
	bool InsertKey(const T& t);

public:
	TThreadSaftyMapValue(void);
	virtual ~TThreadSaftyMapValue(void);
};

//////////////////////////////////////////////////////////////////////////
template<typename T, typename K>
TThreadSaftyMap<T, K>::TThreadSaftyMap(void)
{

}

template<typename T, typename K>
TThreadSaftyMap<T, K>::TThreadSaftyMap(const TThreadSaftyMap& other)
{
	*this = other;
}

template<typename T, typename K>
TThreadSaftyMap<T, K>::~TThreadSaftyMap(void)
{

}

template<typename T, typename K>
bool TThreadSaftyMap<T, K>::Empty() const
{
	CLockRead lock(_mutex);
	return _vMap.empty();
}

template<typename T, typename K>
void TThreadSaftyMap<T, K>::Clear()
{
	CLockWrite lock(_mutex);
	return _vMap.clear();
}

template<typename T, typename K>
size_t TThreadSaftyMap<T, K>::Size() const
{
	CLockRead lock(_mutex);
	return _vMap.size();
}

template<typename T, typename K>
bool TThreadSaftyMap<T, K>::Insert(const T& t, const K& k)
{
	CLockWrite lock(_mutex);

	if (_vMap.find(t) != _vMap.end())return false;//为了安全起见 插入时再查找一次

	_vMap.insert(std::make_pair(t, k));//vMap[tKey]=kValue; 和这种写法有区别。此写法更快速
	return true;
}

template<typename T, typename K>
K TThreadSaftyMap<T, K>::GetValueByKey(const T& t) const
{
	CLockRead lock(_mutex);

	typename StdMap::const_iterator itr = _vMap.find(t);
	assert(itr != _vMap.end());
	return itr->second;
}

template<typename T, typename K>
bool TThreadSaftyMap<T, K>::EraseByKey(const T& t)
{
	CLockWrite lock(_mutex);

	size_t uSize = _vMap.size();
	_vMap.erase(t);
	return 1 == (uSize - _vMap.size());
}

template<typename T, typename K>
bool TThreadSaftyMap<T, K>::IsHasKey(const T& t) const
{
	CLockRead lock(_mutex);
	return _vMap.find(t) != _vMap.end();
}

template<typename T, typename K>
typename TThreadSaftyMap<T, K>::StdMap& TThreadSaftyMap<T, K>::GetMap()
{
	return _vMap;
}

template<typename T, typename K>
const typename TThreadSaftyMap<T, K>::StdMap& TThreadSaftyMap<T, K>::GetMap() const
{
	return _vMap;
}

template<typename T, typename K>
bool TThreadSaftyMap<T, K>::SetMap(const StdMap& vMap)
{
	_vMap = vMap; return true;
}

template<typename T, typename K>
CMutexReadWrite& TThreadSaftyMap<T, K>::GetMutex() const
{
	return _mutex;
}

template<typename T, typename K>
TThreadSaftyMap<T, K>& TThreadSaftyMap<T, K>::operator=(const TThreadSaftyMap<T, K>& other)
{
	CLockWrite	lockWrite(_mutex);
	CLockRead	lockRead(other._mutex);

	_vMap = other._vMap;
	return *this;
}

template<typename T, typename K>
template<typename TDefault>
K TThreadSaftyMap<T, K>::GetValueByKey(const T& t, const TDefault& tDefault) const
{
	CLockRead lock(_mutex);

	typename StdMap::const_iterator itr = _vMap.find(t);
	return itr != _vMap.end() ? itr->second : tDefault;
}

//////////////////////////////////////////////////////////////////////////
template<typename T, typename K>
TThreadSaftyMapValue<T, K>::TThreadSaftyMapValue(void)
{

}

template<typename T, typename K>
TThreadSaftyMapValue<T, K>::~TThreadSaftyMapValue(void)
{

}

template<typename T, typename K>
K TThreadSaftyMapValue<T, K>::GetValueByKeyForce(const T& t, bool bTryRead)
{
	//先搜索一遍，搜索不到再添加
	if (bTryRead)
	{
		CLockRead lock(Supper::_mutex);

		typename Supper::StdMap::iterator itr = Supper::_vMap.find(t);
		if (itr != Supper::_vMap.end())
			return itr->second;
	}
	//多线程需要二次搜索
	{
		CLockWrite lock(Supper::_mutex);

		typename Supper::StdMap::iterator itr = Supper::_vMap.find(t);
		if (itr == Supper::_vMap.end())
		{
			Supper::_vMap[t] = K();
			return Supper::_vMap[t];
		}
		return itr->second;
	}
}


template<typename T, typename K>
K& TThreadSaftyMapValue<T, K>::GetValueRefByKeyForce(const T& t, bool bTryRead)
{
	//先搜索一遍，搜索不到再添加
	if (bTryRead)
	{
		CLockRead lock(Supper::_mutex);

		typename Supper::StdMap::iterator itr = Supper::_vMap.find(t);
		if (itr != Supper::_vMap.end())
			return itr->second;
	}
	//多线程需要二次搜索
	{
		CLockWrite lock(Supper::_mutex);

		typename Supper::StdMap::iterator itr = Supper::_vMap.find(t);
		if (itr == Supper::_vMap.end())
		{
			Supper::_vMap[t] = K();
			return Supper::_vMap[t];
		}
		return itr->second;
	}
}


template<typename T, typename K>
K TThreadSaftyMapValue<T, K>::GetPtrValueByKey(const T& t) const
{
	CLockRead lock(Supper::_mutex);

	typename Supper::StdMap::const_iterator itr = Supper::_vMap.find(t);
	return itr == Supper::_vMap.end() ? K() : itr->second;
}


template<typename T, typename K>
bool TThreadSaftyMapValue<T, K>::InsertKey(const T& t)
{
	CLockWrite lock(Supper::_mutex);
	typename Supper::StdMap::iterator itr = Supper::_vMap.find(t);
	if (itr != Supper::_vMap.end())return false;

	Supper::_vMap.insert(std::make_pair(t, K()));
	return true;
}

NS_TOOL_FRAME_END