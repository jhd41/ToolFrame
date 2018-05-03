#pragma once

#include "Macro.h"
#include "IDMaker.h"

NS_TOOL_FRAME_BEGIN

//基于Vector的映射表 只能存放指针且不能存放空指针
//必须先调用Resize分配空间后才能使用
template<typename TValue>
class TVectorMap
{
	typedef std::vector<TValue>  VectorValue;
public:
	bool			Resize(size_t uSize);					//分配大小
	bool			SetIDRange(size_t uBegin,size_t uEnd);	//设置ID范围
	bool			Insert(size_t uKey,TValue tValue);		//插入
	size_t			Insert(TValue tValue);					//自动插入返回ID,ID不为0
	size_t			SmartInsert(size_t uKey, TValue tValue);//智能优先插入指定位置，若插入失败 则寻找新位置
	TValue			Erase(size_t uKey);						//擦除并返回
	TValue&			GetValue(size_t uKey);
	const TValue&	GetValue(size_t uKey)const;
	size_t			GetSize()const;
	size_t			GetSizeMax()const;
	bool			Empty()const;
	bool			IsHasValue(size_t uKey)const;
	bool			Clear();

	bool			IsFull()const;

	size_t			CalRealKey(size_t uKey)const;
public:
	TVectorMap(void);
	virtual ~TVectorMap(void);
private:
	VectorValue		_vValue;
	size_t			_uSize;
	CIDMakerSize	_xIDMaker;
};

template<typename TValue>
TVectorMap<TValue>::TVectorMap(void)
{
	_uSize = 0;
}

template<typename TValue>
TVectorMap<TValue>::~TVectorMap(void)
{
}

template<typename TValue>
bool TVectorMap<TValue>::SetIDRange(size_t uBegin, size_t uEnd)
{
	return _xIDMaker.SetIDRange(uBegin, uEnd);
}

template<typename TValue>
bool TVectorMap<TValue>::IsFull()const
{
	return _uSize == _vValue.size();
}

template<typename TValue>
bool TVectorMap<TValue>::Clear()
{
	typename VectorValue::iterator itr;
	foreach(itr,_vValue){
		*itr = TValue();
	}
	return true;
}

template<typename TValue>
bool TVectorMap<TValue>::Empty()const
{
	return !!_uSize;
}

template<typename TValue>
size_t TVectorMap<TValue>::GetSizeMax()const
{
	return _vValue.size();
}

template<typename TValue>
size_t TVectorMap<TValue>::GetSize()const
{
	return _uSize;
}

template<typename TValue>
TValue& TVectorMap<TValue>::GetValue( size_t uKey )
{
	return _vValue[CalRealKey(uKey)];
}

template<typename TValue>
const TValue& TVectorMap<TValue>::GetValue(size_t uKey) const
{
	return _vValue[CalRealKey(uKey)];
}

template<typename TValue>
bool TVectorMap<TValue>::IsHasValue(size_t uKey) const
{
	return _vValue[CalRealKey(uKey)] != TValue();
}

template<typename TValue>
size_t TVectorMap<TValue>::CalRealKey(size_t uKey) const
{
	return uKey % GetSizeMax();
}

template<typename TValue>
TValue TVectorMap<TValue>::Erase( size_t uKey )
{
	size_t uKeyReal = CalRealKey(uKey);

	TValue tValue = _vValue[uKeyReal];
	if(tValue){
		_vValue[uKeyReal] = TValue();
		-- _uSize;

		return tValue;
	}
	return TValue();
}

template<typename TValue>
size_t TVectorMap<TValue>::SmartInsert(size_t uKey, TValue tValue)
{
	//尝试指定ID
	if (INVALID_ID != uKey && Insert(uKey, tValue))
		return uKey;

	//如果没有插入成功尝试寻找插入
	return Insert(tValue);
}

template<typename TValue>
bool TVectorMap<TValue>::Insert( size_t uKey,TValue tValue )
{
	if (IsFull())return false;

	size_t uKeyReal = CalRealKey(uKey);

	if (tValue && !_vValue[uKeyReal])
	{
		_vValue[uKeyReal] = tValue;
		++_uSize;

		return true;
	}
	return false;
}

template<typename TValue>
bool TVectorMap<TValue>::Resize( size_t uSize )
{
	if (uSize <= 0)return false;
	_vValue.resize(uSize,TValue());
	return true;
}

template<typename TValue>
size_t TVectorMap<TValue>::Insert(TValue tValue)
{
	if (IsFull())return INVALID_ID;

	size_t uIndex = INVALID_ID;
	do
	{
		uIndex = _xIDMaker.MakeID();
	} while (!Insert(uIndex, tValue));
	return uIndex;
}

NS_TOOL_FRAME_END
