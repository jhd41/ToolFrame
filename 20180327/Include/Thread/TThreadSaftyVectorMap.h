#pragma once

#include "Macro.h"
#include "TVectorMap.h"

NS_TOOL_FRAME_BEGIN

//基于Vector的映射表 只能存放指针且不能存放空指针
//必须先调用Resize分配空间后才能使用
template<typename TValue>
class TThreadSaftyVectorMap
{
public:
	bool			Resize(size_t uSize);					//分配大小
	bool			SetIDRange(size_t uBegin, size_t uEnd);	//设置ID范围
	bool			Insert(size_t uKey,TValue tValue);		//插入
	size_t			Insert(TValue tValue);					//自动插入返回ID,ID不为0
	size_t			SmartInsert(size_t uKey, TValue tValue);//智能优先插入指定位置，若插入失败 则寻找新位置
	TValue			Erase(size_t uKey);						//擦除并返回
	TValue			GetValue(size_t uKey);					//多线程获取值 必须拷贝
	const TValue	GetValue(size_t uKey)const;
	size_t			GetSize()const;
	size_t			GetSizeMax()const;
	bool			Empty()const;
	bool			IsHasValue(size_t uKey)const;
	bool			Clear();

	bool			IsFull()const;

	size_t			CalRealKey(size_t uKey)const;

	//返回读写互斥锁(同一线程也可能死锁,慎用)
	CMutexReadWrite& GetMutex()const { return _mutex; }

	//赋值
	TThreadSaftyVectorMap& operator = (const TThreadSaftyVectorMap& other);
public:
	TThreadSaftyVectorMap(void);
	TThreadSaftyVectorMap(const TThreadSaftyVectorMap& other);
	virtual ~TThreadSaftyVectorMap(void);
protected:
	TVectorMap<TValue> _vVectorMap;
	mutable CMutexReadWrite	_mutex;
};

template<typename TValue>
TThreadSaftyVectorMap<TValue>::TThreadSaftyVectorMap(void)
{
}

template<typename TValue>
TThreadSaftyVectorMap<TValue>::TThreadSaftyVectorMap(const TThreadSaftyVectorMap& other)
{
	*this = other;
}

template<typename TValue>
TThreadSaftyVectorMap<TValue>::~TThreadSaftyVectorMap(void)
{
}

template<typename TValue>
bool TThreadSaftyVectorMap<TValue>::SetIDRange(size_t uBegin, size_t uEnd)
{
	CLockWrite	lockWrite(_mutex);
	return _vVectorMap.SetIDRange(uBegin, uEnd);
}

template<typename TValue>
bool TThreadSaftyVectorMap<TValue>::IsFull()const
{
	CLockRead lock(_mutex);
	return _vVectorMap.IsFull();
}

template<typename TValue>
bool TThreadSaftyVectorMap<TValue>::Clear()
{
	CLockWrite	lockWrite(_mutex);
	return _vVectorMap.Clear();
}

template<typename TValue>
bool TThreadSaftyVectorMap<TValue>::Empty()const
{
	CLockRead lock(_mutex);
	return _vVectorMap.Empty();
}

template<typename TValue>
size_t TThreadSaftyVectorMap<TValue>::GetSizeMax()const
{
	CLockRead lock(_mutex);
	return _vVectorMap.GetSizeMax();
}

template<typename TValue>
size_t TThreadSaftyVectorMap<TValue>::GetSize()const
{
	CLockRead lock(_mutex);
	return _vVectorMap.GetSize();
}

template<typename TValue>
TValue TThreadSaftyVectorMap<TValue>::GetValue( size_t uKey )
{
	CLockRead lock(_mutex);
	return _vVectorMap.GetValue(uKey);
}

template<typename TValue>
const TValue TThreadSaftyVectorMap<TValue>::GetValue(size_t uKey) const
{
	CLockRead lock(_mutex);
	return _vVectorMap.GetValue(uKey);
}

template<typename TValue>
bool TThreadSaftyVectorMap<TValue>::IsHasValue(size_t uKey) const
{
	CLockRead lock(_mutex);
	return _vVectorMap.IsHasValue(uKey);
}

template<typename TValue>
size_t TThreadSaftyVectorMap<TValue>::CalRealKey(size_t uKey) const
{
	CLockRead lock(_mutex);
	return _vVectorMap.CalRealKey(uKey);
}

template<typename TValue>
TValue TThreadSaftyVectorMap<TValue>::Erase( size_t uKey )
{
	CLockWrite	lockWrite(_mutex);
	return _vVectorMap.Erase(uKey);
}

template<typename TValue>
size_t TThreadSaftyVectorMap<TValue>::SmartInsert(size_t uKey, TValue tValue)
{
	CLockWrite	lockWrite(_mutex);
	return _vVectorMap.SmartInsert(uKey, tValue);
}

template<typename TValue>
bool TThreadSaftyVectorMap<TValue>::Insert( size_t uKey,TValue tValue )
{
	CLockWrite	lockWrite(_mutex);
	return _vVectorMap.Insert(uKey, tValue);
}

template<typename TValue>
size_t TThreadSaftyVectorMap<TValue>::Insert(TValue tValue)
{
	CLockWrite	lockWrite(_mutex);
	return _vVectorMap.Insert(tValue);
}

template<typename TValue>
bool TThreadSaftyVectorMap<TValue>::Resize(size_t uSize)
{
	CLockWrite	lockWrite(_mutex);
	return _vVectorMap.Resize(uSize);
}

template<typename TValue>
TThreadSaftyVectorMap<TValue>& TThreadSaftyVectorMap<TValue>::operator=(const TThreadSaftyVectorMap<TValue>& other)
{
	CLockWrite	lockWrite(_mutex);
	CLockRead	lockRead(other._mutex);

	_vVectorMap = other._vVectorMap;
	return *this;
}

NS_TOOL_FRAME_END
