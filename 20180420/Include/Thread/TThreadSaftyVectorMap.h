#pragma once

#include "Macro.h"
#include "TVectorMap.h"

NS_TOOL_FRAME_BEGIN

//����Vector��ӳ��� ֻ�ܴ��ָ���Ҳ��ܴ�ſ�ָ��
//�����ȵ���Resize����ռ�����ʹ��
template<typename TValue>
class TThreadSaftyVectorMap
{
public:
	bool			Resize(size_t uSize);					//�����С
	bool			SetIDRange(size_t uBegin, size_t uEnd);	//����ID��Χ
	bool			Insert(size_t uKey,TValue tValue);		//����
	size_t			Insert(TValue tValue);					//�Զ����뷵��ID,ID��Ϊ0
	size_t			SmartInsert(size_t uKey, TValue tValue);//�������Ȳ���ָ��λ�ã�������ʧ�� ��Ѱ����λ��
	TValue			Erase(size_t uKey);						//����������
	TValue			GetValue(size_t uKey);					//���̻߳�ȡֵ ���뿽��
	const TValue	GetValue(size_t uKey)const;
	size_t			GetSize()const;
	size_t			GetSizeMax()const;
	bool			Empty()const;
	bool			IsHasValue(size_t uKey)const;
	bool			Clear();

	bool			IsFull()const;

	size_t			CalRealKey(size_t uKey)const;

	//���ض�д������(ͬһ�߳�Ҳ��������,����)
	CMutexReadWrite& GetMutex()const { return _mutex; }

	//��ֵ
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
